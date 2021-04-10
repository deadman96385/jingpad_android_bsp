// Copyright (C) 2018 Spreadtrum Communications Inc.

#ifndef __HW_MUX_CFG_H__
#define __HW_MUX_CFG_H__

#include <asm/arch/pinmap.h>

#define SPRD_MAGIC_HEADER		0x5555aaaa
#define SPRD_MAGIC_END			0xaaaa5555
#define SPRD_MAX_SYS_NAME_LEN		20
#define SPRD_UART_MUX_VERSION		0x0000

#define SPRD_MAX_UART_CTRL_NUM		16
#define SPRD_MAX_UART_PORT_NUM		11
#define SPRD_MAX_UPORT_SEL_NUM		15

typedef struct {
	uint32_t index;
	uint32_t reg;
	uint32_t select;
	char name[SPRD_MAX_UPORT_SEL_NUM][SPRD_MAX_SYS_NAME_LEN];
} pin_uart_port_sel_t;

typedef struct {
	uint32_t magic_header;
	uint32_t version;
	uint32_t uart_port_num;
	pin_uart_port_sel_t port[SPRD_MAX_UART_PORT_NUM];
	uint32_t magic_end;
} pin_mux;

#endif
