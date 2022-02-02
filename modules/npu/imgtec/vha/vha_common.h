/*!
 *****************************************************************************
 *
 * @File       vha_common.h
 * ---------------------------------------------------------------------------
 *
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


#ifndef VHA_COMMON_H
#define VHA_COMMON_H

#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/list.h>
#include <linux/dcache.h>
#include <linux/mutex.h>
#include <linux/wait.h>
#include <linux/idr.h>
#include <linux/workqueue.h>
#include <linux/irq.h>
#include <linux/spinlock.h>

#include <uapi/vha.h>
#include <img_mem_man.h>
#include "vha_plat.h"

#ifdef CONFIG_VHA_DUMMY
#  ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
#    define CMD_EXEC_ON_HW(cmd) ((cmd)->user_cmd.cmd_type == VHA_CMD_CNN_SUBMIT)
#  else
#    define CMD_EXEC_ON_HW(cmd) 0
#  endif
#  define VHA_IS_DUMMY(vha) 1
#else
#  define CMD_EXEC_ON_HW(cmd) ((cmd)->user_cmd.cmd_type == VHA_CMD_CNN_SUBMIT)
#  define VHA_IS_DUMMY(vha) 0
#endif

#define VHA_CNN_CMD 0
#define VHA_CMD_MAX 1

#define VHA_INVALID_ID -1

/* Max hw contexts supported by MMU */
#if defined(HW_AX2)
#define VHA_MMU_MAX_HW_CTXS 32
#define VHA_MMU_AUX_HW_CTX_SHIFT 1
#elif defined(HW_AX3)
/* 8 per OS, 4 model requestor, 4 Input/Output requestors */
#define VHA_MMU_MAX_HW_CTXS 8
#define VHA_MMU_AUX_HW_CTX_SHIFT 4
#else
#error "Wrong MMU configuration"
#endif

/* Enable MMU multiple hw contexts support */
#define VHA_MMU_MULTI_HW_CTX_SUPPORT

#ifdef VHA_MMU_MULTI_HW_CTX_SUPPORT
#if defined(HW_AX2)
#  define VHA_MMU_GET_CTXID(session) \
		(((session->mmu_ctxs[0].id-1) + session->vha->mmu_ctx_default) \
		% VHA_MMU_MAX_HW_CTXS);
#elif defined(HW_AX3)
#  define VHA_MMU_GET_CTXID(session) \
		((_OSID_ * VHA_MMU_MAX_HW_CTXS) + \
		(((session->mmu_ctxs[0].id-1) + session->vha->mmu_ctx_default) \
		% (VHA_MMU_MAX_HW_CTXS / 2)));
#endif
#else
#  define VHA_MMU_GET_CTXID(session) \
	(session->vha->mmu_ctx_default % VHA_MMU_MAX_HW_CTXS)
#endif

/* AX2 uses only single MMU sw/hw context,
	AX3 may use dual sw contexts (due to dual hw contexts), first for model,
	second for IO requestors,
	when using single sw context, both hw contexts are programmed
	with the same PC address -> so called "mirrored pages tables" mode
	Note: MMU mirrored context support/mirrored pages tables
	mode is enabled by default */

/* Define model requestor context index */
#define VHA_MMU_REQ_MODEL_CTXID 0

/* Define number of mmu sw contexts & requestors used within session */
#if !defined(VHA_MMU_MIRRORED_CTX_SUPPORT) && defined(HW_AX3)
#define VHA_MMU_MAX_SW_CTXS 2
#define VHA_MMU_REQ_IO_CTXID 1
#else /* VHA_MMU_MIRRORED_SW_SUPPORT || HW_AX2 */
#define VHA_MMU_MAX_SW_CTXS 1
#define VHA_MMU_REQ_IO_CTXID 0
#endif

/* Max number of alternative addresses supported */
#if defined(HW_AX2)
#define VHA_MAX_ALT_ADDRS 8
#elif defined(HW_AX3)
#define VHA_MAX_ALT_ADDRS 16
#endif

/* hw command */
struct vha_hwcmd {
	struct vha_cmd *cmd;
	struct vha_dev *dev;
};

