/*
 * Copyright (C) 2018 Unigroup Spreadtrum & RDA Technologies Co., Ltd.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 * updated at 2018-12-18 10:55:38
 *
 */


#ifndef SLV_FW_IPA1_H
#define SLV_FW_IPA1_H

#define CTL_BASE_SLV_FW_IPA1 0x32832000


#define REG_SLV_FW_IPA1_PORT0_DEFAULT_ADDRESS_0  ( CTL_BASE_SLV_FW_IPA1 + 0x0000 )
#define REG_SLV_FW_IPA1_PORT0_DEFAULT_ADDRESS_1  ( CTL_BASE_SLV_FW_IPA1 + 0x0004 )
#define REG_SLV_FW_IPA1_PORT1_DEFAULT_ADDRESS_0  ( CTL_BASE_SLV_FW_IPA1 + 0x0008 )
#define REG_SLV_FW_IPA1_PORT1_DEFAULT_ADDRESS_1  ( CTL_BASE_SLV_FW_IPA1 + 0x000C )
#define REG_SLV_FW_IPA1_PORT2_DEFAULT_ADDRESS_0  ( CTL_BASE_SLV_FW_IPA1 + 0x0010 )
#define REG_SLV_FW_IPA1_PORT2_DEFAULT_ADDRESS_1  ( CTL_BASE_SLV_FW_IPA1 + 0x0014 )
#define REG_SLV_FW_IPA1_PORT_INT_EN              ( CTL_BASE_SLV_FW_IPA1 + 0x0018 )
#define REG_SLV_FW_IPA1_PORT_INT_CLR             ( CTL_BASE_SLV_FW_IPA1 + 0x001C )
#define REG_SLV_FW_IPA1_PORT_INT_RAW             ( CTL_BASE_SLV_FW_IPA1 + 0x0020 )
#define REG_SLV_FW_IPA1_PORT_INT_FIN             ( CTL_BASE_SLV_FW_IPA1 + 0x0024 )
#define REG_SLV_FW_IPA1_RD_SEC_0                 ( CTL_BASE_SLV_FW_IPA1 + 0x0028 )
#define REG_SLV_FW_IPA1_RD_SEC_1                 ( CTL_BASE_SLV_FW_IPA1 + 0x002C )
#define REG_SLV_FW_IPA1_WR_SEC_0                 ( CTL_BASE_SLV_FW_IPA1 + 0x0030 )
#define REG_SLV_FW_IPA1_WR_SEC_1                 ( CTL_BASE_SLV_FW_IPA1 + 0x0034 )
#define REG_SLV_FW_IPA1_ID0_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0038 )
#define REG_SLV_FW_IPA1_ID0_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x003C )
#define REG_SLV_FW_IPA1_ID0_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x0040 )
#define REG_SLV_FW_IPA1_ID0_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x0044 )
#define REG_SLV_FW_IPA1_ID0_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x0048 )
#define REG_SLV_FW_IPA1_ID0_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x004C )
#define REG_SLV_FW_IPA1_ID0_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x0050 )
#define REG_SLV_FW_IPA1_ID0_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x0054 )
#define REG_SLV_FW_IPA1_ID0_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x0058 )
#define REG_SLV_FW_IPA1_ID0_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x005C )
#define REG_SLV_FW_IPA1_ID0_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x0060 )
#define REG_SLV_FW_IPA1_ID0_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x0064 )
#define REG_SLV_FW_IPA1_ID1_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0068 )
#define REG_SLV_FW_IPA1_ID1_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x006C )
#define REG_SLV_FW_IPA1_ID1_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x0070 )
#define REG_SLV_FW_IPA1_ID1_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x0074 )
#define REG_SLV_FW_IPA1_ID1_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x0078 )
#define REG_SLV_FW_IPA1_ID1_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x007C )
#define REG_SLV_FW_IPA1_ID1_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x0080 )
#define REG_SLV_FW_IPA1_ID1_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x0084 )
#define REG_SLV_FW_IPA1_ID1_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x0088 )
#define REG_SLV_FW_IPA1_ID1_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x008C )
#define REG_SLV_FW_IPA1_ID1_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x0090 )
#define REG_SLV_FW_IPA1_ID1_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x0094 )
#define REG_SLV_FW_IPA1_ID2_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0098 )
#define REG_SLV_FW_IPA1_ID2_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x009C )
#define REG_SLV_FW_IPA1_ID2_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x00A0 )
#define REG_SLV_FW_IPA1_ID2_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x00A4 )
#define REG_SLV_FW_IPA1_ID2_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x00A8 )
#define REG_SLV_FW_IPA1_ID2_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x00AC )
#define REG_SLV_FW_IPA1_ID2_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x00B0 )
#define REG_SLV_FW_IPA1_ID2_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x00B4 )
#define REG_SLV_FW_IPA1_ID2_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x00B8 )
#define REG_SLV_FW_IPA1_ID2_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x00BC )
#define REG_SLV_FW_IPA1_ID2_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x00C0 )
#define REG_SLV_FW_IPA1_ID2_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x00C4 )
#define REG_SLV_FW_IPA1_ID3_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x00C8 )
#define REG_SLV_FW_IPA1_ID3_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x00CC )
#define REG_SLV_FW_IPA1_ID3_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x00D0 )
#define REG_SLV_FW_IPA1_ID3_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x00D4 )
#define REG_SLV_FW_IPA1_ID3_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x00D8 )
#define REG_SLV_FW_IPA1_ID3_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x00DC )
#define REG_SLV_FW_IPA1_ID3_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x00E0 )
#define REG_SLV_FW_IPA1_ID3_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x00E4 )
#define REG_SLV_FW_IPA1_ID3_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x00E8 )
#define REG_SLV_FW_IPA1_ID3_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x00EC )
#define REG_SLV_FW_IPA1_ID3_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x00F0 )
#define REG_SLV_FW_IPA1_ID3_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x00F4 )
#define REG_SLV_FW_IPA1_ID4_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x00F8 )
#define REG_SLV_FW_IPA1_ID4_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x00FC )
#define REG_SLV_FW_IPA1_ID4_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x0100 )
#define REG_SLV_FW_IPA1_ID4_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x0104 )
#define REG_SLV_FW_IPA1_ID4_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x0108 )
#define REG_SLV_FW_IPA1_ID4_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x010C )
#define REG_SLV_FW_IPA1_ID4_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x0110 )
#define REG_SLV_FW_IPA1_ID4_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x0114 )
#define REG_SLV_FW_IPA1_ID4_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x0118 )
#define REG_SLV_FW_IPA1_ID4_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x011C )
#define REG_SLV_FW_IPA1_ID4_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x0120 )
#define REG_SLV_FW_IPA1_ID4_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x0124 )
#define REG_SLV_FW_IPA1_ID5_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0128 )
#define REG_SLV_FW_IPA1_ID5_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x012C )
#define REG_SLV_FW_IPA1_ID5_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x0130 )
#define REG_SLV_FW_IPA1_ID5_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x0134 )
#define REG_SLV_FW_IPA1_ID5_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x0138 )
#define REG_SLV_FW_IPA1_ID5_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x013C )
#define REG_SLV_FW_IPA1_ID5_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x0140 )
#define REG_SLV_FW_IPA1_ID5_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x0144 )
#define REG_SLV_FW_IPA1_ID5_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x0148 )
#define REG_SLV_FW_IPA1_ID5_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x014C )
#define REG_SLV_FW_IPA1_ID5_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x0150 )
#define REG_SLV_FW_IPA1_ID5_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x0154 )
#define REG_SLV_FW_IPA1_ID6_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0158 )
#define REG_SLV_FW_IPA1_ID6_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x015C )
#define REG_SLV_FW_IPA1_ID6_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x0160 )
#define REG_SLV_FW_IPA1_ID6_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x0164 )
#define REG_SLV_FW_IPA1_ID6_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x0168 )
#define REG_SLV_FW_IPA1_ID6_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x016C )
#define REG_SLV_FW_IPA1_ID6_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x0170 )
#define REG_SLV_FW_IPA1_ID6_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x0174 )
#define REG_SLV_FW_IPA1_ID6_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x0178 )
#define REG_SLV_FW_IPA1_ID6_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x017C )
#define REG_SLV_FW_IPA1_ID6_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x0180 )
#define REG_SLV_FW_IPA1_ID6_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x0184 )
#define REG_SLV_FW_IPA1_ID7_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0188 )
#define REG_SLV_FW_IPA1_ID7_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x018C )
#define REG_SLV_FW_IPA1_ID7_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x0190 )
#define REG_SLV_FW_IPA1_ID7_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x0194 )
#define REG_SLV_FW_IPA1_ID7_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x0198 )
#define REG_SLV_FW_IPA1_ID7_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x019C )
#define REG_SLV_FW_IPA1_ID7_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x01A0 )
#define REG_SLV_FW_IPA1_ID7_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x01A4 )
#define REG_SLV_FW_IPA1_ID7_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x01A8 )
#define REG_SLV_FW_IPA1_ID7_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x01AC )
#define REG_SLV_FW_IPA1_ID7_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x01B0 )
#define REG_SLV_FW_IPA1_ID7_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x01B4 )
#define REG_SLV_FW_IPA1_ID8_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x01B8 )
#define REG_SLV_FW_IPA1_ID8_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x01BC )
#define REG_SLV_FW_IPA1_ID8_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x01C0 )
#define REG_SLV_FW_IPA1_ID8_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x01C4 )
#define REG_SLV_FW_IPA1_ID8_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x01C8 )
#define REG_SLV_FW_IPA1_ID8_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x01CC )
#define REG_SLV_FW_IPA1_ID8_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x01D0 )
#define REG_SLV_FW_IPA1_ID8_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x01D4 )
#define REG_SLV_FW_IPA1_ID8_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x01D8 )
#define REG_SLV_FW_IPA1_ID8_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x01DC )
#define REG_SLV_FW_IPA1_ID8_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x01E0 )
#define REG_SLV_FW_IPA1_ID8_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x01E4 )
#define REG_SLV_FW_IPA1_ID9_FIRST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x01E8 )
#define REG_SLV_FW_IPA1_ID9_FIRST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x01EC )
#define REG_SLV_FW_IPA1_ID9_LAST_ADDR_0          ( CTL_BASE_SLV_FW_IPA1 + 0x01F0 )
#define REG_SLV_FW_IPA1_ID9_LAST_ADDR_1          ( CTL_BASE_SLV_FW_IPA1 + 0x01F4 )
#define REG_SLV_FW_IPA1_ID9_MSTID_0              ( CTL_BASE_SLV_FW_IPA1 + 0x01F8 )
#define REG_SLV_FW_IPA1_ID9_MSTID_1              ( CTL_BASE_SLV_FW_IPA1 + 0x01FC )
#define REG_SLV_FW_IPA1_ID9_MSTID_2              ( CTL_BASE_SLV_FW_IPA1 + 0x0200 )
#define REG_SLV_FW_IPA1_ID9_MSTID_3              ( CTL_BASE_SLV_FW_IPA1 + 0x0204 )
#define REG_SLV_FW_IPA1_ID9_MSTID_4              ( CTL_BASE_SLV_FW_IPA1 + 0x0208 )
#define REG_SLV_FW_IPA1_ID9_MSTID_5              ( CTL_BASE_SLV_FW_IPA1 + 0x020C )
#define REG_SLV_FW_IPA1_ID9_MSTID_6              ( CTL_BASE_SLV_FW_IPA1 + 0x0210 )
#define REG_SLV_FW_IPA1_ID9_MSTID_7              ( CTL_BASE_SLV_FW_IPA1 + 0x0214 )
#define REG_SLV_FW_IPA1_ID10_FIRST_ADDR_0        ( CTL_BASE_SLV_FW_IPA1 + 0x0218 )
#define REG_SLV_FW_IPA1_ID10_FIRST_ADDR_1        ( CTL_BASE_SLV_FW_IPA1 + 0x021C )
#define REG_SLV_FW_IPA1_ID10_LAST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0220 )
#define REG_SLV_FW_IPA1_ID10_LAST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x0224 )
#define REG_SLV_FW_IPA1_ID10_MSTID_0             ( CTL_BASE_SLV_FW_IPA1 + 0x0228 )
#define REG_SLV_FW_IPA1_ID10_MSTID_1             ( CTL_BASE_SLV_FW_IPA1 + 0x022C )
#define REG_SLV_FW_IPA1_ID10_MSTID_2             ( CTL_BASE_SLV_FW_IPA1 + 0x0230 )
#define REG_SLV_FW_IPA1_ID10_MSTID_3             ( CTL_BASE_SLV_FW_IPA1 + 0x0234 )
#define REG_SLV_FW_IPA1_ID10_MSTID_4             ( CTL_BASE_SLV_FW_IPA1 + 0x0238 )
#define REG_SLV_FW_IPA1_ID10_MSTID_5             ( CTL_BASE_SLV_FW_IPA1 + 0x023C )
#define REG_SLV_FW_IPA1_ID10_MSTID_6             ( CTL_BASE_SLV_FW_IPA1 + 0x0240 )
#define REG_SLV_FW_IPA1_ID10_MSTID_7             ( CTL_BASE_SLV_FW_IPA1 + 0x0244 )
#define REG_SLV_FW_IPA1_ID11_FIRST_ADDR_0        ( CTL_BASE_SLV_FW_IPA1 + 0x0248 )
#define REG_SLV_FW_IPA1_ID11_FIRST_ADDR_1        ( CTL_BASE_SLV_FW_IPA1 + 0x024C )
#define REG_SLV_FW_IPA1_ID11_LAST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0250 )
#define REG_SLV_FW_IPA1_ID11_LAST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x0254 )
#define REG_SLV_FW_IPA1_ID11_MSTID_0             ( CTL_BASE_SLV_FW_IPA1 + 0x0258 )
#define REG_SLV_FW_IPA1_ID11_MSTID_1             ( CTL_BASE_SLV_FW_IPA1 + 0x025C )
#define REG_SLV_FW_IPA1_ID11_MSTID_2             ( CTL_BASE_SLV_FW_IPA1 + 0x0260 )
#define REG_SLV_FW_IPA1_ID11_MSTID_3             ( CTL_BASE_SLV_FW_IPA1 + 0x0264 )
#define REG_SLV_FW_IPA1_ID11_MSTID_4             ( CTL_BASE_SLV_FW_IPA1 + 0x0268 )
#define REG_SLV_FW_IPA1_ID11_MSTID_5             ( CTL_BASE_SLV_FW_IPA1 + 0x026C )
#define REG_SLV_FW_IPA1_ID11_MSTID_6             ( CTL_BASE_SLV_FW_IPA1 + 0x0270 )
#define REG_SLV_FW_IPA1_ID11_MSTID_7             ( CTL_BASE_SLV_FW_IPA1 + 0x0274 )
#define REG_SLV_FW_IPA1_ID12_FIRST_ADDR_0        ( CTL_BASE_SLV_FW_IPA1 + 0x0278 )
#define REG_SLV_FW_IPA1_ID12_FIRST_ADDR_1        ( CTL_BASE_SLV_FW_IPA1 + 0x027C )
#define REG_SLV_FW_IPA1_ID12_LAST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0280 )
#define REG_SLV_FW_IPA1_ID12_LAST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x0284 )
#define REG_SLV_FW_IPA1_ID12_MSTID_0             ( CTL_BASE_SLV_FW_IPA1 + 0x0288 )
#define REG_SLV_FW_IPA1_ID12_MSTID_1             ( CTL_BASE_SLV_FW_IPA1 + 0x028C )
#define REG_SLV_FW_IPA1_ID12_MSTID_2             ( CTL_BASE_SLV_FW_IPA1 + 0x0290 )
#define REG_SLV_FW_IPA1_ID12_MSTID_3             ( CTL_BASE_SLV_FW_IPA1 + 0x0294 )
#define REG_SLV_FW_IPA1_ID12_MSTID_4             ( CTL_BASE_SLV_FW_IPA1 + 0x0298 )
#define REG_SLV_FW_IPA1_ID12_MSTID_5             ( CTL_BASE_SLV_FW_IPA1 + 0x029C )
#define REG_SLV_FW_IPA1_ID12_MSTID_6             ( CTL_BASE_SLV_FW_IPA1 + 0x02A0 )
#define REG_SLV_FW_IPA1_ID12_MSTID_7             ( CTL_BASE_SLV_FW_IPA1 + 0x02A4 )
#define REG_SLV_FW_IPA1_ID13_FIRST_ADDR_0        ( CTL_BASE_SLV_FW_IPA1 + 0x02A8 )
#define REG_SLV_FW_IPA1_ID13_FIRST_ADDR_1        ( CTL_BASE_SLV_FW_IPA1 + 0x02AC )
#define REG_SLV_FW_IPA1_ID13_LAST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x02B0 )
#define REG_SLV_FW_IPA1_ID13_LAST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x02B4 )
#define REG_SLV_FW_IPA1_ID13_MSTID_0             ( CTL_BASE_SLV_FW_IPA1 + 0x02B8 )
#define REG_SLV_FW_IPA1_ID13_MSTID_1             ( CTL_BASE_SLV_FW_IPA1 + 0x02BC )
#define REG_SLV_FW_IPA1_ID13_MSTID_2             ( CTL_BASE_SLV_FW_IPA1 + 0x02C0 )
#define REG_SLV_FW_IPA1_ID13_MSTID_3             ( CTL_BASE_SLV_FW_IPA1 + 0x02C4 )
#define REG_SLV_FW_IPA1_ID13_MSTID_4             ( CTL_BASE_SLV_FW_IPA1 + 0x02C8 )
#define REG_SLV_FW_IPA1_ID13_MSTID_5             ( CTL_BASE_SLV_FW_IPA1 + 0x02CC )
#define REG_SLV_FW_IPA1_ID13_MSTID_6             ( CTL_BASE_SLV_FW_IPA1 + 0x02D0 )
#define REG_SLV_FW_IPA1_ID13_MSTID_7             ( CTL_BASE_SLV_FW_IPA1 + 0x02D4 )
#define REG_SLV_FW_IPA1_ID14_FIRST_ADDR_0        ( CTL_BASE_SLV_FW_IPA1 + 0x02D8 )
#define REG_SLV_FW_IPA1_ID14_FIRST_ADDR_1        ( CTL_BASE_SLV_FW_IPA1 + 0x02DC )
#define REG_SLV_FW_IPA1_ID14_LAST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x02E0 )
#define REG_SLV_FW_IPA1_ID14_LAST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x02E4 )
#define REG_SLV_FW_IPA1_ID14_MSTID_0             ( CTL_BASE_SLV_FW_IPA1 + 0x02E8 )
#define REG_SLV_FW_IPA1_ID14_MSTID_1             ( CTL_BASE_SLV_FW_IPA1 + 0x02EC )
#define REG_SLV_FW_IPA1_ID14_MSTID_2             ( CTL_BASE_SLV_FW_IPA1 + 0x02F0 )
#define REG_SLV_FW_IPA1_ID14_MSTID_3             ( CTL_BASE_SLV_FW_IPA1 + 0x02F4 )
#define REG_SLV_FW_IPA1_ID14_MSTID_4             ( CTL_BASE_SLV_FW_IPA1 + 0x02F8 )
#define REG_SLV_FW_IPA1_ID14_MSTID_5             ( CTL_BASE_SLV_FW_IPA1 + 0x02FC )
#define REG_SLV_FW_IPA1_ID14_MSTID_6             ( CTL_BASE_SLV_FW_IPA1 + 0x0300 )
#define REG_SLV_FW_IPA1_ID14_MSTID_7             ( CTL_BASE_SLV_FW_IPA1 + 0x0304 )
#define REG_SLV_FW_IPA1_ID15_FIRST_ADDR_0        ( CTL_BASE_SLV_FW_IPA1 + 0x0308 )
#define REG_SLV_FW_IPA1_ID15_FIRST_ADDR_1        ( CTL_BASE_SLV_FW_IPA1 + 0x030C )
#define REG_SLV_FW_IPA1_ID15_LAST_ADDR_0         ( CTL_BASE_SLV_FW_IPA1 + 0x0310 )
#define REG_SLV_FW_IPA1_ID15_LAST_ADDR_1         ( CTL_BASE_SLV_FW_IPA1 + 0x0314 )
#define REG_SLV_FW_IPA1_ID15_MSTID_0             ( CTL_BASE_SLV_FW_IPA1 + 0x0318 )
#define REG_SLV_FW_IPA1_ID15_MSTID_1             ( CTL_BASE_SLV_FW_IPA1 + 0x031C )
#define REG_SLV_FW_IPA1_ID15_MSTID_2             ( CTL_BASE_SLV_FW_IPA1 + 0x0320 )
#define REG_SLV_FW_IPA1_ID15_MSTID_3             ( CTL_BASE_SLV_FW_IPA1 + 0x0324 )
#define REG_SLV_FW_IPA1_ID15_MSTID_4             ( CTL_BASE_SLV_FW_IPA1 + 0x0328 )
#define REG_SLV_FW_IPA1_ID15_MSTID_5             ( CTL_BASE_SLV_FW_IPA1 + 0x032C )
#define REG_SLV_FW_IPA1_ID15_MSTID_6             ( CTL_BASE_SLV_FW_IPA1 + 0x0330 )
#define REG_SLV_FW_IPA1_ID15_MSTID_7             ( CTL_BASE_SLV_FW_IPA1 + 0x0334 )

