#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "adi_hal_internal.h"
#include <asm/arch/common.h>
#include <otp_helper.h>
#include <sprd_pmic_misc.h>

#define KLT8	0x6B4C5438
#define KL	0x6B4C0000
#define SHAR	0x53686172
#define E2	0x65320000
#define WHAL	0x5768616C

int sprd_get_chipid(int *chip_id, int *version_id)
{

	unsigned int chip_id0 = 0, chip_id1 = 0;
	int ch_id;
	int ver_id;

	chip_id0 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID0);
	chip_id1 = __raw_readl((void *)REG_AON_APB_AON_CHIP_ID1);

	switch (chip_id1) {
	case SHAR:
		switch (chip_id0) {
		case KL:
			ch_id = 0x9830;
			break;
		case KLT8:
			ch_id = 0x9838;
			break;
		default:
			ch_id = 0;
			break;
		}
		break;

	case WHAL:
		switch (chip_id0) {
		case E2:
			ch_id = 0x9850;
			break;
		default:
			ch_id = 0;
			break;
		}
		break;

	default:
		ch_id = 0;
		break;
	}

	ver_id = __raw_readl((void *)REG_AON_APB_AON_VER_ID);

	if (!chip_id || !version_id) {
		debugf("chip id = 0x%x, VID = 0x%x\n",ch_id, ver_id);
		return 0;
	}

	*chip_id = ch_id;
	*version_id = ver_id;

	return 0;
}

void misc_init()
{
	pmic_misc_init();

	sprd_get_chipid(NULL, NULL);
}

typedef struct mem_cs_info
{
	uint32_t cs_number;
	uint32_t cs0_size;//bytes
	uint32_t cs1_size;//bytes
}mem_cs_info_t;
PUBLIC int get_dram_cs_number(void)
{
	mem_cs_info_t *cs_info_ptr = 0x1C00;
	return cs_info_ptr->cs_number;
}
PUBLIC int get_dram_cs0_size(void)
{
	mem_cs_info_t *cs_info_ptr = 0x1C00;
	return cs_info_ptr->cs0_size;
}