struct vha_stats {
	/* Total time the core has powered on */
	uint64_t uptime_ms;
	/* Latest processing time of the core (CNN) */
	uint64_t last_proc_us;
	/* Total number of hw kicks for which a failure has been detected */
	unsigned total_failures;
	/* Total cnn kicks */
	unsigned cnn_kicks;
	/* Total cnn kicks that were queued */
	unsigned cnn_queued_kicks;
	/* Total cnn kicks that were completed */
	unsigned cnn_kicks_completed;
	/* CNN total processing time */
	uint64_t cnn_total_proc_us;
	/* CNN last processing time */
	uint64_t cnn_last_proc_us;
	/* CNN average processing time */
	uint64_t cnn_avg_proc_us;
	/* CNN last estimated processing time (based on hw cycles & freq) */
	uint64_t cnn_last_est_proc_us;
	/* CNN average estimated processing time */
	uint64_t cnn_avg_est_proc_us;
	/* CNN total hw cycles */
	uint64_t cnn_total_cycles;
	/* CNN last processing time in hw cycles */
	uint64_t cnn_last_cycles;
	/* CNN utilization */
	unsigned cnn_utilization;
	/* Total memory used by the last session */
	unsigned mem_usage_last;
	/* Temporary vars */
	/* Hw power on timestamp */
	struct timespec hw_start;
	/* Hw processing start timestamp  */
	struct timespec hw_proc_start;
	/* Hw processing end timestamp */
	struct timespec hw_proc_end;
	/* Previous Hw processing end timestamp */
	struct timespec hw_proc_end_prev;
};

/* state of the VHA device: power up or down */
enum vha_state {
	VHA_STATE_OFF,
	VHA_STATE_ON
};


enum vha_ll_mode {
	VHA_LL_DISABLED = 0,
	VHA_LL_SW_KICK,
	VHA_LL_SELF_KICK
};

/* represents a single VHA core, containing a number of CNN devices */
struct vha_dev {
	unsigned int      id;
	struct mutex      lock;
	struct device    *dev;
	struct list_head  list;            /* entry in <struct vha_drv:devices> */
	struct list_head  sessions;        /* list of um sessions: vha_session */
	struct list_head  sched_sessions;  /* scheduling list of um sessions*/
	struct vha_core_props  core_props; /* HW properties */
	uint32_t          mmu_mode;        /* 0:no-mmu else 40 */
	uint8_t           mmu_ctx_default; /* 0:VHA_MMU_MAX_HW_CTXS */
	uint32_t          mmu_page_size;
	uint8_t           cache_sync;
	enum   vha_state  state;           /* the core is up or down */
	struct delayed_work apm_dwork;     /* APM delayed work */
	spinlock_t        irq_lock;
	uint64_t          irq_status;
	uint8_t           irq_count;
	uint8_t           stream_count;
	int               int_heap_id;     /* heap id for internal
			allocations such as crc/debug data, MMU page tables */

	struct vha_hwcmd  pendcmd[VHA_CMD_MAX];   /* pending command */
	struct vha_hwcmd  queuedcmd[VHA_CMD_MAX]; /* queued command */

	int               fp_bufid;	/* fault page buffer id */
	/* active mmu context (id of ctx) */
	int               active_mmu_ctx;
	/* ref counters for mmu hw contexts */
	int               mmu_ctxs[VHA_MMU_MAX_HW_CTXS*VHA_MMU_AUX_HW_CTX_SHIFT];
	/* Indicates if hw is ready to process commands */
	bool              is_ready;

	void __iomem     *reg_base;
	uint64_t          reg_size;
	void             *plat_data;

	struct miscdevice miscdev;	/* UM interface */
	void             *dbgfs_ctx;
	struct work_struct worker;
	/* Indicates if driver should perform calibration during load phase */
	bool              do_calibration;
	uint32_t          calibration_cycles;
	/* Core clock frequency measured during driver load phase
	 * or declared in the platform file */
	int               freq_khz;
	struct vha_stats  stats;
#if defined(HW_AX2)
	uint64_t          wdt_mode;
#endif

	/* Indicates fault injection mode */
	bool              fault_inject;

	enum vha_ll_mode  low_latency; /* Low latency mode */
	int               hw_bypass;   /* Hardware bypass counter */
#ifdef VHA_SCF
	/* Flag to forcefully disable parity checking */
	bool              parity_disable;
#endif
#ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
	/* Hw processing time simulation delayed work */
	struct delayed_work dummy_dwork;
#endif
};

