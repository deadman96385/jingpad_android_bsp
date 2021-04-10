/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 */
#include "sprdfb_chip_common.h"
#include "sprdfb.h"
#include "sprdfb_panel.h"
#include "../../spi/sprd_spi.h"

#define REG32(x)              (*((volatile uint32_t *)(x)))
#define LCM_GPIO_RS		LCM_GPIO_RSTN

unsigned char start_send_pixels_flag = 0;

 extern int sprd_gpio_request(struct gpio_chip *chip, unsigned offset);
 extern int sprd_gpio_direction_output(struct gpio_chip *chip, unsigned offset, int value);
 extern void sprd_gpio_set(struct gpio_chip *chip, unsigned offset, int value);

 struct spi_init_param spi_int_parm[] =
 {
	{
	 sck_reverse,
	 tx_pos_edge,
	 rx_pos_edge,
	 tx_rx_msb,
	 rx_tx_mode,
	 master_mode,
	 0x0,
	 24000000
	 },  //for spi_lcm test
	//{TX_POS_EDGE,RX_NEG_EDGE,TX_RX_LSB,RX_TX_MODE,NO_SWITCH,SLAVE_MODE,0x0,0x0,0xF0,0x0,0x0,SPI_TX_FIFO_DEPTH - 1,0x0,SPI_RX_FIFO_DEPTH - 1},
 };


 /**---------------------------------------------------------------------------*
 **                 SPI Interface for LCM test case  depend on spi_drv.c      *
 **---------------------------------------------------------------------------*/
//CASE1:
// --------------------------------------------------------------------------- //
//  Description:   configure the start byte
//	Global resource dependence:
//  Author:         lichd
//  Note  : LCM test code
// --------------------------------------------------------------------------- //

static void DISPC_SpiWriteCmd(uint32_t cmd)
{
	sprd_spi_set_data_width(8);
	sprd_spi_set_cs(0, TRUE);
	sprd_gpio_set(NULL,138,0);
	// Write a data identical with buswidth
	sprd_spi_write_data( &cmd, 1, 0);

	sprd_spi_set_cs(0, FALSE);
}

static void DISPC_SpiWriteData(uint32_t data)
{
	sprd_spi_set_data_width(8);

	sprd_spi_set_cs(0, TRUE);

	if (!start_send_pixels_flag)
		sprd_gpio_set(NULL,138,1);

	// Write a data identical with buswidth
	sprd_spi_write_data( &data, 1, 0);

	sprd_spi_set_cs(0, FALSE);
}

static void SPI_Read( uint32_t* data,uint32_t len)
{
	sprd_spi_set_cs(0, TRUE);
	sprd_gpio_set(NULL,138,1);
	sprd_spi_set_data_width(8);

	sprd_spi_read_data(data, len, 2);  //unit of buswidth
	sprd_spi_set_cs(0, FALSE);
}

void SPI_PinCfg( void )
{
	/*enable access the spi reg*/
	*((volatile uint32_t *)(0x4b000008)) |= BIT_1;
	*((volatile uint32_t *)(0x4b0000c0)) |= BIT_0;
}

BOOLEAN sprdfb_sprd_spi_init(struct sprdfb_device *dev)
{
	unsigned int reg_val;

	sprd_gpio_request(NULL,138);
	sprd_gpio_direction_output(NULL,138,1);

	sprd_spi_enable(1);
	sprd_spi_clk_set(1,3,0);
	sprd_spi_init( spi_int_parm);

	#ifdef CONFIG_SPIMODE_4WIRE_8BIT_SDIO
	sprd_spi_set_spi_mode(SPIMODE_4WIRE_8BIT_SDIO);
	#else
	sprd_spi_set_spi_mode(SPIMODE_4WIRE_8BIT_SDA);
	#endif
	return TRUE;
}

BOOLEAN sprdfb_spi_uninit(struct sprdfb_device *dev)
{
	return TRUE;
}

void spi_clock_set(unsigned int speed)
{
	sprd_spi_clk_div(speed);
}

struct ops_spi sprdfb_spi_ops = {
	.spi_send_cmd = DISPC_SpiWriteCmd,
	.spi_send_data = DISPC_SpiWriteData,
	.spi_read = SPI_Read,
	.spi_clock_set = spi_clock_set,
};


static int32_t sprdfb_spi_panel_check(struct panel_spec *panel)
{
	if(NULL == panel){
		printf("sprdfb: [%s] fail. (Invalid param)\n", __FUNCTION__);
		return 0;
	}

	if(SPRDFB_PANEL_TYPE_SPI != panel->type){
		printf("sprdfb: [%s] fail. (not spi param)\n", __FUNCTION__);
		return 0;
	}

	FB_PRINT("sprdfb: [%s]\n",__FUNCTION__);

	return 1;
}

static void sprdfb_spi_panel_mount(struct sprdfb_device *dev)
{
	if((NULL == dev) || (NULL == dev->panel)){
		printf("sprdfb: [%s]: Invalid Param\n", __FUNCTION__);
		return;
	}
	dev->panel_if_type = SPRDFB_PANEL_IF_SPI;
	if (dev->panel->info.spi)
	{
		printf("sprdfb:sprdfb_spi_panel_mount sprdfb_spi_ops\n");
		dev->panel->info.spi->ops = &sprdfb_spi_ops;
	}
}

static void sprdfb_spi_panel_init(struct sprdfb_device *dev)
{
	int ret=false;
	printf("sprdfb: [%s]\n",__FUNCTION__);
	ret=sprdfb_sprd_spi_init(dev);
	if(!ret)
	{
		printf( "sprdfb: [%s]: bus init fail!\n", __FUNCTION__);
		return ;
	}
}

static void sprdfb_spi_panel_uninit(struct sprdfb_device *dev)
{
	int ret=false;
	printf("sprdfb: [%s]\n",__FUNCTION__);
	ret=sprdfb_spi_uninit(dev);
	if(!ret)
	{
		printf( "sprdfb: [%s]: init fail!\n", __FUNCTION__);
		return ;
	}
}

struct panel_if_ctrl sprdfb_spi_ctrl = {
	.if_name		= "spi",
	.panel_if_check	= sprdfb_spi_panel_check,
	.panel_if_mount	= sprdfb_spi_panel_mount,
	.panel_if_init		= sprdfb_spi_panel_init,
	.panel_if_before_refresh	= NULL,
	.panel_if_after_refresh	= NULL,
};