/* REG_SLV_FW_IPA1_PORT0_DEFAULT_ADDRESS_0 */

#define BIT_SLV_FW_IPA1_PORT0_DEFAULT_ADDRESS_0_PORT0_DEFAULT_ADDRESS_0(x)  (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_PORT0_DEFAULT_ADDRESS_1 */

#define BIT_SLV_FW_IPA1_PORT0_DEFAULT_ADDRESS_1_PORT0_DEFAULT_ADDRESS_1(x)  (((x) & 0x3))

/* REG_SLV_FW_IPA1_PORT1_DEFAULT_ADDRESS_0 */

#define BIT_SLV_FW_IPA1_PORT1_DEFAULT_ADDRESS_0_PORT1_DEFAULT_ADDRESS_0(x)  (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_PORT1_DEFAULT_ADDRESS_1 */

#define BIT_SLV_FW_IPA1_PORT1_DEFAULT_ADDRESS_1_PORT1_DEFAULT_ADDRESS_1(x)  (((x) & 0x3))

/* REG_SLV_FW_IPA1_PORT2_DEFAULT_ADDRESS_0 */

#define BIT_SLV_FW_IPA1_PORT2_DEFAULT_ADDRESS_0_PORT2_DEFAULT_ADDRESS_0(x)  (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_PORT2_DEFAULT_ADDRESS_1 */

