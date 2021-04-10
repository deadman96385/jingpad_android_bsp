
#include <common.h>
#include <sprd_ufs.h>
#include <asm/arch/ufs_cfg.h>
#include <linux/io.h>
#include <asm/arch/sprd_reg.h>
#include "ip_env.h"

void init_global_reg(void)
{
	struct ufs_cfg_info *sprd_ufs_info;
	struct unipro_cfg_info *sprd_unipro_info;

	sprd_ufs_info = get_ufscontrol_info();
	sprd_unipro_info = get_uniprocontrol_info();

	ufs_info.base_addr = sprd_ufs_info->ufshci_regbase;

	if (sprd_ufs_info->ldo_core != 0)
		regulator_enable(sprd_ufs_info->ldo_core);
	if (sprd_ufs_info->ldo_io != 0)
		regulator_enable(sprd_ufs_info->ldo_io);

	debugf("ufs ldo_core:%s, ldo_io:%s\n",
		   sprd_ufs_info->ldo_core, sprd_ufs_info->ldo_io);
	udelay(1000);

	CHIP_REG_SET(sprd_ufs_info->ufs_tx_clk_cfg,
			sprd_ufs_info->ufs_tx_clk_val);

	CHIP_REG_SET(sprd_ufs_info->ufs_rx_clk_cfg,
			sprd_ufs_info->ufs_rx_clk_val);

	CHIP_REG_OR(sprd_ufs_info->apb_enable_reg,
			sprd_ufs_info->apb_enable_bit);
	CHIP_REG_OR(sprd_ufs_info->ao_aon_apb_enable_reg,
			sprd_ufs_info->ao_aon_apb_enable_bit);

	/*enable mipi use c2g trim value without efuse*/
	CHIP_REG_OR(sprd_ufs_info->anlg_phy_g1_trim_sel_reg,
			sprd_ufs_info->anlg_phy_g1_trim_bit);

	/*as defaut byp ufs_pwr_gate, as use ufs,we will clear it*/
	CHIP_REG_AND(sprd_ufs_info->pmu_bypass_enable_reg,
			~(sprd_ufs_info->pmu_bypass_enable_bit));

	/*reset mphy */
	CHIP_REG_AND(sprd_ufs_info->anlg_phy_g1_reg,
			~(sprd_ufs_info->anlg_phy_g1_reset_bit));
	udelay(1000);
	CHIP_REG_OR(sprd_ufs_info->anlg_phy_g1_reg,
			sprd_ufs_info->anlg_phy_g1_reset_bit);

	CHIP_REG_OR(sprd_ufs_info->apb_reset_reg,
			sprd_ufs_info->apb_reset_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_ufs_info->apb_reset_reg,
			~(sprd_ufs_info->apb_reset_bit));

	CHIP_REG_OR(sprd_ufs_info->ao_aon_apb_reset_reg,
			sprd_ufs_info->ao_aon_apb_reset_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_ufs_info->ao_aon_apb_reset_reg,
			~(sprd_ufs_info->ao_aon_apb_reset_bit));

	/*reset unipro data-link network transport dme */
	CHIP_REG_OR(sprd_unipro_info->dl_reset_reg,
			sprd_unipro_info->dl_reset_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_unipro_info->dl_reset_reg,
			~(sprd_unipro_info->dl_reset_bit));

	CHIP_REG_OR(sprd_unipro_info->n_reset_reg,
			sprd_unipro_info->n_reset_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_unipro_info->n_reset_reg,
			~(sprd_unipro_info->n_reset_bit));

	CHIP_REG_OR(sprd_unipro_info->t_reset_reg,
			sprd_unipro_info->t_reset_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_unipro_info->t_reset_reg,
			~(sprd_unipro_info->t_reset_bit));

	CHIP_REG_OR(sprd_unipro_info->dme_reset_reg,
			sprd_unipro_info->dme_reset_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_unipro_info->dme_reset_reg,
				~(sprd_unipro_info->dme_reset_bit));

	CHIP_REG_OR(ufs_info.base_addr + DW_UFS_RESET_MISC, (BIT_12 | BIT_28));

	CHIP_REG_AND(sprd_ufs_info->utp_reset_reg,
			~(sprd_ufs_info->utp_reset_bit));
	udelay(1000);
	CHIP_REG_OR(sprd_ufs_info->utp_reset_reg,
			sprd_ufs_info->utp_reset_bit);

	udelay(1000);
	CHIP_REG_AND(ufs_info.base_addr + DW_UFS_RESET_MISC, ~(BIT_12 | BIT_28));

	CHIP_REG_OR(sprd_ufs_info->ao_regbase,
			sprd_ufs_info->ao_rest_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_ufs_info->ao_regbase,
			~(sprd_ufs_info->ao_rest_bit));

	CHIP_REG_OR(sprd_unipro_info->pa_rxtx_reset_reg,
			sprd_unipro_info->pa_rxtx_reset_bit);
	udelay(1000);
	CHIP_REG_AND(sprd_unipro_info->pa_rxtx_reset_reg,
			~(sprd_unipro_info->pa_rxtx_reset_bit));
	//fix osc error
	CHIP_REG_OR(0x719000A4,BIT_29);

	//WORKAROUND no rsp data abort error
	CHIP_REG_AND(0x71a00104,~0xff);
	CHIP_REG_OR(0x71a00104,0x4);

	CHIP_REG_OR(0x323B808C,BIT_15);
	CHIP_REG_OR(0x323B801C,BIT_24);

	//WORKAROUND no rsp data abort erro
	CHIP_REG_OR(0x323b4008,0xff);
	CHIP_REG_AND(0x323b801c,~(0x7 << 14));
	CHIP_REG_OR(0x323b801c,0x4 << 14);

	CHIP_REG_OR(0x71800148,BIT_0);
}




