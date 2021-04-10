#ifndef _MIPI_DSI_API_H_
#define _MIPI_DSI_API_H_

#include "sprd_dsi.h"

int mipi_dsi_init(struct sprd_dsi *dsi);
int mipi_dsi_uninit(struct sprd_dsi *dsi);
int mipi_dsi_dpi_video(struct sprd_dsi *dsi,
			struct dpi_video_param *param);
int mipi_dsi_edpi_video(struct sprd_dsi *dsi,
			struct edpi_video_param *param);
int mipi_dsi_htime_update(struct sprd_dsi *dsi,
			struct dpi_video_param *param);
int mipi_dsi_gen_write(struct sprd_dsi *dsi, u8 *param, u16 len);
int mipi_dsi_gen_read(struct sprd_dsi *dsi, u8 *param, u16 len,
						u8 *buf, u8 count);
int mipi_dsi_dcs_write(struct sprd_dsi *dsi, u8 *param, u16 len);
int mipi_dsi_dcs_read(struct sprd_dsi *dsi, u8 param, u8 *buf, u8 count);
int mipi_dsi_force_write(struct sprd_dsi *dsi, u8 type, u8 *param, u16 len);
int mipi_dsi_set_max_return_size(struct sprd_dsi *dsi, u16 size);
int mipi_dsi_dcs_set_column_address(struct sprd_dsi *dsi, u16 start, u16 end);
int mipi_dsi_dcs_set_page_address(struct sprd_dsi *dsi, u16 start, u16 end);
int mipi_dsi_dcs_read_memory_start(struct sprd_dsi *dsi, u8 *buf, u8 size);
int mipi_dsi_dcs_read_memory_continue(struct sprd_dsi *dsi, u8 *buf, u8 size);
void mipi_dsi_set_work_mode(struct sprd_dsi *dsi, u8 mode);
int mipi_dsi_get_work_mode(struct sprd_dsi *dsi);
void mipi_dsi_lp_cmd_enable(struct sprd_dsi *dsi, int enable);
void mipi_dsi_state_reset(struct sprd_dsi *dsi);
u32 mipi_dsi_int_status(struct sprd_dsi *dsi, int index);
void mipi_dsi_int_mask(struct sprd_dsi *dsi, int index);

#endif /* _MIPI_DSI_API_H_ */