#define BIT_SLV_FW_IPA1_PORT2_DEFAULT_ADDRESS_1_PORT2_DEFAULT_ADDRESS_1(x)  (((x) & 0x3))

/* REG_SLV_FW_IPA1_PORT_INT_EN */

#define BIT_SLV_FW_IPA1_PORT_INT_EN_PORT_2_R_EN                             BIT(5)
#define BIT_SLV_FW_IPA1_PORT_INT_EN_PORT_2_W_EN                             BIT(4)
#define BIT_SLV_FW_IPA1_PORT_INT_EN_PORT_1_R_EN                             BIT(3)
#define BIT_SLV_FW_IPA1_PORT_INT_EN_PORT_1_W_EN                             BIT(2)
#define BIT_SLV_FW_IPA1_PORT_INT_EN_PORT_0_R_EN                             BIT(1)
#define BIT_SLV_FW_IPA1_PORT_INT_EN_PORT_0_W_EN                             BIT(0)

/* REG_SLV_FW_IPA1_PORT_INT_CLR */

#define BIT_SLV_FW_IPA1_PORT_INT_CLR_PORT_2_R_CLR                           BIT(5)
#define BIT_SLV_FW_IPA1_PORT_INT_CLR_PORT_2_W_CLR                           BIT(4)
#define BIT_SLV_FW_IPA1_PORT_INT_CLR_PORT_1_R_CLR                           BIT(3)
#define BIT_SLV_FW_IPA1_PORT_INT_CLR_PORT_1_W_CLR                           BIT(2)
#define BIT_SLV_FW_IPA1_PORT_INT_CLR_PORT_0_R_CLR                           BIT(1)
#define BIT_SLV_FW_IPA1_PORT_INT_CLR_PORT_0_W_CLR                           BIT(0)