/* contains a user command message */
struct vha_cmd {
	struct list_head    list;           /* entry into list vha_session.cmds     */
	struct vha_session *session;        /* session this command belongs to      */
	struct vha_rsp     *rsp;            /* command response                     */
	bool                in_hw;          /* currently being processed by hw      */
	bool                queued;         /* currently waiting to processed by hw */
	bool                inbufs_ready;   /* all input buffers are ready          */
	uint32_t            stream_size;    /* actual size of command stream        */
	size_t              size;           /* actual size of user_cmd, in bytes    */
	struct timespec     hw_proc_start;  /* Hw processing start timestamp        */
#ifdef CONFIG_VHA_DUMMY_SIMULATE_HW_PROCESSING_TIME
	uint32_t            dummy_exec_time;/* Estimated exec time for dummy driver */
	bool                dummy_kicked;   /* Dummy execution kicked               */
#endif
	struct vha_user_cmd user_cmd;
};
/* contains a user response message */
struct vha_rsp {
	struct list_head    list;    /* entry into list vha_session.rsps */
	struct vha_session *session;
	size_t              size;
	struct vha_user_rsp user_rsp;
};

/* macros to simplify iteration through input and output buffers in a command */
#define vha_cmd_inbuf(cmd, idx) \
	((cmd)->user_cmd.data[idx])
#define vha_cmd_outbuf(cmd, idx) \
	((cmd)->user_cmd.data[(cmd)->user_cmd.num_inbufs + (idx)])

struct cnn_dbg {
	struct vha_buffer *cnn_crc_buf;
	struct vha_buffer *cnn_dbg_buf;
	int                cnn_dbg_flush; /* mode for flushing debug bufs */
};

struct mmu_context {
	struct mmu_ctx    *ctx;
	/* mmu context id (associated with session number) */
	int                id;
	/* mmu hardware context number for this session */
	uint8_t            hw_id;    /* 0 - VHA_MMU_MAX_HW_CTXS-1 */
	uint32_t           pc_baddr; /* page catalogue base address */
	int                pc_bufid; /* page catalogue buffer id */
};

/* connection between a userspace file handle and a particular device */
struct vha_session {
	struct vha_dev    *vha;        /* associated device pointer */
	struct list_head   list;       /* entry in <struct vha_dev:sessions> */
	struct list_head   sched_list; /* entry in <struct vha_dev:sched_sessions> */
	struct list_head   bufs;       /* list of the session's buffers */
	struct list_head   cmds;       /* list of commands to be sent to hw */
					/* type: struct vha_cmd */
	struct list_head   rsps;       /* list of responses to be sent */
					/* to user process: struct vha_rsp */
	struct mem_ctx    *mem_ctx;

	bool               oom;        /* out of memory */

	/* Mmu hw contexts */
	struct mmu_context mmu_ctxs[VHA_MMU_MAX_SW_CTXS];

	struct idr         onchip_maps; /* id alloc for on-chip ram mappings */
	wait_queue_head_t  wq;          /* for waking up on completion of job */
	struct mmu_vaa    *vaa_ctx;     /* virtual address allocator used
				for device buffers allocated in the kernel */
	struct dentry     *dbgfs;       /* file in debugfs */
	struct cnn_dbg     cnn_dbg;

	/* Unisoc add for pm_runtime management */
	struct mutex pm_lock;
	u32 pm_count;
};

/* pdump cache info structure used for LDB commands */
struct vha_pcache {
	bool     valid;
	uint32_t offset;
	uint32_t size;
};

/* Type of the buffer saying what MMU requestors group it belongs to */
enum vha_req_type {
	VHA_REQ_MODEL = 0,
	VHA_REQ_IO
};

#ifdef KERNEL_DMA_FENCE_SUPPORT
/* Buffer synchronisation data. */
struct vha_buf_sync_info {
	int                 in_sync_fd;   /* input sync file descriptor */
	struct file        *in_sync_file; /* input sync file */
	struct dma_fence   *in_fence;     /* input fence */
	struct dma_fence_cb in_sync_cb;   /* input fence callback */
};
#endif

/*
 * A single buffer, which may be used by a command as either an input or
 * an output buffer.
 * Buffers have state: they are either
 *    filled (ready to be read)
 *    or empty (waiting to be written to)
 */
