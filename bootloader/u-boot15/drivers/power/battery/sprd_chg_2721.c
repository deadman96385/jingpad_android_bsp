#include <common.h>
#include <asm/io.h>

#include <regs_adi.h>
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>
#include <asm/arch/sprd_eic.h>
#include <sprd_battery.h>
#include "sprd_chg_helper.h"

#ifdef DEBUG
#define debugf(fmt, args...) do { printf("chg: %s(): ", __func__); printf(fmt, ##args); } while (0)
#else
#define debugf(fmt, args...)
#endif

void sprdchg_start_charge(int value)
{
	ANA_REG_MSK_OR(ANA_REG_GLB_CHGR_CTRL0, 0, BIT_CHGR_PD);
}

void sprdchg_stop_charge(int value)
{
	ANA_REG_MSK_OR(ANA_REG_GLB_CHGR_CTRL0, BIT_CHGR_PD, BIT_CHGR_PD);
}

int sprd_charge_pd_control(bool enable)
{
	if (enable)
		ANA_REG_MSK_OR(ANA_REG_GLB_CHGR_CTRL0, 0, BIT_CHGR_PD_EXT);
	else
		ANA_REG_MSK_OR(ANA_REG_GLB_CHGR_CTRL0, BIT_CHGR_PD_EXT,
			     BIT_CHGR_PD_EXT);

	return 0;
}

static void sprdchg_set_recharge(void)
{
	ANA_REG_OR(ANA_REG_GLB_CHGR_CTRL0, BIT_RECHG);
}

static void sprdchg_set_chg_cur(uint32_t chg_current)
{
	uint32_t temp;

	if (chg_current < 1400) {
		temp = ((chg_current - 300) / 50);
	} else {
		temp = ((chg_current - 1400) / 100);
		temp += 0x16;
	}

	sci_adi_clr(ANA_REG_GLB_CHGR_CTRL0, BIT_CHGR_CC_EN);

	sci_adi_write(ANA_REG_GLB_CHGR_CTRL1,
		      BITS_CHGR_CC_I(temp), BITS_CHGR_CC_I(~0));

	sci_adi_set(ANA_REG_GLB_CHGR_CTRL0, BIT_CHGR_CC_EN);
}


void sprdchg_common_cfg(void)
{
	sprdchg_set_recharge();
	ANA_REG_OR(ANA_REG_GLB_CHGR_CTRL0, BIT_CHGR_CC_EN);

#if defined(CONFIG_ADIE_SC2723S) || defined(CONFIG_ADIE_SC2723)
	sci_adi_write(ANA_REG_GLB_CHGR_CTRL2,
		BITS_CHGR_DPM(3), BITS_CHGR_DPM(~0));	//fixed bug367845, only for 2723
	mdelay(10);
#endif
}

static void sprdchg_ic_init(void)
{
	/* nothing to do for charge */
}
static void sprdchg_reset_timer(void)
{
	/* nothing to do for charge */
}

static int sprdchg_cmd(enum sprdchg_cmd cmd,int value)
{
	switch (cmd) {
		case CHG_SET_CURRENT:
			sprdchg_set_chg_cur(value);
			break;
		default:
			break;
	}

	return 0;
}

static struct sprdchg_ic_operations sprdchg_op ={
	.ic_init = sprdchg_ic_init,
	.chg_start = sprdchg_start_charge,
	.chg_stop = sprdchg_stop_charge,
	.timer_callback = sprdchg_reset_timer,
	.chg_cmd = sprdchg_cmd,
};

void sprdchg_2721_init(void)
{
	sprdchg_register_ops(&sprdchg_op);
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

