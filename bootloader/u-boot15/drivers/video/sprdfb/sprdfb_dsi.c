/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 */

#include "sprdfb_chip_common.h"
#include "sprdfb.h"
#include "sprdfb_panel.h"

#ifdef CONFIG_DSIH_VERSION_1P21A
#include "dsi_1_21a/mipi_dsih_local.h"
#include "dsi_1_21a/mipi_dsih_dphy.h"
#include "dsi_1_21a/mipi_dsih_hal.h"
#include "dsi_1_21a/mipi_dsih_api.h"
#else
#include "dsi_1_10a/mipi_dsih_local.h"
#include "dsi_1_10a/mipi_dsih_dphy.h"
#include "dsi_1_10a/mipi_dsih_hal.h"
#include "dsi_1_10a/mipi_dsih_api.h"
#endif

#define DSI_PHY_REF_CLOCK (26*1000)

#define DSI_EDPI_CFG (0x6c)

#define MAX_TIME_HS2LP	120 /* unit: ns */
#define MAX_TIME_LP2HS	500 /* unit: ns */


struct sprdfb_dsi_context {
	uint16_t			is_inited;

	dsih_ctrl_t	dsi_inst;
};

static struct sprdfb_dsi_context dsi_ctx;

static uint32_t dsi_core_read_function(unsigned long addr, uint32_t offset)
{
	return __raw_readl(addr + offset);
}

static void dsi_core_write_function(unsigned long addr, uint32_t offset, uint32_t data)
{
	__raw_writel(data, addr + offset);
}


static void dsi_reset(void)
{
	FB_PRINT("sprdfb:[%s]\n", __FUNCTION__);
	__raw_writel(__raw_readl(DSI_AHB_SOFT_RST) | (BIT_DSI_SOFT_RST), DSI_AHB_SOFT_RST);
	udelay(10);
	__raw_writel(__raw_readl(DSI_AHB_SOFT_RST) & (~(BIT_DSI_SOFT_RST)),DSI_AHB_SOFT_RST);
}

int32_t dsi_early_int(void)
{
	FB_PRINT("sprdfb:[%s]\n", __FUNCTION__);

	if(dsi_ctx.is_inited){
		FB_PRINT("sprdfb: dispc early init warning!(has been inited)");
		return 0;
	}

#ifdef CONFIG_FPGA
#if !((defined(CONFIG_SC9833)) || (defined(CONFIG_SOC_SHARKLJ1)) || (defined(CONFIG_SOC_SHARKLE)) || (defined(CONFIG_SOC_PIKE2)) || (defined(CONFIG_SOC_SHARKL3)) ||  (defined(CONFIG_SOC_ROC1)) || (defined(CONFIG_SOC_SHARKL5)) || (defined(CONFIG_SOC_SHARKL5PRO)))
	usc28c_dsi_init();
#endif
#endif
	dsi_reset();

	memset(&(dsi_ctx.dsi_inst), 0, sizeof(dsi_ctx.dsi_inst));

	dsi_ctx.is_inited = 1;
	return 0;
}

static int32_t dsi_edpi_setbuswidth(struct info_mipi * mipi)
{
	dsih_color_coding_t color_coding = 0;

	switch(mipi->video_bus_width){
	case 16:
		color_coding = COLOR_CODE_16BIT_CONFIG1;
		break;
	case 18:
		color_coding = COLOR_CODE_18BIT_CONFIG1;
		break;
	case 24:
		color_coding = COLOR_CODE_24BIT;
		break;
	default:
		printf("sprdfb:[%s] fail, invalid video_bus_width\n", __FUNCTION__);
		break;
	}
#ifdef CONFIG_DSIH_VERSION_1P21A
	__raw_bits_or(color_coding,(DSI_CTL_BEGIN+R_DSI_HOST_DPI_COLOR_CODE));
#else
	dsi_core_write_function(DSI_CTL_BEGIN,  R_DSI_HOST_DPI_CFG, (uint32_t)(color_coding<<2));
#endif
	return 0;
}


static int32_t dsi_edpi_init(void)
{
#ifdef CONFIG_DSIH_VERSION_1P21A
	dsi_core_write_function(DSI_CTL_BEGIN,  (uint32_t)R_DSI_HOST_EDPI_CMD_SIZE, 0x500);
#else
	dsi_core_write_function(DSI_CTL_BEGIN,  (uint32_t)R_DSI_HOST_EDPI_CFG, 0x10500);
#endif
	return 0;
}

