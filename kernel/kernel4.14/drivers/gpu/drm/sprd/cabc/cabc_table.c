/*
 *Copyright (C) 2019 Spreadtrum Communications Inc.
 *
 *This software is licensed under the terms of the GNU General Public
 *License version 2, as published by the Free Software Foundation, and
 *may be copied, distributed, and modified under those terms.
 *
 *This program is distributed in the hope that it will be useful,
 *but WITHOUT ANY WARRANTY; without even the implied warranty of
 *MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *GNU General Public License for more details.
 */

#include "cabc_definition.h"

u16 g_brightness_step[32] = {
	1020, 960, 896, 832, 768, 708, 652, 600, 548,
	500, 452, 408, 368, 328, 284, 256, 216, 192, 164,
	144, 112, 104, 92, 72, 52, 52, 52, 52, 52, 52, 52, 52,
};

u16 g_backlight_compensation_table[256] = {
	0x31a7, 0x31a7, 0x243b, 0x1e22, 0x1a70, 0x17e4, 0x15fd, 0x1480,
	0x134b, 0x124a, 0x116f, 0x10b1, 0x100c, 0x0f79, 0x0ef6, 0x0e7f,
	0x0e14, 0x0db2, 0x0d58, 0x0d05, 0x0cb8, 0x0c71, 0x0c2e, 0x0bf0,
	0x0bb5, 0x0b7e, 0x0b4a, 0x0b19, 0x0aeb, 0x0abe, 0x0a94, 0x0a6c,
	0x0a46, 0x0a21, 0x09fe, 0x09dd, 0x09bd, 0x099e, 0x0980, 0x0964,
	0x0948, 0x092e, 0x0914, 0x08fb, 0x08e3, 0x08cc, 0x08b6, 0x08a0,
	0x088b, 0x0877, 0x0863, 0x0850, 0x083d, 0x082b, 0x0819, 0x0808,
	0x07f7, 0x07e7, 0x07d7, 0x07c7, 0x07b8, 0x07a9, 0x079b, 0x078d,
	0x077f, 0x0772, 0x0764, 0x0757, 0x074b, 0x073e, 0x0732, 0x0727,
	0x071b, 0x0710, 0x0704, 0x06f9, 0x06ef, 0x06e4, 0x06da, 0x06d0,
	0x06c6, 0x06bc, 0x06b3, 0x06a9, 0x06a0, 0x0697, 0x068e, 0x0685,
	0x067c, 0x0674, 0x066b, 0x0663, 0x065b, 0x0653, 0x064b, 0x0644,
	0x063c, 0x0634, 0x062d, 0x0626, 0x061f, 0x0618, 0x0611, 0x060a,
	0x0603, 0x05fc, 0x05f6, 0x05ef, 0x05e9, 0x05e2, 0x05dc, 0x05d6,
	0x05d0, 0x05ca, 0x05c4, 0x05be, 0x05b8, 0x05b3, 0x05ad, 0x05a7,
	0x05a2, 0x059d, 0x0597, 0x0592, 0x058d, 0x0587, 0x0582, 0x057d,
	0x0578, 0x0573, 0x056e, 0x056a, 0x0565, 0x0560, 0x055b, 0x0557,
	0x0552, 0x054e, 0x0549, 0x0545, 0x0540, 0x053c, 0x0538, 0x0533,
	0x052f, 0x052b, 0x0527, 0x0523, 0x051f, 0x051b, 0x0517, 0x0513,
	0x050f, 0x050b, 0x0507, 0x0504, 0x0500, 0x04fc, 0x04f8, 0x04f5,
	0x04f1, 0x04ee, 0x04ea, 0x04e6, 0x04e3, 0x04e0, 0x04dc, 0x04d9,
	0x04d5, 0x04d2, 0x04cf, 0x04cb, 0x04c8, 0x04c5, 0x04c2, 0x04bf,
	0x04bb, 0x04b8, 0x04b5, 0x04b2, 0x04af, 0x04ac, 0x04a9, 0x04a6,
	0x04a3, 0x04a0, 0x049d, 0x049b, 0x0498, 0x0495, 0x0492, 0x048f,
	0x048c, 0x048a, 0x0487, 0x0484, 0x0482, 0x047f, 0x047c, 0x047a,
	0x0477, 0x0474, 0x0472, 0x046f, 0x046d, 0x046a, 0x0468, 0x0465,
	0x0463, 0x0460, 0x045e, 0x045c, 0x0459, 0x0457, 0x0454, 0x0452,
	0x0450, 0x044d, 0x044b, 0x0449, 0x0447, 0x0444, 0x0442, 0x0440,
	0x043e, 0x043b, 0x0439, 0x0437, 0x0435, 0x0433, 0x0431, 0x042f,
	0x042c, 0x042a, 0x0428, 0x0426, 0x0424, 0x0422, 0x0420, 0x041e,
	0x041c, 0x041a, 0x0418, 0x0416, 0x0414, 0x0412, 0x0410, 0x040e,
	0x040d, 0x040b, 0x0409, 0x0407, 0x0405, 0x0403, 0x0401, 0x0400,
};
