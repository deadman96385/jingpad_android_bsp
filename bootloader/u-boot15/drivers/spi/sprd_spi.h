/******************************************************************************
 ** File Name:    sprd_spi.h                                        *
 ** Author:       mengkai.zhao                                      *
 ** DATE:         2017-08-01                                        *
 ** Copyright:    2017 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 **    DATE         NAME            DESCRIPTION                    *
 ** 2017-08-01   mengkai.zhao       First Draft
 ******************************************************************************/

#ifndef __SPRD_SPI_H__
#define __SPRD_SPI_H__

/*The register offset*/
#define SPI_TXD			0x0000
#define SPI_CLKD		0x0004
#define SPI_CTL0		0x0008
#define SPI_CTL1		0x000C
#define SPI_CTL2		0x0010
#define SPI_CTL3		0x0014
#define SPI_CTL4		0x0018
#define SPI_CTL5		0x001C
#define SPI_INT_EN		0x0020
#define SPI_INT_CLR		0x0024
#define SPI_INT_RAW_STS		0x0028
#define SPI_INT_MASK_STS	0x002C
#define SPI_STS1		0x0030
#define SPI_STS2		0x0034
#define SPI_DSP_WAIT		0x0038
#define SPI_STS3		0x003C
#define SPI_CTL6		0x0040
#define SPI_STS4		0x0044
#define SPI_FIFO_RST		0x0048
#define SPI_CTL7		0x004C
#define SPI_STS5		0x0050
#define SPI_CTL8		0x0054
#define SPI_CTL9		0x0058
#define SPI_CTL10		0x005C
#define SPI_CTL11		0x0060
#define SPI_CTL12		0x0064
#define SPI_STS6		0x0068
#define SPI_STS7		0x006C
#define SPI_STS8		0x0070
#define SPI_STS9		0x0074

/* Bit define for register INT_RAW_STS */
#define SPI_RX_FIFO_EMPTY_RAW_STS	BIT(1)
#define SPI_TX_FIFO_FULL_RAW_STS	BIT(2)
#define SPI_RX_FIFO_OVERRUN_RAW_STS	BIT(4)
#define SPI_TIME_OUT_RAW_STS		BIT(5)
#define SPI_RX_FIFO_FULL_RAW_STS	BIT(6)
#define SPI_TX_FIFO_EMPTY_RAW_STS	BIT(7)
#define SPI_TX_END_RAW_STS		BIT(8)
#define SPI_RX_END_RAW_STS		BIT(9)

/* Bit define for register INT_CLR */
#define SPI_RX_FIFO_FULL_CLR		BIT(0)
#define SPI_RX_FIFO_EMPTY_CLR		BIT(1)
#define SPI_TX_FIFO_FULL_CLR		BIT(2)
#define SPI_TX_FIFO_EMPTY_CLR		BIT(3)
#define SPI_RX_FIFO_OVERRUN_CLR		BIT(4)
#define SPI_TIME_OUT_CLR		BIT(5)
#define SPI_TX_END_CLR			BIT(8)
#define SPI_RX_END_CLR			BIT(9)
#define SPI_ALL_INT_CLR			0xFFFFFFFF


/* Bit define for register STS2 */
/*
#define SPI_RX_FIFO_FULL		BIT(0)
#define SPI_RX_FIFO_EMPTY		BIT(1)
#define SPI_TX_FIFO_FULL		BIT(2)
#define SPI_TX_FIFO_EMPTY		BIT(3)
#define SPI_RX_FIFO_REALLY_FULL		BIT(4)
#define SPI_RX_FIFO_REALLY_EMPTY	BIT(5)
#define SPI_TX_FIFO_REALLY_FULL		BIT(6)
#define SPI_TX_FIFO_REALLY_EMPTY	BIT(7)
*/
#define SPI_BUSY			BIT(8)

/* Bit define for register ctl1 */
#define SPI_RX_MODE			BIT(12)
#define SPI_TX_MODE			BIT(13)

/* Bit define for register ctl2 */
#define SPI_DMA_EN			BIT(6)

/* Bit define for register ctl4 */
#define SPI_START_RX			BIT(9)

#define SPRD_SPI_FIFO_SIZE		32
#define SPRD_DMA_STEP_LEN		8
#define FIFO_RX_FULL			8
#define FIFO_TX_EMPTY			2
#define SPRD_SPI_MAX_RECV_BLK		0x1FF
#define SPRD_SPI_CHIP_CS_NUM		0x4
#define MAX_BITS_PER_WORD		32
#define SPI_TIME_OUT			0xFF0000

