#include "sci_types.h"
#include "ddrc_r1p0.h"
extern DRAM_CHIP_INFO ddr_chip_cur;
u16 dram_init_powerup_times = 0;
extern u8 cur_odt_on[8];

LPDDR3_MR_INFO lpddr3_mr_info = {
		DEFAULT_LPDDR3_BL,  /*burst length*/
		0,                 /*burst type*/
		0,                 /*wrap*/
		3,                 /*nwr*/
		3,                 /*read latency*/
		6,                 /*write latency*/
		DDR_DRV_CFG,       /*driver strength
				    * 34.3ohm,typical pull-down/pull-up
				    *400hm,48ohm,60ohm,80ohm
				    */
};


LPDDR4_MR_INFO lpddr4_mr_info = {
		DEFAULT_LPDDR4_BL,  /*burst length*/
		0,                 /*burst type*/
		0,                 /*wrap*/
		3,                 /*nwr*/
		32,               /*read latency*/
		14,                /*write latency*/
		DDR_DRV_CFG,       /*driver strength*/
		1                  /*DBI en*/
};

static const DDRC_R1P0_TIMING_CFG ddrc_local_timing_lpddr4[] = {
	{
	933,
	{			/*31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 9 8 7 6 5 4 3 2 1 0*/
		0X460B0909,//DTM0/*t_ccd[31:28],t_rrd[27:24],t_rpab[20:16],t_rcd[12:8],t_rp[4:0]*/
		0X020D2902,//DTM1/*t_rtr[27:24],t_wtr[20:16],t_wtw[15:12],t_rtw[11:8],t_rtp[3:0]*/
		0X82424487,//DTM2
		0X740F1315,//DTM3
		0X22531504,//DTM4
		0X00000F06,//DTM5
		0X00000B0A,//DTM6
		0X005E01D3,//DTM7
		0X11d40000,//DTM8
		0X00030c80,//DTM9
		0X150e0005,//DTM10
		0X00000000,//DTM11 mr14--mr0
		0X00000000,//DTM12 mr0--mr0
		0X0134021B,//DTM13 mr2--mr0
		0X0134021B,//DTM14 mr0--mr11
		0X00000000,//DTM15 mr0--mr0
		0X00000000,//DTM16 mr0--mr0
		0X00000000,//DTM17 mr0--mr0
		0X00000000,//DTM18 mr0--mr0
		0Xffffffff//DTM19
	}
	},

	{
	800,
	{
		0x450A0808,//DTM0
		0x020B2702,//DTM1
		0x6F383873,//DTM2
		0x630F1012,//DTM3
		0x22431403,//DTM4
		0x00000F05,//DTM5
		0x00000807,//DTM6
		0x00500190,//DTM7
		0x11910000,//DTM8
		0x00030C80,//DTM9
		0x150C0005,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01240212,//DTM13
		0x01240212,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
        }
	},

	{
	622,
	{
		0x44080707, //DTM0
		0x020A2702,//DTM1
		0x572C345A,//DTM2
		0x530F0C0F,//DTM3
		0x22431403,//DTM4
		0x00000F05,//DTM5
		0x00000807,//DTM6
		0x003F0137,//DTM7
		0x11380000,//DTM8
		0x00030C80,//DTM9
		0x150A0005,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01240212,//DTM13
		0x01240212,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	533,
	{
		0x43070505,//DTM0
		0x02092502,//DTM1
		0x4A262C4D,//DTM2
		0x43040B0C,//DTM3
		0x22431302,//DTM4
		0x00000F04,//DTM5
		0x00000505,//DTM6
		0x0036010B,//DTM7
		0x110C0000,//DTM8 //half mode setting
		0x00030C80,//DTM9
		0x15080005,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01140209,//DTM13
		0x01140209,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	400,
	{
		0x42050404,//DTM0
		0x02092502,//DTM1
		0x371C243A,//DTM2
		0x33040809,//DTM3
		0x22431302,//DTM4
		0x00000F04,//DTM5
		0x00000505,//DTM6
		0x00280C8,//DTM7
		0x50C90000,//DTM8
		0x00030C80,//DTM9
		0x15060005,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01140209,//DTM13
		0x01140209,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},

	{
	311,
	{
		0x42040303,//DTM0
		0x02092502,//DTM1
		0x2B16242D,//DTM2
		0x33040608,//DTM3
		0x22431302,//DTM4
		0x00000F04,//DTM5
		0x00000505,//DTM6
		0x0020009C,//DTM7
		0x509D0000,//DTM8
		0x00030C80,//DTM9
		0x15050005,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01140209,//DTM13
		0x01140209,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	233,
	{
		0x42030202,//DTM0
		0x02082402,//DTM1
		0x20111C22,//DTM2
		0x23040506,//DTM3
		0x22431201,//DTM4
		0x00000F03,//DTM5
		0x00000303,//DTM6
		0x00180075,//DTM7
		0x50760000,//DTM8
		0x00030C80,//DTM9
		0x15040005,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01040200,//DTM13
		0x01040200,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	160,
	{
		0x42020202,//DTM0
		0x02082402,//DTM1
		0x170C1C18,//DTM2
		0x23040404,//DTM3
		0x22431201,//DTM4
		0x00000F03,//DTM5
		0x00000303,//DTM6
		0x00100050,//DTM7
		0x50510000,//DTM8
		0x00030C80,//DTM9
		0x15040005,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01040200,//DTM13
		0x03830383,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},

};

static const DDRC_R1P0_TIMING_CFG ddrc_local_timing_lpddr3[] = {
	{
	933,
	{
		0x260B0909,//DTM0
		0x02080702,//DTM1
		0x612A3067,//DTM2
		0x74061715,//DTM3
		0x00330302,//DTM4
		0x00000F03,//DTM5
		0x00000006,//DTM6
		0x005E01DE,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x10A90000,//DTM8
		0x00030000,//DTM9
		0x00000002,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x0143021c,//DTM13
		0x0143021c,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF //DTM19
	}
	},
	{
	800,
	{
		0x250A0808,//DTM0
		0x02070601,//DTM1
		0x53242858,//DTM2
		0x63051412,//DTM3
		0x00330201,//DTM4
		0x00000F02,//DTM5
		0x00000005,//DTM6
		0x0050019A,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x10910000,//DTM8
		0x00030000,//DTM9
		0x00000002,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x0143021a,//DTM13
		0x0143021a,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},

	{
	622,
	{
		0x24080606, //DTM0
		0x02060501,//DTM1
		0x411C2445,//DTM2
		0x5304100E,//DTM3
		0x00330201,//DTM4
		0x00000F02,//DTM5
		0x00000004,//DTM6
		0x003F013F,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x10710000,//DTM8
		0x00030000,//DTM9
		0x00000002,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01030218,//DTM13
		0x01030218,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	533,
	{
		0x23070505,//DTM0
		0x02050400,//DTM1
		0x37181C3B,//DTM2
		0x42040D0C,//DTM3
		0x00330100,//DTM4
		0x00000F01,//DTM5
		0x00000003,//DTM6
		0x00360111,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x10610000,//DTM8 //half mode setting
		0x00030000,//DTM9
		0x00000002,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01C30206,//DTM13
		0x01C30206,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	400,
	{
		0x22050404,//DTM0
		0x02040400,//DTM1
		0x2912182C,//DTM2
		0x32040A09,//DTM3
		0x00330100,//DTM4
		0x00000F01,//DTM5
		0x00000002,//DTM6
		0x002800CD,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x10490000,//DTM8
		0x00030000,//DTM9
		0x000000F2,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01830204,//DTM13
		0x01830204,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},

	{
	311,
	{
		0x22040303,//DTM0
		0x02040300,//DTM1
		0x200E1423,//DTM2
		0x32040807,//DTM3
		0x00330100,//DTM4
		0x00000F01,//DTM5
		0x00000002,//DTM6
		0x002000A0,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x10390000,//DTM8
		0x00030000,//DTM9
		0x000000F2,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01830204,//DTM13
		0x01830204,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	233,
	{
		0x21030202,//DTM0
		0x02040300,//DTM1
		0x180B141A,//DTM2
		0x21040605,//DTM3
		0x00330100,//DTM4
		0x00000F01,//DTM5
		0x00000002,//DTM6
		0x00180078,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x102B0000,//DTM8
		0x00030000,//DTM9
		0x000000F2,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01830204,//DTM13
		0x01830204,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},
	{
	160,
	{
		0x21030202,//DTM0
		0x02040300,//DTM1
		0x180B141A,//DTM2
		0x21040605,//DTM3
		0x00330100,//DTM4
		0x00000F01,//DTM5
		0x00000002,//DTM6
		0x00180052,//DTM7 [15:0] self_ref_idle_cnt 512ns
		0x50390000,//DTM8
		0x00030000,//DTM9
		0x000000F2,//DTM10
		0x00000000,//DTM11
		0x00000000,//DTM12
		0x01830204,//DTM13
		0x01830204,//DTM14
		0x00000000,//DTM15
		0x00000000,//DTM16
		0x00000000,//DTM17
		0x00000000,//DTM18
		0xFFFFFFFF//DTM19
	}
	},

};

void lpddr_dmc_mrw(DMC_CMD_CS_INDEX cs, int mr_addr, unsigned char val)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 tmp;

	/*set reg val*/
	tmp = pdmc->dmc_dcfg2;
	tmp = u32_bits_set(tmp, 0, 8, val);
	pdmc->dmc_dcfg2 = tmp;
	dmc_sprd_delay(10);

	tmp = pdmc->dmc_dcfg1;
	/*set mr register addr*/
	tmp = u32_bits_set(tmp, 0, 16, mr_addr);
	/*set cs index*/
	if (CMD_CS_0 == cs)
	{
		/*1 cs mode*/
		tmp = u32_bits_set(tmp, 31, 1, 0);
		/*cs index*/
		tmp = u32_bits_set(tmp, 28, 1, 0);
	}
	else if (CMD_CS_1 == cs)
	{
		/*1 cs mode*/
		tmp = u32_bits_set(tmp, 31, 1, 0);
		/*cs index*/
		tmp = u32_bits_set(tmp, 28, 1, 1);
	}
	/*2 cs mode*/
	else
	{
		tmp = u32_bits_set(tmp, 31, 1, 1);
	}
	/*triger MRW*/
	tmp = u32_bits_set(tmp, 24, 1, 1);
	pdmc->dmc_dcfg1 = tmp;

	/* wait until [27:19]==0 */
	while(((pdmc->dmc_dcfg1 >> 19) & 0x1ff) != 0);
}
int search_for_freq_point(DDRC_R1P0_TIMING_CFG *dmc_timing, int size,  u32 clk)
{
	int i;
	for(i = 0; i < size; i++)
	{
		if (clk == dmc_timing[i].clk)
		{
			return i;
		}
	}
	return -1;
}

int  lpddr_timing_init(DRAM_TYPE ddr_type, dfs_freq_table ddr_frequency[8])
{
	int i, j, k;
	int  size;
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	DDRC_R1P0_TIMING_CFG *dmc_local_timing_ptr;
	u32  ddr_clk;

	if (ddr_type == DRAM_LPDDR3)
	{
		dmc_local_timing_ptr = ddrc_local_timing_lpddr3;
		size = sizeof(ddrc_local_timing_lpddr3)/sizeof(ddrc_local_timing_lpddr3[0]);
	}
	else
	{
		dmc_local_timing_ptr = ddrc_local_timing_lpddr4;
		size = sizeof(ddrc_local_timing_lpddr4)/sizeof(ddrc_local_timing_lpddr4[0]);
	}


	/*timing array */
	for(i = 0; i < 8; i++)
	{
		k = search_for_freq_point(dmc_local_timing_ptr, size, ddr_frequency[i].freq);
		if (k < 0)
		{
			/* Can not find timing parameters for this ddr_clk */
			return -1;
		}
		pdmc->dmc_dtmg_f[i][0]=dmc_local_timing_ptr[k].dtmg[0];
		pdmc->dmc_dtmg_f[i][1]=dmc_local_timing_ptr[k].dtmg[1];
		pdmc->dmc_dtmg_f[i][2]=dmc_local_timing_ptr[k].dtmg[2];
		pdmc->dmc_dtmg_f[i][3]=dmc_local_timing_ptr[k].dtmg[3];
		pdmc->dmc_dtmg_f[i][4]=dmc_local_timing_ptr[k].dtmg[4];
		pdmc->dmc_dtmg_f[i][5]=dmc_local_timing_ptr[k].dtmg[5];
		pdmc->dmc_dtmg_f[i][6]=dmc_local_timing_ptr[k].dtmg[6];
		pdmc->dmc_dtmg_f[i][7]=dmc_local_timing_ptr[k].dtmg[7];
		pdmc->dmc_dtmg_f[i][8]=dmc_local_timing_ptr[k].dtmg[8];
		pdmc->dmc_dtmg_f[i][9]=dmc_local_timing_ptr[k].dtmg[9];
		pdmc->dmc_dtmg_f[i][10]=dmc_local_timing_ptr[k].dtmg[10];
		pdmc->dmc_dtmg_f[i][11]=dmc_local_timing_ptr[k].dtmg[11];
		pdmc->dmc_dtmg_f[i][12]=dmc_local_timing_ptr[k].dtmg[12];
		pdmc->dmc_dtmg_f[i][13]=dmc_local_timing_ptr[k].dtmg[13];
		pdmc->dmc_dtmg_f[i][14]=dmc_local_timing_ptr[k].dtmg[14];
		pdmc->dmc_dtmg_f[i][15]=dmc_local_timing_ptr[k].dtmg[15];
		pdmc->dmc_dtmg_f[i][16]=dmc_local_timing_ptr[k].dtmg[16];
		pdmc->dmc_dtmg_f[i][17]=dmc_local_timing_ptr[k].dtmg[17];
		pdmc->dmc_dtmg_f[i][18]=dmc_local_timing_ptr[k].dtmg[18];
		pdmc->dmc_dtmg_f[i][19]=dmc_local_timing_ptr[k].dtmg[19];
	}
	return 0;
}
static uint32  lpddr3_get_mr1_val(u32 ddr_clk)
{
	unsigned char	mr1_value = 0x3;
	if ((ddr_clk > 933) && (ddr_clk <= 1066))
	{
		mr1_value = (1 << 6) | 0x3;
	}
	else if (ddr_clk > 800)
	{
		mr1_value = (1 << 6) | 0x3;
	}
	else if (ddr_clk > 733)
	{
		mr1_value = (1 << 6) | 0x3;
	}
	else if (ddr_clk > 667)
	{
		mr1_value = (1 << 5) | 0x3;
	}
	else if (ddr_clk > 600)
	{
		mr1_value = (0 << 5) | 0x3;
	}
	else if (ddr_clk > 533)
	{
		mr1_value = (7 << 5) | 0x3;
	}
	else if (ddr_clk > 400)
	{
		mr1_value = (3 << 6) | 0x3;
	}
	else if (ddr_clk > 166)
	{
		mr1_value = (1 << 7) | 0x3;
	}
	else
	{
		mr1_value = (1 << 5) | 0x3;
	}
	return mr1_value;
}
static void lpddr3_get_mr2_val(u32 ddr_clk)
{
	unsigned char	mr2_value;
	/* Only lpddr3 is considered  temporarily*/
	if ((ddr_clk > 933) && (ddr_clk <= 1066))
	{
		lpddr3_mr_info.rl = 16;
		lpddr3_mr_info.wl = 8;
	}
	else if (ddr_clk > 800)
	{
		lpddr3_mr_info.rl = 14;
		lpddr3_mr_info.wl = 8;
	}
	else if (ddr_clk > 733)
	{
		lpddr3_mr_info.rl = 12;
		lpddr3_mr_info.wl = 6;
	}
	else if (ddr_clk > 667)
	{
		lpddr3_mr_info.rl = 11;
		lpddr3_mr_info.wl = 6;
	}
	else if (ddr_clk > 600)
	{
		lpddr3_mr_info.rl = 10;
		lpddr3_mr_info.wl = 6;
	}
	else if (ddr_clk > 533)
	{
		lpddr3_mr_info.rl = 9;
		lpddr3_mr_info.wl = 5;
	}
	else if (ddr_clk > 400)
	{
		lpddr3_mr_info.rl = 8;
		lpddr3_mr_info.wl = 4;
	}
	else if (ddr_clk > 166)
	{
		lpddr3_mr_info.rl = 6;
		lpddr3_mr_info.wl = 3;
	}
	else
	{
		lpddr3_mr_info.rl = 6;
		lpddr3_mr_info.wl = 3;
	}
}
int lpddr3_mr_set_rlwl(int rl, int wl)
{
	if ((rl == 3) && (wl == 1))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 1);
	}
	else if ((rl == 6) && (wl == 3))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 4);
	}
	else if ((rl == 8) && (wl == 4))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 6);
	}
	else if ((rl == 9) && (wl == 5))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 7);
	}
	else if ((rl == 10) && (wl == 6))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 0x18);
	}
	else if ((rl == 11) && (wl == 6))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 0x19);
	}
	else if ((rl == 12) && (wl == 6))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 0x1a);
	}
	else if ((rl == 14) && (wl == 8))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 0x1c);
	}
	else if ((rl == 16) && (wl == 8))
	{
		lpddr_dmc_mrw(CMD_CS_BOTH, 0x2, 0x1e);
	}
	else
	{
		return -1;
	}
	return 0;
}


