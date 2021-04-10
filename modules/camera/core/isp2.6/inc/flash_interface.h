/*
 * Copyright (C) 2017-2018 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef _FLASH_INTERFACE_H_
#define _FLASH_INTERFACE_H_

struct cam_flash_task_info {
	struct sprd_img_set_flash set_flash;
	uint32_t frame_skipped;
	uint32_t after_af;
	struct timeval timestamp;
	uint32_t skip_number;	/*cap skip*/
	uint32_t cam_idx;

	struct completion flash_thread_com;
	struct task_struct *flash_thread;
	uint32_t is_flash_thread_stop;
};


struct cam_flash_ops {
	int (*open)(void *flash_handle, void *arg);
	int (*close)(void *flash_handle);
	int (*cfg_flash)(void *flash_handle, void *arg);
	int (*set_flash)(void *flash_handle, void *arg);
	int (*get_flash)(void *flash_handle, void *arg);
	int (*start_flash)(void *flash_handle);
	void (*set_frame_skip)(void *flash_handle, int skip_frame);
};

struct cam_flash_ops *get_flash_ops(void);

void *get_cam_flash_handle(uint32_t cam_idx);
int put_cam_flash_handle(void *flash_handle);

#endif