#define TX_MAX_LEN_MASK			0xFFFFF
#define TX_DUMY_LEN_MASK		0x3F
#define TX_DATA_LEN_H_MASK		0xF
#define TX_DATA_LEN_L_MASK		0xFFFF

#define RX_MAX_LEN_MASK			0xFFFFF
#define RX_DUMY_LEN_MASK		0x3F
#define RX_DATA_LEN_H_MASK		0xF
#define RX_DATA_LEN_L_MASK		0xFFFF

/* Define the SPI interface mode for LCM */
#define SPIMODE_DISABLE			0
#define SPIMODE_3WIRE_9BIT_SDA		1	/* 3 wire 9 bit, cd bit, SDI/SDO share  one IO */
#define SPIMODE_3WIRE_9BIT_SDIO		2	/* 3 wire 9 bit, cd bit, SDI, SDO */
#define SPIMODE_4WIRE_8BIT_SDA		3	/* 4 wire 8 bit, cd pin, SDI/SDO share one IO */
#define SPIMODE_4WIRE_8BIT_SDIO		4	/* 4 wire 8 bit, cd pin, SDI, SDO */

#define SPI_CD_MASK			BIT(15)
#define SPI_MODE_SHIFT			3
#define SPI_MODE_MASK			(0x7<<SPI_MODE_SHIFT)
#define SW_RX_REQ_MASK			BIT(0)
#define SW_TX_REQ_MASK			BIT(1)

/* Define the clk src for SPI mode */
#define SPICLK_SEL_192M			3
#define SPICLK_SEL_154M			2
#define SPICLK_SEL_128M			1
#define SPICLK_SEL_26M			0

/* SPI CS select in master mode */
#define SPI_SEL_CS0			0xE	/* 2'B1110 */
#define SPI_SEL_CS1			0xD	/* 2'B1101 */
#define SPI_SEL_CS2			0xB	/* 2'B1011 */
#define SPI_SEL_CS3			0x7	/* 2'B0111 */
#define SPI_SEL_CS_SHIFT		8

/*Structure Definition*/
enum spi_sck_sel {
	sck_default = 0,
	sck_reverse,
};

enum spi_tx_edge {
	tx_pos_edge = 0,
	tx_neg_edge,
};

enum spi_rx_edge {
	rx_pos_edge = 0,
	rx_neg_edge,
};

enum spi_msb_lsb_sel {
	tx_rx_msb = 0,
	tx_rx_lsb,
};

enum spi_transfer_mode {
	idle_mode = 0,
	rx_mode,
	tx_mode,
	rx_tx_mode,
};

enum spi_operate_mode {
	master_mode = 0,
	slave_mode,
};

enum spi_dma_en {
	dma_disable = 0,
	dma_enable,
};

enum spi_cs_signal {
	cd_low = 0,
	cd_high,
};

struct spi_init_param {
	enum spi_sck_sel sck_sel;
	enum spi_tx_edge tx_edge;
	enum spi_rx_edge rx_edge;
	enum spi_msb_lsb_sel msb_lsb_sel;
	enum spi_transfer_mode tx_rx_mode;
	enum spi_operate_mode op_mode;
	unsigned int data_width;
	unsigned int max_speed;
};

struct spi_transfer {
	enum spi_transfer_mode rt_mode;
	enum spi_dma_en dma_en;
	unsigned int *tx_buf;
	unsigned int *rx_buf;
	unsigned int data_len;
};

/*Function Propertype*/
void sprd_spi_enable(unsigned int spi_id);
void sprd_spi_disable(unsigned int spi_id);
void sprd_spi_reset(unsigned int spi_id);
void sprd_spi_clk_set(unsigned int spi_id, unsigned int clk_src, unsigned int clk_div);
void sprd_spi_clk_div(unsigned int speed);

void sprd_spi_set_cs(unsigned int spi_sel_csx, unsigned int is_low);
void sprd_spi_set_cd(unsigned int cd);
void sprd_spi_set_spi_mode(unsigned int spi_mode);
void sprd_spi_set_data_width(unsigned int data_width);

void sprd_spi_init(struct spi_init_param *spi_param);
int sprd_spi_transfer(struct spi_transfer *transfer);

int sprd_spi_write_data(unsigned int *pbuf, unsigned int data_len, unsigned int dummy_bit_len);
int sprd_spi_read_data(unsigned int *pbuf, unsigned int data_len, unsigned int dummy_bit_len);

#endif /*_SPRD_SPI_H*/
