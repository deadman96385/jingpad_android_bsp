/******************************************************************************
 ** File Name:    sprd_spi.c                                        *
 ** Author:       mengkai.zhao                                      *
 ** DATE:         2017-08-01                                        *
 ** Copyright:    2017 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:                                                    *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 **    DATE         NAME            DESCRIPTION                     *
 ** 2017-08-01   mengkai.zhao       First Draft
 ******************************************************************************/

#include <asm/arch/spi/sprd_spi.h>
#include "sprd_spi.h"

#define spi_max_id		(sizeof(sprd_spi)/sizeof(sprd_spi[0]))
#define spi_trans_timeout	(-1)

static unsigned int spi_use_id = 0;
static unsigned int spi_clk_src = 26000000;

static unsigned long sprd_get_spi_base(void)
{
	return sprd_spi[spi_use_id].spi_base;
}

static void sprd_spi_dump_regs(unsigned long spi_base)
{
	printf("SPI_CLKD:0x%x\n", readl(spi_base + SPI_CLKD));
	printf("SPI_CTL0:0x%x\n", readl(spi_base + SPI_CTL0));
	printf("SPI_CTL1:0x%x\n", readl(spi_base + SPI_CTL1));
	printf("SPI_CTL2:0x%x\n", readl(spi_base + SPI_CTL2));
	printf("SPI_CTL3:0x%x\n", readl(spi_base + SPI_CTL3));
	printf("SPI_CTL4:0x%x\n", readl(spi_base + SPI_CTL4));
	printf("SPI_CTL5:0x%x\n", readl(spi_base + SPI_CTL5));
	printf("SPI_INT_RAW_STS:0x%x\n", readl(spi_base + SPI_INT_RAW_STS));
	printf("SPI_INT_EN:0x%x\n", readl(spi_base + SPI_INT_EN));
	printf("SPI_STS2:0x%x\n", readl(spi_base + SPI_STS2));
	printf("SPI_DSP_WAIT:0x%x\n", readl(spi_base + SPI_DSP_WAIT));
	printf("SPI_CTL6:0x%x\n", readl(spi_base + SPI_CTL6));
	printf("SPI_CTL7:0x%x\n", readl(spi_base + SPI_CTL7));
	printf("SPI_CTL8:0x%x\n", readl(spi_base + SPI_CTL8));
	printf("SPI_CTL9:0x%x\n", readl(spi_base + SPI_CTL9));
	printf("SPI_CTL10:0x%x\n", readl(spi_base + SPI_CTL10));
	printf("SPI_CTL11:0x%x\n", readl(spi_base + SPI_CTL11));
	printf("SPI_STS6:0x%x\n", readl(spi_base + SPI_STS6));
	printf("SPI_STS7:0x%x\n", readl(spi_base + SPI_STS7));
	printf("SPI_STS8:0x%x\n", readl(spi_base + SPI_STS8));
	printf("SPI_STS9:0x%x\n", readl(spi_base + SPI_STS9));
}

void sprd_spi_enable(unsigned int spi_id)
{
	unsigned int reg_val = 0;

	if (spi_max_id <= spi_id) {
		printf("spi enable error, spi_id %u is out of range\n", spi_id);
		return;
	}

	spi_use_id = spi_id;
	reg_val = readl(sprd_spi[spi_id].apb_base_eb);
	reg_val |= sprd_spi[spi_id].spi_eb;
	writel(reg_val, sprd_spi[spi_id].apb_base_eb);
}

void sprd_spi_disable(unsigned int spi_id)
{
	unsigned int reg_val = 0;

	if (spi_max_id <= spi_id)
		return;

	reg_val = readl(sprd_spi[spi_id].apb_base_eb);
	reg_val &= ~(sprd_spi[spi_id].spi_eb);
	writel(reg_val, sprd_spi[spi_id].apb_base_eb);
}

void sprd_spi_reset(unsigned int spi_id)
{
	unsigned int reg_val = 0;

	if (spi_max_id <= spi_id)
		return;

	reg_val = readl(sprd_spi[spi_id].apb_base_rst);
	reg_val |= sprd_spi[spi_id].spi_rst;

	writel(reg_val, sprd_spi[spi_id].apb_base_rst);
	udelay(10);
	reg_val &= ~(sprd_spi[spi_id].spi_rst);
	writel(reg_val, sprd_spi[spi_id].apb_base_rst);
}

