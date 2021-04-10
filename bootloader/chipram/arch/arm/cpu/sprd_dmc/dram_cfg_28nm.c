#include "dram_phy_28nm.h"
#include <common.h>

#if defined(DDR_LPDDR2)
const DDR_ACTIMING_T LPDDR2_ACTIMING_NATIVE =
{
	(39000),		/*tREFI unit tCK*/
	5/*4*/,			/*tMRD unit tCK*/
	430,			/*tRAS unit ns  plus temperature derating +2ns*/
	650,			/*tRC unit ns   plus temperature derating +2ns*/
	2200,			/*tRFC unit ns*/
	200,			/*tRCD unit ns*/
	200,			/*tRP unit ns*/
	200,			/*tRRD unit ns plus temperature derating +2ns*/
	150,			/*tWR unit ns*/
	75,			/*tWTR datasheet 7.5  200M 10ns*/
	1400,			/*tXSR unit ns*/
	80,			/*tXP unit ns*/
	3,			/*tCKE unit tCK*/
	1300,			/*tRFCab*/
	600,			/*tRFCpb*/
	10000,			/*tZQINIT*/
	3600,			/*tZQCL*/
	900,			/*tZQCS not always 90ns*/
	500,			/*tZQreset unit tCK*/
	0,			/*tZQoper unit tCK*/
	150,			/*tCKESR*/
	/*2*/6,			/*tCCD*/
	80,			/*tRTP*/
	600,			/*tFAW*/
	5000000,		/*tDPD*/
	30,			/*tDQSCK*/
	60,			/*tDQSCKmax*/
	5,			/*tMRW*/
	2,			/*tMRR*/
	0,			/*tDLLK*/
	0,			/*tMOD*/
	0,			/*tXS*/
	0,			/*tCKSRE*/
	0,			/*tCKSRX*/
	3,			/*cntRDMode*/
	4,			/*cntRDDLY*/
	2,			/*cntDQSGX*/
	1,			/*cntPGWAIT*/
	11,			/*cntZQDIV*/
};

DDR_ACTIMING_T lpddr2_actiming;

#elif defined(DDR_LPDDR3)
const DDR_ACTIMING_T LPDDR3_ACTIMING_NATIVE =
{
	(39000),		/*tREFI unit tCK*/
	10,			/*tMRD unit tCK*/
	440,			/*tRAS unit ns  plus temperature derating +2ns*/
	730,			/*tRC unit ns   plus temperature derating +2ns*/
	1300,			/*tRFC unit ns*/
	260,			/*tRCD unit ns*/
	290,			/*tRP unit ns*/
	120,			/*tRRD unit ns plus temperature derating +2ns*/
	150,			/*tWR unit ns*/
	75,			/*tWTR datasheet 7.5  200M 10ns*/
	1400,			/*tXSR unit ns*/
	75,			/*tXP unit ns*/
	75,			/*tCKE unit ns*/
	1300,			/*tRFCab*/
	600,			/*tRFCpb*/
	10000,			/*tZQINIT*/
	3600,			/*tZQCL*/
	900,			/*tZQCS not always 90ns*/
	500,			/*tZQreset unit tCK*/
	0,			/*tZQoper unit tCK*/
	150,			/*tCKESR*/
	4,			/*tCCD*/
	75,			/*tRTP*/
	500,			/*tFAW*/
	5000000,		/*tDPD*/
	25,			/*tDQSCK*/
	57,			/*tDQSCKmax*/
	10,			/*tMRW*/
	4,			/*tMRR*/
	0,			/*tDLLK*/
	0,			/*tMOD*/
	0,			/*tXS*/
	0,			/*tCKSRE*/
	0,			/*tCKSRX*/
	3,			/*cntRDMode*/
	4,			/*cntRDDLY*/
	2,			/*cntDQSGX*/
	1,			/*cntPGWAIT*/
	11,			/*cntZQDIV*/
};

DDR_ACTIMING_T lpddr3_actiming;
#endif

