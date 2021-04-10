#include "mipi_dsih_dphy.h"

static struct pll_frequency_intel pll_frequency_intel_set[] = {

[0] = {
	.phy_clk = 800*1000,
	.div5b = 1,
	.div2or3 = 0,
	.div5bbyass = 0,
	.i_fbdivratio = 0x7c,
	.i_fracdiv2 = 0x3,
	.i_fracdiv1 = 0xf0,
	.i_fracdiv0 = 0x3f,
	.i_feedfwrdgain = 0x2,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0,
	.i_sscstepsize1 = 0,

	.i_sscsteplength0 = 0,
	.i_sscsteplength1 = 0,
	.i_sscstepnum = 0,
	.i_ssctype = 0,
	.i_sscen_h = 0,
	.i_prop_coeff = 0x5,
	.i_int_coeff = 0x9,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0,
	.i_lockthreshsel = 0,
	.i_pllwait_cntr = 0x2,
       },


[1] = {
	.phy_clk = 861999,
	.div5b = 0,
	.div2or3 = 0x1,
	.div5bbyass = 0,
	.i_fbdivratio = 0x63,
	.i_fracdiv2 = 0x1d,
	.i_fracdiv1 = 0x89,
	.i_fracdiv0 = 0xd8,
	.i_feedfwrdgain = 0x3,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0,
	.i_sscstepsize1 = 0,
	.i_sscsteplength0 = 0,
	.i_sscsteplength1 = 0,
	.i_sscstepnum = 0,
	.i_ssctype = 0,
	.i_sscen_h = 0,
	.i_prop_coeff = 0x4,
	.i_int_coeff = 0x8,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0,
	.i_lockthreshsel = 0,
	.i_pllwait_cntr = 0x2,
       },

[2] = {
	.phy_clk = 862*1000,
	.div5b = 0,
	.div2or3 = 0x1,
	.div5bbyass = 0,
	.i_fbdivratio = 0x63,
	.i_fracdiv2 = 0x1d,
	.i_fracdiv1 = 0x89,
	.i_fracdiv0 = 0xd8,
	.i_feedfwrdgain = 0x3,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0,
	.i_sscstepsize1 = 0,
	.i_sscsteplength0 = 0,
	.i_sscsteplength1 = 0,
	.i_sscstepnum = 0,
	.i_ssctype = 0,
	.i_sscen_h = 0,
	.i_prop_coeff = 0x4,
	.i_int_coeff = 0x8,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0,
	.i_lockthreshsel = 0,
	.i_pllwait_cntr = 0x2,
       },

[3] = {
	.phy_clk = 880*1000,
	.div5b = 0x0,
	.div2or3 = 0x1,
	.div5bbyass = 0x0,
	.i_fbdivratio = 0x65,
	.i_fracdiv2 = 0x3a,
	.i_fracdiv1 = 0x17,
	.i_fracdiv0 = 0xa1,
	.i_feedfwrdgain = 0x03 ,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0= 0x0,
	.i_sscstepsize1 = 0x0,
	.i_sscsteplength0 = 0x0,
	.i_sscsteplength1 = 0x0,
	.i_sscstepnum = 0x0,
	.i_ssctype = 0x0,
	.i_sscen_h = 0x0,
	.i_prop_coeff = 0x4,
	.i_int_coeff = 0x8,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0x0,
	.i_lockthreshsel = 0x0,
	.i_pllwait_cntr = 0x2,
       },

[4] = {
	.phy_clk = 900*1000,
	.div5b = 0,
	.div2or3 = 0x1,
	.div5bbyass = 0,
	.i_fbdivratio = 0x68,
	.i_fracdiv2 = 0x7,
	.i_fracdiv1 = 0xe0,
	.i_fracdiv0 = 0x7e,
	.i_feedfwrdgain = 0x3,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0,
	.i_sscstepsize1 = 0,

	.i_sscsteplength0 = 0,
	.i_sscsteplength1 = 0,
	.i_sscstepnum = 0,
	.i_ssctype = 0,
	.i_sscen_h = 0,
	.i_prop_coeff = 0x4,
	.i_int_coeff = 0x8,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0,
	.i_lockthreshsel = 0,
	.i_pllwait_cntr = 0x2,
       },

[5] = {
	.phy_clk = 930*1000,
	.div5b = 0,
	.div2or3 = 0x1,
	.div5bbyass = 0,
	.i_fbdivratio = 0x6b,
	.i_fracdiv2 = 0x1c,
	.i_fracdiv1 = 0x8d,
	.i_fracdiv0 = 0xc8,
	.i_feedfwrdgain = 0x3,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0,
	.i_sscstepsize1 = 0,

	.i_sscsteplength0 = 0,
	.i_sscsteplength1 = 0,
	.i_sscstepnum = 0,
	.i_ssctype = 0,
	.i_sscen_h = 0,
	.i_prop_coeff = 0x4,
	.i_int_coeff = 0x8,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0,
	.i_lockthreshsel = 0,
	.i_pllwait_cntr = 0x2,
       },


[6] = {
	.phy_clk = 960*1000,
	.div5b = 0x0,
	.div2or3 = 0x1,
	.div5bbyass = 0x0,
	.i_fbdivratio = 0x6e,
	.i_fracdiv2 = 0x31,
	.i_fracdiv1 = 0x3b,
	.i_fracdiv0 = 0x13,
	.i_feedfwrdgain = 0x02,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0x0,
	.i_sscstepsize1 = 0x0,
	.i_sscsteplength0 = 0x0,
	.i_sscsteplength1 = 0x0,
	.i_sscstepnum = 0x0,
	.i_ssctype = 0x0,
	.i_sscen_h = 0x0,
	.i_prop_coeff = 0x4,
	.i_int_coeff = 0x8,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0x0,
	.i_lockthreshsel = 0x0,
	.i_pllwait_cntr = 0x2,
       },

[7] = {
	.phy_clk = 1000*1000,
	.div5b = 0,
	.div2or3 = 0x1,
	.div5bbyass = 0,
	.i_fbdivratio = 0x74,
	.i_fracdiv2 = 0x13,
	.i_fracdiv1 = 0xb1,
	.i_fracdiv0 = 0x3b,
	.i_feedfwrdgain = 0x2,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0,
	.i_sscstepsize1 = 0,

	.i_sscsteplength0 = 0,
	.i_sscsteplength1 = 0,
	.i_sscstepnum = 0,
	.i_ssctype = 0,
	.i_sscen_h = 0,
	.i_prop_coeff = 0x5,
	.i_int_coeff = 0x9,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0,
	.i_lockthreshsel = 0,
	.i_pllwait_cntr = 0x2,
       },

[8] = {
	.phy_clk = 790*1000,
	.div5b = 1,
	.div2or3 = 0x0,
	.div5bbyass = 0,
	.i_fbdivratio = 0x7a,
	.i_fracdiv2 = 0x25,
	.i_fracdiv1 = 0x6a,
	.i_fracdiv0 = 0x56,
	.i_feedfwrdgain = 0x2,
	.i_fracnen_h = 0x1,
	.i_sscstepsize0 = 0,
	.i_sscstepsize1 = 0,

	.i_sscsteplength0 = 0,
	.i_sscsteplength1 = 0,
	.i_sscstepnum = 0,
	.i_ssctype = 0,
	.i_sscen_h = 0,
	.i_prop_coeff = 0x5,
	.i_int_coeff = 0x9,
	.i_gainctrl = 0x1,
	.i_tdctargetcnt0 = 0x22,
	.i_tdctargetcnt1 = 0,
	.i_lockthreshsel = 0,
	.i_pllwait_cntr = 0x2,
       },

[9] = {
       .phy_clk = 9646*100,
       .div5b = 0,
       .div2or3 = 0x1,
       .div5bbyass = 0,
       .i_fbdivratio = 0x6f,
       .i_fracdiv2 = 0x13,
       .i_fracdiv1 = 0x33,
       .i_fracdiv0 = 0x33,
       .i_feedfwrdgain = 0x2,
       .i_fracnen_h = 0x1,
       .i_sscstepsize0 = 0,
       .i_sscstepsize1 = 0,

       .i_sscsteplength0 = 0,
       .i_sscsteplength1 = 0,
       .i_sscstepnum = 0,
       .i_ssctype = 0,
       .i_sscen_h = 0,
       .i_prop_coeff = 0x4,
       .i_int_coeff = 0x8,
       .i_gainctrl = 0x1,
       .i_tdctargetcnt0 = 0x22,
       .i_tdctargetcnt1 = 0,
       .i_lockthreshsel = 0,
       .i_pllwait_cntr = 0x2,
      },
[10] = {
       .phy_clk = 460*1000,
       .div5b = 1,
       .div2or3 = 0x1,
       .div5bbyass = 0,
       .i_fbdivratio = 0x6a,
       .i_fracdiv2 = 0x15,
       .i_fracdiv1 = 0xa9,
       .i_fracdiv0 = 0x5a,
       .i_feedfwrdgain = 0x3,
       .i_fracnen_h = 0x1,
       .i_sscstepsize0 = 0,
       .i_sscstepsize1 = 0,

       .i_sscsteplength0 = 0,
       .i_sscsteplength1 = 0,
       .i_sscstepnum = 0,
       .i_ssctype = 0,
       .i_sscen_h = 0,
       .i_prop_coeff = 0x4,
       .i_int_coeff = 0x8,
       .i_gainctrl = 0x1,
       .i_tdctargetcnt0 = 0x22,
       .i_tdctargetcnt1 = 0,
       .i_lockthreshsel = 0,
       .i_pllwait_cntr = 0x2,
      },
[11] = {
       .phy_clk = 500*1000,
       .div5b = 1,
       .div2or3 = 0x1,
       .div5bbyass = 0,
       .i_fbdivratio = 0x75,
       .i_fracdiv2 = 0x1a,
       .i_fracdiv1 = 0x95,
       .i_fracdiv0 = 0xa9,
       .i_feedfwrdgain = 0x2,
       .i_fracnen_h = 0x1,
       .i_sscstepsize0 = 0,
       .i_sscstepsize1 = 0,

       .i_sscsteplength0 = 0,
       .i_sscsteplength1 = 0,
       .i_sscstepnum = 0,
       .i_ssctype = 0,
       .i_sscen_h = 0,
       .i_prop_coeff = 0x4,
       .i_int_coeff = 0x8,
       .i_gainctrl = 0x1,
       .i_tdctargetcnt0 = 0x22,
       .i_tdctargetcnt1 = 0,
       .i_lockthreshsel = 0,
       .i_pllwait_cntr = 0x2,
      },
[12] = {
       .phy_clk = 530*1000,
       .div5b = 1,
       .div2or3 = 0x1,
       .div5bbyass = 0,
       .i_fbdivratio = 0x7c,
       .i_fracdiv2 = 0x03,
       .i_fracdiv1 = 0xf0,
       .i_fracdiv0 = 0x3f,
       .i_feedfwrdgain = 0x2,
       .i_fracnen_h = 0x1,
       .i_sscstepsize0 = 0,
       .i_sscstepsize1 = 0,

       .i_sscsteplength0 = 0,
       .i_sscsteplength1 = 0,
       .i_sscstepnum = 0,
       .i_ssctype = 0,
       .i_sscen_h = 0,
       .i_prop_coeff = 0x4,
       .i_int_coeff = 0x8,
       .i_gainctrl = 0x1,
       .i_tdctargetcnt0 = 0x22,
       .i_tdctargetcnt1 = 0,
       .i_lockthreshsel = 0,
       .i_pllwait_cntr = 0x2,
      },
[13] = {
       .phy_clk = 600*1000,
       .div5b = 1,
       .div2or3 = 0x0,
       .div5bbyass = 0,
       .i_fbdivratio = 0x5d,
       .i_fracdiv2 = 0x02,
       .i_fracdiv1 = 0xf4,
       .i_fracdiv0 = 0x2f,
       .i_feedfwrdgain = 0x3,
       .i_fracnen_h = 0x1,
       .i_sscstepsize0 = 0,
       .i_sscstepsize1 = 0,

       .i_sscsteplength0 = 0,
       .i_sscsteplength1 = 0,
       .i_sscstepnum = 0,
       .i_ssctype = 0,
       .i_sscen_h = 0,
       .i_prop_coeff = 0x4,
       .i_int_coeff = 0x8,
       .i_gainctrl = 0x1,
       .i_tdctargetcnt0 = 0x22,
       .i_tdctargetcnt1 = 0,
       .i_lockthreshsel = 0,
       .i_pllwait_cntr = 0x2,
      },
[14] = {
       .phy_clk = 450*1000,
       .div5b = 1,
       .div2or3 = 0x1,
       .div5bbyass = 0,
       .i_fbdivratio = 0x68,
       .i_fracdiv2 = 0x07,
       .i_fracdiv1 = 0xe0,
       .i_fracdiv0 = 0x7e,
       .i_feedfwrdgain = 0x3,
       .i_fracnen_h = 0x1,
       .i_sscstepsize0 = 0,
       .i_sscstepsize1 = 0,

       .i_sscsteplength0 = 0,
       .i_sscsteplength1 = 0,
       .i_sscstepnum = 0,
       .i_ssctype = 0,
       .i_sscen_h = 0,
       .i_prop_coeff = 0x4,
       .i_int_coeff = 0x8,
       .i_gainctrl = 0x1,
       .i_tdctargetcnt0 = 0x22,
       .i_tdctargetcnt1 = 0,
       .i_lockthreshsel = 0,
       .i_pllwait_cntr = 0x2,
      },
[15] = {
       .phy_clk = 9798*100,
       .div5b = 0,
       .div2or3 = 0x1,
       .div5bbyass = 0,
       .i_fbdivratio = 0x71,
       .i_fracdiv2 = 0x3,
       .i_fracdiv1 = 0x72,
       .i_fracdiv0 = 0x37,
       .i_feedfwrdgain = 0x2,
       .i_fracnen_h = 0x1,
       .i_sscstepsize0 = 0,
       .i_sscstepsize1 = 0,

       .i_sscsteplength0 = 0,
       .i_sscsteplength1 = 0,
       .i_sscstepnum = 0,
       .i_ssctype = 0,
       .i_sscen_h = 0,
       .i_prop_coeff = 0x4,
       .i_int_coeff = 0x8,
       .i_gainctrl = 0x1,
       .i_tdctargetcnt0 = 0x22,
       .i_tdctargetcnt1 = 0,
       .i_lockthreshsel = 0,
       .i_pllwait_cntr = 0x2,
      },
};