/* REG_SLV_FW_IPA1_PORT_INT_RAW */

#define BIT_SLV_FW_IPA1_PORT_INT_RAW_PORT_2_R_RAW                           BIT(5)
#define BIT_SLV_FW_IPA1_PORT_INT_RAW_PORT_2_W_RAW                           BIT(4)
#define BIT_SLV_FW_IPA1_PORT_INT_RAW_PORT_1_R_RAW                           BIT(3)
#define BIT_SLV_FW_IPA1_PORT_INT_RAW_PORT_1_W_RAW                           BIT(2)
#define BIT_SLV_FW_IPA1_PORT_INT_RAW_PORT_0_R_RAW                           BIT(1)
#define BIT_SLV_FW_IPA1_PORT_INT_RAW_PORT_0_W_RAW                           BIT(0)

/* REG_SLV_FW_IPA1_PORT_INT_FIN */

#define BIT_SLV_FW_IPA1_PORT_INT_FIN_PORT_2_R_FIN                           BIT(5)
#define BIT_SLV_FW_IPA1_PORT_INT_FIN_PORT_2_W_FIN                           BIT(4)
#define BIT_SLV_FW_IPA1_PORT_INT_FIN_PORT_1_R_FIN                           BIT(3)
#define BIT_SLV_FW_IPA1_PORT_INT_FIN_PORT_1_W_FIN                           BIT(2)
#define BIT_SLV_FW_IPA1_PORT_INT_FIN_PORT_0_R_FIN                           BIT(1)
#define BIT_SLV_FW_IPA1_PORT_INT_FIN_PORT_0_W_FIN                           BIT(0)