static unsigned char lpddr4_get_mr1_val(u32 clk)
{
	u32 val;

	if (clk <= 266)
	{
		val = 0x04;
	}
	else if (clk <= 533)
	{
		val = 0x14;
	}
	else if (clk <= 800)
	{
		val = 0x24;
	}
	else if (clk <= 1333)
	{
		val = 0x34;
	}
	else if (clk <= 1600)
	{
		val = 0x44;
	}
	else
	{
		val = 0x34;
	}

    return val;
}
static unsigned char lpddr4_get_mr2_val(u32 clk)
{

	unsigned char val;
	if(clk <= 266)
	{
		val = 0;
	}
	else if (clk <= 533)
	{
		val = 1|(1<<3);
	}
	else if (clk <= 800)
	{
		val = 2|(2<<3);
	}
	else if (clk <= 1066)
	{
		val = 3|(3<<3);
	}
	else if (clk <= 1333)
	{
		val = 4|(4<<3);
	}
	else if (clk <= 1600)
	{
		val = 5|(5<<3);
	}
	else if (clk <= 1866)
	{
		val = 6|(6<<3);
	}
	else if (clk <= 2133)
	{
		val = 7|(7<<3);
	}
	else /*<=1066*/
	{
		val = 7|(7<<3);
	}
	return val;
}
static unsigned char lpddr4_get_mr3_val(clock)
{
	unsigned char mr3_val = 0x3;
	/*pdds*/
	mr3_val |= (0x6 << 3);
#ifdef RD_DBI_EN
	mr3_val |= (1 << 6);
#else
	mr3_val |= (0 << 6);
#endif
	mr3_val |= (1 << 7);

	return mr3_val;
}

