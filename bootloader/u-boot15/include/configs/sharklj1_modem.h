/*
 * (C) Copyright 2009 DENX Software Engineering
 * Author: John Rigby <jrigby@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston,
 * MA 02111-1307 USA
 */

#ifndef __CONFIG_MODEM_H
#define __CONFIG_MODEM_H

#define CONFIG_KERNEL_BOOT_CP

#define CONFIG_MEM_LAYOUT_DECOUPLING
#define CONFIG_DECOUPLING_NO_SURPPORT_RSVMEM


//#define DFS_ON_ARM7
#define DFS_PARAM_SRC_ADDR     0x0001c0c
#define DFS_PARAM_TARGET_ADDR  0x50805400
#define DFS_PARAM_LEN  0x400

//#define CONFIG_SUPPORT_TDLTE
#define CONFIG_SUPPORT_LTE
//#define CONFIG_SUPPORT_WLTE
//#define CONFIG_SUPPORT_GSM

#define LTE_GDSP_LOAD_OFFSET	0x20000

#define LTE_FIXNV_SIZE 0x000c8000 // 800K the max size is 3.75M
#define LTE_RUNNV_SIZE 0x000e8000 // 928k the max size is 4M
#define LTE_FIXNV_ADDR 0x8d3a0000
#define LTE_RUNNV_ADDR (LTE_FIXNV_ADDR + LTE_FIXNV_SIZE)
#define LTE_MODEM_SIZE 0x00D00000
#define LTE_MODEM_ADDR 0x8b800000
#define LTE_LDSP_SIZE  0x00c00000
#define LTE_LDSP_ADDR  0x89D00000
#define LTE_GDSP_SIZE  0x00600000
#define LTE_GDSP_ADDR (0x89600000 + LTE_GDSP_LOAD_OFFSET)

#define LTE_CP_CMDLINE_ADDR 0x8d7d0000
#define CALIBRATION_FLAG_CP1  LTE_CP_CMDLINE_ADDR

#define FIXNV_SIZE     LTE_FIXNV_SIZE

#define CONFIG_DFS_ENABLE
#define DFS_ADDR    0x50800000
#define DFS_SIZE    0xC000     //48K

#define DSP_BOOT_IRAM_START   0x5001F000//2k
#define LDSP_SHARE_MEM_START  0x5001F800//10k
#define TGDSP_SHARE_MEM_START 0x50022000//4k
#define MULTI_MODE_MEM_START  0x50023000//4k

/*active arm7 ram before access to it*/
#define CONFIG_ARM7_RAM_ACTIVE

#endif /* __CONFIG_MODEM_H */

