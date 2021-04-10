#include <common.h>
#include <asm/io.h>
#include <regs_adi.h>
#include "adi_hal_internal.h"
#include <asm/arch/sprd_reg.h>
#include <sprd_battery.h>
#include "sprd_chg_helper.h"

int sprd_charge_pd_control(bool enable)
{
	if (enable)
		ANA_REG_MSK_OR(ANA_REG_GLB_CHGR_CTRL, 0, BIT_CHGR_PD);
	else
		ANA_REG_MSK_OR(ANA_REG_GLB_CHGR_CTRL, BIT_CHGR_PD,
			       BIT_CHGR_PD);
	return 0;
}

void sprdchg_common_cfg(void)
{
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