static void mr_set_drv(int drv)
{
	unsigned char val;

	switch(drv)
	{
	case 34:
		val = 1;
		break;
	case 40:
		val = 2;
		break;
	case 48:
		val = 3;
		break;
	case 60:
		val = 4;
		break;
	case 80:
		val = 6;
		break;
	case 120:
		val = 7;
		break;
	default:
		val = 2;;
	}
	lpddr_dmc_mrw(CMD_CS_BOTH, 3, val);
}

static void mr_set_zq(void)
{
	lpddr_dmc_mrw(CMD_CS_0, 10, 0xff);
	dmc_sprd_delay(10);
	lpddr_dmc_mrw(CMD_CS_1, 10, 0xff);
}

static void mpc_set_zq(u32 channel)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	u32 regval;
	/*enable channel xx software command.*/
	regval = pdmc->dmc_dcfg0;
	regval = u32_bits_set(regval, 20, 4, channel);
	pdmc->dmc_dcfg0 = regval;

	/*mpc zqcal start cs0*/
	pdmc->dmc_dcfg2 = 0x4f;
	pdmc->dmc_dcfg1 = 0x08000000;
	while((pdmc->dmc_dcfg1 >> 19 & 0x1ff) != 0);
	dmc_sprd_delay(2);

	/*mpc zqcal latch cs0*/
	pdmc->dmc_dcfg2 = 0x51;
	pdmc->dmc_dcfg1 = 0x08000000;
	while((pdmc->dmc_dcfg1 >> 19 & 0x1ff) != 0);
	dmc_sprd_delay(2);

	/*mpc zqcal start cs1*/
	pdmc->dmc_dcfg2 = 0x4f;
	pdmc->dmc_dcfg1 = 0x18000000;
	while((pdmc->dmc_dcfg1 >> 19 & 0x1ff) != 0);
	dmc_sprd_delay(2);

	/*mpc zqcal latch cs1*/
	pdmc->dmc_dcfg2 = 0x51;
	pdmc->dmc_dcfg1 = 0x18000000;
	while((pdmc->dmc_dcfg1 >> 19 & 0x1ff) != 0);

	pdmc->dmc_dcfg0 |= (0xf << 20);
}
void dram_init_mrws_lp3(u32 clock)
{
	unsigned int regval;
	unsigned char mrval;

	/*MR2 set RL WL*/
	lpddr3_get_mr2_val(clock);
	lpddr3_mr_set_rlwl(lpddr3_mr_info.rl, lpddr3_mr_info.wl);

	/*MR1 */
	mrval = lpddr3_get_mr1_val(clock);
	lpddr_dmc_mrw(CMD_CS_BOTH, 1, mrval);

}
void dram_init_mrws_lp4(u32 clock)
{
	unsigned int regval;
	unsigned char mrval;
	unsigned int freq;
	freq = find_freq_num(clock);
	/*MR1*/
	 mrval = lpddr4_get_mr1_val(clock);
	 lpddr_dmc_mrw(CMD_CS_BOTH, 1, mrval);

	 /*MR2 RL&WL*/
	 mrval = lpddr4_get_mr2_val(clock);
	 lpddr_dmc_mrw(CMD_CS_BOTH, 2, mrval);

	 /*MR3 dbi en*/
	 mrval = lpddr4_get_mr3_val(clock);
	 lpddr_dmc_mrw(CMD_CS_BOTH, 3, mrval);

	if ((cur_odt_on[freq] == 1))
	{
		mrval = 0x2;
		lpddr_dmc_mrw(CMD_CS_BOTH, 11, mrval);
	}
	else
	{
		//for kingston lpddr4 add
		lpddr_dmc_mrw(CMD_CS_BOTH, 11, 0x0);
		dmc_sprd_delay(10);
	}
	 /*MR12*/
	//if (ddr_chip_cur.io_mode == IO_LP4X)
	{
		mrval = 0x5E;
		lpddr_dmc_mrw(CMD_CS_BOTH, 12, mrval);
	}
	 /*MR13*/
	 mrval = 0;
	 lpddr_dmc_mrw(CMD_CS_BOTH, 13, mrval);
	 dmc_sprd_delay(10);

}

