#ifndef DL_UBI_H
#define DL_UBI_H

#include <ubi_uboot.h>

struct ubi_selected_dev {
	int ubi_initialized;
	int dev_num;
	struct ubi_device *dev;
};

int fdl_ubi_create_vol(struct ubi_device *ubi, char *volume, int *vol_id, long long size, int dynamic);

int fdl_ubi_remove_vol(struct ubi_device *ubi, char *volume);

int fdl_ubi_volume_write(struct ubi_device *ubi, char *volume, void *buf, size_t size);

int fdl_ubi_volume_read(struct ubi_device *ubi, char *volume, char *buf, size_t size, size_t offset);

int fdl_ubi_dev_init(void);

int fdl_ubi_volume_start_update(struct ubi_device *ubi, char *volume, size_t size);

#endif