void sprd_spi_clk_set(unsigned int spi_id, unsigned int clk_src, unsigned int clk_div)
{
	unsigned int reg_val = 0;
	unsigned int clk = clk_src & 0x3;
	unsigned int div = clk_div & 0x7;
	if (spi_max_id <= spi_id)
		return;

	reg_val = clk | (div << 8);
	writel(reg_val, sprd_spi[spi_id].spi_clk_base);

	switch (clk) {
	case SPICLK_SEL_26M :
		spi_clk_src = 26000000 / (div + 1);
		break;
	case SPICLK_SEL_128M :
		spi_clk_src = 128000000 / (div + 1);
		break;
	case SPICLK_SEL_154M:
		spi_clk_src = 153600000 / (div + 1);
		break;
	case SPICLK_SEL_192M:
		spi_clk_src = 192000000 / (div + 1);
		break;
	}
}

void sprd_spi_set_cs(unsigned int spi_sel_csx, unsigned int is_low)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int reg_val = readl((spi_base + SPI_CTL0));

	if (is_low)
		reg_val &= ~((1<<spi_sel_csx)<<SPI_SEL_CS_SHIFT);
	else
		reg_val |= ((1<<spi_sel_csx)<<SPI_SEL_CS_SHIFT);

	writel(reg_val, (spi_base + SPI_CTL0));
}

void sprd_spi_set_cd(unsigned int cd)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int reg_val = readl((spi_base + SPI_CTL8));

	if (0 == cd)
		reg_val &= ~(SPI_CD_MASK);
	else
		reg_val |= (SPI_CD_MASK);

	writel(reg_val, (spi_base + SPI_CTL8));
}

void sprd_spi_set_spi_mode(unsigned int spi_mode)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int reg_val = readl((spi_base + SPI_CTL7));

	reg_val &= ~SPI_MODE_MASK;
	reg_val |= ((spi_mode & 0x7) << SPI_MODE_SHIFT);
	writel(reg_val, (spi_base + SPI_CTL7));
}

void sprd_spi_set_data_width(unsigned int data_width)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int reg_val = readl((spi_base + SPI_CTL0));

	reg_val &= ~0x7C;
	if (32 != data_width)
		reg_val |= ((data_width & 0x1F) << 2);

	writel(reg_val, (spi_base + SPI_CTL0));
}

static void sprd_spi_set_tx_length(unsigned int data_len, unsigned int dummy_bit_len)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int reg_val = readl((spi_base + SPI_CTL8));

	data_len &= TX_MAX_LEN_MASK;
	dummy_bit_len &= TX_DUMY_LEN_MASK;

	reg_val &= ~((TX_DUMY_LEN_MASK << 4) | TX_DATA_LEN_H_MASK);
	reg_val |= ((dummy_bit_len << 4) | (data_len >> 16));
	writel(reg_val, (spi_base + SPI_CTL8));
	writel((data_len & TX_DATA_LEN_L_MASK), (spi_base + SPI_CTL9));

	if (0x18 == (readl(spi_base + SPI_CTL7) & (0x7 << 3))) {
		reg_val = readl(spi_base + SPI_CTL10);
		reg_val &= ~(0x3ff);
		writel(reg_val, (spi_base + SPI_CTL10));
		writel(0x0, (spi_base + SPI_CTL11));
	}
}

static void sprd_spi_set_rx_length(unsigned int data_len, unsigned int dummy_bit_len)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int reg_val = readl((spi_base + SPI_CTL10));

	data_len &= RX_MAX_LEN_MASK;
	dummy_bit_len &= RX_DUMY_LEN_MASK;

	reg_val &= ~((RX_DUMY_LEN_MASK << 4) | RX_DATA_LEN_H_MASK);
	reg_val |= ((dummy_bit_len << 4) | (data_len >> 16));
	writel(reg_val, (spi_base + SPI_CTL10));
	writel((data_len & RX_DATA_LEN_L_MASK), (spi_base + SPI_CTL11));

	if (0x18 == (readl(spi_base + SPI_CTL7) & (0x7 << 3))) {
		reg_val = readl(spi_base + SPI_CTL8);
		reg_val &= ~(0x3ff);
		writel(reg_val, (spi_base + SPI_CTL8));
		writel(0x0, (spi_base + SPI_CTL9));
	}
}

static void sprd_spi_tx_req(void)
{
	unsigned long spi_base = sprd_get_spi_base();

	writel(SW_TX_REQ_MASK, (spi_base + SPI_CTL12));
}

static void sprd_spi_rx_req(void)
{
	unsigned long spi_base = sprd_get_spi_base();

	writel(SW_RX_REQ_MASK, (spi_base + SPI_CTL12));
}

static int sprd_spi_wait_tx_finish(void)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int reg_val = 0;
	unsigned int timeout = 0;

#if 0
	while (!(readl(spi_base + SPI_INT_RAW_STS) & SPI_TX_END_RAW_STS)) {
		if (++timeout > SPI_TIME_OUT) {
			printf("spi wait tx error, spi tx end timeout\n");
			sprd_spi_dump_regs(spi_base);
			return spi_trans_timeout;
		}
	}
	writel(SPI_TX_END_CLR, (spi_base + SPI_INT_CLR));
