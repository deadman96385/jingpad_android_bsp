/*
 * Copyright (C) 2016 Spreadtrum Communications, Inc.
 *
 */

#ifndef __UFS_API_H__
#define __UFS_API_H__


int ufs_init(void);
int ufs_lu_read(u8 lun, u64 start_lba, u32 lb_num, void *buf);

#endif /* __UFS_API_H__ */