DRAM_INFO_T dram_info[]=
{
#if defined(DDR_LPDDR2)
/*      type          cs_num bank_num io_width row_num wc    bl    rl     wl    al       ac_timing                  native_ac_timing   */
{DRAM_LPDDR2_1CS_2G_X32, 1,      8,      32,    14,    0,  4,  6,  3,  0,   &lpddr2_actiming,  &LPDDR2_ACTIMING_NATIVE},
{DRAM_LPDDR2_1CS_4G_X32, 1,      8,      32,    14,    0,  4,  6,  3,  0,   &lpddr2_actiming,  &LPDDR2_ACTIMING_NATIVE},
{DRAM_LPDDR2_1CS_8G_X32, 1, 	 8, 	 32,	15,    0,  4,  6,  3,  0,	&lpddr2_actiming,  &LPDDR2_ACTIMING_NATIVE},
{DRAM_LPDDR2_1CS_4G_X16_2P, 1,   8,      32,	14,	   0,  4,  6,  3,  0,   &lpddr2_actiming,  &LPDDR2_ACTIMING_NATIVE},

{DRAM_LPDDR2_2CS_4G_X32, 2, 	 8, 	 32,    14,    0,  4,  6,  3,  0,   &lpddr2_actiming,  &LPDDR2_ACTIMING_NATIVE},
{DRAM_LPDDR2_2CS_8G_X32, 2, 	 8, 	 32,    14,    0,  4,  6,  3,  0,   &lpddr2_actiming,  &LPDDR2_ACTIMING_NATIVE},
#elif defined(DDR_LPDDR3)
{DRAM_LPDDR3_1CS_4G_X32, 1, 	 8, 	 32,    14,    0,  8,  6,  3,  0,   &lpddr3_actiming,  &LPDDR3_ACTIMING_NATIVE},
{DRAM_LPDDR3_1CS_6G_X32, 1, 	 8, 	 32,	15,    0,  8,  6,  3,  0,	&lpddr3_actiming,  &LPDDR3_ACTIMING_NATIVE},
{DRAM_LPDDR3_1CS_8G_X32, 1, 	 8, 	 32,	15,    0,  8,  6,  3,  0,	&lpddr3_actiming,  &LPDDR3_ACTIMING_NATIVE},
{DRAM_LPDDR3_2CS_8G_X32, 2,      8,      32,    14,    0,  8,  6,  3,  0, 	&lpddr3_actiming, &LPDDR3_ACTIMING_NATIVE},

{DRAM_LPDDR3_2CS_12G_X32, 2,     8, 	 32,    15,    0,  8,  6,  3,  0,   &lpddr3_actiming,  &LPDDR3_ACTIMING_NATIVE},
{DRAM_LPDDR3_2CS_6GX2_X32, 2,	 8, 	 32,	15,    0,  8,  6,  3,  0,	&lpddr3_actiming,  &LPDDR3_ACTIMING_NATIVE},
{DRAM_LPDDR3_2CS_16G_X32, 2,	 8, 	 32,	15,    0,  8,  6,  3,  0,	&lpddr3_actiming,  &LPDDR3_ACTIMING_NATIVE},
{DRAM_LPDDR3_2CS_8G_X16_2P, 2,	 8, 	 32,	14,    0,  8,  6,  3,  0,   &lpddr3_actiming,  &LPDDR3_ACTIMING_NATIVE},
#endif
};


#if defined(CONFIG_SC9630) || defined(CONFIG_SCX35L64)
umctl2_port_info_t UMCTL2_PORT_CONFIG[] =
{
//rw_order r_hpr r_pg  r_ugent r_age r_rord_bp r_age_cnt, w_pg  w_ugent w_age  w_age_cnt
    {TRUE, FALSE, TRUE, FALSE,  FALSE,  FALSE,     0x100,   TRUE, FALSE,  FALSE, 0x100},//port0,ca7
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x020,   TRUE, FALSE,  TRUE,  0x020},//port1,display
    {TRUE, FALSE, TRUE, FALSE,  FALSE,  FALSE,     0x100,   TRUE, FALSE,  FALSE, 0x100},//port2,gpu/gsp
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x008,   TRUE, FALSE,  TRUE,  0x008},//port3,ap zip
    {TRUE, FALSE, TRUE, FALSE,  TRUE,   FALSE,     0x040,   TRUE, FALSE,  TRUE,  0x040},//port4,mm
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x010,   TRUE, FALSE,  TRUE,  0x010},//port5,cp0 arm
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x002,   TRUE, FALSE,  TRUE,  0x002},//port6,CP0 dsp
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x002,   TRUE, FALSE,  TRUE,  0x002},//port7,cp1 accharq
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x002,   TRUE, FALSE,  TRUE,  0x002},//port8,cp1 dsp
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x010,   TRUE, FALSE,  TRUE,  0x010}, //port9,CP1 ca5
    {0xff},
};

#elif defined(CONFIG_SPX30G)
umctl2_port_info_t UMCTL2_PORT_CONFIG[] =
{
//rw_order r_hpr r_pg  r_ugent r_age r_rord_bp r_age_cnt, w_pg  w_ugent w_age  w_age_cnt
    {TRUE, FALSE,TRUE, FALSE,  TRUE,  FALSE,     0x040,   TRUE, FALSE,  TRUE, 0x040},//port0,mm/dcam/vsp
    {TRUE, FALSE,TRUE, FALSE,  FALSE, FALSE,     0x100,   TRUE, FALSE,  FALSE,0x100},//port1,GPU/gsp
    {TRUE, TRUE, TRUE, FALSE,  TRUE,  FALSE,     0x020,   TRUE, FALSE,  TRUE, 0x020},//port2,display
    {TRUE, FALSE,TRUE, FALSE,  FALSE, FALSE,     0x100,   TRUE, FALSE,  FALSE,0x100},//port3,CA7
    {TRUE, TRUE, TRUE, FALSE,  TRUE,  FALSE,     0x002,   TRUE, FALSE,  TRUE, 0x002},//port4,CPx DSP
    {TRUE, TRUE, TRUE, FALSE,  TRUE,  FALSE,     0x008,   TRUE, FALSE,  TRUE, 0x008},//port5,CP0W
    {TRUE, TRUE, TRUE, FALSE,  TRUE,  FALSE,     0x010,   TRUE, FALSE,  TRUE, 0x010},//port6,CP0 ARM
    {TRUE, FALSE,TRUE, FALSE,  TRUE,  FALSE,     0x080,   TRUE, FALSE,  TRUE, 0x080},//port7,AP matrix
    {TRUE, TRUE, TRUE, FALSE,  TRUE,  FALSE,     0x008,   TRUE, FALSE,  TRUE, 0x008},//port8,ZIP
    {TRUE, TRUE, TRUE, FALSE,  TRUE,  FALSE,     0x010,   TRUE, FALSE,  TRUE, 0x010}, //port9,CP2
    {0xff},
};
#endif

