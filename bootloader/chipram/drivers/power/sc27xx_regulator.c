#include <common.h>
#include <adi.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_chipram_env.h>

typedef struct
{
	const char* name;
	uint16 type;
	uint32 pd_set;
	uint32 pd_set_bit;
	uint32 vol_base;
	uint32 vol_step;
	uint32 vol_trm;
	uint32 vol_trm_bits;
	uint16 vol_def;
} sci_regu_ctl, * sci_regu_ctl_ptr;

#define WR_UNLOCK 0x6e7f
#define DCDC_WR_UNLOCK 0x2017

#define SCI_REGU_REG(VDD, VDD_TYPE, PD_SET, SET_BIT, VOL_BASE, VOL_STEP, VOL_TRM, VOL_TRM_BITS, VOL_DEF) \
{ \
	#VDD, VDD_TYPE, PD_SET, SET_BIT, VOL_BASE, VOL_STEP, VOL_TRM, VOL_TRM_BITS, VOL_DEF \
},

/**---------------------------------------------------------------------------*
 **                         Local variables                                  *
 **---------------------------------------------------------------------------*/
#ifdef CONFIG_ADIE_SC2721
static sci_regu_ctl regu_ctl_tbl[] =
{
	SCI_REGU_REG(vddcpu, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_CPU_PD,
		     400, 3125, ANA_REG_GLB_DCDC_CPU_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 900)
	SCI_REGU_REG(vddcore, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_CORE_PD,
		 400, 3125, ANA_REG_GLB_DCDC_CORE_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 900)
	SCI_REGU_REG(vddmem, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_MEM_PD,
		 400, 3125, ANA_REG_GLB_DCDC_MEM_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9), 1400)
	SCI_REGU_REG(vddgen, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_GEN_PD,
		 600, 3125, ANA_REG_GLB_DCDC_GEN_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9), 1850)
	SCI_REGU_REG(vddemmccore, 0x10, ANA_REG_GLB_LDO_EMMCCORE_PD_REG, BIT_LDO_EMMCCORE_PD,
		 1200, 10000, ANA_REG_GLB_LDO_EMMCCORE_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 3000)
	SCI_REGU_REG(vddsdcore, 0x10, ANA_REG_GLB_LDO_SD_PD_REG, BIT_LDO_SDCORE_PD,
		 1200, 10000, ANA_REG_GLB_LDO_SD_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7),	3000)
	SCI_REGU_REG(vddsdio, 0x10, ANA_REG_GLB_LDO_SDIO_PD_REG, BIT_LDO_SDIO_PD,
		 1200, 10000, ANA_REG_GLB_LDO_SDIO_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 3000)
	SCI_REGU_REG(ldomem, 0x10, ANA_REG_GLB_POWER_PD_SW, BIT_LDO_MEM_PD,
			 1100, 6250, ANA_REG_GLB_LDO_MEM_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6), 1250)
};
#elif defined(CONFIG_ADIE_SC2720)
static sci_regu_ctl regu_ctl_tbl[] =
{
	SCI_REGU_REG(vddcore, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_CORE_PD,
		 0, 3125, ANA_REG_GLB_DCDC_CORE_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 900)
	SCI_REGU_REG(vddgen, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_GEN_PD, 1300,
		 12500,	ANA_REG_GLB_DCDC_GEN_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 1850)
	SCI_REGU_REG(ldomem, 0x10, ANA_REG_GLB_POWER_PD_SW, BIT_LDO_MEM_PD, 800,
		 12500,	ANA_REG_GLB_LDO_MEM_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5), 1200)
	SCI_REGU_REG(vddemmccore, 0x10, ANA_REG_GLB_LDO_EMMCCORE_PD_REG, BIT_LDO_EMMCCORE_PD,
		 2000, 12500, ANA_REG_GLB_LDO_EMMCCORE_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6), 3000)
	SCI_REGU_REG(vddsdcore, 0x10, ANA_REG_GLB_LDO_SD_PD_REG, BIT_LDO_SDCORE_PD,
		 2000, 12500, ANA_REG_GLB_LDO_SD_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6), 3000)
	SCI_REGU_REG(vddsdio, 0x10, ANA_REG_GLB_LDO_SDIO_PD_REG, BIT_LDO_SDIO_PD,
		 1612, 12500, ANA_REG_GLB_LDO_SDIO_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6), 3000)
};
#elif defined(CONFIG_ADIE_SC2730)
static sci_regu_ctl regu_ctl_tbl[] =
{
	SCI_REGU_REG(vddsram, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_SRAM_PD,
		 0, 3125, ANA_REG_GLB_DCDC_SRAM_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 800)
	SCI_REGU_REG(vddmemq, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_MEMQ_PD,
		 0, 3125, ANA_REG_GLB_DCDC_MEMQ_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 600)
	SCI_REGU_REG(vddmodem, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_MODEM_PD,
		 0, 3125, ANA_REG_GLB_DCDC_MODEM_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 800)
	SCI_REGU_REG(vddgen0, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_GEN0_PD,
		 20, 9375, ANA_REG_GLB_DCDC_GEN0_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 1875)
	SCI_REGU_REG(vddgen1, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_GEN1_PD,
		 50, 6250, ANA_REG_GLB_DCDC_GEN1_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 1350)
	SCI_REGU_REG(vddmem, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_MEM_PD,
		 0, 6250, ANA_REG_GLB_DCDC_MEM_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 1100)
	SCI_REGU_REG(vddcore, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_CORE_PD,
		 0, 3125, ANA_REG_GLB_DCDC_CORE_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 800)
	SCI_REGU_REG(vddcpu, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_CPU_PD,
		 0, 3125, ANA_REG_GLB_DCDC_CPU_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 800)
	SCI_REGU_REG(vddgpu, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT_DCDC_GPU_PD,
		 0, 3125, ANA_REG_GLB_DCDC_GPU_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 800)
	SCI_REGU_REG(vddsdcore, 0x10, ANA_REG_GLB_LDO_SD_PD_REG, BIT_LDO_SDCORE_PD,
		 1200, 10000, ANA_REG_GLB_LDO_SD_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7),	3000)
	SCI_REGU_REG(vddsdio, 0x10, ANA_REG_GLB_LDO_SDIO_PD_REG, BIT_LDO_SDIO_PD,
		 1200, 10000, ANA_REG_GLB_LDO_SDIO_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 3000)
};
#elif defined(CONFIG_ADIE_SC2731)
static sci_regu_ctl regu_ctl_tbl[] =
{
	SCI_REGU_REG(vddarm0, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT(4),
		 400, 3125, ANA_REG_GLB_DCDC_ARM0_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 900)
	SCI_REGU_REG(vddarm1, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT(3),
		 400, 3125, ANA_REG_GLB_DCDC_ARM1_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 900)
	SCI_REGU_REG(vddcore, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT(6),
		 400, 3125, ANA_REG_GLB_DCDC_CORE_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 900)
	SCI_REGU_REG(vddgpu, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT(5),
		 400, 3125, ANA_REG_GLB_DCDC_GPU_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8), 900)
	SCI_REGU_REG(vddmem, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT(7),
		 400, 3125, ANA_REG_GLB_DCDC_MEM_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9), 1000)
	SCI_REGU_REG(vddgen, 0x12, ANA_REG_GLB_POWER_PD_SW, BIT(8),
		 600, 3125, ANA_REG_GLB_DCDC_GEN_VOL, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7)|BIT(8)|BIT(9), 1800)
	SCI_REGU_REG(vddemmccore, 0x10, ANA_REG_GLB_LDO_EMMCCORE_REG0, BIT(0),
		 1200, 10000, ANA_REG_GLB_LDO_EMMCCORE_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 3000)
	SCI_REGU_REG(vddsdcore, 0x10, ANA_REG_GLB_LDO_SD_PD_REG, BIT(0),
		 1200, 10000, ANA_REG_GLB_LDO_SD_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 3000)
	SCI_REGU_REG(vddsdio, 0x10, ANA_REG_GLB_LDO_SDIO_PD_REG, BIT(0),
		 1200, 10000, ANA_REG_GLB_LDO_SDIO_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 3000)
	SCI_REGU_REG(vddsram, 0x10, ANA_REG_GLB_LDO_SRAM_PD_REG, BIT(0),
		 1200, 6250, ANA_REG_GLB_LDO_VDDSRAM_REG1, BIT(0)|BIT(1)|BIT(2)|BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7), 1800)
};
#endif

