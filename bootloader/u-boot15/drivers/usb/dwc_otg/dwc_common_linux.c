/* OS-Level Implementations */

/* This is the Linux kernel implementation of the DWC platform library. */
#include <common.h>
#include <malloc.h>

/*
#include <linux/device.h>
#include <linux/dma-mapping.h>
#include <linux/interrupt.h>
*/
#include <linux/list.h>
#include <linux/string.h>
//#include <linux/timer.h>
#include <usb.h>
//#include <linux/usb/gadget.h>
#include <asm/io.h>

#include "dwc_os.h"
#include "dwc_list.h"
/* MISC */

void *DWC_MEMSET(void *dest, uint8_t byte, uint32_t size)
{
	return memset(dest, byte, size);
}


void *DWC_MEMCPY(void *dest, void const *src, uint32_t size)
{
	return memcpy(dest, src, size);
}


void *DWC_MEMMOVE(void *dest, void *src, uint32_t size)
{
	return memmove(dest, src, size);
}


int DWC_MEMCMP(void *m1, void *m2, uint32_t size)
{
	return memcmp(m1, m2, size);
}


int DWC_STRNCMP(void *s1, void *s2, uint32_t size)
{
	return strncmp(s1, s2, size);
}


int DWC_STRCMP(void *s1, void *s2)
{
	return strcmp(s1, s2);
}


int DWC_STRLEN(char const *str)
{
	return strlen(str);
}


char *DWC_STRCPY(char *to, const char *from)
{
	return strcpy(to, from);
}


char *DWC_STRDUP(char const *str)
{
	int len = DWC_STRLEN(str) + 1;
	char *new = DWC_ALLOC_ATOMIC(len);
	if (!new) {
		return NULL;
	}
	DWC_MEMCPY(new, str, len);
	return new;
}


int DWC_ATOI(char *str, int32_t *value)
{
	char *end = NULL;
	*value = simple_strtol(str, &end, 0);
	if (*end == '\0') {
		return 0;
	}
	return -1;
}


int DWC_ATOUI(char *str, uint32_t *value)
{
	char *end = NULL;
	*value = simple_strtoul(str, &end, 0);
	if (*end == '\0') {
		return 0;
	}
	return -1;
}


/* dwc_debug.h */

dwc_bool_t DWC_IN_IRQ(void)
{
	//return in_irq();
	return 0;
}


void DWC_VPRINTF(char *format, va_list args)
{
	vprintf(format, args);
}


int DWC_VSNPRINTF(char *str, int size, char *format, va_list args)
{
	vsprintf(str, format, args);
       return 0;
}

void DWC_PRINTF(char *format, ...)
{
	va_list args;
	va_start(args, format);
	DWC_VPRINTF(format, args);
	va_end(args);
}


int DWC_SPRINTF(char *buffer, char *format, ...)
{
	int retval;
	va_list args;
	va_start(args, format);
	retval = vsprintf(buffer, format, args);
	va_end(args);
	return retval;
}


int DWC_SNPRINTF(char *buffer, int size, char *format, ...)
{
	int retval;
	va_list args;
	va_start(args, format);
	retval = vsprintf(buffer, format, args);
	va_end(args);
	return retval;
}


void __DWC_WARN(char *format, ...)
{
	va_list args;
	va_start(args, format);
	//DWC_PRINTF(KERN_WARNING);
	DWC_VPRINTF(format, args);
	va_end(args);
}


void __DWC_ERROR(char *format, ...)
{
	va_list args;
	va_start(args, format);
	//DWC_PRINTF(KERN_ERR);
	DWC_VPRINTF(format, args);
	va_end(args);
}


void DWC_EXCEPTION(char *format, ...)
{
	va_list args;
	va_start(args, format);
	//DWC_PRINTF(KERN_ERR);
	DWC_VPRINTF(format, args);
	va_end(args);
	BUG_ON(1);
}


#ifdef DEBUG
void __DWC_DEBUG(char *format, ...)
{
	va_list args;
	va_start(args, format);
	//DWC_PRINTF(KERN_DEBUG);
	DWC_VPRINTF(format, args);
	va_end(args);
}
#endif



/* dwc_mem.h */

