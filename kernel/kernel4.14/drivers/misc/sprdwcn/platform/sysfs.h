/*
 * This file is part of wcn platform
 */

#ifndef __SYSFS_H__
#define __SYSFS_H__

#include "wcn_boot.h"

int wcn_sysfs_init(struct marlin_device *mdev);
void wcn_sysfs_free(struct marlin_device *mdev);
void sysfs_at_cmd_cb(struct marlin_device *mdev);

#endif

