#ifndef __DMC_SPRD_R3P0_BIST_H__
#define __DMC_SPRD_R3P0_BIST_H__

#define BIST_OK			0
#define BIST_FAIL		-1
#define BIST_TOUT		-2
#define BIST_PARA_ERR		-3

typedef enum __BIST_ADDR_MODE{
	BIST_MODE_ADDR_LEN,
	BIST_MODE_MATRIX,
}BIST_ADDR_MODE;

typedef enum __BIST_TYPE {
	BIST_TYPE_LFSR,
	BIST_TYPE_SIPI,
	BIST_TYPE_USRDEF,
	BIST_TYPE_USRDEF_INC,
}BIST_TYPE;

typedef enum __BIST_OP_MODE {
	BIST_OP_MODE_RW,
	BIST_OP_MODE_WRONLY,
	BIST_OP_MODE_RDONLY,
	BIST_OP_MODE_RESERVED
}BIST_OP_MODE;

typedef struct __BIST_LFSR_PARA {
	BIST_OP_MODE op_mode;
	u32 saddr;
	u32 len;
	u32 seed_val;
}BIST_LFSR_PARA;

typedef struct __BIST_SIPI_PARA {
	BIST_OP_MODE op_mode;
	u32 saddr;
	u32 len;
	u32 pattern_data[8];
}BIST_SIPI_PARA;

typedef struct __BIST_USRDEF_PARA {
	BIST_OP_MODE op_mode;
	u32 saddr;
	u32 len;
	u32 pattern_data[8];
}BIST_USRDEF_PARA;

typedef struct __BIST_USRDEF_INC_PARA {
	BIST_OP_MODE op_mode;
	u32 saddr;
	u32 len;
	u32 pattern_data[8];
}BIST_USRDEF_INC_PARA;

extern int dmc_bist_test(BIST_TYPE bist_type, void *para);

#endif
