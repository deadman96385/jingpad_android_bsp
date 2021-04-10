#ifndef _ROOT_INSPECT_H_
#define _ROOT_INSPECT_H_


#define ROOT_MAGIC 0x524F4F54 //"ROOT"
#define ROOT_OFFSET 0x1000

typedef struct {
	u32 magic;
	u32 root_flag;
} root_stat_t;

u32 get_rootflag(root_stat_t *stat);
u32 erase_rootflag(root_stat_t *stat);

#endif