struct vha_buffer {
	struct list_head    list;        /* entry in vha_session.bufs */
	struct list_head    onchip_maps; /* list of vha_onchip_map's*/
	size_t              size;        /* size of buffer */
	void               *dbgfs_priv;  /* debugfs private data */
	uint32_t            id;          /* unique id for the buffer */
	enum vha_buf_status status;      /* is buffer ready to be read */
	enum img_mem_attr   attr;        /* memory attributes */
	void               *kptr;        /* kernel mode pointer */
	uint64_t            devvirt;     /* device virtual address */
	char                name[9];     /* short name for buffer */
	struct vha_pcache   pcache;      /* pdump LDB cache */
	struct vha_session *session;     /* session this buffer belongs to */

	enum vha_req_type   req_type;    /* requestor type */

	bool                inval;       /* needs invalidation? */
	bool                flush;       /* needs flushing? */

#ifdef KERNEL_DMA_FENCE_SUPPORT
	struct vha_buf_sync_info sync_info;
#endif
};

struct vha_onchip_map {
	struct list_head    list;    /* entry in vha_buffer.onchip_maps */
	uint32_t            mapid;   /* unique id for the mapping */
	uint32_t            bufid;   /* bufid of the releated buffer */
	uint64_t            devvirt; /* device virtual address */
};

/* Status of command execution attempt. */
enum do_cmd_status {
	CMD_OK = 0,      /* command scheduled */
	CMD_IN_HW,       /* command already in hardware */
	CMD_WAIT_INBUFS, /* command waiting for input buffers */
	CMD_HW_BUSY,     /* hardware is busy with other command */
	CMD_NOTIFIED     /* command is notified to user space */
};

int vha_deinit(void);
uint64_t vha_buf_addr(struct vha_session *session, struct vha_buffer *buf);
int vha_map_buffer(struct vha_session *session,
		uint32_t buf_id, uint64_t virt_addr, uint32_t map_flags);
int vha_unmap_buffer(struct vha_session *session, uint32_t buf_id);
int vha_map_to_onchip(struct vha_session *session,
		uint32_t buf_id, uint64_t virt_addr, uint32_t page_size,
		unsigned int num_pages, uint32_t page_idxs[], uint32_t *mapid);

irqreturn_t vha_handle_irq(struct device *dev);
irqreturn_t vha_handle_thread_irq(struct device *dev);

int vha_suspend_dev(struct device *dev);
int vha_resume_dev(struct device *dev);

void vha_rm_dev(struct device *dev);
int vha_add_dev(struct device *dev,
		const struct heap_config heap_configs[], const int heaps,
		void *plat_data, struct vha_sys_data *sys_data,
		void __iomem *reg_base, uint32_t reg_size);
void vha_dev_calibrate(struct device *dev, uint32_t cycles);
irqreturn_t vha_handle_irq(struct device *dev);
irqreturn_t vha_handle_thread_irq(struct device *dev);

int vha_add_cmd(struct vha_session *session, struct vha_cmd *cmd);
int vha_rm_cmds(struct vha_session *session, uint32_t cmd_id,
		uint32_t cmd_id_mask);
int vha_add_buf(struct vha_session *session,
		uint32_t buf_id, size_t size, const char *name, enum img_mem_attr attr);
int vha_rm_buf(struct vha_session *session, uint32_t buf_id);
int vha_set_buf_status(struct vha_session *session,
		uint32_t buf_id, enum vha_buf_status stat, int in_sync_fd);
#ifdef KERNEL_DMA_FENCE_SUPPORT
int vha_create_output_sync(struct vha_session *session, uint32_t buf_id_count,
		uint32_t *buf_ids);
int vha_merge_input_syncs(struct vha_session *session, uint32_t in_sync_fd_count,
		int *in_sync_fds);
int vha_release_syncs(struct vha_session *session, uint32_t buf_id_count,
		uint32_t *buf_ids);
#endif
bool vha_buf_needs_inval(struct vha_session *session, uint32_t buf_id);
bool vha_buf_needs_flush(struct vha_session *session, uint32_t buf_id);
struct vha_buffer *vha_find_bufid(const struct vha_session *session,
		uint32_t buf_id);
struct vha_buffer *vha_find_bufvaddr(const struct vha_session *session,
		uint64_t virt_addr);
