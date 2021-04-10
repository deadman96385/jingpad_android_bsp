
#include <common.h>
#include <sprd_ufs.h>
#include <linux/io.h>
static inline uint32_t ufs_readl(int reg)
{
	return readl((void *)ufs_info.base_addr + reg);
}

static inline void ufs_writel(int reg, uint32_t val)
{
	writel(val, (void *)ufs_info.base_addr + reg);
}

void init_global_reg(void);

