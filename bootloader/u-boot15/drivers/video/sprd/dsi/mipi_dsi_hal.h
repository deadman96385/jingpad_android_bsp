#ifndef MIPI_DSI_HAL_H_
#define MIPI_DSI_HAL_H_

#include "sprd_dsi.h"

bool dsi_hal_check_version(struct sprd_dsi *dsi);
void dsi_hal_power_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_video_mode(struct sprd_dsi *dsi);
void dsi_hal_cmd_mode(struct sprd_dsi *dsi);
bool dsi_hal_is_cmd_mode(struct sprd_dsi *dsi);
void dsi_hal_video_vcid(struct sprd_dsi *dsi, u8 vc);
void dsi_hal_rx_vcid(struct sprd_dsi *dsi, u8 vc);
void dsi_hal_dpi_video_burst_mode(struct sprd_dsi *dsi, int burst_mode);
void dsi_hal_dpi_color_coding(struct sprd_dsi *dsi, int coding);
void dsi_hal_dpi_18_loosely_packet_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_dpi_color_mode_pol(struct sprd_dsi *dsi, int active_low);
void dsi_hal_dpi_shut_down_pol(struct sprd_dsi *dsi, int active_low);
void dsi_hal_dpi_hsync_pol(struct sprd_dsi *dsi, int active_low);
void dsi_hal_dpi_vsync_pol(struct sprd_dsi *dsi, int active_low);
void dsi_hal_dpi_data_en_pol(struct sprd_dsi *dsi, int active_low);
void dsi_hal_dpi_sig_delay(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_dpi_hline_time(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_dpi_hsync_time(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_dpi_hbp_time(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_dpi_vact(struct sprd_dsi *dsi, u16 lines);
void dsi_hal_dpi_vfp(struct sprd_dsi *dsi, u16 lines);
void dsi_hal_dpi_vbp(struct sprd_dsi *dsi, u16 lines);
void dsi_hal_dpi_vsync(struct sprd_dsi *dsi, u16 lines);
void dsi_hal_dpi_hporch_lp_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_dpi_vporch_lp_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_dpi_frame_ack_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_dpi_null_packet_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_dpi_multi_packet_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_dpi_chunk_num(struct sprd_dsi *dsi, u16 num);
void dsi_hal_dpi_null_packet_size(struct sprd_dsi *dsi, u16 size);
void dsi_hal_dpi_video_packet_size(struct sprd_dsi *dsi, u16 size);
void dsi_hal_edpi_max_pkt_size(struct sprd_dsi *dsi, u16 size);
void dsi_hal_edpi_video_hs_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_tear_effect_ack_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_cmd_ack_request_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_cmd_mode_lp_cmd_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_video_mode_lp_cmd_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_set_packet_header(struct sprd_dsi *dsi, u8 vc, u8 type,
						u8 wc_lsb, u8 wc_msb);
void dsi_hal_set_packet_payload(struct sprd_dsi *dsi, u32 payload);
u32 dsi_hal_get_rx_payload(struct sprd_dsi *dsi);
void dsi_hal_bta_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_eotp_rx_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_eotp_tx_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_ecc_rx_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_crc_rx_en(struct sprd_dsi *dsi, int enable);
bool dsi_hal_is_bta_returned(struct sprd_dsi *dsi);
bool dsi_hal_is_rx_payload_fifo_full(struct sprd_dsi *dsi);
bool dsi_hal_is_rx_payload_fifo_empty(struct sprd_dsi *dsi);
bool dsi_hal_is_tx_payload_fifo_full(struct sprd_dsi *dsi);
bool dsi_hal_is_tx_payload_fifo_empty(struct sprd_dsi *dsi);
bool dsi_hal_is_tx_cmd_fifo_full(struct sprd_dsi *dsi);
bool dsi_hal_is_tx_cmd_fifo_empty(struct sprd_dsi *dsi);
bool dsi_hal_wait_tx_payload_fifo_empty(struct sprd_dsi *dsi);
bool dsi_hal_wait_tx_cmd_fifo_empty(struct sprd_dsi *dsi);
bool dsi_hal_wait_rd_resp_completed(struct sprd_dsi *dsi);
void dsi_hal_datalane_hs2lp_config(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_datalane_lp2hs_config(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_clklane_hs2lp_config(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_clklane_lp2hs_config(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_max_read_time(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_nc_clk_en(struct sprd_dsi *dsi, int enable);
void dsi_hal_tx_escape_division(struct sprd_dsi *dsi, u8 div);
void dsi_hal_timeout_clock_division(struct sprd_dsi *dsi, u8 div);
void dsi_hal_lp_rx_timeout(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_hs_tx_timeout(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_bta_presp_timeout(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_lp_write_presp_timeout(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_lp_read_presp_timeout(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_hs_write_presp_timeout(struct sprd_dsi *dsi, u16 byte_cycle);
void dsi_hal_hs_read_presp_timeout(struct sprd_dsi *dsi, u16 byte_cycle);
u32 dsi_hal_int0_status(struct sprd_dsi *dsi);
u32 dsi_hal_int1_status(struct sprd_dsi *dsi);
u32 dsi_hal_int2_status(struct sprd_dsi *dsi);
void dsi_hal_int0_mask(struct sprd_dsi *dsi, u32 mask);
void dsi_hal_int1_mask(struct sprd_dsi *dsi, u32 mask);
void dsi_hal_int2_mask(struct sprd_dsi *dsi, u32 mask);


#endif /* MIPI_DSI_HAL_H_ */