void vha_chk_cmd_queues(struct vha_dev *vha, bool threaded);
int vha_add_session(struct vha_session *session);
void vha_rm_session(struct vha_session *session);
void vha_early_init(void);
bool vha_ext_cache_sync(struct vha_dev *vha);

static inline void *vha_get_plat_data(struct device *dev)
{
	struct vha_dev *vha = dev_get_drvdata(dev);

	if (vha)
		return vha->plat_data;
	return NULL;
}
int vha_api_add_dev(struct device *dev, struct vha_dev *vha, unsigned int id);
int vha_api_rm_dev(struct device *dev, struct vha_dev *vha);

void vha_mmu_setup(struct vha_session *session);

enum do_cmd_status vha_do_cnn_cmd(struct vha_cmd *cmd);
void vha_cmd_notify(struct vha_cmd *cmd);

void vha_dev_hwwdt_setup(struct vha_dev *vha, uint64_t cycles, uint64_t mode);
int vha_dev_hwwdt_calculate(struct vha_dev *vha, struct vha_cmd *cmd,
		uint64_t *cycles, uint64_t *mode);
void vha_dev_prepare(struct vha_dev *dev);
void vha_dev_setup(struct vha_dev *dev);
void vha_dev_wait(struct vha_dev *dev);
uint32_t vha_dev_kick_prepare(struct vha_dev *vha,
		struct vha_cmd *cmd, int ctx_id);
void vha_dev_mh_setup(struct vha_dev *vha, int ctx_id);

void vha_cnn_gen_wdt(struct vha_dev *vha);
void vha_cnn_update_stats(struct vha_dev *vha);
void vha_cnn_dump_status(struct vha_dev *vha);
void vha_cnn_cmd_completed(struct vha_cmd *cmd, int status);

void vha_dbg_init(struct vha_dev *vha);
void vha_dbg_deinit(struct vha_dev *vha);
struct dentry* vha_dbg_get_sysfs(struct vha_dev *vha);
int vha_dbg_enable_hwbufs(struct vha_session *session);
void vha_dbg_prepare_hwbufs(struct vha_session *session);
void vha_dbg_flush_hwbufs(struct vha_session *session, char checkpoint);
void vha_dbg_disable_hwbufs(struct vha_session *session);
int vha_dbg_alloc_hwbuf(struct vha_session *session, size_t size,
		struct vha_buffer **buffer, const char *name, bool map);
void vha_dbg_hwbuf_cleanup(struct vha_session *session,
		struct vha_buffer *buf);

int vha_pdump_init(struct vha_dev *vha);
void vha_pdump_deinit(void);
void vha_pdump_ldb_buf(struct vha_session *session, uint32_t pdump_num,
		struct vha_buffer *buffer, uint32_t offset, uint32_t len, bool cache);
void vha_pdump_sab_buf(struct vha_session *session, uint32_t pdump_num,
		struct vha_buffer *buffer, uint32_t offset, uint32_t len);

/*
 * register event observers, notified when significant events occur
 * Only a single observer per event!
 */
struct vha_observers {
	void (*enqueued)(uint32_t devid, uint32_t cmdid);
	void (*submitted)(uint32_t devid, uint32_t cmdid);
	void (*completed)(uint32_t devid, uint32_t cmdid, int status,
			uint64_t cycles, uint64_t mem_usage);
	void (*error)(uint32_t devid, uint32_t cmdid, uint64_t status);
};
extern struct vha_observers vha_observers;
/*
 * register a listener for ENQUEUE events,
 * when requests have been enqueued for submission
*/
extern void vha_observe_event_enqueue(void (*func)(uint32_t devid, uint32_t cmdid));
/*
 * register a listener for SUBMIT events,
 * when requests have been submitted to the HW
 */
extern void vha_observe_event_submit(void (*func)(uint32_t devid, uint32_t cmdid));
/*
 * register a listener for HW COMPLETE events,
 * when hardware has completed a submission
 */
extern void vha_observe_event_complete(void (*func)(uint32_t devid,
							uint32_t cmdid,
							int status,
							uint64_t cycles,
							uint64_t mem_usage));
/*
 * register a listener for ERROR events,
 * when the HW error occurs
 */
extern void vha_observe_event_error(void (*func)(uint32_t devid, uint32_t cmdid, uint64_t status));

#endif /* VHA_COMMON_H */