static void lpddr3_powerup_seq(u32 clock)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;

	/*step 1) cke up*/
	pdmc->dmc_dcfg0 |= 1<< 14;
	dmc_sprd_delay(300);

	/*step 2) reset sdram*/
	lpddr_dmc_mrw(CMD_CS_BOTH, 0x3f, 0);
	dmc_sprd_delay(10);

	/*step 3) ZQ calibration init*/
	mr_set_zq();
	dmc_sprd_delay(10);

	/*step 4) set DRV*/
	mr_set_drv(lpddr3_mr_info.ds);
}


static void  lpddr4_powerup_seq(u32 clock)
{
	DDRC_R1P0_REG_INFO_PTR pdmc = (DDRC_R1P0_REG_INFO_PTR)DMC_REG_ADDR_BASE_PHY;
	unsigned int regval;
	unsigned char mrval;

	/*1) **reset_n hold low*/
	dmc_sprd_delay(300);//tINIT0=200us(min)

	/*2)reset_n high*/
	pdmc->dmc_dcfg0 |= (1 << 15);
	dmc_sprd_delay(3000);//tINIT3=2ms+2us

	/*3) cke up*/
	pdmc->dmc_dcfg0 |= (1 << 14);
	dmc_sprd_delay(300);//tINIT5=2us

	/*rankx mpc -zqcal start*/
	mpc_set_zq(1);
	mpc_set_zq(2);

}
static void dram_power_up_set_post(void)
{
	/*PHY update requeset adn controllor ack counter value setting and cke
	 * ,reset_n SW control mode*/
	/*bit[16] pwrup_cke_rst_en*/
	reg_bits_set(DMC_GUCPHY0_BASE + 0xd1*4, 16, 1, 1);
	reg_bits_set(DMC_GUCPHY1_BASE + 0xd1*4, 16, 1, 1);
}
static void dram_init_power_up(u32 clock)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
		lpddr3_powerup_seq(clock);
	else
		lpddr4_powerup_seq(clock);
}
static void dram_init_mrws(u32 clock)
{
	if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
		dram_init_mrws_lp3(clock);
	else
		dram_init_mrws_lp4(clock);
}
void dram_powerup_seq(u32 clock)
{
	if (dram_init_powerup_times == 0)
	{
		dram_init_power_up(clock);
		dram_power_up_set_post();
	}
	dram_init_mrws(clock);
	dram_init_powerup_times ++;

}