#define LDO_NUMBER_MAX	(ARRAY_SIZE(regu_ctl_tbl))

static int __ffs(int x)
{
	uint32 bits_len = 8 * sizeof(x), i = 0;

	while(bits_len--) {
		if(x & 0x1)
			break;
		x = x >> 1;
		i++;
	}
	return i;
}

static int get_regu_index(char *p_name)
{
	uint8 i = 0;

	for(i = 0; i < LDO_NUMBER_MAX; i++) {
		if(0 == sprd_strcmp(regu_ctl_tbl[i].name, p_name)) {
			return i;
		}
	}

	return LDO_NUMBER_MAX;
}

static sci_regu_ctl_ptr get_regu_ctl(char *p_name)
{
	sci_regu_ctl_ptr ldo_ctl = NULL;
	uint8 idx = get_regu_index(p_name);

	if(idx < LDO_NUMBER_MAX)
		ldo_ctl = &regu_ctl_tbl[idx];

	return ldo_ctl;
}

#ifdef CONFIG_ADIE_SC2721
int regulator_init()
{
	ANA_REG_SET(ANA_REG_GLB_DCDC_VLG_SEL,
		    BIT_VOL_MODE |
		    BIT_DCDC_CPU_VOL_SEL |
		    BIT_DCDC_CORE_VOL_SEL |
		    BIT_DCDC_CORE_NOR_SW_SEL|
		    BIT_DCDC_CORE_SLP_SW_SEL|
		    //BIT_DCDC_GEN_SW_SEL |
		    //BIT_DCDC_WPA_SW_SEL |
		    BIT_DCDC_CPU_SW_SEL|
		    BIT_DCDC_MEM_SW_SEL
		);

	ANA_REG_OR(ANA_REG_GLB_LDO_SD_PD_REG,BIT_LDO_SDCORE_PD);
	ANA_REG_OR(ANA_REG_GLB_LDO_SDIO_PD_REG,BIT_LDO_SDIO_PD);
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(WR_UNLOCK));
	return 0;
}
#elif defined(CONFIG_ADIE_SC2720)
int regulator_init()
{
	ANA_REG_SET(ANA_REG_GLB_DCDC_VLG_SEL,
		BIT_DCDC_CORE_SLP_SW_SEL|
		BIT_DCDC_CORE_NOR_SW_SEL
		);
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(WR_UNLOCK));
	ANA_REG_OR(ANA_REG_GLB_LDO_SD_PD_REG, BIT_LDO_SDCORE_PD);
	ANA_REG_OR(ANA_REG_GLB_LDO_SDIO_PD_REG, BIT_LDO_SDIO_PD);
	return 0;
}
#elif defined(CONFIG_ADIE_SC2730)
int regulator_init()
{
	ANA_REG_SET(ANA_REG_GLB_DCDC_VLG_SEL0,
		BIT_DCDC_MEMQ_SW_SEL|
		BIT_DCDC_CORE_NOR_SW_SEL
		);
	ANA_REG_SET(ANA_REG_GLB_DCDC_VLG_SEL1,
		BIT_DCDC_SRAM_SW_SEL|
		BIT_DCDC_GPU_SW_SEL|
		BIT_DCDC_CPU_SW_SEL|
		BIT_DCDC_MODEM_SW_SEL|
		BIT_DCDC_MEM_SW_SEL
		);
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(WR_UNLOCK));
	ANA_REG_SET(ANA_REG_GLB_DCDC_WR_PROT_VALUE, BITS_DCDC_WR_PROT_VALUE(DCDC_WR_UNLOCK));
	ANA_REG_OR(ANA_REG_GLB_LDO_SD_PD_REG,BIT_LDO_SDCORE_PD);
	ANA_REG_OR(ANA_REG_GLB_LDO_SDIO_PD_REG,BIT_LDO_SDIO_PD);
	return 0;
}
#elif defined(CONFIG_ADIE_SC2731)
int regulator_init()
{
	ANA_REG_SET(ANA_REG_GLB_DCDC_VLG_SEL,
		    BIT_DCDC_CORE_NOR_SW_SEL|
		    BIT_DCDC_CORE_SLP_SW_SEL|
		    BIT_DCDC_GPU_NOR_SW_SEL|
		    BIT_DCDC_GPU_SLP_SW_SEL|
		    BIT_DCDC_ARM0_SW_SEL|
		    BIT_DCDC_ARM1_SW_SEL|
		    BIT_DCDC_MEM_SW_SEL
		    );
	ANA_REG_OR(ANA_REG_GLB_LDO_SD_PD_REG,BIT_LDO_SDCORE_PD);
	ANA_REG_OR(ANA_REG_GLB_LDO_SDIO_PD_REG,BIT_LDO_SDIO_PD);
	ANA_REG_SET(ANA_REG_GLB_PWR_WR_PROT_VALUE, BITS_PWR_WR_PROT_VALUE(WR_UNLOCK));
	return 0;
}
#endif