#endif
	reg_val = readl(spi_base + SPI_STS2);
	while (!(reg_val & SPI_TX_FIFO_REALLY_EMPTY)) {
		if (++timeout > SPI_TIME_OUT) {
			printf("spi wait tx error, spi fifo really empty timeout\n");
			sprd_spi_dump_regs(spi_base);
			return spi_trans_timeout;
		}
		reg_val = readl(spi_base + SPI_STS2);
	}

	reg_val = readl(spi_base + SPI_STS2);
	while ((reg_val & SPI_BUSY)) {
		if (++timeout > SPI_TIME_OUT) {
			printf("spi wait tx error, spi busy timeout\n");
			sprd_spi_dump_regs(spi_base);
			return spi_trans_timeout;
		}
		reg_val = readl(spi_base + SPI_STS2);
	}

	return 0;
}

static int sprd_spi_wait_rx_finish(void)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int timeout = 0;

	while (!(readl(spi_base + SPI_INT_RAW_STS) & SPI_RX_END_RAW_STS)) {
		if (++timeout > SPI_TIME_OUT) {
			printf("spi wait rx error, spi rx end timeout\n");
			sprd_spi_dump_regs(spi_base);
			return spi_trans_timeout;
		}
	}
	writel(SPI_RX_END_CLR, (spi_base + SPI_INT_CLR));

	while(readl(spi_base + SPI_STS2) & SPI_BUSY) {
		if (++timeout > SPI_TIME_OUT) {
			printf("spi wait rx error, spi busy timeout\n");
			sprd_spi_dump_regs(spi_base);
			return spi_trans_timeout;
		}
	}

	return 0;
}

static void sprd_spi_fifo_rst()
{
	unsigned long spi_base = sprd_get_spi_base();
	writel(0x1, (spi_base + SPI_FIFO_RST));
	writel(0x0, (spi_base + SPI_FIFO_RST));
}

void sprd_spi_clk_div(unsigned int speed)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int clk_div;

	clk_div = spi_clk_src/(speed << 1) - 1;
	writel(clk_div, (spi_base + SPI_CLKD));
}

void sprd_spi_init(struct spi_init_param *spi_param)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int clk_div;
	unsigned int reg_val;

	clk_div = spi_clk_src/(spi_param->max_speed << 1) - 1;
	writel(clk_div, (spi_base + SPI_CLKD));

	reg_val = (spi_param->sck_sel << 13) | (0xF << 8) | (spi_param->msb_lsb_sel << 7) |
			((spi_param->data_width & 0x1F) << 2) | (spi_param->tx_edge << 1) |
				 (spi_param->rx_edge);

	writel(reg_val, (spi_base + SPI_CTL0));
	writel((spi_param->tx_rx_mode << 12), (spi_base + SPI_CTL1));
	writel((spi_param->op_mode << 5), (spi_base + SPI_CTL2));
	writel((FIFO_TX_EMPTY << 8) | FIFO_RX_FULL, (spi_base + SPI_CTL3));
	writel(0x0, (spi_base + SPI_CTL4));
	writel(0x9, (spi_base + SPI_CTL5));
	writel(0x0, (spi_base + SPI_INT_EN));
	writel(SPI_ALL_INT_CLR, (spi_base + SPI_INT_CLR));
	writel((FIFO_TX_EMPTY << 8) | FIFO_RX_FULL, (spi_base + SPI_CTL6));
	sprd_spi_fifo_rst();
}

static unsigned int sprd_get_spi_data_mask(void)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int data_width = 0;
	unsigned int data_mask = 0xFFFFFFFF;

	data_width = (readl((spi_base + SPI_CTL0)) >> 2) & 0x1F;
	if (0 != data_width)
		data_mask = data_mask >> (32 - data_width);

	return data_mask;
}

static unsigned int sprd_spi_write_bufs(unsigned int *tx_buf, unsigned int num)
{
	unsigned int i;
	unsigned long spi_base = sprd_get_spi_base();

	for (i = 0; i < num; i++, tx_buf++)
		writel(*tx_buf, (spi_base + SPI_TXD));

	return num;
}

static unsigned int sprd_spi_read_bufs(unsigned int *rx_buf, unsigned int num)
{
	unsigned int i;
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int data_mask = sprd_get_spi_data_mask();

	for (i = 0; i < num; i++, rx_buf++) {
		while ((readl(spi_base + SPI_STS2) & SPI_RX_FIFO_REALLY_EMPTY));
		*rx_buf = data_mask & readl(spi_base + SPI_TXD);
	}

	return num;
}