static int32_t dsi_dpi_init(struct sprdfb_device *dev)
{
	dsih_dpi_video_t dpi_param = {0};
	dsih_error_t result;
	struct panel_spec* panel = dev->panel;
	struct info_mipi * mipi = panel->info.mipi;
	uint32_t hs2lp, lp2hs;

	dpi_param.no_of_lanes = mipi->lan_number;
	dpi_param.byte_clock = mipi->phy_feq / 8;
#ifndef CONFIG_FPGA
	dpi_param.pixel_clock = dev->dpi_clock/1000;//384*1000/11;//DSI_PHY_REF_CLOCK / 4;
#elif defined(CONFIG_ZEBU)
	dpi_param.pixel_clock = dev->dpi_clock/1000;//128*1000/11;//DSI_PHY_REF_CLOCK / 4;
#else
	dpi_param.pixel_clock = 6500;
#endif
#ifdef CONFIG_DSIH_VERSION_1P21A
	hs2lp = MAX_TIME_HS2LP * mipi->phy_feq / 8000000;
	hs2lp += (MAX_TIME_HS2LP * mipi->phy_feq % 8000000) < 4000000 ? 0 : 1;
	dpi_param.max_hs_to_lp_cycles = hs2lp;

	lp2hs = MAX_TIME_LP2HS * mipi->phy_feq / 8000000;
	lp2hs += (MAX_TIME_LP2HS * mipi->phy_feq % 8000000) < 4000000 ? 0 : 1;
	dpi_param.max_lp_to_hs_cycles = lp2hs;

	dpi_param.max_clk_hs_to_lp_cycles = 4;//110;
	dpi_param.max_clk_lp_to_hs_cycles = 15;//10;
#endif
	switch(mipi->video_bus_width){
	case 16:
		dpi_param.color_coding = COLOR_CODE_16BIT_CONFIG1;
		break;
	case 18:
		dpi_param.color_coding = COLOR_CODE_18BIT_CONFIG1;
		break;
	case 24:
#ifdef CONFIG_SOC_IWHALE2
		/*iwhale2 use synposys dsi host , not support COLOR_CODE_COMPRESSTION*/
		dpi_param.color_coding = COLOR_CODE_24BIT;
#else
		if(panel->is_need_dsc)
			dpi_param.color_coding = COLOR_CODE_COMPRESSTION;
		else
			dpi_param.color_coding = COLOR_CODE_24BIT;
#endif
		break;
	default:
		printf("sprdfb:[%s] fail, invalid video_bus_width\n", __FUNCTION__);
		break;
	}

	if(SPRDFB_POLARITY_POS == mipi ->h_sync_pol){
		dpi_param.h_polarity = 1;
	}

	if(SPRDFB_POLARITY_POS == mipi ->v_sync_pol){
		dpi_param.v_polarity = 1;
	}

	if(SPRDFB_POLARITY_POS == mipi ->de_pol){
		dpi_param.data_en_polarity = 1;
	}
	dpi_param.h_active_pixels = panel->width;
	dpi_param.h_sync_pixels = mipi->timing->hsync;
	dpi_param.h_back_porch_pixels = mipi->timing->hbp;
	dpi_param.h_total_pixels = panel->width + mipi->timing->hsync + mipi->timing->hbp + mipi->timing->hfp;

#ifdef CONFIG_SOC_IWHALE2
	if(panel->is_need_dsc){
		dpi_param.h_active_pixels = panel->width / 3;
		dpi_param.h_total_pixels = panel->width + mipi->timing->hsync + mipi->timing->hbp + mipi->timing->hfp
			+(panel->width << 1) / 3;
	}
#endif
	dpi_param.v_active_lines = panel->height;
	dpi_param.v_sync_lines = mipi->timing->vsync;
	dpi_param.v_back_porch_lines = mipi->timing->vbp;
	dpi_param.v_total_lines = panel->height + mipi->timing->vsync + mipi->timing->vbp + mipi->timing->vfp;

	dpi_param.receive_ack_packets = 0;
	dpi_param.video_mode = VIDEO_BURST_WITH_SYNC_PULSES;
	dpi_param.virtual_channel = 0;
#ifndef CONFIG_FB_LCD_ILI9486S1_MIPI
	dpi_param.is_18_loosely = 0;
#else
	dpi_param.is_18_loosely = 1;
#endif

	result = mipi_dsih_dpi_video(&(dsi_ctx.dsi_inst), &dpi_param);
	if(result != OK){
		printf("sprdfb: [%s] mipi_dsih_dpi_video fail (%d)!\n", __FUNCTION__, result);
		return -1;
	}

	return 0;
}