int regulator_enable(char *p_name)
{
	sci_regu_ctl_ptr ctl = get_regu_ctl(p_name);

	if (ctl->pd_set == NULL) {
		return -1;
	}

	ANA_REG_AND(ctl->pd_set, ~ctl->pd_set_bit);

	return 0;
}

int regulator_disable(char *p_name)
{
	sci_regu_ctl_ptr ctl = get_regu_ctl(p_name);
	ANA_REG_OR(ctl->pd_set, ctl->pd_set_bit);
	return 0;
}

static int set_voltage_direct(char *p_name, int min)
{
	sci_regu_ctl_ptr ctl = get_regu_ctl(p_name);
	int mv = min;
	int reg_val = 0;
	int shft;
	uint16 base,step;
	uint32 adi_tmp_val;

	 shft = __ffs(ctl->vol_trm_bits);
	 base = ctl->vol_base;
	 step = ctl->vol_step;

	reg_val = DIV_ROUND_UP((int)(mv - base) * 1000, step);

	if((NULL == ctl->vol_trm) || (reg_val < 0))
		return -1;

	if(reg_val > (ctl->vol_trm_bits >> shft))
		reg_val = (ctl->vol_trm_bits >> shft);

	adi_tmp_val = sci_adi_read(ctl->vol_trm);
	adi_tmp_val &= (uint16)(~(ctl->vol_trm_bits));
	adi_tmp_val |= (uint16)((reg_val << shft)&(ctl->vol_trm_bits));
	sci_adi_raw_write(ctl->vol_trm, adi_tmp_val);

    return 0;
}

