#include <common.h>
#include <linux/types.h>
#include <linux/string.h>

#include "root_inspect.h"
#include "loader_common.h"
#include "sprd_common_rw.h"

u32 get_rootflag(root_stat_t *stat)
{
	u32 result = 0;

	if (0 != common_raw_read(PRODUCTINFO_FILE_PATITION, sizeof(root_stat_t), ROOT_OFFSET, stat)) {
		errorf("read miscdata error.\n");
		return result;
	}

	if (stat->magic == ROOT_MAGIC) {
		debugf("ROOT_MAGIC matched\n");
		debugf("stat.root_flag = %d\n", stat->root_flag);
		result = stat->root_flag;
	}
	return result;
}

u32 erase_rootflag(root_stat_t *stat)
{
	unsigned long erasesize = 0, base_sector = 0;
	unsigned int curArea = 0;
	disk_partition_t info;
	block_dev_desc_t *dev = NULL;

	erasesize = sizeof(root_stat_t);
	char *buf = malloc(erasesize);
	memset(buf, 0, erasesize);

	debugf("Erase miscdata partition.\n");

	if (0 != common_raw_write(PRODUCTINFO_FILE_PATITION, (uint64_t)erasesize, (uint64_t)0, ROOT_OFFSET, buf)) {
		errorf("erase miscdata error.\n");
		free(buf);
		return -1;
	}

	memset(stat, 0, erasesize);

	free(buf);
	return 0;
}