void *__DWC_DMA_ALLOC(uint32_t size, dwc_dma_t *dma_addr)
{
/*
	void *buf = dma_alloc_coherent(NULL, (size_t)size, dma_addr, GFP_KERNEL);
	if (!buf) {
		return NULL;
	}
	memset(buf, 0, (size_t)size);
*/
	void * ptr;
	ptr = malloc(size);
	if(!ptr)
		return NULL;
	else {
		memset(ptr, 0, size);
		return ptr;
	}
}

void __DWC_DMA_FREE(uint32_t size, void *virt_addr, dwc_dma_t dma_addr)
{
	//dma_free_coherent(NULL, size, virt_addr, dma_addr);
	free(virt_addr);
}

void *__DWC_ALLOC(uint32_t size)
{
	//return kzalloc(size, GFP_KERNEL);
	void * ptr;
	ptr = malloc(size);
	if(!ptr)
		return NULL;
	else {
		memset(ptr, 0, size);
		return ptr;
	}
}

void *__DWC_ALLOC_ATOMIC(uint32_t size)
{
	//return kzalloc(size, GFP_ATOMIC);
	return __DWC_ALLOC(size);
}

void __DWC_FREE(void *addr)
{
	//kfree(addr);
	free(addr);
}


/* Registers */

uint32_t DWC_READ_REG32(uint32_t volatile *reg)
{
	return readl(reg);
}


void DWC_WRITE_REG32(uint32_t volatile *reg, uint32_t value)
{
	writel(value, reg);
}


void DWC_MODIFY_REG32(uint32_t volatile *reg, uint32_t clear_mask, uint32_t set_mask)
{
	writel( (readl(reg) & ~clear_mask) | set_mask, reg );
}

/* Threading */

typedef struct work_container
{
	dwc_work_callback_t cb;
	void *data;
	dwc_workq_t *wq;
	char *name;

#ifdef DEBUG
	DWC_CIRCLEQ_ENTRY(work_container) entry;
#endif

	//struct delayed_work work;
} work_container_t;

#ifdef DEBUG
DWC_CIRCLEQ_HEAD(work_container_queue, work_container);
#endif

struct dwc_workq
{
	//struct workqueue_struct *wq;
	int pending;
	dwc_spinlock_t *lock;
	dwc_waitq_t *waitq;

#ifdef DEBUG
	struct work_container_queue entries;
#endif
};

#if 0
static void do_work(struct work_struct *work)
{
	unsigned long flags;
	struct delayed_work *dw = container_of(work, struct delayed_work, work);
	work_container_t *container = container_of(dw, struct work_container, work);
	dwc_workq_t *wq = container->wq;

	container->cb(container->data);

#ifdef DEBUG
	DWC_CIRCLEQ_REMOVE(&wq->entries, container, entry);
#endif

	DWC_DEBUG("Work done: %s, container=%p", container->name, container);
	if (container->name) {
		DWC_FREE(container->name);
	}
	DWC_FREE(container);

	DWC_SPINLOCK_IRQSAVE(wq->lock, &flags);
	wq->pending --;
	DWC_SPINUNLOCK_IRQRESTORE(wq->lock, flags);
	DWC_WAITQ_TRIGGER(wq->waitq);
}

static int work_done(void *data)
{
	dwc_workq_t *workq = (dwc_workq_t *)data;
	return workq->pending == 0;
}
#endif

int DWC_WORKQ_WAIT_WORK_DONE(dwc_workq_t *workq, int timeout)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
       return 0;
	//return DWC_WAITQ_WAIT_TIMEOUT(workq->waitq, work_done, workq, timeout);
}

dwc_workq_t *DWC_WORKQ_ALLOC(char *name)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
	return NULL;
#if 0
	dwc_workq_t *wq = DWC_ALLOC(sizeof(*wq));
	wq->wq = create_singlethread_workqueue(name);
	wq->pending = 0;
	wq->lock = DWC_SPINLOCK_ALLOC();
	wq->waitq = DWC_WAITQ_ALLOC();
#ifdef DEBUG
	DWC_CIRCLEQ_INIT(&wq->entries);
#endif
	return wq;
#endif
}

void DWC_WORKQ_FREE(dwc_workq_t *wq)
{
#if 0
#ifdef DEBUG
	if (wq->pending != 0) {
		struct work_container *wc;
		DWC_ERROR("Destroying work queue with pending work");
		DWC_CIRCLEQ_FOREACH(wc, &wq->entries, entry) {
			DWC_ERROR("Work %s still pending", wc->name);
		}
	}
#endif
	destroy_workqueue((struct workqueue_struct *)wq->wq);
	DWC_SPINLOCK_FREE(wq->lock);
	DWC_WAITQ_FREE(wq->waitq);
	DWC_FREE(wq);
#endif
	dwc_debug("NO SUPPORT %s\r\n", __func__);
}

