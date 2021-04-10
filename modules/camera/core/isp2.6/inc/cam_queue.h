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

#ifndef _CAM_QUEUE_H_
#define _CAM_QUEUE_H_

#include <linux/types.h>
#include <linux/spinlock.h>

#include "cam_types.h"
#include "cam_buf.h"

#define CAM_EMP_Q_LEN_INC		16
#define CAM_EMP_Q_LEN_MAX		1024

enum {
	CAM_Q_INIT,
	CAM_Q_EMPTY,
	CAM_Q_FULL,
	CAM_Q_CLEAR
};

struct camera_frame {
	struct list_head list;
	uint32_t fid;
	uint32_t width;
	uint32_t height;
	uint16_t pattern;
	uint16_t endian;
	uint32_t evt;
	uint32_t channel_id;
	uint32_t irq_type;
	uint32_t irq_property;
	uint32_t is_reserved;
	uint32_t is_compressed;
	uint32_t compress_4bit_bypass;
	uint32_t user_fid;
	uint32_t dcam_idx;
	uint32_t zoom_ratio;
	uint32_t sw_slice_num;
	uint32_t sw_slice_no;
	struct img_trim slice_trim;
	void *priv_data;
	/* for more param extend especially in offline process */
	void *param_data;
	void *sync_data;/* struct dcam_frame_synchronizer */
	struct timeval time;/* time without suspend @ISP DONE */
	ktime_t boot_time;/* ns from boot @ISP DONE */
	struct timeval sensor_time;/* time without suspend @SOF */
	ktime_t boot_sensor_time;/* ns from boot @SOF */
	struct camera_buf buf;
};

struct camera_queue {
	uint32_t type;
	uint32_t state;
	uint32_t max;
	uint32_t cnt;
	spinlock_t lock;
	struct list_head head;
	void (*destroy)(void *param);
};

int camera_enqueue(struct camera_queue *q, struct camera_frame *pframe);
struct camera_frame *camera_dequeue(struct camera_queue *q);
struct camera_frame *camera_dequeue_tail(struct camera_queue *q);
struct camera_frame *
camera_dequeue_if(struct camera_queue *q,
		  bool (*filter)(struct camera_frame *, void *),
		  void *data);
struct camera_frame *camera_dequeue_peek(struct camera_queue *q);

int camera_queue_init(struct camera_queue *q,
			uint32_t max, uint32_t type,
			void (*cb_func)(void *));
int camera_queue_clear(struct camera_queue *q);
uint32_t camera_queue_cnt(struct camera_queue *q);
int camera_queue_same_frame(struct camera_queue *q0, struct camera_queue *q1,
			struct camera_frame **pf0, struct camera_frame **pf1,
			int64_t t);

struct camera_frame *get_empty_frame(void);
int put_empty_frame(struct camera_frame *pframe);
void free_empty_frame(void *param);

#endif /* _CAM_QUEUE_H_ */
