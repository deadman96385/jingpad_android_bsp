#include <linux/kthread.h>
#include "vdsp_dvfs.h"
#include "vdsp_hw.h"
#include "xrp_internal.h"

#define DVFS_MONITOR_CYCLE_TIME   (1000*1000)

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) "sprd-vdsp: dvfs %d: %d %s:" \
	fmt, current->pid, __LINE__, __func__

static enum sprd_vdsp_kernel_power_level translate_powerlevel_fromuser(int32_t in)
{
	switch (in)
	{
	case -1:
		return SPRD_VDSP_KERNEL_POWERHINT_RESTORE_DVFS;
	case 0:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_0;
	case 1:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_1;
	case 2:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_2;
	case 3:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_3;
	case 4:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_4;
	case 5:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_5;
	case 6:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_MAX;
	default:
		return SPRD_VDSP_KERNEL_POWERHINT_LEVEL_MAX;
	}
}

static enum sprd_vdsp_kernel_powerhint_acquire_release
	translate_acquire_release_fromuser(uint32_t acq_rel)
{
	switch (acq_rel)
	{
	case 0:
		return SPRD_VDSP_KERNEL_POWERHINT_ACQUIRE;
	case 1:
		return SPRD_VDSP_KERNEL_POWERHINT_RELEASE;
	default:
		return SPRD_VDSP_KERNEL_POWERHINT_MAX;
	}
}

int32_t set_dvfs_maxminfreq(void *data, int32_t maxminflag)
{
	struct xvp *xvp = (struct xvp*) data;
	int32_t index;

	if (maxminflag)
		index = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_5;
	else
		index = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_0;
	if (xvp->hw_ops->setdvfs)
		xvp->hw_ops->setdvfs(xvp->hw_arg, index);
	return 0;
}

void preprocess_work_piece(void *data)
{
	struct xvp* xvp = (struct xvp*)data;

	mutex_lock(&xvp->dvfs_info.timepiece_lock);
	if (0 == xvp->dvfs_info.workingcount)
		xvp->dvfs_info.piece_starttime = ktime_get();

	xvp->dvfs_info.workingcount++;
	mutex_unlock(&xvp->dvfs_info.timepiece_lock);
}

void postprocess_work_piece(void *data)
{
	ktime_t realstarttime;
	struct xvp *xvp = (struct xvp*)data;

	mutex_lock(&xvp->dvfs_info.timepiece_lock);
	xvp->dvfs_info.workingcount--;
	if (0 == xvp->dvfs_info.workingcount) {
		realstarttime =
			(ktime_compare(xvp->dvfs_info.piece_starttime,
				xvp->dvfs_info.starttime) > 0)
			? xvp->dvfs_info.piece_starttime : xvp->dvfs_info.starttime;
		xvp->dvfs_info.cycle_totaltime += ktime_sub(ktime_get(), realstarttime);
	}
	pr_debug("workingcount:%d", xvp->dvfs_info.workingcount);
	mutex_unlock(&xvp->dvfs_info.timepiece_lock);
}

int32_t set_powerhint_flag(void *data, int32_t power, uint32_t acq_rel)
{
	int32_t index;
	struct xvp *xvp = (struct xvp*) data;
	int ret = 0;
	int i;
	enum sprd_vdsp_kernel_power_level level;
	enum sprd_vdsp_kernel_powerhint_acquire_release acquire_release;

	level = translate_powerlevel_fromuser(power);
	if ((level == SPRD_VDSP_KERNEL_POWERHINT_LEVEL_MAX) ||
		(level == SPRD_VDSP_KERNEL_POWERHINT_RESTORE_DVFS)) {
		pr_err("level:%d is error", level);
		return -1;
	}
	acquire_release = translate_acquire_release_fromuser(acq_rel);
	mutex_lock(&xvp->dvfs_info.powerhint_lock);
	if (acquire_release == SPRD_VDSP_KERNEL_POWERHINT_ACQUIRE)
		xvp->dvfs_info.powerhint_count_level[level]++;
	else if (SPRD_VDSP_KERNEL_POWERHINT_RELEASE == acquire_release)
		xvp->dvfs_info.powerhint_count_level[level]--;

	for (i = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_MAX - 1; i >= 0; i--) {
		if (xvp->dvfs_info.powerhint_count_level[i] != 0)
			break;
	}

	pr_debug("acquire_release:%d, level:%d, i:%d, last_powerhint_level:%d\n",
		acquire_release, level, i, xvp->dvfs_info.last_powerhint_level);
	if ((i != -1) && (xvp->dvfs_info.last_powerhint_level != i)) {
		/*set power hint*/
		index = i;
		if (xvp->hw_ops->setdvfs) {
			pr_debug("setdvfs index:%d\n", index);
			xvp->hw_ops->setdvfs(xvp->hw_arg, index);
		}
		xvp->dvfs_info.last_powerhint_level = i;
	}else if (-1 == i) {
		xvp->dvfs_info.last_dvfs_index = xvp->dvfs_info.last_powerhint_level;
		xvp->dvfs_info.last_powerhint_level = SPRD_VDSP_KERNEL_POWERHINT_RESTORE_DVFS;
	}
	mutex_unlock(&xvp->dvfs_info.powerhint_lock);
	return ret;
}