static void dsi_log_error(const char * string)
{
	FB_PRINT(string);
}


int32_t sprdfb_dsi_init(struct sprdfb_device *dev)
{
	dsih_error_t result = OK;
	dsih_ctrl_t* dsi_instance = &(dsi_ctx.dsi_inst);
	dphy_t *phy = &(dsi_instance->phy_instance);
	struct info_mipi * mipi = dev->panel->info.mipi;
	unsigned int dsi_cycle_period_n;
	int i = 0;
#ifdef CONFIG_FPGA
	int j = 0;
#endif

	dsi_enable();


	FB_PRINT("sprdfb:[%s]\n", __FUNCTION__);

	dsi_early_int();
	phy->address = DSI_CTL_BEGIN;
	phy->core_read_function = dsi_core_read_function;
	phy->core_write_function = dsi_core_write_function;
	phy->log_error = dsi_log_error;
	phy->log_info = NULL;
	phy->reference_freq = DSI_PHY_REF_CLOCK;

	dsi_instance->address = DSI_CTL_BEGIN;
	dsi_instance->color_mode_polarity =mipi->color_mode_pol;
	dsi_instance->shut_down_polarity = mipi->shut_down_pol;
	dsi_instance->non_continuous_clock = dev->panel->non_continue_clk_en;
	dsi_instance->core_read_function = dsi_core_read_function;
	dsi_instance->core_write_function = dsi_core_write_function;
	dsi_instance->log_error = dsi_log_error;
	dsi_instance->log_info = NULL;
	/*in our rtl implementation, this is max rd time, not bta time and use 15bits*/
	dsi_cycle_period_n = 8000 * 1000 / mipi->phy_feq;
	dsi_instance->max_bta_cycles = (2000 + 6600) / dsi_cycle_period_n;
	#ifndef CONFIG_DSIH_VERSION_1P21A
	dsi_instance->max_hs_to_lp_cycles = 4;//110;
	dsi_instance->max_lp_to_hs_cycles = 15;//10;
	#endif
	dsi_instance->max_lanes = mipi->lan_number;

#ifdef CONFIG_DSIH_VERSION_1P21A
	dsi_core_write_function(DSI_CTL_BEGIN,  R_DSI_HOST_INT_MSK0, 0x1fffff);
	dsi_core_write_function(DSI_CTL_BEGIN,  R_DSI_HOST_INT_MSK1, 0x3ffff);
#else
	dsi_core_write_function(DSI_CTL_BEGIN,  R_DSI_HOST_ERROR_MSK0, 0x1fffff);
	dsi_core_write_function(DSI_CTL_BEGIN,  R_DSI_HOST_ERROR_MSK1, 0x3ffff);
#endif
	dsi_instance->phy_feq = dev->panel->info.mipi->phy_feq;

	printf("phy status0 %x\n",dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_STATUS));
	result = mipi_dsih_open(dsi_instance);
	if(OK != result){
		printf("sprdfb: [%s]: mipi_dsih_open fail (%d)!\n", __FUNCTION__, result);
		return -1;
	}

	printf("phy status1 %x\n",dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_STATUS));
	result = mipi_dsih_dphy_configure(phy,  mipi->lan_number, mipi->phy_feq);
	if(OK != result){
		printf("sprdfb: [%s]: mipi_dsih_dphy_configure fail (%d)!\n", __FUNCTION__, result);
		return -1;
	}

#ifdef CONFIG_MIPI_DSIH_SPRD
	while(0x0A != (dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_STATUS) & 0x0A)){
#else
	while(5 != (dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_STATUS) & 5)){
#endif
		if(0x0 == ++i%500000){
			printf("sprdfb: [%s] warning: busy waiting!\n", __FUNCTION__);
#ifdef CONFIG_FPGA
			if(++j > 5) {
				break;
			}
#endif
		}
	}

	printf("phy status2 %x\n",dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_STATUS));
	if(SPRDFB_MIPI_MODE_CMD == mipi->work_mode){
		dsi_edpi_init();
		dsi_edpi_setbuswidth(mipi);
	}

	result = mipi_dsih_enable_rx(dsi_instance, 1);
	if(OK != result){
		printf("sprdfb: [%s]: mipi_dsih_enable_rx fail (%d)!\n", __FUNCTION__, result);
		return -1;
	}

	result = mipi_dsih_ecc_rx(dsi_instance, 1);
	if(OK != result){
		printf("sprdfb: [%s]: mipi_dsih_ecc_rx fail (%d)!\n", __FUNCTION__, result);
		return -1;
	}

	result = mipi_dsih_eotp_rx(dsi_instance, 1);
	if(OK != result){
		printf("sprdfb: [%s]: mipi_dsih_eotp_rx fail (%d)!\n", __FUNCTION__, result);
		return -1;
	}

	result = mipi_dsih_eotp_tx(dsi_instance, 1);
	if(OK != result){
		printf("sprdfb: [%s]: mipi_dsih_eotp_tx fail (%d)!\n", __FUNCTION__, result);
		return -1;
	}

	if(SPRDFB_MIPI_MODE_VIDEO == mipi->work_mode){
		dsi_dpi_init(dev);
	}

	return 0;
}

