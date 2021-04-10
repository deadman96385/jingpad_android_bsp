#include "ddrc_debug_interface.h"

void only_ctl0_x32()
{
	reg_bit_set(DMC_CTL0_(0x0100),8,0x1);//drf_data_width
	reg_bit_set(DMC_CTL0_(0x0100),0,2,0x1);//drf_chn_pinmux_mode
	reg_bit_set(DMC_CTL0_(0x0144),24,3,0x0);//rf_interleave_mode
	reg_bit_set(DMC_CTL0_(0x0000),0,3,0x7);//rf_cs_position
	reg_bit_set(DMC_CTL0_(0x0014),3,1,0x1);//rf_remap_en
	__raw_writel(DMC_CTL0_(0x0018),0x98543210);//rf_dmc_remap_addr_0
	__raw_writel(DMC_CTL0_(0x001c),0x3210dcba);//rf_dmc_remap_addr_1
}

void only_ctl1_x32()
{
	reg_bit_set(DMC_CTL0_(0x0148),0,14,0x0);//rf_linear_base_chn0
	reg_bit_set(DMC_CTL0_(0x0148),16,14,0x200);//rf_linear_base_chn1
	reg_bit_set(DMC_CTL0_(0x0150), 0,14,0x400);//rf_linear_base

}

void ctl1_wbuf_bist_test()
{
	u32 bist_addr[3]={0};
	u32 size=0;
	u32 bist_result=0;
	only_ctl1_x32();
	reg_bit_set(DMC_CTL0_(0x0144),16,1,0x1);//rf_period_cpst_en
	reg_bit_set(DMC_CTL0_(0x0144), 4,12,0x19);//drf_t_cpst--3.9us for cpst
	reg_bit_set(DMC_PHY0_(0x0680),10,1,0x0);//rf_dl_cpst_en_ac1
	reg_bit_set(DMC_PHY0_(0x0680),12,1,0x0);//rf_dl_cpst_auto_ref_en_ac1
	reg_bit_set(DMC_PHY0_(0x0740),10,1,0x0);//rf_dl_cpst_en_ds2
	reg_bit_set(DMC_PHY0_(0x0740),12,1,0x0);//rf_dl_cpst_auto_ref_en_ds2
	reg_bit_set(DMC_PHY0_(0x0780),10,1,0x0);//rf_dl_cpst_en_ds3
	reg_bit_set(DMC_PHY0_(0x0780),12,1,0x0);//rf_dl_cpst_auto_ref_en_ds3
	while(1)
	{
		for(bist_addr[0]=0x20000000;bist_addr[0]<0x40000000;bist_addr[0]+=0x800)
		{
			bist_init(BIST_ALLWRC,USER_DATA_PATTERN,0x7,bist_addr);
			reg_bit_set(DMC_PHY0_(0x0740),10,1,0x0);//rf_dl_cpst_en_ds2
			while(((__raw_readl(DMC_CTL0_(0x00A4))>>6)&0X1F) != 0xc);//ch1_rfdmem_cmdb_st
			bist_en();
			bist_clear_reset(BIST_CHN0);
			bist_trigger(BIST_CHN0);
			while(__raw_readl(DMC_CTL0_(0x0548)) != 0x0);//rf_dbg_data3_wbuf_ch1
			reg_bit_set(DMC_PHY0_(0x0740),10,1,0x1);//rf_dl_cpst_en_ds2			
			bist_wait_done(BIST_CHN0);
			bist_result += get_bist_result(BIST_CHN0);
			if(bist_result>0)
			{
				dmc_print_str("bist test fail!!!!/r/n");
				while(1);
			}
			dmc_print_str("USER PATTERN Bist test ok!!!/r/n");
			bist_clear(BIST_CHN0);
			bist_dis();
		}
	}

}
