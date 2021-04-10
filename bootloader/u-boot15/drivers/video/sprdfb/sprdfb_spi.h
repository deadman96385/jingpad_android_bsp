#ifndef _SPRDFB_SPI_H_
#define _SPRDFB_SPI_H_

#define SPI_TX_FIFO_DEPTH 		16
#define SPI_RX_FIFO_DEPTH 		16

typedef unsigned char			uint8;
typedef unsigned long int		uint32;

typedef enum
{
	TX_POS_EDGE = 0,
	TX_NEG_EDGE
}TX_EDGE;

typedef enum
{
	RX_POS_EDGE = 0,
	RX_NEG_EDGE
}RX_EDGE;

typedef enum
{
	TX_RX_MSB = 0,
	TX_RX_LSB
}MSB_LSB_SEL;

typedef enum
{
	IDLE_MODE = 0,
	RX_MODE,
	TX_MODE,
	RX_TX_MODE
}TRANCIEVE_MODE;

typedef enum
{
	NO_SWITCH    = 0,
	BYTE_SWITCH  = 1,
	HWORD_SWITCH = 2
}SWT_MODE;

typedef enum
{
	MASTER_MODE = 0,
	SLAVE_MODE = 1
}SPI_OPERATE_MODE_E;

typedef struct _init_param
{
	TX_EDGE tx_edge;
	RX_EDGE rx_edge;
	MSB_LSB_SEL msb_lsb_sel;
	TRANCIEVE_MODE tx_rx_mode;
	SWT_MODE switch_mode;
	SPI_OPERATE_MODE_E op_mode;
	uint32 DMAsrcSize;
	uint32 DMAdesSize;
	uint32 clk_div;
	uint8 data_width;
	uint8 tx_empty_watermark;
	uint8 tx_full_watermark;
	uint8 rx_empty_watermark;
	uint8 rx_full_watermark;
}SPI_INIT_PARM,*SPI_INIT_PARM_P;

#endif
