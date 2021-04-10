#include <common.h>
#include <asm/io.h>

#include <regs_adi.h>
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_eic.h>
#include <sprd_battery.h>
#include "sprd_chg_helper.h"

#ifdef DEBUG
#define debugf(fmt, args...) do { printf("chg2731 %s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define debugf(fmt, args...)
#endif

#define CHG_CFG0		(ANA_SWICHG_BASE+ 0x00)
#define CHG_CFG1		(ANA_SWICHG_BASE+ 0x04)
#define CHG_CFG2		(ANA_SWICHG_BASE+ 0x08)
#define CHG_CFG3		(ANA_SWICHG_BASE+ 0x0c)
#define CHG_CFG4		(ANA_SWICHG_BASE+ 0x10)
#define CHG_CFG5		(ANA_SWICHG_BASE + 0x28)
#define CHG_CFG6		(ANA_SWICHG_BASE+ 0x2c)

#define RG_SETUP_TIME	(ANA_FLASH_BASE + 0x04)
#define RG_BST_CFG0		(ANA_FLASH_BASE + 0x18)
#define RG_BST_CFG2		(ANA_FLASH_BASE + 0x20)
#define RG_OTG_NEW		(ANA_FLASH_BASE + 0x28)


//RG_SETUP_TIME
#define OTG_SETUP(x)	(((x) & 0x3) << 2)

//RG_BST_CFG0
#define RG_BST_STB_OP(x)	(((x) & 0x3F) << 5)

//RG_BST_CFG2
#define RG_BST_DIS_PFM		BIT(12)
#define RG_BST_DCM_EN		BIT(11)

//RG_OTG_NEW
#define RG_OTG_OCP(x)	(((x) & 0x3))
#define RG_BST_UVLO_DBC(x)	(((x) & 0x3) << 5)


#define SWTCHG_APB_EN		BIT(5)

//CHG_CFG0
#define SPRD2731_CC_EN		BIT(13)
#define BITS_PRECHG_RNG(x)	(((x) & 0x3) << 11)

//CHG_CFG1
#define BITS_CUR(x)			((x) & 0x3f)

/* CHG_CFG5 */
#define BITS_ICRSET(x)		(((x) & 0x3) << 8)

/* CHG_PD */
#define SC2731_CHG_PD			BIT(0)

int sprd_charge_pd_control(bool enable)
{
	if (enable)
		return sci_adi_write(CHG_CFG0, 0, SC2731_CHG_PD);

	return sci_adi_write(CHG_CFG0, SC2731_CHG_PD,
			     SC2731_CHG_PD);
}

static void sprd2731_chg_init(void)
{
	debugf("sprd2731_init\n");
	sci_adi_set(ANA_REG_GLB_MODULE_EN1, SWTCHG_APB_EN);

	//for otg setting
	sci_adi_write(RG_BST_CFG0, RG_BST_STB_OP(0x3c),
		  RG_BST_STB_OP(~0));
	sci_adi_write(RG_BST_CFG2, RG_BST_DIS_PFM,
		  (RG_BST_DIS_PFM | RG_BST_DCM_EN));
	sci_adi_write(RG_SETUP_TIME, OTG_SETUP(~0),
		  OTG_SETUP(~0));
	//CA or later version, use this setup
	if (sci_adi_read(ANA_REG_GLB_CHIP_ID_LOW) >= 0xC000) {
		sci_adi_write(RG_OTG_NEW, RG_OTG_OCP(2) | RG_BST_UVLO_DBC(~0),
			RG_OTG_OCP(~0) | RG_BST_UVLO_DBC(~0));
	}
}

static void sprd2731_chg_leakage_cur_config(void)
{
	debugf("sprd2731_chg_leakage_cur_config\n");
	sci_adi_write(CHG_CFG6, 0xA86, 0xFFF);
}

static void sprd2731_chg_start_charge(int value)
{
	sci_adi_set(CHG_CFG0, SPRD2731_CC_EN);
	sci_adi_write(CHG_CFG0, 0, BIT(0));
}

static void sprd2731_chg_stop_charge(int value)
{
	sci_adi_write(CHG_CFG0, BIT(0), 0);
}

static void sprd2731_chg_set_current_limit(unsigned int cur)
{
	unsigned char reg_val;

	if (cur <= 100)
		reg_val = 0;
	else if (cur <= 500)
		reg_val = 3;
	else if (cur <= 900)
		reg_val = 2;
	else
		reg_val = 1;
	sci_adi_write(CHG_CFG5, BITS_ICRSET(reg_val), BITS_ICRSET(~0U));
}

static void sprd2731_chg_set_chg_cur(uint32_t chg_current)
{
	BYTE reg_val;
	reg_val = (chg_current -450) / 50;

	/* cur = prechg_rng(450) + x*50 */
	sci_adi_write(CHG_CFG0, BITS_PRECHG_RNG(0x3), BITS_PRECHG_RNG(~0U));

	sci_adi_write(CHG_CFG1, reg_val, BITS_CUR(reg_val));
}

void sprdchg_common_cfg(void)
{
	sprd2731_chg_init();
	sprd2731_chg_leakage_cur_config();
}

static void sprd2731_chg_ic_init(void)
{
	/* nothing to do for charge */
}

static void sprd2731_chg_reset_timer(void)
{
	/* nothing to do for charge */
}

static int sprd2731_chg_cmd(enum sprdchg_cmd cmd,int value)
{
	switch (cmd) {
		case CHG_SET_CURRENT:
			sprd2731_chg_set_chg_cur(value);
			break;
		case CHG_SET_LIMIT_CURRENT:
			sprd2731_chg_set_current_limit(value);
			break;
		default:
			break;
	}

	return 0;
}

static struct sprdchg_ic_operations sprd_chg2731_op ={
	.ic_init = sprd2731_chg_ic_init,
	.chg_start = sprd2731_chg_start_charge,
	.chg_stop = sprd2731_chg_stop_charge,
	.timer_callback = sprd2731_chg_reset_timer,
	.chg_cmd = sprd2731_chg_cmd,
};

void sprdchg_2731_init(void)
{
	sprdchg_register_ops(&sprd_chg2731_op);
}

int sprdchg_charger_is_adapter(void)
{
	int ret = ADP_TYPE_UNKNOW;
	int charger_status;
	charger_status = sci_adi_read(ANA_REG_GLB_CHGR_STATUS)
	    & (BIT_CDP_INT | BIT_DCP_INT | BIT_SDP_INT);

	switch (charger_status) {
	case BIT_CDP_INT:
		ret = ADP_TYPE_CDP;
		break;
	case BIT_DCP_INT:
		ret = ADP_TYPE_DCP;
		break;
	case BIT_SDP_INT:
		ret = ADP_TYPE_SDP;
		break;
	default:
		break;
	}
	return ret;
}