#ifdef PIKEL_DRIVER_SUPPORT_ON
umctl2_port_info_t UMCTL2_PORT_CONFIG_PIKEL[] =
{
//rw_order r_hpr r_pg  r_ugent r_age r_rord_bp r_age_cnt, w_pg  w_ugent w_age  w_age_cnt
    {TRUE, FALSE, TRUE, FALSE,  FALSE,  FALSE,     0x100,   TRUE, FALSE,  FALSE, 0x100},//port0,ca7
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x020,   TRUE, FALSE,  TRUE,  0x020},//port1,display
    {TRUE, FALSE, TRUE, FALSE,  FALSE,  FALSE,     0x100,   TRUE, FALSE,  FALSE, 0x100},//port2,gpu/gsp
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x008,   TRUE, FALSE,  TRUE,  0x008},//port3,ap zip
    {TRUE, FALSE, TRUE, FALSE,  TRUE,   FALSE,     0x040,   TRUE, FALSE,  TRUE,  0x040},//port4,mm
    //{TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x010,   TRUE, FALSE,  TRUE,  0x010},//port5,cp0 arm
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x002,   TRUE, FALSE,  TRUE,  0x002},//port6,CP0 dsp
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x002,   TRUE, FALSE,  TRUE,  0x002},//port7,cp1 accharq
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x002,   TRUE, FALSE,  TRUE,  0x002},//port8,cp1 dsp
    {TRUE, TRUE,  TRUE, FALSE,  TRUE,   FALSE,     0x010,   TRUE, FALSE,  TRUE,  0x010}, //port9,CP1 ca5
    {0xff},
};
#endif
extern void ddr_print(const unsigned char *string);

DRAM_INFO_T* get_dram_cfg(DRAM_TYPE_E dram_type)
{
	unsigned int i;

	for(i=0;i<sizeof(dram_info)/sizeof(dram_info[0]);i++){
		if(dram_type == dram_info[i].dram_type){
			return (DRAM_INFO_T*)&dram_info[i];
		}
	}
	ddr_print("\r\n can not find supported dram info!");
	while(1);
	return (DRAM_INFO_T*)&dram_info[0];
}

void __cal_actiming(DRAM_INFO_T *dram,unsigned int clk)
{
	DDR_ACTIMING_T *ac_timing		= dram->ac_timing;
	DDR_ACTIMING_T *native_ac_timing	= dram->native_ac_timing;

	if((clk > CLK_667MHZ) && (clk <= CLK_800MHZ))
	{
		dram->rl				=	12;
		dram->wl				=	6;
		ac_timing->cntDQSGX	=	3;
		ac_timing->cntRDDLY	=	6;
	}

	if((clk > CLK_600MHZ) && (clk <= CLK_667MHZ))
	{
		dram->rl				=	0x10;
		dram->wl				=	0x6;
		ac_timing->cntDQSGX	=	3;
		ac_timing->cntRDDLY	=	6;
	}

	if((clk > CLK_533MHZ) && (clk <= CLK_600MHZ))
	{
		dram->rl				=	0x9;
		dram->wl				=	0x5;
		ac_timing->cntDQSGX	=	3;
		ac_timing->cntRDDLY	=	5;
	}

	if((clk > CLK_467MHZ) && (clk <= CLK_533MHZ))
	{
		dram->rl		        =	0x8;
		dram->wl		        =	0x4;
		ac_timing->cntDQSGX	=	3;
		ac_timing->cntRDDLY	=	5;
	}

	if((clk > CLK_400MHZ) && (clk <= CLK_467MHZ))
	{
#if defined(DDR_LPDDR3)
        dram->rl                =   0x8;
		dram->wl                =   0x4;
#endif
#if defined(DDR_LPDDR2)
		dram->rl                =   0x7;
		dram->wl                =   0x4;
#endif
		ac_timing->cntDQSGX	=	3;
		ac_timing->cntRDDLY	=	5;
	}

	if((clk > CLK_100MHZ) && (clk <= CLK_400MHZ))
	{
		dram->rl		        =	0x6;
		dram->wl		        =	0x3;
		ac_timing->cntDQSGX	=	2;
		ac_timing->cntRDDLY	=	4;
	}

	ac_timing->cntPGWAIT	=	native_ac_timing->cntPGWAIT;    //PUB_AHB_CLK<200
	ac_timing->cntRDMode	=	native_ac_timing->cntRDMode;
	ac_timing->cntZQDIV		=	native_ac_timing->cntZQDIV;
}
