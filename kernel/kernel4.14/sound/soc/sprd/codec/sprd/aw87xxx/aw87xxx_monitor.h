#ifndef __AW87XXX_MONITOR_H__
#define __AW87XXX_MONITOR_H__

/********************************************
*
* vmax of matching about capacity
*
*********************************************/
#define AW87XXX_MONITOR_DEFAULT_FLAG		0
#define AW87XXX_MONITOR_DEFAULT_TIMER_VAL	30000
#define AW87XXX_MONITOR_DEFAULT_TIMER_COUNT	2

#define AW87XXX_VBAT_CAPACITY_MIN	0
#define AW87XXX_VBAT_CAPACITY_MAX	100
#define AW_VMAX_INIT_VAL		(0xFFFFFFFF)

enum aw_monitor_first_enter {
	AW_FIRST_ENTRY = 0,
	AW_NOT_FIRST_ENTRY = 1,
};

struct vmax_single_config {
	uint32_t min_thr;
	uint32_t vmax;
};

struct vmax_config {
	int vmax_cfg_num;
	struct vmax_single_config vmax_cfg_total[];
};

struct aw87xxx_monitor {
	uint8_t first_entry;
	uint8_t timer_cnt;
	uint8_t cfg_update_flag;
	uint8_t update_num;
	uint32_t monitor_flag;
	uint32_t timer_cnt_max;
	uint32_t timer_val;
	uint32_t vbat_sum;
	uint32_t custom_capacity;
	uint32_t pre_vmax;

	struct hrtimer timer;
	struct work_struct work;
	struct vmax_config *vmax_cfg;
};

/**********************************************************
 * aw87xxx monitor function
***********************************************************/
void aw87xxx_monitor_stop(struct aw87xxx_monitor *monitor);
void aw87xxx_monitor_init(struct aw87xxx_monitor *monitor);
void aw87xxx_parse_monitor_dt(struct aw87xxx_monitor *monitor);
void aw87xxx_monitor_work_func(struct work_struct *work);

/**********************************************************
 * aw87xxx dsp
***********************************************************/
#define AWINIC_ADSP_ENABLE

#define AFE_PARAM_ID_AWDSP_RX_SET_ENABLE		(0x10013D11)
#define AFE_PARAM_ID_AWDSP_RX_PARAMS			(0x10013D12)
#define AFE_PARAM_ID_AWDSP_TX_SET_ENABLE		(0x10013D13)
#define AFE_PARAM_ID_AWDSP_RX_VMAX_L			(0X10013D17)
#define AFE_PARAM_ID_AWDSP_RX_VMAX_R			(0X10013D18)
#define AFE_PARAM_ID_AWDSP_RX_CALI_CFG_L		(0X10013D19)
#define AFE_PARAM_ID_AWDSP_RX_CALI_CFG_R		(0x10013d1A)
#define AFE_PARAM_ID_AWDSP_RX_RE_L			(0x10013d1B)
#define AFE_PARAM_ID_AWDSP_RX_RE_R			(0X10013D1C)
#define AFE_PARAM_ID_AWDSP_RX_NOISE_L			(0X10013D1D)
#define AFE_PARAM_ID_AWDSP_RX_NOISE_R			(0X10013D1E)
#define AFE_PARAM_ID_AWDSP_RX_F0_L			(0X10013D1F)
#define AFE_PARAM_ID_AWDSP_RX_F0_R			(0X10013D20)
#define AFE_PARAM_ID_AWDSP_RX_REAL_DATA_L		(0X10013D21)
#define AFE_PARAM_ID_AWDSP_RX_REAL_DATA_R		(0X10013D22)

enum afe_param_id_awdsp {
	INDEX_PARAMS_ID_RX_PARAMS = 0,
	INDEX_PARAMS_ID_RX_ENBALE,
	INDEX_PARAMS_ID_TX_ENABLE,
	INDEX_PARAMS_ID_RX_VMAX,
	INDEX_PARAMS_ID_RX_CALI_CFG,
	INDEX_PARAMS_ID_RX_RE,
	INDEX_PARAMS_ID_RX_NOISE,
	INDEX_PARAMS_ID_RX_F0,
	INDEX_PARAMS_ID_RX_REAL_DATA,
	INDEX_PARAMS_ID_MAX
};

enum {
	MTK_DSP_MSG_TYPE_DATA = 0,
	MTK_DSP_MSG_TYPE_CMD = 1,
};

enum aw_vmax_percentage {
	VMAX_100_PERCENTAGE = 0x00000000,
	VMAX_086_PERCENTAGE = 0xFFED714D,
	VMAX_075_PERCENTAGE = 0xFFD80505,
	VMAX_063_PERCENTAGE = 0xFFBEAE7E,
	VMAX_NONE = 0xFFFFFFFF,
};

typedef struct mtk_dsp_msg_header {
	int32_t type;
	int32_t params_id;
	int32_t reserver[4];
} mtk_dsp_hdr_t;

/********************************************
 *
 * dsp function
 *
 *******************************************/
int aw_read_data_from_dsp(int index, void *data, int len, int channel);
int aw_write_data_to_dsp(int index, void *data, int len, int channel);

#endif