static uint32_t calculate_vdsp_usage(void *data, ktime_t fromtime)
{
	int32_t percent;
	ktime_t current_time = ktime_get();
	struct xvp * xvp = (struct xvp*)data;

	mutex_lock(&xvp->dvfs_info.timepiece_lock);
	if (xvp->dvfs_info.workingcount != 0) {
		/*now some piece may executing*/
		if (ktime_compare(xvp->dvfs_info.piece_starttime, fromtime) <= 0)
			xvp->dvfs_info.cycle_totaltime = ktime_sub(current_time, fromtime);
		else
			xvp->dvfs_info.cycle_totaltime += ktime_sub(current_time,
				xvp->dvfs_info.piece_starttime);
	}
	percent = (xvp->dvfs_info.cycle_totaltime * 100) / ktime_sub(current_time, fromtime);
	pr_debug("cycle_totaltime:%d ms, timeeclapse:%d ms, percent:%d",
		(int)(xvp->dvfs_info.cycle_totaltime / 1000000),
		(int)(ktime_sub(current_time, fromtime) / 1000000),
		percent);
	xvp->dvfs_info.starttime = ktime_get();
	xvp->dvfs_info.cycle_totaltime = 0;
	mutex_unlock(&xvp->dvfs_info.timepiece_lock);
	return percent;
}

static uint32_t calculate_dvfs_index(uint32_t percent)
{
	enum sprd_vdsp_kernel_power_level level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_0;
	static uint32_t last_percent = 0;

	if ((last_percent > 50)) {
		if (percent > 50)
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_5;
		else if ((percent <= 50) && (percent > 20))
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_3;
		else if (percent <= 20)
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_2;
	}else if ((last_percent <= 50) && (last_percent > 20)) {
		if (percent > 50)
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_5;
		else if ((percent <= 50) && (percent > 20))
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_3;
		else if (percent <= 20)
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_2;
		else
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_2;
	}else if (last_percent <= 20){
		if (percent > 50)
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_5;
		else if ((percent <= 50) && (percent > 20))
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_2;
		else if (percent <= 20)
			level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_2;
	}else {
		level = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_2;
	}
	last_percent = percent;
	return level;
}

int vdsp_dvfs_thread(void* data)
{
	uint32_t percentage;
	int32_t index;
	long ret = 0;
	struct xvp *xvp = (struct xvp *)data;

	while (!kthread_should_stop()) {
		mutex_lock(&xvp->dvfs_info.powerhint_lock);
		if (SPRD_VDSP_KERNEL_POWERHINT_RESTORE_DVFS ==
				xvp->dvfs_info.last_powerhint_level) {
			percentage = calculate_vdsp_usage(xvp, xvp->dvfs_info.starttime);
			/*dvfs set freq*/
			index = calculate_dvfs_index(percentage);
			pr_debug("percentage:%d, dvfs index:%d, last index:%d\n",
				percentage, index, xvp->dvfs_info.last_dvfs_index);
			if (index != xvp->dvfs_info.last_dvfs_index) {
				if (xvp->hw_ops->setdvfs){
					xvp->hw_ops->setdvfs(xvp->hw_arg, index);
					xvp->dvfs_info.last_dvfs_index = index;
				}
			}
		}
		mutex_unlock(&xvp->dvfs_info.powerhint_lock);//.unlock();
		ret = wait_event_interruptible_timeout(xvp->dvfs_info.wait_q,
			kthread_should_stop(), msecs_to_jiffies(1000));
		pr_debug("wait_event_interruptible_timeout ret:%ld\n", ret);
	}
	pr_debug("dvfs exit\n");
	return 0;
}

int vdsp_dvfs_init(void *data) {
	int i;
	struct xvp* xvp = (struct xvp*)data;

	mutex_init(&xvp->dvfs_info.timepiece_lock);
	mutex_init(&xvp->dvfs_info.powerhint_lock);
	init_waitqueue_head(&xvp->dvfs_info.wait_q);
	xvp->dvfs_info.starttime = 0;
	xvp->dvfs_info.cycle_totaltime = 0;
	xvp->dvfs_info.piece_starttime = 0;
	xvp->dvfs_info.last_powerhint_level = SPRD_VDSP_KERNEL_POWERHINT_RESTORE_DVFS;
	xvp->dvfs_info.last_dvfs_index = 0;
	for (i = 0; i < SPRD_VDSP_KERNEL_POWERHINT_LEVEL_MAX; i++) {
		xvp->dvfs_info.powerhint_count_level[i] = 0;
	}
	/*when open init to max freq*/
	if (xvp->hw_ops->setdvfs) {
		xvp->hw_ops->setdvfs(xvp->hw_arg, SPRD_VDSP_KERNEL_POWERHINT_LEVEL_5);
		xvp->dvfs_info.last_dvfs_index = SPRD_VDSP_KERNEL_POWERHINT_LEVEL_5;
	}
	xvp->dvfs_info.dvfs_thread = kthread_run(vdsp_dvfs_thread, xvp,
		"vdsp_dvfs_thread");
	if (IS_ERR(xvp->dvfs_info.dvfs_thread)) {
		pr_err("kthread_run err\n");
		return -1;
	}
	return 0;
}

void vdsp_dvfs_deinit(void *data) {
	struct xvp* xvp = (struct xvp*)data;

	if (xvp->dvfs_info.dvfs_thread) {
		kthread_stop(xvp->dvfs_info.dvfs_thread);
		xvp->dvfs_info.dvfs_thread = NULL;
		pr_debug("kthread_stop\n");
	}
	if (xvp->hw_ops->setdvfs)
		xvp->hw_ops->setdvfs(xvp->hw_arg, SPRD_VDSP_KERNEL_POWERHINT_LEVEL_0);
	mutex_destroy(&xvp->dvfs_info.timepiece_lock);
	mutex_destroy(&xvp->dvfs_info.powerhint_lock);
	pr_debug("dvfs deinit exit\n");
	return;
}