/* REG_SLV_FW_IPA1_RD_SEC_0 */

#define BIT_SLV_FW_IPA1_RD_SEC_0_PCIE3_REG_RD_SEC(x)                        (((x) & 0x3) << 30)
#define BIT_SLV_FW_IPA1_RD_SEC_0_BUSMON_PERF_PAM_U3_RD_SEC(x)               (((x) & 0x3) << 28)
#define BIT_SLV_FW_IPA1_RD_SEC_0_BUSMON_PERF_PAM_IPA_RD_SEC(x)              (((x) & 0x3) << 26)
#define BIT_SLV_FW_IPA1_RD_SEC_0_BUSMON_PERF_IPA_TOP_RD_SEC(x)              (((x) & 0x3) << 24)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_INTC_RD_SEC(x)                         (((x) & 0x3) << 22)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_UART_RD_SEC(x)                         (((x) & 0x3) << 20)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_TIMER_RD_SEC(x)                        (((x) & 0x3) << 18)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_WDG_RD_SEC(x)                          (((x) & 0x3) << 16)
#define BIT_SLV_FW_IPA1_RD_SEC_0_USB3_AHB_REG_RD_SEC(x)                     (((x) & 0x3) << 14)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_CM4_CACHE_REG_RD_SEC(x)                (((x) & 0x3) << 12)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_AHB_REG_RD_SEC(x)                      (((x) & 0x3) << 10)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_CLK_REG_RD_SEC(x)                      (((x) & 0x3) << 8)
#define BIT_SLV_FW_IPA1_RD_SEC_0_PAM_U3_APB_RD_SEC(x)                       (((x) & 0x3) << 6)
#define BIT_SLV_FW_IPA1_RD_SEC_0_PAM_IPA_APB_RD_SEC(x)                      (((x) & 0x3) << 4)
#define BIT_SLV_FW_IPA1_RD_SEC_0_IPA_S0_APB_RD_SEC(x)                       (((x) & 0x3) << 2)
#define BIT_SLV_FW_IPA1_RD_SEC_0_PAM_WIFI_APB_RD_SEC(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_RD_SEC_1 */

