#include "ddr_common.h"
#include "ddr_init.h"
#include "ddr_timing.h"
#include "ddr_qos.h"

uint32 ctl_reg_file[] =
{
	#ifdef DRAM_LPDDR3
	#include "ctrl_reg_lp3.h"
	#else
	#include "ctrl_reg_lp4.h"
	#endif
};

uint32 pi_reg_file[] = 
{
	#ifdef DRAM_LPDDR3
	#include "pi_reg_lp3.h"
	#else
	#include "pi_reg_lp4.h"
	#endif
};

uint32 phy_reg_file_f0[] = 
{
	#ifdef DRAM_LPDDR3
	#include "phy_reg_lp3_f0.h"
	#else
	#include "phy_reg_lp4_f0.h"
	#endif
};

uint32 phy_reg_file_f1[] = 
{
	#ifdef DRAM_LPDDR3
	#include "phy_reg_lp3_f1.h"
	#else
	#include "phy_reg_lp4_f1.h"
	#endif
};

uint32 phy_reg_file_f2[] = 
{
	#ifdef DRAM_LPDDR3
	#include "phy_reg_lp3_f2.h"
	#else
	#include "phy_reg_lp4_f2.h"
	#endif
};

uint32 phy_reg_file_f3[] = 
{
	#ifdef DRAM_LPDDR3
	#include "phy_reg_lp3_f3.h"
	#else
	#include "phy_reg_lp4_f3.h"
	#endif
};

void cands_ctl_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,
					CANDS_CTL_TIMING_T * ctl_timing, CANDS_CTL_PERCHN_QOS_T* perchn_qos,CANDS_CTL_ALLCHN_QOS_T* allchn_qos,
					uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	for(i=0;i<CTL_REG_NUM;i++)
	{
		__raw_writel(CANDS_CTL0_(i)+chn_offset, ctl_reg_file[i]);
	}
}

void cands_pi_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_PI_TIMING_T	*pi_timing,
				   uint32 f0, uint32 f1, uint32 f2, uint32 f3, uint32 f4)
{
	uint32 i;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	for(i=0;i<PI_REG_NUM;i++)
	{
		__raw_writel(CANDS_PI0_(i)+chn_offset, pi_reg_file[i]);
	}
}
#ifdef MUTILCAST_ENABLE
void cands_phy_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_PHY_TIMING_T* phy_timing_info,
					uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i,j;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	__raw_writel(CANDS_PHY0_(1024)+chn_offset, phy_reg_file_f0[1024]);
	//en multicast
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,0,1,1);
	for(j=1025;j<PHY_REG_NUM;j++)
	{
	    __raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f0[j]);
	}
	for(j=0;j<1024;j++)
	{
	    __raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f0[j]);
	}
}
#else
void cands_phy_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type,CANDS_PHY_TIMING_T* phy_timing_info,
					uint32 f0, uint32 f1, uint32 f2, uint32 f3)
{
	uint32 i,j;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	for(i=0;i<4;i++)
	{
		switch(i)
		{
			case 0:	__raw_writel(CANDS_PHY0_(1024)+chn_offset, phy_reg_file_f0[1024]);
					break;
			case 1:	__raw_writel(CANDS_PHY0_(1024)+chn_offset, phy_reg_file_f1[1024]);
					break;
			case 2:	__raw_writel(CANDS_PHY0_(1024)+chn_offset, phy_reg_file_f2[1024]);
					break;
			case 3:	__raw_writel(CANDS_PHY0_(1024)+chn_offset, phy_reg_file_f3[1024]);
					break;
			default:	break;
		}
	//dis multicast
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,0,1,0);
	        reg_bit_set(CANDS_PHY0_(1024)+chn_offset,8,3,i);
		for(j=1025;j<PHY_REG_NUM;j++)
		{
			switch(i)
			{
				case 0:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f0[j]);
						break;
				case 1:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f1[j]);
						break;
				case 2:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f2[j]);
						break;
				case 3:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f3[j]);
						break;
				default:	break;
			}
		}
		for(j=0;j<1024;j++)
		{
			switch(i)
			{
				case 0:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f0[j]);
						break;
				case 1:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f1[j]);
						break;
				case 2:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f2[j]);
						break;
				case 3:	__raw_writel(CANDS_PHY0_(j)+chn_offset, phy_reg_file_f3[j]);
						break;
				default:	break;
			}
		}
	}
}
#endif
