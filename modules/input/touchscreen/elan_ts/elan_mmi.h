#ifndef _LINUX_ELAN_MMI_H
#define _LINUX_ELAN_MMI_H

#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>



struct dynamic_anang_para {
	uint16_t origph1;
	uint16_t origph2;
	uint16_t origph3;
};

enum adc_type {
	NORMAL_ADC	= 0xCD,
	SHORT_ADC	= 0x34
};


enum data_type {
	NORMAL_TYPE	= 0x00,
	SHORT_TYPE	= 0xC0,
};


struct csv_struct {
	char store_path[100];
	char csv_name[100];
	char time[100];
	struct rtc_time tm;
	struct timex  txc;
	//struct timespec times;
};


enum ack_type {
	ACK_OK			=	0,
	ERR_TIMEOUT		=	-1,
	ERR_I2CWRITE	=	-2,
	ERR_I2CREAD		=	-3,
	ERR_I2CPOLL		=	-4,
	ERR_DEVSTATUS	=	-5,
	ERR_DEVACK		=	-6,

	ERR_DISABLALG	=	-7,
	ERR_BUFEMPTY	=	-8,
	ERR_BUFFALLOC	=	-9,
	ERR_DYNAMICANALOG	=	-10,
	ERR_RECALIBRATE	=	-11,

	ERR_NORMALADC	= -12,
	ERR_SKIPFRAME	= -13,
	ERR_GETNORMALADC	=	-14,
	ERR_TESTMODE		= -15,
	ERR_RXOPEN			=	-16,
	ERR_TESTFRAME		=	-17,
	ERR_RXOPENTEST		= -18,

	ERR_SETPHX			= -19,
	ERR_LBTEST			= -20,
	

	ERR_SHORTMODE		= -21,
	ERR_GETSHORTDATA	= -22,
	ERR_SHORTDATA		= -23,
	ERR_SHORTTEST		= -24,
	ERR_MEANLBTEST		= -25,

	ERR_TXOPENTEST		= -26,
	ERR_TXOPEN			= -27,

	ERR_TXRXSHORT		= -28,
	ERR_DISABLEREPOR	= -29,

	ERR_NOISETEST		= -30,

	ERR_GETRAWDATA	=	-120,
	ERR_TPMODUINIT	=	-121,	

};

struct noise_limit {
	int *noise_limit_hb;
	int *noise_limit_lb;
	int *noise_test_hb;
	int *noise_test_lb;
	int noise_test_hb_fail_point;
	int noise_test_lb_fail_point;
};

struct analog_parameter {
	int ph1;
	int ph2;
	int ph3;
};


#define NOISE_ADC_PRINT    0
#define SHORT_DATA_PRINT    1
#define RXTX_DIFF_PRINT    2

#define VAILD_DATA_LEN	60

#define RAW_DATALEN_HIGHBYTE		11
#define RAW_DATALEN_LOWBYTE		12

#define NoiseTestHB	"noise_test_hb"
#define NoiseTestLB	"noise_test_lb"
#define NoiseTestFailPoint "noise_test_fail_point"
#define NoiseTestLimitHB	"noise_test_limit_hb"
#define NoiseTestLimitLB	"noise_test_limit_lb"
#define NoiseSkipFrame	2
#define NoiseTestFrame	10


#define TP_Test_Version "MT Build in Driver V1.0.1"
#endif