#define PHY_OFFSET 0x0
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
void set_pll_frequency(uint32_t output_freq)
{
    uint32_t div5b,div2or3,div5bbyass,i_fbdivratio,i_fracdiv2,i_fracdiv1,i_fracdiv0;
    uint32_t i_feedfwrdgain,i_fracnen_h,i_sscstepsize0,i_sscstepsize1;
    uint32_t i_sscsteplength0,i_sscsteplength1,i_sscstepnum,i_ssctype,i_sscen_h,i_prop_coeff;
    uint32_t i_int_coeff,i_gainctrl,i_tdctargetcnt0,i_tdctargetcnt1,i_lockthreshsel,i_pllwait_cntr;
    uint8_t i;
    int count;

    count = ARRAY_SIZE(pll_frequency_intel_set);
    for(i=0;i<count;i++)
	if(pll_frequency_intel_set[i].phy_clk == output_freq)
	{
		div5b = pll_frequency_intel_set[i].div5b;
		div2or3 = pll_frequency_intel_set[i].div2or3;
		div5bbyass = pll_frequency_intel_set[i].div5bbyass;
		i_fbdivratio = pll_frequency_intel_set[i].i_fbdivratio;
		i_fracdiv2 = pll_frequency_intel_set[i].i_fracdiv2;
		i_fracdiv1 = pll_frequency_intel_set[i].i_fracdiv1;
		i_fracdiv0 = pll_frequency_intel_set[i].i_fracdiv0;
		i_feedfwrdgain = pll_frequency_intel_set[i].i_feedfwrdgain;
		i_fracnen_h = pll_frequency_intel_set[i].i_fracnen_h;
		i_sscstepsize0 = pll_frequency_intel_set[i].i_sscstepsize0;
		i_sscstepsize1 = pll_frequency_intel_set[i].i_sscstepsize1;
		i_sscsteplength0 = pll_frequency_intel_set[i].i_sscsteplength0;
		i_sscsteplength1 = pll_frequency_intel_set[i].i_sscsteplength1;
		i_sscstepnum = pll_frequency_intel_set[i].i_sscstepnum;
		i_ssctype = pll_frequency_intel_set[i].i_ssctype;
		i_sscen_h = pll_frequency_intel_set[i].i_sscen_h;
		i_prop_coeff = pll_frequency_intel_set[i].i_prop_coeff;
		i_int_coeff = pll_frequency_intel_set[i].i_int_coeff;
		i_gainctrl = pll_frequency_intel_set[i].i_gainctrl;
		i_tdctargetcnt0 = pll_frequency_intel_set[i].i_tdctargetcnt0;
		i_tdctargetcnt1 = pll_frequency_intel_set[i].i_tdctargetcnt1;
		i_lockthreshsel = pll_frequency_intel_set[i].i_lockthreshsel;
		i_pllwait_cntr = pll_frequency_intel_set[i].i_pllwait_cntr;
		break;
	}
    if (i >= count) {
	    printf("sprd-adf:error: cannot found any frequence (0x%x)\n",
			    output_freq);
	    return;
    }
    writel_nbits(div5b,3,1,0xe41b0004+PHY_OFFSET);
    writel_nbits(div2or3,1,4,0xe41b0004+PHY_OFFSET);
    writel_nbits(div5bbyass,1,5,0xe41b0004+PHY_OFFSET);
    writel_nbits(i_fbdivratio,8,0,0xe41b0300+PHY_OFFSET);
    writel_nbits(i_fracdiv2,6,16,0xe41b0308+PHY_OFFSET);
    writel_nbits(i_fracdiv1,8,8,0xe41b0308+PHY_OFFSET);
    writel_nbits(i_fracdiv0,8,0,0xe41b0308+PHY_OFFSET);
    writel_nbits(i_feedfwrdgain,4,0,0xe41b030c+PHY_OFFSET);
    writel_nbits(i_fracnen_h,1,16,0xe41b030c+PHY_OFFSET);
    writel_nbits(i_sscstepsize0,8,0,0xe41b0310+PHY_OFFSET);
    writel_nbits(i_sscstepsize1,2,8,0xe41b0310+PHY_OFFSET);
    writel_nbits(i_sscsteplength0,8,16,0xe41b0310+PHY_OFFSET);
    writel_nbits(i_sscsteplength1,2,24,0xe41b0310+PHY_OFFSET);
    writel_nbits(i_sscstepnum,3,0,0xe41b0314+PHY_OFFSET);
    writel_nbits(i_ssctype,2,8,0xe41b0314+PHY_OFFSET);
    writel_nbits(i_sscen_h,1,16,0xe41b0314+PHY_OFFSET);
    writel_nbits(i_prop_coeff,4,0,0xe41b0318+PHY_OFFSET);
    writel_nbits(i_int_coeff,5,8,0xe41b0318+PHY_OFFSET);
    writel_nbits(i_gainctrl,3,16,0xe41b0318+PHY_OFFSET);
    writel_nbits(i_tdctargetcnt0,8,0,0xe41b0320+PHY_OFFSET);
    writel_nbits(i_tdctargetcnt1,2,8,0xe41b0320+PHY_OFFSET);
    writel_nbits(i_lockthreshsel,1,0,0xe41b0324+PHY_OFFSET);
    writel_nbits(i_pllwait_cntr,3,16,0xe41b0324+PHY_OFFSET);
}
