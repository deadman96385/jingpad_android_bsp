#ifndef _DDRC_FEATURE_INIT
#define _DDRC_FEATURE_INIT
#include "ddrc_common.h"
/***************************************************QOSC***********************************************/
#define PUB_CHN_NUM	7

//urgent
#define QOS_SWITCH							(PUB_CTL_APB_BASE_ADDR+0x31C8)
#define PUB_AXI_QOS_URGENT_REG_0			(PUB_CTL_APB_BASE_ADDR+0x3200)
#define PUB_AXI_QOS_URGENT_REG_1			(PUB_CTL_APB_BASE_ADDR+0x3204)
#define QOS_THRESHOLD_0						(PUB_CTL_APB_BASE_ADDR+0x3418)
#define QOS_THRESHOLD_1						(PUB_CTL_APB_BASE_ADDR+0x341C)

//ap qos
#define AP_QOS0								(AP_AHB_RF_BASE_ADDR+0x00b0)
#define AP_QOS1								(AP_AHB_RF_BASE_ADDR+0x00b8)
#define AP_QOS2								(AP_AHB_RF_BASE_ADDR+0x00bc)

typedef struct QOS_TIMEOUT_CHN
{
	u8 timeout_thr_rd_ch;
	u8 timeout_thr_wr_ch;
	u8 pri_wr_ch;
	u8 pri_rd_ch;
}QOS_TIMEOUT_CHN_T;



#define RF_LINEAR_BASE_CHN0		0x0
#define RF_LINEAR_BASE_CHN1		0x0
#define RF_LINEAR_BASE_CHN2		0x0
#define RF_LINEAR_BASE_CHN3		0x0
#define RF_INTERLEAVE_BASE			0x0
#define RF_INTERLEAVE_OFFSET		0x0

typedef enum INTERLEAVE_SIZE{
	INT_SIZE_64B=0x0,
	INT_SIZE_128B,
	INT_SIZE_256B,
	INT_SIZE_512B,
	INT_SIZE_1KB,
	INT_SIZE_2KB,
	INT_SIZE_4KB,
	INT_SIZE_8KB,
}INTERLEAVE_SIZE_E;


void ddrc_ctrl_qos_set();
void ddrc_ctrl_interleave_set(u32 intlv_size );
#endif