#define BIT_SLV_FW_IPA1_RD_SEC_1_IRAM_64K_RD_SEC(x)                         (((x) & 0x3) << 8)
#define BIT_SLV_FW_IPA1_RD_SEC_1_IRAM_RD_SEC(x)                             (((x) & 0x3) << 6)
#define BIT_SLV_FW_IPA1_RD_SEC_1_PCIE2_SLV_RD_SEC(x)                        (((x) & 0x3) << 4)
#define BIT_SLV_FW_IPA1_RD_SEC_1_PCIE3_SLV_RD_SEC(x)                        (((x) & 0x3) << 2)
#define BIT_SLV_FW_IPA1_RD_SEC_1_PCIE2_REG_RD_SEC(x)                        (((x) & 0x3))

/* REG_SLV_FW_IPA1_WR_SEC_0 */

#define BIT_SLV_FW_IPA1_WR_SEC_0_PCIE3_REG_WR_SEC(x)                        (((x) & 0x3) << 30)
#define BIT_SLV_FW_IPA1_WR_SEC_0_BUSMON_PERF_PAM_U3_WR_SEC(x)               (((x) & 0x3) << 28)
#define BIT_SLV_FW_IPA1_WR_SEC_0_BUSMON_PERF_PAM_IPA_WR_SEC(x)              (((x) & 0x3) << 26)
#define BIT_SLV_FW_IPA1_WR_SEC_0_BUSMON_PERF_IPA_TOP_WR_SEC(x)              (((x) & 0x3) << 24)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_INTC_WR_SEC(x)                         (((x) & 0x3) << 22)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_UART_WR_SEC(x)                         (((x) & 0x3) << 20)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_TIMER_WR_SEC(x)                        (((x) & 0x3) << 18)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_WDG_WR_SEC(x)                          (((x) & 0x3) << 16)
#define BIT_SLV_FW_IPA1_WR_SEC_0_USB3_AHB_REG_WR_SEC(x)                     (((x) & 0x3) << 14)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_CM4_CACHE_REG_WR_SEC(x)                (((x) & 0x3) << 12)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_AHB_REG_WR_SEC(x)                      (((x) & 0x3) << 10)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_CLK_REG_WR_SEC(x)                      (((x) & 0x3) << 8)
#define BIT_SLV_FW_IPA1_WR_SEC_0_PAM_U3_APB_WR_SEC(x)                       (((x) & 0x3) << 6)
#define BIT_SLV_FW_IPA1_WR_SEC_0_PAM_IPA_APB_WR_SEC(x)                      (((x) & 0x3) << 4)
#define BIT_SLV_FW_IPA1_WR_SEC_0_IPA_S0_APB_WR_SEC(x)                       (((x) & 0x3) << 2)
#define BIT_SLV_FW_IPA1_WR_SEC_0_PAM_WIFI_APB_WR_SEC(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_WR_SEC_1 */

