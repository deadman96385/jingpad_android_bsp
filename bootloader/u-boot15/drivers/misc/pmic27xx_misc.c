#include <common.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include "adi_hal_internal.h"
#include <asm/arch/common.h>
#include <otp_helper.h>
#include <sprd_pmic_misc.h>


#define PBINT_7S_HW_FLAG (BIT(7))	//Only Hard 7s reset flag
#define PBINT_7S_SW_FLAG (BIT(12))	//All 7S reset flag,HW OR SW

static u32 pbint_7s_flag = 0;

int is_7s_reset(void)
{
	return pbint_7s_flag & PBINT_7S_SW_FLAG;
}

int is_7s_reset_for_systemdump(void)
{
	int val;
	int mask = PBINT_7S_SW_FLAG | PBINT_7S_HW_FLAG;

	val = pbint_7s_flag & mask;

	return (val == PBINT_7S_SW_FLAG);
}

static inline int pbint_7s_rst_disable(uint32_t disable)
{
	if (disable) {
		sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_DISABLE);
	} else {
		sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_DISABLE);
	}
	return 0;
}

static inline int pbint_7s_rst_set_2keymode(uint32_t mode)
{
#if defined CONFIG_ADIE_SC2723S || defined CONFIG_ADIE_SC2723
	if (!mode) {
		sci_adi_set(ANA_REG_GLB_SWRST_CTRL, BIT_KEY2_7S_RST_EN);
	} else {
		sci_adi_clr(ANA_REG_GLB_SWRST_CTRL, BIT_KEY2_7S_RST_EN);
	}
#elif defined(CONFIG_ADIE_SC2721) || defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	if (!mode) {
		sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_KEY2_7S_RST_EN);
	} else {
		sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_KEY2_7S_RST_EN);
	}
#else
	if (!mode) {
		sci_adi_set(ANA_REG_GLB_SWRST_CTRL0, BIT_KEY2_7S_RST_EN);
	} else {
		sci_adi_clr(ANA_REG_GLB_SWRST_CTRL0, BIT_KEY2_7S_RST_EN);
	}
#endif
	return 0;
}
static inline int pbint_7s_rst_set_sw(uint32_t mode)
{
	if (mode) {
		sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_MODE);
	} else {
		sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_MODE);
	}
	return 0;
}

static inline int pbint_7s_rst_set_swmode(uint32_t mode)
{
	if (mode) {
		sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_SWMODE);
	} else {
		sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_RST_SWMODE);
	}
	return 0;
}

static inline int pbint_7s_rst_set_threshold(uint32_t th)
{
#if defined CONFIG_ADIE_SC2723S || defined CONFIG_ADIE_SC2723
	th = (th - 1)/2;
#else
	if (th > 2) th--;
#endif
	sci_adi_write(ANA_REG_GLB_POR_7S_CTRL, BITS_PBINT_7S_RST_THRESHOLD(th), BITS_PBINT_7S_RST_THRESHOLD(~0));
	return 0;
}

int pbint_7s_rst_cfg(uint32_t en, uint32_t sw_rst, uint32_t short_rst)
{
	pbint_7s_flag = sci_adi_read(ANA_REG_GLB_POR_SRC_FLAG);
	sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_FLAG_CLR);
	udelay(10);
	sci_adi_clr(ANA_REG_GLB_POR_7S_CTRL, BIT_PBINT_7S_FLAG_CLR); //it is necessary,

	/* ignore sw_rst, please refer to config.h */
	if (en) {
		pbint_7s_rst_set_threshold(CONFIG_7S_RST_THRESHOLD);
		pbint_7s_rst_set_sw(!sw_rst);

		pbint_7s_rst_set_swmode(short_rst);

		pbint_7s_rst_set_2keymode(CONFIG_7S_RST_2KEY_MODE);
	}
	return pbint_7s_rst_disable(!en);
}

void enable_ext_reset_mode(void)
{
	sci_adi_set(ANA_REG_GLB_POR_7S_CTRL, BIT_EXT_RSTN_MODE);
}

int sprd_get_pmic_chipid(void)
{
	unsigned int  chip_id = 0;

	chip_id = sci_adi_read(ANA_REG_GLB_CHIP_ID_HIGH) & 0xffff;

	return chip_id;
}

int is_hw_smpl_enable(void)
{
	return !!(sci_adi_read(ANA_REG_GLB_SMPL_CTRL1) & BIT_SMPL_EN);
}

int is_smpl_bootup(void)
{
	int ret = sci_adi_read(ANA_REG_GLB_SMPL_CTRL1) & BIT_SMPL_PWR_ON_FLAG;

	sci_adi_set(ANA_REG_GLB_SMPL_CTRL1, BIT_SMPL_PWR_ON_FLAG_CLR);

	return ret;

}
#define CONFIG_SMPL_EN_KEY			0x1935
#ifdef CONFIG_SMPL_EN
static int smpl_config(void)
{
	u32 val = BITS_SMPL_ENABLE(CONFIG_SMPL_EN_KEY);

	debugf("smpl_config\n");

	val |= BITS_SMPL_MODE(CONFIG_SMPL_THRESHOLD);

	return sci_adi_write(ANA_REG_GLB_SMPL_CTRL0, val, ~0);
}
#endif

void pmic_misc_init(void)
{
	debugf("pmic_misc_init\n");

	pbint_7s_rst_cfg(CONFIG_7S_RST_MODULE_EN,
				CONFIG_7S_RST_SW_MODE,
				CONFIG_7S_RST_SHORT_MODE);

#ifdef CONFIG_SMPL_EN
	smpl_config();
#endif

#if defined CONFIG_ADIE_SC2723S || defined CONFIG_ADIE_SC2723
	sci_adi_set(ANA_REG_GLB_LDO_SHPT_PD2, BIT_LDO_VIBR_SHPT_PD);	//close vibr short protection
#endif

#if defined(CONFIG_ADIE_SC2731) || defined(CONFIG_ADIE_SC2721) \
	|| defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	sci_adi_write(ANA_REG_GLB_OTP_CTRL, (BIT_OTP_EN|BITS_OTP_OP(0)), (BIT_OTP_EN|BITS_OTP_OP(3)));	//open otp and set 135C
#endif

#if defined(CONFIG_ADIE_SC2721) || defined(CONFIG_ADIE_SC2720) || defined(CONFIG_ADIE_SC2730)
	printf("last shutdown flag ANA_REG_GLB_POR_OFF_FLAG:0x%x\n",ANA_REG_GET(ANA_REG_GLB_POR_OFF_FLAG));
	sci_adi_set(ANA_REG_GLB_POR_OFF_FLAG, 0xffff);	//clear power off flag

#endif
	regulator_pmic_init();
}