static int sprd_spi_read(struct spi_transfer *transfer)
{
	unsigned long spi_base = sprd_get_spi_base();
	unsigned int block_num = transfer->data_len;
	unsigned int reg_val = 0;
	unsigned int trans_num = 0;
	unsigned int read_num = 0;
	unsigned int timeout = 0;
	unsigned int *pbuf = transfer->rx_buf;

	reg_val = readl(spi_base + SPI_CTL4);
	reg_val &= ~(SPI_START_RX | 0x1FF);
	writel(reg_val, (spi_base + SPI_CTL4));

	while (block_num) {
		trans_num = block_num > SPRD_SPI_FIFO_SIZE ? SPRD_SPI_FIFO_SIZE : block_num;
		reg_val = readl(spi_base + SPI_CTL4);
		reg_val |= trans_num;
		writel(reg_val, (spi_base + SPI_CTL4));
		reg_val = readl(spi_base + SPI_CTL4);
		reg_val |= SPI_START_RX;
		writel(reg_val, (spi_base + SPI_CTL4));

		while ((readl(spi_base + SPI_STS3)) != trans_num) {
			if (++timeout > SPI_TIME_OUT) {
				printf("spi read error, at_only_read mode spi send timeout!\n");
				return spi_trans_timeout;
			}
		}

		read_num += sprd_spi_read_bufs(pbuf, trans_num);
		pbuf += trans_num;
		block_num -= trans_num;
		timeout = 0;
	}

	return transfer->data_len;
}

static int sprd_spi_write_read(struct spi_transfer *transfer)
{
	unsigned int write_num = 0;
	unsigned int read_num = 0;
	unsigned int trans_num = 0;
	unsigned int *tx_buf = transfer->tx_buf;
	unsigned int *rx_buf = transfer->rx_buf;
	unsigned int block_num = transfer->data_len;

	while (block_num) {
		trans_num = block_num > SPRD_SPI_FIFO_SIZE ? SPRD_SPI_FIFO_SIZE : block_num;
		if (rx_tx_mode == transfer->rt_mode) {
			sprd_spi_set_tx_length(trans_num, 0);
			sprd_spi_set_rx_length(trans_num, 0);
		}
		else
			sprd_spi_set_tx_length(trans_num, 0);

		write_num += sprd_spi_write_bufs(tx_buf, trans_num);

		if (spi_trans_timeout == sprd_spi_wait_tx_finish())
			return spi_trans_timeout;

		if (rx_mode != transfer->rt_mode) {
			if (spi_trans_timeout == sprd_spi_wait_rx_finish())
				return spi_trans_timeout;
			read_num += sprd_spi_read_bufs(rx_buf, trans_num);
			rx_buf += trans_num;
		}
		tx_buf += trans_num;
		block_num -= trans_num;
	}

	return transfer->data_len;
}

int sprd_spi_transfer(struct spi_transfer *transfer)
{
	sprd_spi_fifo_rst();
	if (rx_mode == transfer->rt_mode)
		return sprd_spi_read(transfer);
	else
		return sprd_spi_write_read(transfer);
}

int sprd_spi_write_data(unsigned int *pbuf, unsigned int data_len, unsigned int dummy_bit_len)
{
	unsigned int block_num = data_len;
	unsigned int trans_num = 0;
	unsigned int write_num = 0;
	unsigned int first_write = 1;

	sprd_spi_fifo_rst();
	while (block_num) {
		trans_num = block_num > SPRD_SPI_FIFO_SIZE ? SPRD_SPI_FIFO_SIZE : block_num;
		if (first_write)
			sprd_spi_set_tx_length(trans_num, dummy_bit_len);
		else
			sprd_spi_set_tx_length(trans_num, 0);

		write_num += sprd_spi_write_bufs(pbuf, trans_num);
		sprd_spi_tx_req();

		if (spi_trans_timeout == sprd_spi_wait_tx_finish())
			return spi_trans_timeout;

		pbuf += trans_num;
		block_num -= trans_num;
		first_write = 0;
	}

	return data_len;
}

int sprd_spi_read_data(unsigned int *pbuf, unsigned int data_len, unsigned int dummy_bit_len)
{
	unsigned int block_num = data_len;
	unsigned int trans_num = 0;
	unsigned int read_num = 0;
	unsigned int first_read = 1;

	sprd_spi_fifo_rst();
	while (block_num) {
		trans_num = block_num > SPRD_SPI_FIFO_SIZE ? SPRD_SPI_FIFO_SIZE : block_num;
		if (first_read)
			sprd_spi_set_rx_length(trans_num, dummy_bit_len);
		else
			sprd_spi_set_rx_length(trans_num, 0);

		sprd_spi_rx_req();
		if (spi_trans_timeout == sprd_spi_wait_rx_finish())
			return spi_trans_timeout;

		read_num += sprd_spi_read_bufs(pbuf, trans_num);
		pbuf += trans_num;
		block_num -= trans_num;
		first_read = 0;
	}

	return data_len;
}