int32_t sprdfb_dsi_uninit(struct sprdfb_device *dev)
{
	dsih_error_t result;
#ifdef CONFIG_DSIH_VERSION_1P21A
	mipi_dsih_dphy_enable_hs_clk(&(dsi_ctx.dsi_inst.phy_instance), 0);
#else
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_IF_CTRL, 0);
#endif

	result = mipi_dsih_close(&(dsi_ctx.dsi_inst));
	if(OK != result){
		printf("sprdfb: [%s]: sprdfb_dsi_uninit fail (%d)!\n", __FUNCTION__, result);
		return -1;
	} else {
	    dsi_ctx.dsi_inst.status = NOT_INITIALIZED;
		dsi_ctx.is_inited = 0;
	}

	mdelay(3);
    dsi_disable();
	return 0;
}

int32_t sprdfb_dsi_ready(struct sprdfb_device *dev)
{
	struct info_mipi * mipi = dev->panel->info.mipi;

	if(SPRDFB_MIPI_MODE_CMD == mipi->work_mode){
		mipi_dsih_cmd_mode(&(dsi_ctx.dsi_inst), 1);
#ifdef CONFIG_DSIH_VERSION_1P21A
	    mipi_dsih_dphy_enable_hs_clk(&(dsi_ctx.dsi_inst.phy_instance), 1);
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_CMD_MODE_CFG, 0x0);
#else
		dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_CMD_MODE_CFG, 0x1);
		dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_IF_CTRL, 0x1);
#endif
	}else{
#ifdef CONFIG_DSIH_VERSION_1P21A
        mipi_dsih_dphy_enable_hs_clk(&(dsi_ctx.dsi_inst.phy_instance), 1);
#else
		dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_IF_CTRL, 0x1);
#endif
		mipi_dsih_video_mode(&(dsi_ctx.dsi_inst), 1);
		dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_PWR_UP, 0);
		udelay(100);
		dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_PWR_UP, 1);
		udelay(10*1000);
#ifdef CONFIG_DSIH_VERSION_1P21A
		dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_INT_ST0);
		dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_INT_ST1);
#else
		dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_ERROR_ST0);
		dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_ERROR_ST1);
#endif
	}
	return 0;
}


static int32_t sprdfb_dsi_set_lp_mode(void)
{
	uint32_t reg_val;
	FB_PRINT("sprdfb:[%s]\n", __FUNCTION__);

	mipi_dsih_cmd_mode(&(dsi_ctx.dsi_inst), 1);
#ifdef CONFIG_DSIH_VERSION_1P21A
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_CMD_MODE_CFG, 0x01ffff00);
	mipi_dsih_dphy_enable_hs_clk(&(dsi_ctx.dsi_inst.phy_instance), 0);
#else
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_CMD_MODE_CFG, 0x1fff);
	reg_val = dsi_core_read_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_IF_CTRL);
	reg_val = reg_val & (~(BIT(0)));
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_IF_CTRL,  reg_val);
#endif
	return 0;
}

static int32_t sprdfb_dsi_set_hs_mode(void)
{
	FB_PRINT("sprdfb:[%s]\n", __FUNCTION__);

	mipi_dsih_cmd_mode(&(dsi_ctx.dsi_inst), 1);
#ifdef CONFIG_DSIH_VERSION_1P21A
	mipi_dsih_dphy_enable_hs_clk(&(dsi_ctx.dsi_inst.phy_instance), 1);
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_CMD_MODE_CFG, 0x0);
#else
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_CMD_MODE_CFG, 0x1);
	dsi_core_write_function(DSI_CTL_BEGIN, R_DSI_HOST_PHY_IF_CTRL, 0x1);