void DWC_WORKQ_SCHEDULE(dwc_workq_t *wq, dwc_work_callback_t work_cb, void *data, char *format, ...)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	unsigned long flags;
	work_container_t *container;
	static char name[128];

	va_list args;
	va_start(args, format);
	DWC_VSNPRINTF(name, 128, format, args);
	va_end(args);

	DWC_SPINLOCK_IRQSAVE(wq->lock, &flags);
	wq->pending ++;
	DWC_SPINUNLOCK_IRQRESTORE(wq->lock, flags);
	DWC_WAITQ_TRIGGER(wq->waitq);

	container = DWC_ALLOC_ATOMIC(sizeof(*container));

	container->data = data;
	container->cb = work_cb;
	container->wq = wq;
	container->name = DWC_STRDUP(name);
	DWC_DEBUG("Queueing work: %s, contianer=%p", container->name, container);
	INIT_WORK(&container->work.work, do_work);

#ifdef DEBUG
	DWC_CIRCLEQ_INSERT_TAIL(&wq->entries, container, entry);
#endif

	queue_work(wq->wq, &container->work.work);
#endif
}

void DWC_WORKQ_SCHEDULE_DELAYED(dwc_workq_t *wq, dwc_work_callback_t work_cb, void *data, uint32_t time, char *format, ...)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	unsigned long flags;
	work_container_t *container;
	static char name[128];

	va_list args;
	va_start(args, format);
	DWC_VSNPRINTF(name, 128, format, args);
	va_end(args);

	DWC_SPINLOCK_IRQSAVE(wq->lock, &flags);
	wq->pending ++;
	DWC_SPINUNLOCK_IRQRESTORE(wq->lock, flags);
	DWC_WAITQ_TRIGGER(wq->waitq);

	container = DWC_ALLOC_ATOMIC(sizeof(*container));

	container->data = data;
	container->cb = work_cb;
	container->wq = wq;
	container->name = DWC_STRDUP(name);
	DWC_DEBUG("Queueing work: %s, contianer=%p", container->name, container);
	INIT_DELAYED_WORK(&container->work, do_work);

#ifdef DEBUG
	DWC_CIRCLEQ_INSERT_TAIL(&wq->entries, container, entry);
#endif

	queue_delayed_work(wq->wq, &container->work, msecs_to_jiffies(time));
#endif
}

int DWC_WORKQ_PENDING(dwc_workq_t *wq)
{
	return wq->pending;
}

dwc_spinlock_t *DWC_SPINLOCK_ALLOC(void)
{
	dwc_spinlock_t *sl = (dwc_spinlock_t *)1;
#if defined(CONFIG_PREEMPT) || (defined(CONFIG_SMP) && (!defined(CONFIG_X86)))
	sl = DWC_ALLOC(sizeof(*sl));
	spin_lock_init(sl);
#endif
	return (dwc_spinlock_t *)sl;
}

void DWC_SPINLOCK_FREE(dwc_spinlock_t *lock)
{
#if defined(CONFIG_PREEMPT) || (defined(CONFIG_SMP) && (!defined(CONFIG_X86)))
	DWC_FREE(lock);
#endif
}

void DWC_SPINLOCK(dwc_spinlock_t *lock)
{
#if defined(CONFIG_PREEMPT) || (defined(CONFIG_SMP) && (!defined(CONFIG_X86)))
	spin_lock((spinlock_t *)lock);
#endif
}

void DWC_SPINUNLOCK(dwc_spinlock_t *lock)
{
#if defined(CONFIG_PREEMPT) || (defined(CONFIG_SMP) && (!defined(CONFIG_X86)))
	spin_unlock((spinlock_t *)lock);
#endif
}

void DWC_SPINLOCK_IRQSAVE(dwc_spinlock_t *lock, unsigned long *flags)
{
	unsigned long f;
#if defined(CONFIG_PREEMPT) || (defined(CONFIG_SMP) && (!defined(CONFIG_X86)))
        spin_lock_irqsave((spinlock_t *)lock, f);
#else
	//local_irq_save(f);
#endif
        *flags = f;
}