#define BIT_SLV_FW_IPA1_WR_SEC_1_IRAM_64K_WR_SEC(x)                         (((x) & 0x3) << 8)
#define BIT_SLV_FW_IPA1_WR_SEC_1_IRAM_WR_SEC(x)                             (((x) & 0x3) << 6)
#define BIT_SLV_FW_IPA1_WR_SEC_1_PCIE2_SLV_WR_SEC(x)                        (((x) & 0x3) << 4)
#define BIT_SLV_FW_IPA1_WR_SEC_1_PCIE3_SLV_WR_SEC(x)                        (((x) & 0x3) << 2)
#define BIT_SLV_FW_IPA1_WR_SEC_1_PCIE2_REG_WR_SEC(x)                        (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID0_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID0_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID0_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID0_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID0_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID0_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID0_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID0_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID0_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID1_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID1_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID1_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID1_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID1_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID1_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID1_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID1_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID2_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID2_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID2_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID2_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID2_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID2_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID2_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID2_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID3_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID3_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID3_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID3_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID3_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID3_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID3_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID3_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID4_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID4_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID4_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID4_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID4_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID4_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID4_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID4_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID5_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID5_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID5_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID5_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID5_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID5_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID5_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID5_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID6_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID6_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID6_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID6_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID6_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID6_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID6_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID6_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID7_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID7_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID7_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID7_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID7_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID7_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID7_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID7_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID8_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID8_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID8_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID8_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID8_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID8_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID8_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID8_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID9_FIRST_ADDR_0_FIRST_ADDR_0(x)                    (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID9_FIRST_ADDR_1_FIRST_ADDR_1(x)                    (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID9_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID9_LAST_ADDR_0_LAST_ADDR_0(x)                      (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID9_LAST_ADDR_1_LAST_ADDR_1(x)                      (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID9_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_0_MSTID_0(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_1_MSTID_1(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_2_MSTID_2(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_3_MSTID_3(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_4_MSTID_4(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_5_MSTID_5(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_6_MSTID_6(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID9_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID9_MSTID_7_MSTID_7(x)                              (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID10_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID10_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID10_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID10_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID10_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID10_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID10_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID10_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID11_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID11_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID11_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID11_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID11_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID11_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID11_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID11_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID12_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID12_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID12_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID12_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID12_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID12_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID12_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID12_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID13_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID13_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID13_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID13_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID13_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID13_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID13_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID13_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID14_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID14_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID14_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID14_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID14_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID14_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID14_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID14_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_FIRST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID15_FIRST_ADDR_0_FIRST_ADDR_0(x)                   (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_FIRST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID15_FIRST_ADDR_1_FIRST_ADDR_1(x)                   (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID15_LAST_ADDR_0 */

#define BIT_SLV_FW_IPA1_ID15_LAST_ADDR_0_LAST_ADDR_0(x)                     (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_LAST_ADDR_1 */

#define BIT_SLV_FW_IPA1_ID15_LAST_ADDR_1_LAST_ADDR_1(x)                     (((x) & 0x3))

/* REG_SLV_FW_IPA1_ID15_MSTID_0 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_0_MSTID_0(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_MSTID_1 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_1_MSTID_1(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_MSTID_2 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_2_MSTID_2(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_MSTID_3 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_3_MSTID_3(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_MSTID_4 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_4_MSTID_4(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_MSTID_5 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_5_MSTID_5(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_MSTID_6 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_6_MSTID_6(x)                             (((x) & 0xFFFFFFFF))

/* REG_SLV_FW_IPA1_ID15_MSTID_7 */

#define BIT_SLV_FW_IPA1_ID15_MSTID_7_MSTID_7(x)                             (((x) & 0xFFFFFFFF))


#endif /* SLV_FW_IPA1_H */