#endif
	return 0;
}

int32_t sprdfb_dsi_before_panel_reset(struct sprdfb_device *dev)
{
	sprdfb_dsi_set_lp_mode();
	return 0;
}

static int32_t sprdfb_dsi_set_cmd_mode(void)
{
	mipi_dsih_cmd_mode(&(dsi_ctx.dsi_inst), 1);
	return 0;
}

static int32_t sprdfb_dsi_set_video_mode(void)
{
	mipi_dsih_video_mode(&(dsi_ctx.dsi_inst), 1);
	return 0;
}

static int32_t sprdfb_dsi_gen_write(uint8_t *param, uint16_t param_length)
{
	dsih_error_t result;

	result = mipi_dsih_gen_wr_cmd(&(dsi_ctx.dsi_inst), 0, param, param_length);

	if(OK != result){
		printf("sprdfb: [%s] error (%d)\n", __FUNCTION__, result);
		return -1;
	}
	return 0;
}

static int32_t sprdfb_dsi_gen_read(uint8_t *param, uint16_t param_length, uint8_t bytes_to_read, uint8_t *read_buffer)
{
	uint16_t result;
	result = mipi_dsih_gen_rd_cmd(&(dsi_ctx.dsi_inst), 0, param, param_length, bytes_to_read, read_buffer);
	if(0 == result){
		printf("sprdfb: [%s] error (%d)\n", __FUNCTION__, result);
		return -1;
	}
	return 0;
}

static int32_t sprdfb_dsi_dcs_write(uint8_t *param, uint16_t param_length)
{
	dsih_error_t result;
	result = mipi_dsih_dcs_wr_cmd(&(dsi_ctx.dsi_inst), 0, param, param_length);
	if(OK != result){
		printf("sprdfb: [%s] error (%d)\n", __FUNCTION__, result);
		return -1;
	}
	return 0;
}

static int32_t sprdfb_dsi_dcs_read(uint8_t command, uint8_t bytes_to_read, uint8_t *read_buffer)
{
	uint16_t result;
	result = mipi_dsih_dcs_rd_cmd(&(dsi_ctx.dsi_inst), 0, command, bytes_to_read, read_buffer);
	if(0 == result){
		printf("sprdfb: [%s] error (%d)\n", __FUNCTION__, result);
		return -1;
	}
	return 0;
}

static int32_t sprd_dsi_force_write(uint8_t data_type, uint8_t *p_params, uint16_t param_length)
{
	int32_t iRtn = 0;

	iRtn = mipi_dsih_gen_wr_packet(&(dsi_ctx.dsi_inst), 0, data_type,  p_params, param_length);

	return iRtn;
}

static int32_t sprd_dsi_force_read(uint8_t command, uint8_t bytes_to_read, uint8_t * read_buffer)
{
	int32_t iRtn = 0;

	iRtn = mipi_dsih_gen_rd_packet(&(dsi_ctx.dsi_inst),  0,  6,  0, command,  bytes_to_read, read_buffer);

	return iRtn;
}

static int32_t sprd_dsi_eotp_set(uint8_t rx_en, uint8_t tx_en)
{
	dsih_ctrl_t *curInstancePtr = &(dsi_ctx.dsi_inst);
	if(0 == rx_en)
		mipi_dsih_eotp_rx(curInstancePtr, 0);
	else if(1 == rx_en)
		mipi_dsih_eotp_rx(curInstancePtr, 1);
	if(0 == tx_en)
		mipi_dsih_eotp_tx(curInstancePtr, 0);
	else if(1 == tx_en)
		mipi_dsih_eotp_tx(curInstancePtr, 1);
	return 0;
}

struct ops_mipi sprdfb_mipi_ops = {
	.mipi_set_cmd_mode = sprdfb_dsi_set_cmd_mode,
	.mipi_set_video_mode = sprdfb_dsi_set_video_mode,
	.mipi_set_lp_mode = sprdfb_dsi_set_lp_mode,
	.mipi_set_hs_mode = sprdfb_dsi_set_hs_mode,
	.mipi_gen_write = sprdfb_dsi_gen_write,
	.mipi_gen_read = sprdfb_dsi_gen_read,
	.mipi_dcs_write = sprdfb_dsi_dcs_write,
	.mipi_dcs_read = sprdfb_dsi_dcs_read,
	.mipi_force_write = sprd_dsi_force_write,
	.mipi_force_read = sprd_dsi_force_read,
	.mipi_eotp_set = sprd_dsi_eotp_set,
};