void DWC_SPINUNLOCK_IRQRESTORE(dwc_spinlock_t *lock, unsigned long flags)
{
#if defined(CONFIG_PREEMPT) || (defined(CONFIG_SMP) && (!defined(CONFIG_X86)))
        spin_unlock_irqrestore((spinlock_t *)lock, flags);
#else
      //  local_irq_restore(flags);
#endif
}

dwc_mutex_t *DWC_MUTEX_ALLOC(void)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	dwc_mutex_t *mutex = (dwc_mutex_t*)DWC_ALLOC(sizeof(struct mutex));
	struct mutex *m = (struct mutex *)mutex;
	mutex_init(m);
	return mutex;
#endif
       return NULL;
}

#if (defined(DWC_LINUX) && defined(CONFIG_DEBUG_MUTEXES))
#else
void DWC_MUTEX_FREE(dwc_mutex_t *mutex)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	mutex_destroy((struct mutex *)mutex);
	DWC_FREE(mutex);
#endif
}
#endif

void DWC_MUTEX_LOCK(dwc_mutex_t *mutex)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
/*
	struct mutex *m = (struct mutex *)mutex;
	mutex_lock(m);
*/
}


int DWC_MUTEX_TRYLOCK(dwc_mutex_t *mutex)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
/*
	struct mutex *m = (struct mutex *)mutex;
	return mutex_trylock(m);
*/
       return 0;
}


void DWC_MUTEX_UNLOCK(dwc_mutex_t *mutex)
{
/*
	struct mutex *m = (struct mutex *)mutex;
	mutex_unlock(m);
*/
}


/* Timers */

struct dwc_timer
{
	//struct timer_list *t;
	char *name;
	dwc_timer_callback_t cb;
	void *data;
	uint8_t scheduled;
	dwc_spinlock_t *lock;
};

#if 0
static void set_scheduled(dwc_timer_t *t, int s)
{
	unsigned long flags;
	DWC_SPINLOCK_IRQSAVE(t->lock, &flags);
	t->scheduled = s;
	DWC_SPINUNLOCK_IRQRESTORE(t->lock, flags);
}

static int get_scheduled(dwc_timer_t *t)
{
	int s;
	unsigned long flags;
	DWC_SPINLOCK_IRQSAVE(t->lock, &flags);
	s = t->scheduled;
	DWC_SPINUNLOCK_IRQRESTORE(t->lock, flags);
	return s;
}

static void timer_callback(unsigned long data)
{
	dwc_timer_t *timer = (dwc_timer_t *)data;
	set_scheduled(timer, 0);
	DWC_DEBUG("Timer %s callback", timer->name);
	timer->cb(timer->data);
}

#endif

dwc_timer_t *DWC_TIMER_ALLOC(char *name, dwc_timer_callback_t cb, void *data)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);

#if 0
	dwc_timer_t *t = DWC_ALLOC(sizeof(*t));
	if (!t) {
		DWC_ERROR("Cannot allocate memory for timer");
		return NULL;
	}
	t->t = DWC_ALLOC(sizeof(*t->t));
	if (!t->t) {
		DWC_ERROR("Cannot allocate memory for timer->t");
		goto no_timer;
	}

	t->name = DWC_STRDUP(name);
	if (!t->name) {
		DWC_ERROR("Cannot allocate memory for timer->name");
		goto no_name;
	}

	t->lock = DWC_SPINLOCK_ALLOC();
	if (!t->lock) {
		DWC_ERROR("Cannot allocate memory for lock");
		goto no_lock;
	}
	t->scheduled = 0;
	t->t->base = &boot_tvec_bases;
	t->t->expires = jiffies;
	setup_timer(t->t, timer_callback, (unsigned long)t);

	t->cb = cb;
	t->data = data;

	return t;

 no_lock:
	DWC_FREE(t->name);
 no_name:
	DWC_FREE(t->t);
 no_timer:
	DWC_FREE(t);
#endif
	return NULL;
}

void DWC_TIMER_FREE(dwc_timer_t *timer)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	if (get_scheduled(timer)) {
		del_timer(timer->t);
	}

	DWC_SPINLOCK_FREE(timer->lock);
	DWC_FREE(timer->t);
	DWC_FREE(timer->name);
	DWC_FREE(timer);