static int dcdc_set_voltage(char *p_name, int min)
{
	int to_vol;
	int step;
	int vol;

	vol = regulator_get_voltage(p_name);
	to_vol = min;
	/* uV */
	step = 25;

	if (vol < to_vol) {
		do {
			vol += step;
			if (vol > to_vol)
				vol = to_vol;
			set_voltage_direct(p_name, vol);
		} while (vol < to_vol);
	} else {
		do {
			vol -= step;
			if (vol < to_vol)
				vol = to_vol;
			set_voltage_direct(p_name, vol);
		} while (vol > to_vol);
	}
	return 0;
}

int regulator_set_voltage(char *p_name, int to_vol)
{
	int ret = 0;
	sci_regu_ctl_ptr ctl = get_regu_ctl(p_name);
	int vdd_type = ctl->type & (BIT(4) - 1);

	if (vdd_type == 2 /*VDD_TYP_DCDC*/)
		ret = dcdc_set_voltage(p_name,to_vol);
	else if (vdd_type == 0 /*VDD_TYP_LDO*/)
		ret = set_voltage_direct(p_name, to_vol);
	return ret;
}

int regulator_get_voltage(char *p_name)
{
	sci_regu_ctl_ptr ctl = get_regu_ctl(p_name);
	int mv = 0;
	uint32 reg_val = 0;
	int lev = -1;

	if(NULL == ctl->vol_trm)
		return -1;

	reg_val = sci_adi_read(ctl->vol_trm);
	reg_val = ( reg_val & ctl->vol_trm_bits) >> __ffs(ctl->vol_trm_bits);
	mv = ctl->vol_base + reg_val * ctl->vol_step / 1000;

    return mv;
}

