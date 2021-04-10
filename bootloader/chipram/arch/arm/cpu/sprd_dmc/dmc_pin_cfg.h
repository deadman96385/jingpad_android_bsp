#ifndef __DMC_PIN_CFG_H__
#define __DMC_PIN_CFG_H__
typedef enum __DMC_PIN_NAME {	
	DMC_PIN_DQ_BYTE0,	/*DQ0~7 + DM0*/
	DMC_PIN_DQ_BYTE1,	/*DQ8~15 + DM1*/
	DMC_PIN_DQ_BYTE2,	/*DQ16~23 + DM2*/
	DMC_PIN_DQ_BYTE3,	/*DQ24~31 + DM3*/	
	DMC_PIN_DQS0_T,		/*DQS0_T*/
	DMC_PIN_DQS0_C,		/*DQS0_C*/
	DMC_PIN_DQS1_T,		/*DQS1_T*/
	DMC_PIN_DQS1_C,		/*DQS1_C*/
	DMC_PIN_DQS2_T,		/*DQS2_T*/
	DMC_PIN_DQS2_C,		/*DQS2_C*/
	DMC_PIN_DQS3_T,		/*DQS3_T*/
	DMC_PIN_DQS3_C,		/*DQS3_C*/
	DMC_PIN_CA,			/*CA0~9*/
	DMC_PIN_CK_T,		/*CK_T*/
	DMC_PIN_CK_C,		/*CK_C*/
	DMC_PIN_CS0,		/*CS0*/
	DMC_PIN_CS1,		/*CS1*/
	DMC_PIN_CKE0,		/*CKE0*/
	DMC_PIN_CKE1,		/*CKE1*/
	DMC_PIN_INVALID		/*end of enum*/
}DMC_PIN_TEAM_NAME;

typedef enum __DMC_POLAR_TYPE {
	DMC_POLAR_PMOS,
	DMC_POLAR_NMOS,	
}DMC_POLAR_TYPE;

#define PIN_REG_BASE 0x402a0000
#define REG_DRV_PIN_DQ_BYTE0	(PIN_REG_BASE+0x26c)
#define REG_DRV_PIN_DQ_BYTE1	(PIN_REG_BASE+0x298)
#define REG_DRV_PIN_DQ_BYTE2	(PIN_REG_BASE+0x308)
#define REG_DRV_PIN_DQ_BYTE3	(PIN_REG_BASE+0x334)
#define REG_DRV_PIN_DQS0_T		(PIN_REG_BASE+0x250)
#define REG_DRV_PIN_DQS0_C		(PIN_REG_BASE+0x254)
#define REG_DRV_PIN_DQS1_T		(PIN_REG_BASE+0x27C)
#define REG_DRV_PIN_DQS1_C		(PIN_REG_BASE+0x280)
#define REG_DRV_PIN_DQS2_T		(PIN_REG_BASE+0x2eC)
#define REG_DRV_PIN_DQS2_C		(PIN_REG_BASE+0x2f0)
#define REG_DRV_PIN_DQS3_T		(PIN_REG_BASE+0x318)
#define REG_DRV_PIN_DQS3_C		(PIN_REG_BASE+0x31c)
#define REG_DRV_PIN_CA			(PIN_REG_BASE+0x2d4)
#define REG_DRV_PIN_CK_T		(PIN_REG_BASE+0x2b0)
#define REG_DRV_PIN_CK_C		(PIN_REG_BASE+0x2b4)
#define REG_DRV_PIN_CS0			(PIN_REG_BASE+0x2dc)
#define REG_DRV_PIN_CS1			(PIN_REG_BASE+0x2d8)
#define REG_DRV_PIN_CKE0		(PIN_REG_BASE+0x2bc)
#define REG_DRV_PIN_CKE1		(PIN_REG_BASE+0x2b8)

typedef struct __DMC_PIN_DRV_INFO {
	DMC_PIN_TEAM_NAME name;
	u32 drv_cfg_reg;
	int drv_pos_target;
	int drv_neg_target;
}DMC_PIN_DRV_INFO;

typedef struct __DMC_PIN_PULL_INFO {
	DMC_PIN_TEAM_NAME name;
	u32 drv_cfg_reg;
	PULL_RESIS_VAL resis_val;
}DMC_PIN_PULL_INFO;



#define AON_APB_BASE 0x402e0000
#define REG_DDR_ZQ_CAL (AON_APB_BASE+0x60)

void dmc_set_drv_target(int drv);

#endif