#endif
}

void DWC_TIMER_SCHEDULE(dwc_timer_t *timer, uint32_t time)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);

#if 0
	if (!get_scheduled(timer)) {
		set_scheduled(timer, 1);
		DWC_DEBUG("Scheduling timer %s to expire in +%d msec", timer->name, time);
		timer->t->expires = jiffies + msecs_to_jiffies(time);
		add_timer(timer->t);
	}
	else {
		DWC_DEBUG("Modifying timer %s to expire in +%d msec", timer->name, time);
		mod_timer(timer->t, jiffies + msecs_to_jiffies(time));
	}
#endif
}

void DWC_TIMER_CANCEL(dwc_timer_t *timer)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
	//del_timer(timer->t);
}

struct dwc_tasklet
{
//	struct tasklet_struct t;
	dwc_tasklet_callback_t cb;
	void *data;
};

#if 0
static void tasklet_callback(unsigned long data)
{
	dwc_tasklet_t *t = (dwc_tasklet_t *)data;
	t->cb(t->data);
}
#endif

dwc_tasklet_t *DWC_TASK_ALLOC(dwc_tasklet_callback_t cb, void *data)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	dwc_tasklet_t *t = DWC_ALLOC(sizeof(*t));

	if(t) {
		t->data = data;
		t->cb = cb;
		tasklet_init(&t->t, tasklet_callback, (unsigned long)t);
	} else {
		DWC_ERROR("Cannot allocate memory for tasklet\n");
	}

	return t;
#endif
	return NULL;
}

void DWC_TASK_FREE(dwc_tasklet_t *t)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
	//DWC_FREE(t);
}

void DWC_TASK_SCHEDULE(dwc_tasklet_t *task)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
//	tasklet_schedule(&task->t);
}
/* Timing */

void DWC_UDELAY(uint32_t usecs)
{
	udelay(usecs);
}

void DWC_MDELAY(uint32_t msecs)
{
	mdelay(msecs);
}

void DWC_MSLEEP(uint32_t msecs)
{
	//msleep(msecs);
	DWC_MDELAY(msecs);
}

uint32_t DWC_TIME(void)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
	//return jiffies_to_msecs(jiffies);
       return 0;
}


/* Wait Queues */

struct dwc_waitq
{
//	wait_queue_head_t queue;
	int abort;
};

dwc_waitq_t *DWC_WAITQ_ALLOC(void)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	dwc_waitq_t *wq = DWC_ALLOC(sizeof(*wq));
	init_waitqueue_head(&wq->queue);
	wq->abort = 0;
	return wq;
#endif
	return NULL;
}

void DWC_WAITQ_FREE(dwc_waitq_t *wq)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
	//DWC_FREE(wq);
}

#if 0
static int32_t check_result(dwc_waitq_t *wq, int result)
{	int32_t msecs;
	if (result > 0) {
		msecs = jiffies_to_msecs(result);
		if (!msecs) {
			return 1;
		}
		return msecs;
	}

	if (result == 0) {
		return -DWC_E_TIMEOUT;
	}

	if ((result == -ERESTARTSYS) || (wq->abort == 1)) {
		return -DWC_E_ABORT;
	}

	return -DWC_E_UNKNOWN;
}
#endif

int32_t DWC_WAITQ_WAIT(dwc_waitq_t *wq, dwc_waitq_condition_t condition, void *data)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
#if 0
	int result = wait_event_interruptible(wq->queue,
						  condition(data) || wq->abort);
	return check_result(wq, result);
#endif
	return 0;
}

int32_t DWC_WAITQ_WAIT_TIMEOUT(dwc_waitq_t *wq, dwc_waitq_condition_t condition,
			       void *data, int32_t msecs)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);

#if 0
	int result = wait_event_interruptible_timeout(wq->queue,
							  condition(data) || wq->abort,
							  msecs_to_jiffies(msecs));
	return check_result(wq, result);
#endif
	return 0;
}

void DWC_WAITQ_TRIGGER(dwc_waitq_t *wq)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
//	wake_up_interruptible(&wq->queue);
}

void DWC_WAITQ_ABORT(dwc_waitq_t *wq)
{
	dwc_debug("NO SUPPORT %s\r\n", __func__);
	/*
	wq->abort = 1;
	DWC_WAITQ_TRIGGER(wq);
	*/
}
