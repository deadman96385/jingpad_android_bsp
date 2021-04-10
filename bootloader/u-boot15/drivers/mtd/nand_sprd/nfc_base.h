

#ifndef __NFC_BASE_
#define __NFC_BASE_
#include <linux/mtd/flashchip.h>

/**
 * MTD operation modes
 *
 * @MTD_OPS_PLACE_OOB:	OOB data are placed at the given offset (default)
 * @MTD_OPS_AUTO_OOB:	OOB data are automatically placed at the free areas
 *			which are defined by the internal ecclayout
 * @MTD_OPS_RAW:	data are transferred as-is, with no error correction;
 *			this mode implies %MTD_OPS_PLACE_OOB
 *
 * These modes can be passed to ioctl(MEMWRITE) and are also used internally.
 * See notes on "MTD file modes" for discussion on %MTD_OPS_RAW vs.
 * %MTD_FILE_MODE_RAW.
 */
 #if 0
enum {
	MTD_OPS_PLACE_OOB = 0,
	MTD_OPS_AUTO_OOB = 1,
	MTD_OPS_RAW = 2,
};
#endif
#define TASK_UNINTERRUPTIBLE
#define wake_up(...)	do { } while (0)

#define DPRINTK(format, args...)					\
do {									\
	printf("%s[%d]: " format "\n", __func__, __LINE__, ##args);	\
} while (0)

    /* build.c */
#define get_device(...)
#define put_device(...)
#define ubi_sysfs_init(...)		0
#define ubi_sysfs_close(...)		do { } while (0)
#if 0
    static inline int is_power_of_2(unsigned long n)
    {
        return (n != 0 && ((n & (n - 1)) == 0));
    }
#endif
    /* FIXME */
#define MKDEV(...)			0
#define MAJOR(dev)			0
#define MINOR(dev)			0

#define alloc_chrdev_region(...)	0
#define unregister_chrdev_region(...)

#define class_create(...)		__builtin_return_address(0)
#define class_create_file(...)		0
#define class_remove_file(...)
#define class_destroy(...)
#define misc_register(...)		0
#define misc_deregister(...)

    /* vmt.c */
#define device_register(...)		0
#define volume_sysfs_init(...)		0
#define volume_sysfs_close(...)		do { } while (0)

    /* kapi.c */

    /* eba.c */

    /* io.c */
#define init_waitqueue_head(...)	do { } while (0)
#define wait_event_interruptible(...)	0
#define wake_up_interruptible(...)	do { } while (0)
#define print_hex_dump(...)		do { } while (0)
#define dump_stack(...)			do { } while (0)

    /* wl.c */
#define task_pid_nr(x)			0
#define set_freezable(...)		do { } while (0)
#define try_to_freeze(...)		0
#define set_current_state(...)		do { } while (0)
#define kthread_should_stop(...)	0
#define schedule()			do { } while (0)

    /* upd.c */
#if 0
    static inline unsigned long copy_from_user(void *dest, const void *src,
                           unsigned long count)
    {
        memcpy((void *)dest, (void *)src, count);
        return 0;
    }
#endif
    /* common */
    typedef int wait_queue_head_t;
#define spin_lock_init(...)
#define spin_lock(...)
#define spin_lock_irqsave(...)
#define spin_lock_irq(...)
#define spin_unlock(...)
#define spin_unlock_irqrestore(...)
#define spin_unlock_irq(...)
#if 0
typedef enum _bool{ 
	false = 0,
	true = 1 
} bool;
#endif
#define mutex_init(...)
#define mutex_lock(...)
#define mutex_unlock(...)

#define init_rwsem(...)			do { } while (0)
#define down_read(...)			do { } while (0)
#define down_write(...)			do { } while (0)
#define down_write_trylock(...)		1
#define up_read(...)			do { } while (0)
#define up_write(...)			do { } while (0)

    //struct kmem_cache { int i; };
#define kmem_cache_create(...)		1
#define kmem_cache_alloc(obj, gfp)	malloc(sizeof(struct ubi_wl_entry))
#define kmem_cache_free(obj, size)	free(size)
#define kmem_cache_destroy(...)

#define cond_resched()			do { } while (0)
#define yield()				do { } while (0)

#define KERN_WARNING
#define KERN_ERR
#define KERN_NOTICE
#define KERN_DEBUG

#define GFP_KERNEL			0
#define GFP_NOFS			1

#define __user
#define __init
#define __exit

#define __initdata



#define NFC_MAX_ID_LEN 8
#define  THIS_MODULE 0
//typedef int spinlock_t;
typedef int wait_queue_head_t;

typedef struct NFC_BASE {
// resource0:These infomation is initialize by nfc base self;
	spinlock_t lock;
	flstate_t state;
	wait_queue_head_t wq;

	uint32_t pageMsk;
	uint32_t blkMsk;
	uint32_t pagePerBuf;
	uint32_t pagePerMtd;
	uint32_t *bbt;
	uint32_t allowEraseBadBlock;

// resource1:This infomation must be give by user
	uint8_t id[NFC_MAX_ID_LEN];
	uint32_t ecc_mode;
	uint32_t risk_threshold;
	struct nand_ecclayout layout;
	uint32_t oobSize;
	uint32_t pageShift;
	uint32_t blkShift;
	uint32_t chipShift;
	uint32_t chipNum;
	uint32_t bufShift;

	uint8_t *mBuf_v;
	uint8_t *sBuf_v;

	int (*_ctrl_en) (struct NFC_BASE * this, uint32_t en);
	void (*_ctrl_suspend) (struct NFC_BASE * this);
	int (*_ctrl_resume) (struct NFC_BASE * this);

	int (*_readPageInBlk) (struct NFC_BASE * this, uint32_t page, uint32_t num, uint32_t * retNum, uint32_t ifHasMBuf, uint32_t ifHasSBuf, uint32_t mode,
			       struct mtd_ecc_stats * ecc_sts);
	int (*_writePageInBlk) (struct NFC_BASE * this, uint32_t page, uint32_t num, uint32_t * retNum, uint32_t ifHasMBuf, uint32_t ifHasSBuf, uint32_t mode);
	int (*_nand_eraseBlk) (struct NFC_BASE * this, uint32_t page);
	int (*_nand_isBadBlk) (struct NFC_BASE * this, uint32_t page);
	int (*_nand_markBadBlk) (struct NFC_BASE * this, uint32_t page);

	void *priv;
} NFC_BASE_T;

int nfc_base_register(NFC_BASE_T * this);
#endif
