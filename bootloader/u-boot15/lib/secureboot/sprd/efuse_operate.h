/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */
#ifndef _EFUSE_OPERATE_H_
#define _EFUSE_OPERATE_H_

int arm7_key_write( char *key, u32 count);
int arm7_key_read( char *key, u32 count);
int efuse_hash_write( char *hash, u32 count);
int efuse_hash_read(char *hash, u32 count);
int efuse_uid_read(char *uid, int count);
int secure_efuse_program_sprd(void);
int efuse_rollback_version_read(int type);

#endif/*_EFUSE_OPERATE_H_*/
