/* drivers/video/sprdfb/lcd_nt35596_mipi.c
 *
 * Support for nt35596 mipi LCD device
 *
 * Copyright (C) 2015 Spreadtrum
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

#include "../sprdfb_chip_common.h"
#include "../sprdfb.h"
#include "../sprdfb_panel.h"

#define printk printf

#ifdef DEBUG
#define  LCD_DEBUG
#endif
#ifdef LCD_DEBUG
#define LCD_PRINT printk
#else
#define LCD_PRINT(...)
#endif

#define MAX_DATA   10

typedef struct LCM_Init_Code_tag {
	unsigned int tag;
	unsigned char data[MAX_DATA];
}LCM_Init_Code;

typedef struct LCM_force_cmd_code_tag{
	unsigned int datatype;
	LCM_Init_Code real_cmd_code;
}LCM_Force_Cmd_Code;

#define LCM_TAG_SHIFT 24
#define LCM_TAG_MASK  ((1 << 24) -1)
#define LCM_SEND(len) ((1 << LCM_TAG_SHIFT)| len)
#define LCM_SLEEP(ms) ((2 << LCM_TAG_SHIFT)| ms)

#define LCM_TAG_SEND  (1<< 0)
#define LCM_TAG_SLEEP (1 << 1)

static LCM_Init_Code init_data[] = {
{LCM_SEND(2), {0xFF, 0xEE}},
{LCM_SEND(2), {0x18, 0x40}},
{LCM_SLEEP(10)},
{LCM_SEND(2), {0x18, 0x00}},
{LCM_SLEEP(20)},

//CMD2_P0
{LCM_SEND(2), {0xFF, 0x01}},
{LCM_SEND(2), {0xFB, 0x01}},


{LCM_SEND(2), {0x00, 0x01}},
{LCM_SEND(2), {0x01, 0x55}},
{LCM_SEND(2), {0x02, 0x40}},

// VGH CHARGE PUMP 2XAVDD AVEE-VCI1
{LCM_SEND(2), {0x05, 0x40}},


//VGH SEL TO 8V
{LCM_SEND(2), {0x06, 0x94}},
//VGL SEL TO -7V
{LCM_SEND(2), {0x07, 0x94}},
{LCM_SEND(2), {0x08, 0x0C}},


//VCOM SEL
{LCM_SEND(2), {0x11, 0x19}},
{LCM_SEND(2), {0x12, 0x19}},
{LCM_SEND(2), {0x13, 0x03}},

//VGH
{LCM_SEND(2), {0x14, 0x94}},

//AVDDR SEL TO 5.0V
{LCM_SEND(2), {0x15, 0x15}},
//AVEER SEL TO -5.0V
{LCM_SEND(2), {0x16, 0x15}},
{LCM_SEND(2), {0x6D, 0x22}},

//GVDDP SEL TO 4.6V
{LCM_SEND(2), {0x0B, 0xAF}},
//GVDDN SEL TO -4.6V
{LCM_SEND(2), {0x0C, 0xAF}},

//VGHO SEL TO 8.0V
{LCM_SEND(2), {0x0E, 0xAB}},
//VGLO SEL TO -7.0 V
{LCM_SEND(2), {0x0F, 0xA4}},



//GATE_EQ
{LCM_SEND(2), {0x58, 0x82}},
{LCM_SEND(2), {0x59, 0x02}},
{LCM_SEND(2), {0x5A, 0x02}},
{LCM_SEND(2), {0x5B, 0x02}},
{LCM_SEND(2), {0x5C, 0x82}},
{LCM_SEND(2), {0x5D, 0x82}},
{LCM_SEND(2), {0x5E, 0x02}},
{LCM_SEND(2), {0x5F, 0x02}},

//gamma  R(+/-);G(+) 3/2 ADD
{LCM_SEND(2), {0x75, 0x00}},
{LCM_SEND(2), {0x76, 0x00}},
{LCM_SEND(2), {0x77, 0x00}},
{LCM_SEND(2), {0x78, 0x11}},
{LCM_SEND(2), {0x79, 0x00}},
{LCM_SEND(2), {0x7A, 0x30}},
{LCM_SEND(2), {0x7B, 0x00}},
{LCM_SEND(2), {0x7C, 0x4A}},
{LCM_SEND(2), {0x7D, 0x00}},
{LCM_SEND(2), {0x7E, 0x62}},
{LCM_SEND(2), {0x7F, 0x00}},
{LCM_SEND(2), {0x80, 0x78}},
{LCM_SEND(2), {0x81, 0x00}},
{LCM_SEND(2), {0x82, 0x8C}},
{LCM_SEND(2), {0x83, 0x00}},
{LCM_SEND(2), {0x84, 0x9E}},
{LCM_SEND(2), {0x85, 0x00}},
{LCM_SEND(2), {0x86, 0xAE}},
{LCM_SEND(2), {0x87, 0x00}},
{LCM_SEND(2), {0x88, 0xE4}},
{LCM_SEND(2), {0x89, 0x01}},
{LCM_SEND(2), {0x8A, 0x0E}},
{LCM_SEND(2), {0x8B, 0x01}},
{LCM_SEND(2), {0x8C, 0x4C}},
{LCM_SEND(2), {0x8D, 0x01}},
{LCM_SEND(2), {0x8E, 0x7B}},
{LCM_SEND(2), {0x8F, 0x01}},
{LCM_SEND(2), {0x90, 0xC2}},
{LCM_SEND(2), {0x91, 0x01}},
{LCM_SEND(2), {0x92, 0xFB}},
{LCM_SEND(2), {0x93, 0x01}},
{LCM_SEND(2), {0x94, 0xFC}},
{LCM_SEND(2), {0x95, 0x02}},
{LCM_SEND(2), {0x96, 0x34}},
{LCM_SEND(2), {0x97, 0x02}},
{LCM_SEND(2), {0x98, 0x79}},
{LCM_SEND(2), {0x99, 0x02}},
{LCM_SEND(2), {0x9A, 0xA4}},
{LCM_SEND(2), {0x9B, 0x02}},
{LCM_SEND(2), {0x9C, 0xDD}},
{LCM_SEND(2), {0x9D, 0x03}},
{LCM_SEND(2), {0x9E, 0x05}},
{LCM_SEND(2), {0x9F, 0x03}},
{LCM_SEND(2), {0xA0, 0x39}},
{LCM_SEND(2), {0xA2, 0x03}},
{LCM_SEND(2), {0xA3, 0x48}},
{LCM_SEND(2), {0xA4, 0x03}},
{LCM_SEND(2), {0xA5, 0x58}},
{LCM_SEND(2), {0xA6, 0x03}},
{LCM_SEND(2), {0xA7, 0x6A}},
{LCM_SEND(2), {0xA9, 0x03}},
{LCM_SEND(2), {0xAA, 0x7F}},
{LCM_SEND(2), {0xAB, 0x03}},
{LCM_SEND(2), {0xAC, 0x98}},
{LCM_SEND(2), {0xAD, 0x03}},
{LCM_SEND(2), {0xAE, 0xB7}},
{LCM_SEND(2), {0xAF, 0x03}},
{LCM_SEND(2), {0xB0, 0xD7}},
{LCM_SEND(2), {0xB1, 0x03}},
{LCM_SEND(2), {0xB2, 0xFF}},
//R(-)
{LCM_SEND(2), {0xB3, 0x00}},
{LCM_SEND(2), {0xB4, 0x00}},
{LCM_SEND(2), {0xB5, 0x00}},
{LCM_SEND(2), {0xB6, 0x11}},
{LCM_SEND(2), {0xB7, 0x00}},
{LCM_SEND(2), {0xB8, 0x30}},
{LCM_SEND(2), {0xB9, 0x00}},
{LCM_SEND(2), {0xBA, 0x4A}},
{LCM_SEND(2), {0xBB, 0x00}},
{LCM_SEND(2), {0xBC, 0x62}},
{LCM_SEND(2), {0xBD, 0x00}},
{LCM_SEND(2), {0xBE, 0x78}},
{LCM_SEND(2), {0xBF, 0x00}},
{LCM_SEND(2), {0xC0, 0x8C}},
{LCM_SEND(2), {0xC1, 0x00}},
{LCM_SEND(2), {0xC2, 0x9E}},
{LCM_SEND(2), {0xC3, 0x00}},
{LCM_SEND(2), {0xC4, 0xAE}},
{LCM_SEND(2), {0xC5, 0x00}},
{LCM_SEND(2), {0xC6, 0xE4}},
{LCM_SEND(2), {0xC7, 0x01}},
{LCM_SEND(2), {0xC8, 0x0E}},
{LCM_SEND(2), {0xC9, 0x01}},
{LCM_SEND(2), {0xCA, 0x4C}},
{LCM_SEND(2), {0xCB, 0x01}},
{LCM_SEND(2), {0xCC, 0x7B}},
{LCM_SEND(2), {0xCD, 0x01}},
{LCM_SEND(2), {0xCE, 0xC2}},
{LCM_SEND(2), {0xCF, 0x01}},
{LCM_SEND(2), {0xD0, 0xFB}},
{LCM_SEND(2), {0xD1, 0x01}},
{LCM_SEND(2), {0xD2, 0xFC}},
{LCM_SEND(2), {0xD3, 0x02}},
{LCM_SEND(2), {0xD4, 0x34}},
{LCM_SEND(2), {0xD5, 0x02}},
{LCM_SEND(2), {0xD6, 0x79}},
{LCM_SEND(2), {0xD7, 0x02}},
{LCM_SEND(2), {0xD8, 0xA4}},
{LCM_SEND(2), {0xD9, 0x02}},
{LCM_SEND(2), {0xDA, 0xDD}},
{LCM_SEND(2), {0xDB, 0x03}},
{LCM_SEND(2), {0xDC, 0x05}},
{LCM_SEND(2), {0xDD, 0x03}},
{LCM_SEND(2), {0xDE, 0x39}},
{LCM_SEND(2), {0xDF, 0x03}},
{LCM_SEND(2), {0xE0, 0x48}},
{LCM_SEND(2), {0xE1, 0x03}},
{LCM_SEND(2), {0xE2, 0x58}},
{LCM_SEND(2), {0xE3, 0x03}},
{LCM_SEND(2), {0xE4, 0x6A}},
{LCM_SEND(2), {0xE5, 0x03}},
{LCM_SEND(2), {0xE6, 0x7F}},
{LCM_SEND(2), {0xE7, 0x03}},
{LCM_SEND(2), {0xE8, 0x98}},
{LCM_SEND(2), {0xE9, 0x03}},
{LCM_SEND(2), {0xEA, 0xB7}},
{LCM_SEND(2), {0xEB, 0x03}},
{LCM_SEND(2), {0xEC, 0xD7}},
{LCM_SEND(2), {0xED, 0x03}},
{LCM_SEND(2), {0xEE, 0xFF}},
//G(+)
{LCM_SEND(2), {0xEF, 0x00}},
{LCM_SEND(2), {0xF0, 0x00}},
{LCM_SEND(2), {0xF1, 0x00}},
{LCM_SEND(2), {0xF2, 0x11}},
{LCM_SEND(2), {0xF3, 0x00}},
{LCM_SEND(2), {0xF4, 0x30}},
{LCM_SEND(2), {0xF5, 0x00}},
{LCM_SEND(2), {0xF6, 0x4A}},
{LCM_SEND(2), {0xF7, 0x00}},
{LCM_SEND(2), {0xF8, 0x62}},
{LCM_SEND(2), {0xF9, 0x00}},
{LCM_SEND(2), {0xFA, 0x78}},

//CMD2_P0
{LCM_SEND(2), {0xFF, 0x02}},
{LCM_SEND(2), {0xFB, 0x01}},

{LCM_SEND(2), {0x00, 0x00}},
{LCM_SEND(2), {0x01, 0x8C}},
{LCM_SEND(2), {0x02, 0x00}},
{LCM_SEND(2), {0x03, 0x9E}},
{LCM_SEND(2), {0x04, 0x00}},
{LCM_SEND(2), {0x05, 0xAE}},
{LCM_SEND(2), {0x06, 0x00}},
{LCM_SEND(2), {0x07, 0xE4}},
{LCM_SEND(2), {0x08, 0x01}},
{LCM_SEND(2), {0x09, 0x0E}},
{LCM_SEND(2), {0x0A, 0x01}},
{LCM_SEND(2), {0x0B, 0x4C}},
{LCM_SEND(2), {0x0C, 0x01}},
{LCM_SEND(2), {0x0D, 0x7B}},
{LCM_SEND(2), {0x0E, 0x01}},
{LCM_SEND(2), {0x0F, 0xC2}},
{LCM_SEND(2), {0x10, 0x01}},
{LCM_SEND(2), {0x11, 0xFB}},
{LCM_SEND(2), {0x12, 0x01}},
{LCM_SEND(2), {0x13, 0xFC}},
{LCM_SEND(2), {0x14, 0x02}},
{LCM_SEND(2), {0x15, 0x34}},
{LCM_SEND(2), {0x16, 0x02}},
{LCM_SEND(2), {0x17, 0x79}},
{LCM_SEND(2), {0x18, 0x02}},
{LCM_SEND(2), {0x19, 0xA4}},
{LCM_SEND(2), {0x1A, 0x02}},
{LCM_SEND(2), {0x1B, 0xDD}},
{LCM_SEND(2), {0x1C, 0x03}},
{LCM_SEND(2), {0x1D, 0x05}},
{LCM_SEND(2), {0x1E, 0x03}},
{LCM_SEND(2), {0x1F, 0x39}},
{LCM_SEND(2), {0x20, 0x03}},
{LCM_SEND(2), {0x21, 0x48}},
{LCM_SEND(2), {0x22, 0x03}},
{LCM_SEND(2), {0x23, 0x58}},
{LCM_SEND(2), {0x24, 0x03}},
{LCM_SEND(2), {0x25, 0x6A}},
{LCM_SEND(2), {0x26, 0x03}},
{LCM_SEND(2), {0x27, 0x7F}},
{LCM_SEND(2), {0x28, 0x03}},
{LCM_SEND(2), {0x29, 0x98}},
{LCM_SEND(2), {0x2A, 0x03}},
{LCM_SEND(2), {0x2B, 0xB7}},
{LCM_SEND(2), {0x2D, 0x03}},
{LCM_SEND(2), {0x2F, 0xD7}},
{LCM_SEND(2), {0x30, 0x03}},
{LCM_SEND(2), {0x31, 0xFF}},
//G(-)
{LCM_SEND(2), {0x32, 0x00}},
{LCM_SEND(2), {0x33, 0x00}},
{LCM_SEND(2), {0x34, 0x00}},
{LCM_SEND(2), {0x35, 0x11}},
{LCM_SEND(2), {0x36, 0x00}},
{LCM_SEND(2), {0x37, 0x30}},
{LCM_SEND(2), {0x38, 0x00}},
{LCM_SEND(2), {0x39, 0x4A}},
{LCM_SEND(2), {0x3A, 0x00}},
{LCM_SEND(2), {0x3B, 0x62}},
{LCM_SEND(2), {0x3D, 0x00}},
{LCM_SEND(2), {0x3F, 0x78}},
{LCM_SEND(2), {0x40, 0x00}},
{LCM_SEND(2), {0x41, 0x8C}},
{LCM_SEND(2), {0x42, 0x00}},
{LCM_SEND(2), {0x43, 0x9E}},
{LCM_SEND(2), {0x44, 0x00}},
{LCM_SEND(2), {0x45, 0xAE}},
{LCM_SEND(2), {0x46, 0x00}},
{LCM_SEND(2), {0x47, 0xE4}},
{LCM_SEND(2), {0x48, 0x01}},
{LCM_SEND(2), {0x49, 0x0E}},
{LCM_SEND(2), {0x4A, 0x01}},
{LCM_SEND(2), {0x4B, 0x4C}},
{LCM_SEND(2), {0x4C, 0x01}},
{LCM_SEND(2), {0x4D, 0x7B}},
{LCM_SEND(2), {0x4E, 0x01}},
{LCM_SEND(2), {0x4F, 0xC2}},
{LCM_SEND(2), {0x50, 0x01}},
{LCM_SEND(2), {0x51, 0xFB}},
{LCM_SEND(2), {0x52, 0x01}},
{LCM_SEND(2), {0x53, 0xFC}},
{LCM_SEND(2), {0x54, 0x02}},
{LCM_SEND(2), {0x55, 0x34}},
{LCM_SEND(2), {0x56, 0x02}},
{LCM_SEND(2), {0x58, 0x79}},
{LCM_SEND(2), {0x59, 0x02}},
{LCM_SEND(2), {0x5A, 0xA4}},
{LCM_SEND(2), {0x5B, 0x02}},
{LCM_SEND(2), {0x5C, 0xDD}},
{LCM_SEND(2), {0x5D, 0x03}},
{LCM_SEND(2), {0x5E, 0x05}},
{LCM_SEND(2), {0x5F, 0x03}},
{LCM_SEND(2), {0x60, 0x39}},
{LCM_SEND(2), {0x61, 0x03}},
{LCM_SEND(2), {0x62, 0x48}},
{LCM_SEND(2), {0x63, 0x03}},
{LCM_SEND(2), {0x64, 0x58}},
{LCM_SEND(2), {0x65, 0x03}},
{LCM_SEND(2), {0x66, 0x6A}},
{LCM_SEND(2), {0x67, 0x03}},
{LCM_SEND(2), {0x68, 0x7F}},
{LCM_SEND(2), {0x69, 0x03}},
{LCM_SEND(2), {0x6A, 0x98}},
{LCM_SEND(2), {0x6B, 0x03}},
{LCM_SEND(2), {0x6C, 0xB7}},
{LCM_SEND(2), {0x6D, 0x03}},
{LCM_SEND(2), {0x6E, 0xD7}},
{LCM_SEND(2), {0x6F, 0x03}},
{LCM_SEND(2), {0x70, 0xFF}},
//B(+)
{LCM_SEND(2), {0x71, 0x00}},
{LCM_SEND(2), {0x72, 0x00}},
{LCM_SEND(2), {0x73, 0x00}},
{LCM_SEND(2), {0x74, 0x11}},
{LCM_SEND(2), {0x75, 0x00}},
{LCM_SEND(2), {0x76, 0x30}},
{LCM_SEND(2), {0x77, 0x00}},
{LCM_SEND(2), {0x78, 0x4A}},
{LCM_SEND(2), {0x79, 0x00}},
{LCM_SEND(2), {0x7A, 0x62}},
{LCM_SEND(2), {0x7B, 0x00}},
{LCM_SEND(2), {0x7C, 0x78}},
{LCM_SEND(2), {0x7D, 0x00}},
{LCM_SEND(2), {0x7E, 0x8C}},
{LCM_SEND(2), {0x7F, 0x00}},
{LCM_SEND(2), {0x80, 0x9E}},
{LCM_SEND(2), {0x81, 0x00}},
{LCM_SEND(2), {0x82, 0xAE}},
{LCM_SEND(2), {0x83, 0x00}},
{LCM_SEND(2), {0x84, 0xE4}},
{LCM_SEND(2), {0x85, 0x01}},
{LCM_SEND(2), {0x86, 0x0E}},
{LCM_SEND(2), {0x87, 0x01}},
{LCM_SEND(2), {0x88, 0x4C}},
{LCM_SEND(2), {0x89, 0x01}},
{LCM_SEND(2), {0x8A, 0x7B}},
{LCM_SEND(2), {0x8B, 0x01}},
{LCM_SEND(2), {0x8C, 0xC2}},
{LCM_SEND(2), {0x8D, 0x01}},
{LCM_SEND(2), {0x8E, 0xFB}},
{LCM_SEND(2), {0x8F, 0x01}},
{LCM_SEND(2), {0x90, 0xFC}},
{LCM_SEND(2), {0x91, 0x02}},
{LCM_SEND(2), {0x92, 0x34}},
{LCM_SEND(2), {0x93, 0x02}},
{LCM_SEND(2), {0x94, 0x79}},
{LCM_SEND(2), {0x95, 0x02}},
{LCM_SEND(2), {0x96, 0xA4}},
{LCM_SEND(2), {0x97, 0x02}},
{LCM_SEND(2), {0x98, 0xDD}},
{LCM_SEND(2), {0x99, 0x03}},
{LCM_SEND(2), {0x9A, 0x05}},
{LCM_SEND(2), {0x9B, 0x03}},
{LCM_SEND(2), {0x9C, 0x39}},
{LCM_SEND(2), {0x9D, 0x03}},
{LCM_SEND(2), {0x9E, 0x48}},
{LCM_SEND(2), {0x9F, 0x03}},
{LCM_SEND(2), {0xA0, 0x58}},
{LCM_SEND(2), {0xA2, 0x03}},
{LCM_SEND(2), {0xA3, 0x6A}},
{LCM_SEND(2), {0xA4, 0x03}},
{LCM_SEND(2), {0xA5, 0x7F}},
{LCM_SEND(2), {0xA6, 0x03}},
{LCM_SEND(2), {0xA7, 0x98}},
{LCM_SEND(2), {0xA9, 0x03}},
{LCM_SEND(2), {0xAA, 0xB7}},
{LCM_SEND(2), {0xAB, 0x03}},
{LCM_SEND(2), {0xAC, 0xD7}},
{LCM_SEND(2), {0xAD, 0x03}},
{LCM_SEND(2), {0xAE, 0xFF}},
//B(-)
{LCM_SEND(2), {0xAF, 0x00}},
{LCM_SEND(2), {0xB0, 0x00}},
{LCM_SEND(2), {0xB1, 0x00}},
{LCM_SEND(2), {0xB2, 0x11}},
{LCM_SEND(2), {0xB3, 0x00}},
{LCM_SEND(2), {0xB4, 0x30}},
{LCM_SEND(2), {0xB5, 0x00}},
{LCM_SEND(2), {0xB6, 0x4A}},
{LCM_SEND(2), {0xB7, 0x00}},
{LCM_SEND(2), {0xB8, 0x62}},
{LCM_SEND(2), {0xB9, 0x00}},
{LCM_SEND(2), {0xBA, 0x78}},
{LCM_SEND(2), {0xBB, 0x00}},
{LCM_SEND(2), {0xBC, 0x8C}},
{LCM_SEND(2), {0xBD, 0x00}},
{LCM_SEND(2), {0xBE, 0x9E}},
{LCM_SEND(2), {0xBF, 0x00}},
{LCM_SEND(2), {0xC0, 0xAE}},
{LCM_SEND(2), {0xC1, 0x00}},
{LCM_SEND(2), {0xC2, 0xE4}},
{LCM_SEND(2), {0xC3, 0x01}},
{LCM_SEND(2), {0xC4, 0x0E}},
{LCM_SEND(2), {0xC5, 0x01}},
{LCM_SEND(2), {0xC6, 0x4C}},
{LCM_SEND(2), {0xC7, 0x01}},
{LCM_SEND(2), {0xC8, 0x7B}},
{LCM_SEND(2), {0xC9, 0x01}},
{LCM_SEND(2), {0xCA, 0xC2}},
{LCM_SEND(2), {0xCB, 0x01}},
{LCM_SEND(2), {0xCC, 0xFB}},
{LCM_SEND(2), {0xCD, 0x01}},
{LCM_SEND(2), {0xCE, 0xFC}},
{LCM_SEND(2), {0xCF, 0x02}},
{LCM_SEND(2), {0xD0, 0x34}},
{LCM_SEND(2), {0xD1, 0x02}},
{LCM_SEND(2), {0xD2, 0x79}},
{LCM_SEND(2), {0xD3, 0x02}},
{LCM_SEND(2), {0xD4, 0xA4}},
{LCM_SEND(2), {0xD5, 0x02}},
{LCM_SEND(2), {0xD6, 0xDD}},
{LCM_SEND(2), {0xD7, 0x03}},
{LCM_SEND(2), {0xD8, 0x05}},
{LCM_SEND(2), {0xD9, 0x03}},
{LCM_SEND(2), {0xDA, 0x39}},
{LCM_SEND(2), {0xDB, 0x03}},
{LCM_SEND(2), {0xDC, 0x48}},
{LCM_SEND(2), {0xDD, 0x03}},
{LCM_SEND(2), {0xDE, 0x58}},
{LCM_SEND(2), {0xDF, 0x03}},
{LCM_SEND(2), {0xE0, 0x6A}},
{LCM_SEND(2), {0xE1, 0x03}},
{LCM_SEND(2), {0xE2, 0x7F}},
{LCM_SEND(2), {0xE3, 0x03}},
{LCM_SEND(2), {0xE4, 0x98}},
{LCM_SEND(2), {0xE5, 0x03}},
{LCM_SEND(2), {0xE6, 0xB7}},
{LCM_SEND(2), {0xE7, 0x03}},
{LCM_SEND(2), {0xE8, 0xD7}},
{LCM_SEND(2), {0xE9, 0x03}},
{LCM_SEND(2), {0xEA, 0xFF}},

//ccmoff
//ccmrun


//CMD2_P4
{LCM_SEND(2), {0xFF, 0x05}},
{LCM_SEND(2), {0xFB, 0x01}},
//ccmon
//CGOUT
{LCM_SEND(2), {0x00, 0x00}},
{LCM_SEND(2), {0x01, 0x01}},
{LCM_SEND(2), {0x02, 0x0B}},  //0c/2.10
{LCM_SEND(2), {0x03, 0x0C}},  //0b/2.10
{LCM_SEND(2), {0x04, 0x00}},
{LCM_SEND(2), {0x05, 0x03}},
{LCM_SEND(2), {0x06, 0x00}},
{LCM_SEND(2), {0x07, 0x04}},
{LCM_SEND(2), {0x08, 0x00}},
{LCM_SEND(2), {0x09, 0x00}},
{LCM_SEND(2), {0x0A, 0x00}},
{LCM_SEND(2), {0x0B, 0x00}},
{LCM_SEND(2), {0x0C, 0x00}},
{LCM_SEND(2), {0x0D, 0x17}},
{LCM_SEND(2), {0x0E, 0x15}},
{LCM_SEND(2), {0x0F, 0x13}},
{LCM_SEND(2), {0x10, 0x00}},
{LCM_SEND(2), {0x11, 0x01}},
{LCM_SEND(2), {0x12, 0x0B}},  //0C/2.10
{LCM_SEND(2), {0x13, 0x0C}},  //0B/2.10
{LCM_SEND(2), {0x14, 0x00}},
{LCM_SEND(2), {0x15, 0x03}},
{LCM_SEND(2), {0x16, 0x00}},
{LCM_SEND(2), {0x17, 0x04}},
{LCM_SEND(2), {0x18, 0x00}},
{LCM_SEND(2), {0x19, 0x00}},
{LCM_SEND(2), {0x1A, 0x00}},
{LCM_SEND(2), {0x1B, 0x00}},
{LCM_SEND(2), {0x1C, 0x00}},
{LCM_SEND(2), {0x1D, 0x17}},
{LCM_SEND(2), {0x1E, 0x15}},
{LCM_SEND(2), {0x1F, 0x13}},

//STV;
{LCM_SEND(2), {0x20, 0x09}},
{LCM_SEND(2), {0x21, 0x02}},
{LCM_SEND(2), {0x22, 0x00}},
{LCM_SEND(2), {0x23, 0x00}},
{LCM_SEND(2), {0x24, 0x00}},
{LCM_SEND(2), {0x25, 0x3D}},



//UD;
{LCM_SEND(2), {0x29, 0x38}},
{LCM_SEND(2), {0x2A, 0x2B}},


//GCKS;
{LCM_SEND(2), {0x2F, 0x02}},
{LCM_SEND(2), {0x30, 0x01}},  //por
{LCM_SEND(2), {0x31, 0x49}},
{LCM_SEND(2), {0x32, 0x23}},
{LCM_SEND(2), {0x33, 0x01}},
{LCM_SEND(2), {0x34, 0x05}},
{LCM_SEND(2), {0x35, 0x74}},
{LCM_SEND(2), {0x36, 0x00}},
{LCM_SEND(2), {0x37, 0x2D}},
{LCM_SEND(2), {0x38, 0x08}},
{LCM_SEND(2), {0x92, 0x94}},  //RTN

//CTRL1
{LCM_SEND(2), {0x5B, 0x00}},
{LCM_SEND(2), {0x5F, 0x1D}},
{LCM_SEND(2), {0x63, 0x00}},
{LCM_SEND(2), {0x67, 0x04}},
{LCM_SEND(2), {0x6C, 0x55}},

//MUX;
{LCM_SEND(2), {0x7A, 0x00}},
{LCM_SEND(2), {0x7B, 0xA2}},
{LCM_SEND(2), {0x7C, 0xD8}},
{LCM_SEND(2), {0x7D, 0x50}},
{LCM_SEND(2), {0x7E, 0x0A}},
{LCM_SEND(2), {0x7F, 0x1C}},
{LCM_SEND(2), {0x81, 0x06}},  //MUX
{LCM_SEND(2), {0x82, 0x02}},  //MUX
{LCM_SEND(2), {0x84, 0x03}},
{LCM_SEND(2), {0x85, 0x05}},

{LCM_SEND(2), {0xC5, 0x20}},

//Source EQ;
{LCM_SEND(2), {0x80, 0x00}},
{LCM_SEND(2), {0x83, 0x00}},

//FP  BP;
{LCM_SEND(2), {0x93, 0x08}},
{LCM_SEND(2), {0x94, 0x0A}},

//Inversion T4pe
{LCM_SEND(2), {0x8A, 0x33}},
{LCM_SEND(2), {0xA4, 0x0F}},
{LCM_SEND(2), {0x9B, 0x0F}},

//Scan Type
{LCM_SEND(2), {0x9D, 0xB0}},
//CMD_9D_1DATA4 DBH 9D,B6

//VIDEO DROP
{LCM_SEND(2), {0xE7, 0x83}},

//CMD_EC_1DATA4 DBH EC,00

{LCM_SEND(2), {0xE3, 0x02}},

//CMD1
{LCM_SEND(2), {0xFF, 0x00}},
//CMD_FB_1DATA1 DBH FB,01
{LCM_SEND(2), {0xD2, 0x03}},
{LCM_SEND(2), {0xD3, 0x0E}},//vsync + vbp
{LCM_SEND(2), {0xD4, 0x06}},//vfp
{LCM_SEND(2), {0x35, 0x00}},
//{LCM_SEND(2), {0x36, 0xC0}},  //2/15 ADD



{LCM_SEND(2), {0xBA, 0x03}},

{LCM_SEND(1), {0x11}}, //Sleep Out
{LCM_SLEEP(120)},
{LCM_SEND(1), {0x29}}, //Display On

//{LCM_SEND(2), {0xFF, 0x05}},
//{LCM_SEND(2), {0xEC, 0x01}},


};


static LCM_Force_Cmd_Code rd_prep_code[]={
//	{0x39, {LCM_SEND(8), {0x6, 0, 0xF0, 0x55, 0xAA, 0x52, 0x08, 0x01}}},
	{0x37, {LCM_SEND(2), {0x3, 0}}},
};

static int32_t nt35596_mipi_init(struct panel_spec *self)
{
	int32_t i = 0;
	LCM_Init_Code *init = init_data;
	unsigned int tag;

	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_gen_write_t mipi_gen_write = self->info.mipi->ops->mipi_gen_write;

	mipi_set_hs_mode_t mipi_set_hs_mode = self->info.mipi->ops->mipi_set_hs_mode;

	LCD_PRINT("sprdfb:nt35596_mipi_init\n");

	//mipi_set_hs_mode();
	mipi_set_cmd_mode();

	for(i = 0; i < ARRAY_SIZE(init_data); i++){
		tag = (init->tag >>24);
		if(tag & LCM_TAG_SEND){
			mipi_gen_write(init->data, (init->tag & LCM_TAG_MASK));
			udelay(20);
		}else if(tag & LCM_TAG_SLEEP){
			mdelay((init->tag & LCM_TAG_MASK));
		}
		init++;
	}
	return 0;
}

static uint32_t nt35596_readid(struct panel_spec *self)
{
	int32_t i = 0;
	uint32_t j =0;
	LCM_Force_Cmd_Code * rd_prepare = rd_prep_code;
	uint8_t read_data[3] = {0};
	int32_t read_rtn = 0;
	unsigned int tag = 0;
	mipi_set_cmd_mode_t mipi_set_cmd_mode = self->info.mipi->ops->mipi_set_cmd_mode;
	mipi_force_write_t mipi_force_write = self->info.mipi->ops->mipi_force_write;
	mipi_force_read_t mipi_force_read = self->info.mipi->ops->mipi_force_read;
	mipi_eotp_set_t mipi_eotp_set = self->info.mipi->ops->mipi_eotp_set;

	LCD_PRINT("sprdfb:lcd_nt35596_mipi read id!\n");

	mipi_set_cmd_mode();
	mipi_eotp_set(0,1);

	for(j = 0; j < 4; j++){
		rd_prepare = rd_prep_code;
		for(i = 0; i < ARRAY_SIZE(rd_prep_code); i++){
			tag = (rd_prepare->real_cmd_code.tag >> 24);
			if(tag & LCM_TAG_SEND){
				mipi_force_write(rd_prepare->datatype, rd_prepare->real_cmd_code.data, (rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}else if(tag & LCM_TAG_SLEEP){
				mdelay((rd_prepare->real_cmd_code.tag & LCM_TAG_MASK));
			}
			rd_prepare++;
		}
		read_rtn = mipi_force_read(0xF4, 1,(uint8_t *)read_data);
		debugf("lcd_nt35596_mipi read id 0xF4 value is 0x%x, 0x%x, 0x%x!\n", read_data[0], read_data[1], read_data[2]);

		if(0x96 == read_data[0]){
			debugf("lcd_nt35596_mipi read id success!\n");
			mipi_eotp_set(1,1);

			i2c_set_bus_num(4);
			if (0x0A != i2c_reg_read(0x3E, 0x00)) {
				i2c_reg_write(0x3E, 0x00, 0x0A);
				i2c_reg_write(0x3E, 0x01, 0x0A);
				i2c_reg_write(0x3E, 0x03, 0x03);
				i2c_reg_write(0x3E, 0xFF, 0x80);
				mdelay(50);
			}

			return 0x96;
		}
	}
	mipi_eotp_set(1,1);
	return 0x0;
}

int32_t nt35596_reset(struct panel_spec *self)
{
	sprd_gpio_request(NULL, LCM_GPIO_AVDDEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_AVDDEN, 1);
	mdelay(10);

	sprd_gpio_request(NULL, LCM_GPIO_AVEEEN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_AVEEEN, 1);
	mdelay(20);

	sprd_gpio_request(NULL, LCM_GPIO_RSTN);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 0);
	mdelay(5);
	sprd_gpio_direction_output(NULL, LCM_GPIO_RSTN, 1);
	mdelay(20);

	return 0;
}

static struct panel_operations lcd_nt35596_mipi_operations = {
	.panel_init = nt35596_mipi_init,
	.panel_readid = nt35596_readid,
	.panel_reset = nt35596_reset,
};

static struct timing_rgb lcd_nt35596_mipi_timing = {
	.hfp = 6,  /* unit: pixel */
	.hbp = 6,
	.hsync = 8,
	.vfp = 6, /*unit: line*/
	.vbp = 6,
	.vsync = 8,
};

static struct info_mipi lcd_nt35596_mipi_info = {
	.work_mode  = SPRDFB_MIPI_MODE_VIDEO,
	.video_bus_width = 24, /*18,16*/
	.lan_number = 4,
	.phy_feq = 1000*1000,
	.h_sync_pol = SPRDFB_POLARITY_POS,
	.v_sync_pol = SPRDFB_POLARITY_POS,
	.de_pol = SPRDFB_POLARITY_POS,
	.te_pol = SPRDFB_POLARITY_POS,
	.color_mode_pol = SPRDFB_POLARITY_NEG,
	.shut_down_pol = SPRDFB_POLARITY_NEG,
	.timing = &lcd_nt35596_mipi_timing,
	.ops = NULL,
};

struct panel_spec lcd_nt35596_mipi_spec = {
	.width = 1080,
	.height = 1920,
	.fps = 60,
	.type = LCD_MODE_DSI,
	.direction = LCD_DIRECT_NORMAL,
	.is_need_reset = 1,
	.info = {
		.mipi = &lcd_nt35596_mipi_info
	},
	.ops = &lcd_nt35596_mipi_operations,
};

