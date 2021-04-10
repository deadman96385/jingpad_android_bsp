
#include "fsck.h"
//#include <libgen.h>
//#include <ctype.h>
//#include <getopt.h>
//#include "quotaio.h"


static struct f2fs_sb_info g_sbi;
static int do_resize(struct f2fs_sb_info *sbi)
{
	struct f2fs_super_block *sb = F2FS_RAW_SUPER(sbi);
	u_int64_t old = get_sb(block_count) << get_sb(log_sectors_per_block);
	u_int64_t delta = 0;

	if (!c.target_sectors)
		c.target_sectors = c.total_sectors;

	if (c.target_sectors > c.total_sectors) {
		printf("Out-of-range Target=0x%llx / 0x%llx",
				c.target_sectors, c.total_sectors);
		return -1;
	}

	/* may different sector size */
	if ((c.target_sectors * c.sector_size >>
			get_sb(log_blocksize)) <= get_sb(block_count)) {
		printf("Nothing to resize, now only support resize to expand\n");
		return -1;
	}

	delta = (c.target_sectors >= old) ? (c.target_sectors - old) : (old - c.target_sectors);
	if (delta <= 2048 ) {
		printf("Nothing to resize; 0x%llx : % 0xllx : 0x%llx\n", c.target_sectors, old, c.total_sectors);
		return -1;
	}
	return f2fs_resize(sbi);
}

//Running /system/bin/resize.f2fs -r 16384 /dev/block/platform/soc/soc:ap-ahb/20600000.sdio/by-name/userdata
int f2fs_resize_main(uint64_t device_total_size, uint32_t device_sector_size, f2fs_devcie_callback write, f2fs_devcie_callback read, void *device_handle, unsigned char *cache_buffer, uint64_t cache_buffer_size)
{
	struct f2fs_sb_info *sbi;
	int ret = -1;
	sbi = &g_sbi;
	MSG(0, "device size=0x%llx\n", device_total_size);
	if (device_total_size >
			(u_int64_t)F2FS_MAX_SEGMENT * 2 * 1024 * 1024) {
			MSG(0, "\tError: F2FS can support 16TB at most!!!\n");
		return -1;
	}

	if (f2fs_init_configuration(device_total_size, device_sector_size))
		return -1;

	c.dbg_lv = 0; // 5;
	c.func = RESIZE;
	c.device_handle = device_handle;
	c.write = write;
	c.read = read;
	c.cache_buffer_dirty_end = 0LL;
	c.cache_buffer_size = cache_buffer_size;
	c.cache_buffer = cache_buffer;
	if (c.cache_buffer_size > device_total_size)
		c.cache_buffer_size = device_total_size;

	memset(c.cache_buffer, 0, c.cache_buffer_size);

	printf("cache size 0x%llx use 0x%llx\n", cache_buffer_size, c.cache_buffer_size);

	c.read(c.device_handle, c.cache_buffer_size, (uint64_t)0LL, c.cache_buffer);

	ret = f2fs_do_mount(sbi);
	if (ret != 0) {
		goto out_err;
	}

	if (do_resize(sbi))
		goto out_err;

	f2fs_do_umount(sbi);

	c.write(c.device_handle, c.cache_buffer_dirty_end, (uint64_t)0LL, c.cache_buffer);
	printf("\nDone.\n");
	return 0;

out_err:
	if (sbi->ckpt)
		free(sbi->ckpt);
	if (sbi->raw_super)
		free(sbi->raw_super);
	return -1;
}
