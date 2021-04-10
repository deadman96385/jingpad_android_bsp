#include <asm/types.h>
#include <common.h>
#include <asm/arch/clk_para_config.h>
#include "dmc_sprd_r3p0.h"

extern DRAM_CHIP_INFO ddr_chip_cur;

DMC_LOCAL_TIMING_CFG dmc_local_timing_lpddr3[] = {
	{
	667,
	{
		0x460F0C0C,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
		0x030D0A02,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
		0x8B3D4C93,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0xA508211C,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x00110606,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x001E0005,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0005,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x001C0005,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x03FF000A,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x03FF000A,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x03FC000A,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x03F86D08,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x14528F08,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_clk_mode[15]	dll_satu_cnt[14:8]		dll_init_cnt[6:0]*/
		0x0010010A	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},

	{
	533,
	{
		0x450C0909,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
#ifdef CONFIG_SOC_PIKE2
		0x03090A00,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#else
		0x03090900,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#endif
		0x6E303876,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x73081A16,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x000E0404,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
#ifdef CONFIG_SOC_PIKE2
		0x007F0002,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x007F0002,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x001C0003,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x03FF0007,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x03FF0007,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
#else
		0x001E0003,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0003,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x001C0003,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x00FF0008, /*dtmg8 ,data_ie_sel[31:16] data_ie_dly[4:0]*/
		0x00FF0008, /*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
#endif
		0x00FC0008,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x03286D06,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x10321308,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x000D00D5	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},
	{
	466,
	{
		0x440A0808,
		0x03090A00,
		0x602A3467,
		0x63081713,
		0x000E0404,
		0x007F0002,
		0x007F0002,
		0x001C0003,
		0x03FF0006,
		0x03FF0006,
		0x00FC0008,
		0x02C86D06,
		0x0E321608,
		0x000B00BA
	}
	},
#ifdef CONFIG_SOC_PIKE2
	{
	400,
	{
		0x43090707,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
		0x03080900,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
		0x52242C58,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x52081310,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x000C0303,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x007F0001,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x007F0001,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x001C0002,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x03FF0004,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x03FF0004,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x00FC0006,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x02686D04,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x0C321A08,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x000A00A0	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},
#endif
	{
	384,
	{
		0x43090606,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
		0x03080800,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
		0x4F232C55,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x52081310,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x000C0303,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x001E0002,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0002,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x001C0002,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x00FF0006,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x00FF0006,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x00FC0006,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x02586D04,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x0BB21B08,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x00090099	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},


	{
	256,
	{
		0x42060404,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
		0x03080700,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
		0x34182439,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x31080C0A,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x000B0303,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x001E0002,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0002,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x001C0002,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x003F0006,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x003F0006,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x003C0006,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x01A86D04,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x07C22908,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x00060066	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},

	{
	192,
	{
		0x41050303,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
		0x03080700,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
		0x2712242B,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x21080908,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x000B0303,	/*dtmg4 ,drf_rdata_latency[20:16]	drf_wdm_latency[11:8]	drf_wdata_latency[3:0]*/
		0x001E0002,	/*dtmg5 ,drf_data_oe_sel[31:16]		drf_data_oe_dly[3:0]*/
		0x001E0002,	/*dtmg6 ,drf_dqs_oe_sel[31:16]		drf_dqs_oe_dly[3:0]*/
		0x001C0002,	/*dtmg7 ,drf_dqs_out_sel[31:16]		drf_dqs_out_dly[3:0]*/
		0x003F0006,	/*dtmg8 ,drf_data_ie_sel[31:16]		drf_data_ie_dly[4:0]*/
		0x003F0006,	/*dtmg9 ,drf_dqs_ie_sel[31:16]		drf_dqs_ie_dly[4:0]*/
		0x003C0006,	/*dtmg10,drf_dqs_gate_sel[31:16]	drf_dqs_gate_dly[4:0]*/
		0x01486D04,	/*dtmg11,drf_t_zq[31:20]		drf_dll_auto_cnt[19:12]	drf_io_ib2_en[11]		drf_dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x05D23708,	/*dtmg12,drf_t_refpb[31:20]	drf_t_derate[17:16]	drf_dll_clk_mode[15]	drf_dll_satu_cnt[14:8]	drf_dll_init_cnt[6:0]*/
		0x0004004C     /*dtmg13,drf_pwr_down_idle_cnt[31:16]	drf_self_ref_idle_cnt[15:0]*/
	}
	},

	{
	166,
	{
		0x41040202,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
#ifdef CONFIG_SOC_PIKE2
		0x03060500,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#else
		0x03060400,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#endif
		0x210F1C25,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x21080806,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x00070101,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x001E0000,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0000,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x001C0000,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x000F0003,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x000F0003,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x000C0003,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x01186F01,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x05024008,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x00040042	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},

};

DMC_DELAY_LINE_CFG dl_cfg_lpddr3 = {
#ifndef CONFIG_SOC_PIKE2
	/*dmc_cfg_dll_ac*/
	0xF922C501,		/*dmc_cfg_dll_ac*/
	/*dmc_cfg_dll_ds*/
	0xF922C501,		/*dmc_cfg_dll_ds0*/
	0xF922C501,		/*dmc_cfg_dll_ds1*/
	0xF922C501,		/*dmc_cfg_dll_ds2*/
	0xF922C501,		/*dmc_cfg_dll_ds3*/
#else

	/*dmc_cfg_dll_ac*/
	0xF9228501,		/*dmc_cfg_dll_ac*/
	/*dmc_cfg_dll_ds*/
	0xF9228501,		/*dmc_cfg_dll_ds0*/
	0xF9228501,		/*dmc_cfg_dll_ds1*/
	0xF9228501,		/*dmc_cfg_dll_ds2*/
	0xF9228501,		/*dmc_cfg_dll_ds3*/
#endif
	/*dll ac*/
	CFG_DLL_CLKWR_AC,		/*dmc_clkwr_dll_ac*/
	/*dll ds*/
	CFG_DLL_CLKWR_DS0,		/*dmc_clkwr_dll_ds0*/
	CFG_DLL_CLKWR_DS1,		/*dmc_clkwr_dll_ds1*/
	CFG_DLL_CLKWR_DS2,		/*dmc_clkwr_dll_ds2*/
	CFG_DLL_CLKWR_DS3,		/*dmc_clkwr_dll_ds3*/
	/*dll dqsin pos*/
	CFG_DLL_DQSIN_POS_DS0,	/*dmc_dqsin_pos_dll_ds0*/
	CFG_DLL_DQSIN_POS_DS1,	/*dmc_dqsin_pos_dll_ds1*/
	CFG_DLL_DQSIN_POS_DS2,	/*dmc_dqsin_pos_dll_ds2*/
	CFG_DLL_DQSIN_POS_DS3,	/*dmc_dqsin_pos_dll_ds3*/
	/*dll dqsin neg*/
	CFG_DLL_DQSIN_NEG_DS0,	/*dmc_dqsin_neg_dll_ds0*/
	CFG_DLL_DQSIN_NEG_DS1,	/*dmc_dqsin_neg_dll_ds1*/
	CFG_DLL_DQSIN_NEG_DS2,	/*dmc_dqsin_neg_dll_ds2*/
	CFG_DLL_DQSIN_NEG_DS3,	/*dmc_dqsin_neg_dll_ds3*/
	/*dll dqsgate*/
	DMC_DQSGATE_DL_DS0,		/*dmc_dqsgate_dll_ds0*/
	DMC_DQSGATE_DL_DS1,		/*dmc_dqsgate_dll_ds1*/
	DMC_DQSGATE_DL_DS2,		/*dmc_dqsgate_dll_ds2*/
	DMC_DQSGATE_DL_DS3,		/*dmc_dqsgate_dll_ds3*/
};


LPDDR_MR_INFO lpddr3_mr_info = {
#ifdef CFG_BL
				CFG_BL,		/*burst length*/
#else
				DEFAULT_LPDDR3_BL,/*burst length*/
#endif

				 0,		/*burst type*/
				 0,		/*wrap*/
				 3,		/*nwr*/
				 6,		/*read latency*/
				 3,		/*write latency*/
				 DDR_DRV_MEM_CFG	/*driver strength*/
};

/* LPDDR2 timing/dll parameters should be defined here when request. */

DMC_LOCAL_TIMING_CFG dmc_local_timing_lpddr2[] = {
	{
	533,
	{
		0x450C0909,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
#ifdef CONFIG_SOC_PIKE2
		0x03090A00,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#else
		0x03090900,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#endif
		0x6E303876,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x73081A16,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x000E0404,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
#ifdef CONFIG_SOC_PIKE2
		0x007F0002,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x007F0002,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x00180003,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x03FF0007,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x03FF0007,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
#else
		0x001E0003,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0003,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x00180003,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x00FF0008,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x00FF0007,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
#endif
		0x00FC0008,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
#ifdef CONFIG_SOC_PIKE2
		0x03286D06,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
#else
		0x03286506,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
#endif
		0x10321308,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x000D00D5	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},

	{
       466,
	{
		0x440A0808,
#ifdef CONFIG_SOC_PIKE2
		0x03090900,
#else
		0x03090800,
#endif
		0x602A3467,
		0x63081713,
		0x000D0404,
#ifdef CONFIG_SOC_PIKE2
		0x007F0002,
		0x007F0002,
		0x00180003,
		0x03FF0005,
		0x03FF0005,
#else
		0x001E0003,
		0x001E0003,
		0x00180003,
		0x00FF0007,
		0x00FF0007,
#endif
		0x00FC0007,
		0x02C86D05,
		0x0E321608,
		0x000B00BA
	}
	},
	{
	400,
	{
		0x43090707,
#ifdef CONFIG_SOC_PIKE2
		0x03080900, /*dtmg1 ,tRTR[27:24]        tWTR[20:16] tRTW[11:8]  tRTP[3:0]*/
#else
		0x03080800,
#endif
		0x52242C58,
		0x52081310,
		0x000C0303,
#ifdef CONFIG_SOC_PIKE2
		0x007F0001, /*dtmg5 ,data_oe_sel[31:16] data_oe_dly[3:0]*/
		0x007F0001, /*dtmg6 ,dqs_oe_sel[31:16]          dqs_oe_dly[3:0]*/
		0x00180002, /*dtmg7 ,dqs_out_sel[31:16] dqs_out_dly[3:0]*/
		0x03FF0004, /*dtmg8 ,data_ie_sel[31:16] data_ie_dly[4:0]*/
		0x03FF0004, /*dtmg9 ,dqs_ie_sel[31:16]          dqs_ie_dly[4:0]*/
		0x00FC0006, /*dtmg10,dqs_gate_sel[31:16]        dqs_gate_dly[4:0]*/
#else
		0x001E0002,
		0x001E0002,
		0x00180002,
		0x00FF0006,
		0x00FF0006,
		0x00FFC006,
#endif
		0x02686D04,
		0x0C321A08,
		0x000A00A0
	}
	},
	{
	384,
	{
		0x43090606,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
		0x03080800,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
		0x4F232C55,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x52081310,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x000C0303,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x001E0002,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0002,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x00180002,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x00FF0006,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x00FF0006,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x00FC0006,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x02586D04,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x0BB21B08,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x00090099	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},


	{
	256,
	{
		0x42060404,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
		0x03070601,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
		0x34182039,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x31080C0A,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x00090202,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x001E0001,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0001,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x00180001,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x003F0004,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x003F0004,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x003C0004,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x01A86D02,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x07C22908,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x00060066	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},

	{
	192,
	{
		0x41050303, /*dtmg0 ,tCCD[31:28]		tRRD[27:24] tRPab[20:16]		tRCD[12:8]		tRP[4:0]*/
		0x03060600, /*dtmg1 ,tRTR[27:24]		tWTR[20:16] tRTW[11:8]	tRTP[3:0]*/
		0x27121C2B, /*dtmg2 ,tRFC[31:24]		tRFCpb[23:16]	tWR[15:10]		tXSR[9:0]*/
		0x21080908, /*dtmg3 ,tCKE[31:28]		tXP[27:24]		tMRD[19:16] tFAW[15:8]	tRAS[5:0]*/
		0x00080101, /*dtmg4 ,rdata_latency[20:16]		wdm_latency[11:8]		wdata_latency[3:0]*/
		0x001E0000, /*dtmg5 ,data_oe_sel[31:16] data_oe_dly[3:0]*/
		0x001E0000, /*dtmg6 ,dqs_oe_sel[31:16]			dqs_oe_dly[3:0]*/
		0x00180000, /*dtmg7 ,dqs_out_sel[31:16] dqs_out_dly[3:0]*/
		0x003F0003, /*dtmg8 ,data_ie_sel[31:16] data_ie_dly[4:0]*/
		0x003F0003, /*dtmg9 ,dqs_ie_sel[31:16]			dqs_ie_dly[4:0]*/
		0x003C0003, /*dtmg10,dqs_gate_sel[31:16]		dqs_gate_dly[4:0]*/
		0x01486D01, /*dtmg11,tZQ[31:20] dll_auto_cnt[19:12] io_ib2_en[11]		dll_bypass_mode[10] dll_satu_mode[9]	dll_half_mode[8]		dfs_mrw_mr2[7:0]*/
		0x05D23708, /*dtmg12,tRefpb[31:20]		tDerate[17:16]	dll_satu_cnt[13:7]				dll_init_cnt[6:0]*/
		0x0004004C		/*dtmg13,pwr_down_idle_cnt[31:16]				self_ref_idle_cnt[15:0]*/
	}
	},

	{
	166,
	{
		0x41040202,	/*dtmg0 ,tCCD[31:28]	tRRD[27:24]	tRPab[20:16]	tRCD[12:8]	tRP[4:0]*/
#ifdef CONFIG_SOC_PIKE2
		0x03060500,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#else
		0x03060400,	/*dtmg1 ,tRTR[27:24]	tWTR[20:16]	tRTW[11:8]	tRTP[3:0]*/
#endif
		0x210F1C25,	/*dtmg2 ,tRFC[31:24]	tRFCpb[23:16]	tWR[15:10]	tXSR[9:0]*/
		0x21080806,	/*dtmg3 ,tCKE[31:28]	tXP[27:24]	tMRD[19:16]	tFAW[15:8]  tRAS[5:0]*/
		0x00070101,	/*dtmg4 ,rdata_latency[20:16]	wdm_latency[11:8]	wdata_latency[3:0]*/
		0x001E0000,	/*dtmg5 ,data_oe_sel[31:16]	data_oe_dly[3:0]*/
		0x001E0000,	/*dtmg6 ,dqs_oe_sel[31:16]		dqs_oe_dly[3:0]*/
		0x00180000,	/*dtmg7 ,dqs_out_sel[31:16]	dqs_out_dly[3:0]*/
		0x000F0003,	/*dtmg8 ,data_ie_sel[31:16]	data_ie_dly[4:0]*/
		0x000F0003,	/*dtmg9 ,dqs_ie_sel[31:16]		dqs_ie_dly[4:0]*/
		0x000C0003,	/*dtmg10,dqs_gate_sel[31:16]	dqs_gate_dly[4:0]*/
		0x01186F01,	/*dtmg11,tZQ[31:20]	dll_auto_cnt[19:12]	io_ib2_en[11]	dll_bypass_mode[10]	dll_satu_mode[9]	dll_half_mode[8]	dfs_mrw_mr2[7:0]*/
		0x05024008,	/*dtmg12,tRefpb[31:20]	tDerate[17:16]	dll_satu_cnt[13:7]		dll_init_cnt[6:0]*/
		0x00040042	/*dtmg13,pwr_down_idle_cnt[31:16]		self_ref_idle_cnt[15:0]*/
	}
	},

};

DMC_DELAY_LINE_CFG dl_cfg_lpddr2;

LPDDR_MR_INFO lpddr2_mr_info = {
#ifdef CFG_BL
				CFG_BL,/*burst length*/
#else
				DEFAULT_LPDDR2_BL,/*burst length*/
#endif
				0,/*burst type*/
				0,/*wrap*/
				3,/*nwr*/
				6,/*read latency*/
				3,/*write latency*/
				DDR_DRV_MEM_CFG/*driver strength*/
};

#ifdef DDR_FREQ_AUTO_SEL
MR_AUTO_FREQ_SEL mr_freq_detect[] = {
	{
	DDR_REG_VAL_MR5_INDEX0,
	DDR_REG_VAL_MR6_INDEX0,
	DDR_REG_VAL_MR7_INDEX0,
	DDR_REG_VAL_MR8_INDEX0,
	DDR_CS_NUM_VAL_INDEX0,
	MR_DDR_CLK_SEL_INDEX0
	},
	{
	DDR_REG_VAL_MR5_INDEX1,
	DDR_REG_VAL_MR6_INDEX1,
	DDR_REG_VAL_MR7_INDEX1,
	DDR_REG_VAL_MR8_INDEX1,
	DDR_CS_NUM_VAL_INDEX1,
	MR_DDR_CLK_SEL_INDEX1
	},
	{
	DDR_REG_VAL_MR5_INDEX2,
	DDR_REG_VAL_MR6_INDEX2,
	DDR_REG_VAL_MR7_INDEX2,
	DDR_REG_VAL_MR8_INDEX2,
	DDR_CS_NUM_VAL_INDEX2,
	MR_DDR_CLK_SEL_INDEX2
	},
	{
	DDR_REG_VAL_MR5_INDEX3,
	DDR_REG_VAL_MR6_INDEX3,
	DDR_REG_VAL_MR7_INDEX3,
	DDR_REG_VAL_MR8_INDEX3,
	DDR_CS_NUM_VAL_INDEX3,
	MR_DDR_CLK_SEL_INDEX3
	},
	{
	DDR_REG_VAL_MR5_INDEX4,
	DDR_REG_VAL_MR6_INDEX4,
	DDR_REG_VAL_MR7_INDEX4,
	DDR_REG_VAL_MR8_INDEX4,
	DDR_CS_NUM_VAL_INDEX4,
	MR_DDR_CLK_SEL_INDEX4
	},
	{
	DDR_REG_VAL_MR5_INDEX5,
	DDR_REG_VAL_MR6_INDEX5,
	DDR_REG_VAL_MR7_INDEX5,
	DDR_REG_VAL_MR8_INDEX5,
	DDR_CS_NUM_VAL_INDEX5,
	MR_DDR_CLK_SEL_INDEX5
	},
	{
	DDR_REG_VAL_MR5_INDEX6,
	DDR_REG_VAL_MR6_INDEX6,
	DDR_REG_VAL_MR7_INDEX6,
	DDR_REG_VAL_MR8_INDEX6,
	DDR_CS_NUM_VAL_INDEX6,
	MR_DDR_CLK_SEL_INDEX6
	},
	{
	DDR_REG_VAL_MR5_INDEX7,
	DDR_REG_VAL_MR6_INDEX7,
	DDR_REG_VAL_MR7_INDEX7,
	DDR_REG_VAL_MR8_INDEX7,
	DDR_CS_NUM_VAL_INDEX7,
	MR_DDR_CLK_SEL_INDEX7
	}

};
#endif

void pin_swap_config(void)
{
#ifdef CONFIG_SOC_PIKE2
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 val;

	pdmc->dmc_ca_bit_pattern_0 = DDR_CA_SWAP_MAP0;
	pdmc->dmc_ca_bit_pattern_1 = DDR_CA_SWAP_MAP1;
#ifdef MANUAL_CONFIG_SWAP
	/*DQ set byte switch*/
	pdmc->dmc_dcfg4 = DDR_DQ_SWAP_MAP_BYTE0;
#endif
#endif
}

int search_for_freq_point(DMC_LOCAL_TIMING_CFG *dmc_timing, int size,  u32 clk)
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
#ifdef DDR_MR8_READ
int lpddr_timing_pre_init(DRAM_TYPE ddr_type, u32 ddr_clk, int number)
{
	int  k;
	int  size;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	DMC_LOCAL_TIMING_CFG *dmc_local_timing_ptr;

	if (ddr_type == DRAM_LPDDR2)
	{
		dmc_local_timing_ptr = dmc_local_timing_lpddr2;
		size = sizeof(dmc_local_timing_lpddr2)/sizeof(dmc_local_timing_lpddr2[0]);
	}
	else
	{
		dmc_local_timing_ptr = dmc_local_timing_lpddr3;
		size = sizeof(dmc_local_timing_lpddr3)/sizeof(dmc_local_timing_lpddr3[0]);
	}
	k = search_for_freq_point(dmc_local_timing_ptr, size, ddr_clk);
	pdmc->dmc_dtmg_f[number][0]=dmc_local_timing_ptr[k].dtmg[0];
	pdmc->dmc_dtmg_f[number][1]=dmc_local_timing_ptr[k].dtmg[1];
	pdmc->dmc_dtmg_f[number][2]=dmc_local_timing_ptr[k].dtmg[2];
	pdmc->dmc_dtmg_f[number][3]=dmc_local_timing_ptr[k].dtmg[3];
	pdmc->dmc_dtmg_f[number][4]=dmc_local_timing_ptr[k].dtmg[4];
	pdmc->dmc_dtmg_f[number][5]=dmc_local_timing_ptr[k].dtmg[5];
	pdmc->dmc_dtmg_f[number][6]=dmc_local_timing_ptr[k].dtmg[6];
	pdmc->dmc_dtmg_f[number][7]=dmc_local_timing_ptr[k].dtmg[7];
	pdmc->dmc_dtmg_f[number][8]=dmc_local_timing_ptr[k].dtmg[8];
	pdmc->dmc_dtmg_f[number][9]=dmc_local_timing_ptr[k].dtmg[9];
	pdmc->dmc_dtmg_f[number][10]=dmc_local_timing_ptr[k].dtmg[10];
	pdmc->dmc_dtmg_f[number][11]=dmc_local_timing_ptr[k].dtmg[11];
	pdmc->dmc_dtmg_f[number][12]=dmc_local_timing_ptr[k].dtmg[12];
	pdmc->dmc_dtmg_f[number][13]=dmc_local_timing_ptr[k].dtmg[13];

	return 0;
}
#endif

int lpddr_timing_init(DRAM_TYPE ddr_type, u32 ddr_clks_array[4])
{
	int i, k;
	int  size;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	DMC_LOCAL_TIMING_CFG *dmc_local_timing_ptr;
	u32  ddr_clk;

	if (ddr_type == DRAM_LPDDR2)
	{
		dmc_local_timing_ptr = dmc_local_timing_lpddr2;
		size = sizeof(dmc_local_timing_lpddr2)/sizeof(dmc_local_timing_lpddr2[0]);
	}
	else
	{
		dmc_local_timing_ptr = dmc_local_timing_lpddr3;
		size = sizeof(dmc_local_timing_lpddr3)/sizeof(dmc_local_timing_lpddr3[0]);
	}

	/*timing array */
	for(i = 0; i < 4; i++)
	{
		ddr_clk = ddr_clks_array[i];
		k = search_for_freq_point(dmc_local_timing_ptr, size, ddr_clk);
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
	}

	return 0;
}


int lpddr_dll_init(DRAM_TYPE ddr_type)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	DMC_DELAY_LINE_CFG  *p_dll_cfg;

	p_dll_cfg = &dl_cfg_lpddr3;

	/*step1, set dll*/
	pdmc->dmc_cfg_dll_ac = p_dll_cfg->dmc_cfg_dll_ac;
	pdmc->dmc_cfg_dll_ds0 = p_dll_cfg->dmc_cfg_dll_ds0;
	pdmc->dmc_cfg_dll_ds1 = p_dll_cfg->dmc_cfg_dll_ds1;
	pdmc->dmc_cfg_dll_ds2 = p_dll_cfg->dmc_cfg_dll_ds2;
	pdmc->dmc_cfg_dll_ds3 = p_dll_cfg->dmc_cfg_dll_ds3;

	/*step2, start dll*/
	pdmc->dmc_clkwr_dll_ac = p_dll_cfg->dmc_clkwr_dll_ac;
	pdmc->dmc_cfg_dll_ac &= ~(1<<8); //disable rf_dll_clr
	pdmc->dmc_cfg_dll_ac &= ~(1<<24); //rf_dll_pd_cnt[26:24] = 2
	pdmc->dmc_cfg_dll_ac |= (1<<25);

	pdmc->dmc_clkwr_dll_ds0 = p_dll_cfg->dmc_clkwr_dll_ds0;
	pdmc->dmc_dqsin_pos_dll_ds0 = p_dll_cfg->dmc_dqsin_pos_dll_ds0;
	pdmc->dmc_dqsin_neg_dll_ds0 = p_dll_cfg->dmc_dqsin_neg_dll_ds0;
	//pdmc->dmc_dqsgate_dll_ds0 = p_dll_cfg->dmc_dqsgate_dll_ds0;
	pdmc->dmc_cfg_dll_ds0 &= ~(1<<8); //disable rf_dll_clr
	pdmc->dmc_cfg_dll_ds0 &= ~(1<<24); //rf_dll_pd_cnt[26:24] = 2
	pdmc->dmc_cfg_dll_ds0 |= (1<<25);

	pdmc->dmc_clkwr_dll_ds1 = p_dll_cfg->dmc_clkwr_dll_ds1;
	pdmc->dmc_dqsin_pos_dll_ds1 = p_dll_cfg->dmc_dqsin_pos_dll_ds1;
	pdmc->dmc_dqsin_neg_dll_ds1 = p_dll_cfg->dmc_dqsin_neg_dll_ds1;
	//pdmc->dmc_dqsgate_dll_ds1 = p_dll_cfg->dmc_dqsgate_dll_ds1;
	pdmc->dmc_cfg_dll_ds1 &= ~(1<<8);  //disable rf_dll_clr
	pdmc->dmc_cfg_dll_ds1 &= ~(1<<24); //rf_dll_pd_cnt[26:24] = 2
	pdmc->dmc_cfg_dll_ds1 |= (1<<25);

	pdmc->dmc_clkwr_dll_ds2 = p_dll_cfg->dmc_clkwr_dll_ds2;
	pdmc->dmc_dqsin_pos_dll_ds2 = p_dll_cfg->dmc_dqsin_pos_dll_ds2;
	pdmc->dmc_dqsin_neg_dll_ds2 = p_dll_cfg->dmc_dqsin_neg_dll_ds2;
	//pdmc->dmc_dqsgate_dll_ds2 = p_dll_cfg->dmc_dqsgate_dll_ds2;
	pdmc->dmc_cfg_dll_ds2 &= ~(1<<8);  //disable rf_dll_clr
	pdmc->dmc_cfg_dll_ds2 &= ~(1<<24); //rf_dll_pd_cnt[26:24] = 2
	pdmc->dmc_cfg_dll_ds2 |= (1<<25);

	pdmc->dmc_clkwr_dll_ds3 = p_dll_cfg->dmc_clkwr_dll_ds3;
	pdmc->dmc_dqsin_pos_dll_ds3 = p_dll_cfg->dmc_dqsin_pos_dll_ds3;
	pdmc->dmc_dqsin_neg_dll_ds3 = p_dll_cfg->dmc_dqsin_neg_dll_ds3;
	//pdmc->dmc_dqsgate_dll_ds3 = p_dll_cfg->dmc_dqsgate_dll_ds3;
	pdmc->dmc_cfg_dll_ds3 &= ~(1<<8);  //disable rf_dll_clr
	pdmc->dmc_cfg_dll_ds3 &= ~(1<<24); //rf_dll_pd_cnt[26:24] = 2
	pdmc->dmc_cfg_dll_ds3 |= (1<<25);

	return 0;
}


int dram_zq_calibration(void)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	u32 tmp;

	/* Disable auto-refresh and per-bank auto-refresh mode*/
	tmp = pdmc->dmc_dcfg3;
	tmp = u32_bits_set(tmp, 12, 1, 0);
	tmp = u32_bits_set(tmp, 15, 1, 0);
	pdmc->dmc_dcfg3 = tmp;

	dmc_mrw(CMD_CS_0, 0xa, 0xff);
	dmc_sprd_delay(2);
	dmc_mrw(CMD_CS_1, 0xa, 0xff);
	dmc_sprd_delay(2);

	return 0;
}


void phy_io_ds_dqs_pull(void)
{
	u32 temp;
	temp = REG32(0x300004a4);			//phy_io_ds0_dqs_pull
	temp = u32_bits_set(temp, 24, 2, 3);
	REG32(0x300004a4) = temp;
	temp = REG32(0x300005a4);			//phy_io_ds1_dqs_pull
	temp = u32_bits_set(temp, 24, 2, 3);
	REG32(0x300004a4) = temp;
	temp = REG32(0x300006a4);			//phy_io_ds2_dqs_pull
	temp = u32_bits_set(temp, 24, 2, 3);
	REG32(0x300004a4) = temp;
	temp = REG32(0x300007a4);			//phy_io_ds3_dqs_pull
	temp = u32_bits_set(temp, 24, 2, 3);
	REG32(0x300004a4) = temp;
}


int lpddr_update_row_column(DRAM_JEDEC_INFO *info, LPDDR_JEDEC_ORIGINIZE *org_standard_ptr, int org_standard_num)
{
	int i;
	for (i = 0; i < org_standard_num; i++)
	{
		if ((info->cs_size == org_standard_ptr[i].cs_size) &&
			(info->dw == org_standard_ptr[i].dw) &&
			(info->bank == org_standard_ptr[i].bank))
		{
			info->row = org_standard_ptr[i].row;
			info->column= org_standard_ptr[i].column;
			return 0;
		}
	}
	return -1;
}

int lpddr2_update_jedec_info(u8 val, DRAM_JEDEC_INFO *info,
			     LPDDR_JEDEC_ORIGINIZE *org_standard_ptr,
			     int org_standard_num)
{
	u8 tmp;

	/*dw*/
	tmp = val>>6;
	if (0 == tmp)
	{
		info->dw = 32;
	}
	else if (1 == tmp)
	{
		info->dw = 16;
	}
	else if (2 == tmp)
	{
		/* DMC r2p0 just supports 32/16. */
		info->dw = 8;
		return -1;
	}
	else
	{
		return -1;
	}
	/*cs size*/
	tmp = (val>>2)&0xf;
	switch(tmp)
	{
		case 0:
			info->cs_size = 0x800000;
			info->bank = 4;
			break;
		case 1:
			info->cs_size = 0x1000000;
			info->bank = 4;
			break;
		case 2:
			info->cs_size = 0x2000000;
			info->bank = 4;
			break;
		case 3:
			info->cs_size = 0x4000000;
			info->bank = 4;
			break;
		case 4:
			info->cs_size = 0x8000000;
			if ((val&0x3) == 0)
			{
				info->bank = 8;
			}
			else if ((val&0x3) == 1)
			{
				info->bank = 4;
			}
			else
			{
				return -2;
			}
			break;
		case 5:
			info->cs_size = 0x10000000;
			if ((val&0x3) == 0)
			{
				info->bank = 8;
			}
			else if ((val&0x3) == 1)
			{
				info->bank = 4;
			}
			else
			{
				return -3;
			}
			break;
		case 6:
			info->cs_size = 0x20000000;
			info->bank = 8;
			break;
		case 7:
			info->cs_size = 0x40000000;
			info->bank = 8;
			break;
		case 0xe:
			info->cs_size = 0x30000000;
			info->bank = 8;
			break;
		default:
			return -4;
	}

	if (0 != lpddr_update_row_column(info, org_standard_ptr, org_standard_num))
	{
		return -5;
	}
	return 0;
}

int lpddr3_update_jedec_info(u8 val, DRAM_JEDEC_INFO *info,
			     LPDDR_JEDEC_ORIGINIZE *org_standard_ptr,
			     int org_standard_num)
{
	u8 tmp;

	/*dw*/
	tmp = val>>6;
	if (0 == tmp)
	{
		info->dw = 32;
	}
	else if (1 == tmp)
	{
		info->dw = 16;
	}
	else
	{
		return -1;
	}
	/*cs size*/
	tmp = (val>>2)&0xf;
	switch(tmp)
	{
		case 6:
			info->cs_size = 0x20000000;
			info->bank = 8;
			break;
		case 7:
			info->cs_size = 0x40000000;
			info->bank = 8;
			break;
		case 8:
			info->cs_size = 0x80000000;
			info->bank = 8;
			break;
		case 0xd:
			info->cs_size = 0x60000000;
			info->bank = 8;
			break;
		case 0xe:
			info->cs_size = 0x30000000;
			info->bank = 8;
			break;
		default:
			return -2;
	}

	if (0 != lpddr_update_row_column(info, org_standard_ptr, org_standard_num))
	{
		return -3;
	}
	return 0;
}


#ifdef DDR_AUTO_DETECT

extern LPDDR_JEDEC_ORIGINIZE org_standard[14];

extern DDR_UNSYMMETRY_MODE unsymmetry_mode_cur;
char  log_string_1[32];
static char *  toHex(u32 val)
{
	int i, j, num;
	u32 temp = val;

	log_string_1[0] = '0';
	log_string_1[1] = 'x';
	for (i = 0; i < 8; i++)
	{
		temp = (val >> ((7-i)*4)) & 0xf;
		if (temp < 0xa)
			log_string_1[2+i] = temp+0x30;
		else
			log_string_1[2+i] = 'A'+temp-0xa;
	}
	log_string_1[10] = ' ';
	log_string_1[11] = 0;
	return log_string_1;
}
int update_cs_num(void)
{
	int cs_num = 0;
	int i,j,t1=0,t2=0;
	u8 mr5_cs[2],mr8_cs[2];
	for(i = 0; i <= 1; i++)
	{
		t1 = t2 = 0;
		for(j = 0; j < 8; j++)
		{
			dmc_mrr(i, 5, &mr5_cs[i], 10000);
			dmc_mrr(i, 8, &mr8_cs[i], 10000);
			if((t1 == 0) && (t2 == 0))
			{
				t1 = mr5_cs[i];
				t2 = mr8_cs[i];
			}
			else if(t1 != mr5_cs[i])
			{
				mr5_cs[i] = 0xff;
				break;
			}
			else if(t2 != mr8_cs[i])
			{
				mr8_cs[i] = 0xff;
				break;
			}
		}
	}

	if(((ddr_chip_cur.chip_type == DRAM_LPDDR3) && (1 != (mr8_cs[0] >> 7)) ||
	     ((ddr_chip_cur.chip_type == DRAM_LPDDR2) && (3 != (mr8_cs[0] >> 6)) )))
	{
		cs_num++;

		/* CS 1 is valid. */
		if((mr5_cs[0] == mr5_cs[1]) && (mr5_cs[1] != mr8_cs[1]) )
		{
			cs_num++;
		}
	}

	if(cs_num<1)
	{
		return -1;
	}
	else if(cs_num == 1)
	{
		//jedec_info_cs1.cs_size = 0;
		ddr_chip_cur.cs1_jedec_info->cs_size = 0;
	}
	ddr_chip_cur.cs_num = cs_num;
	ddr_chip_cur.manufacture_id = mr5_cs[0];
	return 0;
}
/*
#ifndef CONFIG_SOC_PIKE2
int update_chip_type(u8 mr8)
{
	int temp;
	temp = ((mr8>>4)&0x3);
	if (temp == 0x3)
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR3;
	}
	else if ((temp == 0) || (temp == 1))
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR2;
	}
	else
	{
		return -1;
	}
	return 0;
}
#else
int update_chip_type(u8 mr8)
{
	if ((mr8&0x3) == 0x3)
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR3;
	}
	else if ((mr8&0x3)==0 || (mr8&0x3) == 1)
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR2;
	}
	else
	{
		return -1;
	}
	return 0;
}
#endif
*/
int update_jedec_info(u8 mr8, int cs_index,LPDDR_JEDEC_ORIGINIZE *org_standard_ptr, int org_standard_num)
{
	DRAM_JEDEC_INFO *info;

	if (0 == cs_index)
	{
		info = ddr_chip_cur.cs0_jedec_info;
	}
	else if (1 == cs_index)
	{
		info = ddr_chip_cur.cs1_jedec_info;
	}
	else
	{
		return -1;
	}

	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		if (0 != lpddr2_update_jedec_info(mr8, info,org_standard_ptr, org_standard_num))
		{
			return -2;
		}
	}
	else if (ddr_chip_cur.chip_type == DRAM_LPDDR3)
	{
		if (0 != lpddr3_update_jedec_info(mr8, info,org_standard_ptr, org_standard_num))
		{
			return -3;
		}
	}
	else
	{
		return -4;
	}
	return 0;
}


/*According to constraintion all ddr chip's cs width must be 32 bits.
  So if the information we read fraom MR register is 16 bits width it
  must be two die in one cs*/
int correct_parameter_by_product_constraintion(int cs)
{
	DRAM_JEDEC_INFO *info;

	if (0 == cs)
	{
		info = ddr_chip_cur.cs0_jedec_info;
	}
	else if (1 == cs)
	{
		info = ddr_chip_cur.cs1_jedec_info;
	}
	else
	{
		return -1;
	}

	if (info->dw == 16)
	{
		info->dw = 32;
		info->cs_size *= 2;
	}
	return 0;
}

int lpddr_auto_detect(void)
{
	u8 mr8;
	int  org_standard_num;
	DRAM_JEDEC_INFO *cs0_info, *cs1_info;

	if (0 != dmc_mrr(0, 8, &mr8, 10000))
	{
		return -1;
	}
	dmc_print_str("Swap later\r\n");
	dmc_print_str("CS0_MR8:");
	dmc_print_str(toHex(mr8));
	dmc_print_str("\r\n");
	/*if (0 != update_chip_type(mr8))
	{
		return -1;
	}*/

	if (0 != update_cs_num())
	{
		return -1;
	}

	org_standard_num = sizeof(org_standard)/sizeof(org_standard[0]);
	if (0 != update_jedec_info(mr8, 0, org_standard, org_standard_num))
	{
		return -1;
	}

	cs0_info = ddr_chip_cur.cs0_jedec_info;
	cs1_info = ddr_chip_cur.cs1_jedec_info;

	correct_parameter_by_product_constraintion(0);
	if (2 == ddr_chip_cur.cs_num)
	{
		if (0 != dmc_mrr(1, 8, &mr8, 10000))
		{
			return -1;
		}
		dmc_print_str("CS1_MR8:");
		dmc_print_str(toHex(mr8));
		dmc_print_str("\r\n");
		if (0 != update_jedec_info(mr8, 1, org_standard, org_standard_num))
		{
			return -1;
		}
		correct_parameter_by_product_constraintion(1);
		if (cs0_info->cs_size == cs1_info->cs_size)
		{
			ddr_chip_cur.unsymmetry = 0;
		}
		else
		{
			/* TODO: needs update here according to ddr column configuration document from ASIC team and how to configure dmc_cfg0. */
			if ((cs0_info->cs_size == 0x20000000) && (cs1_info->cs_size == 0x10000000))
			{
				unsymmetry_mode_cur = DDR_6Gb_10_COL_MODE;
			}
			else if((cs0_info->cs_size == 0x40000000) && (cs1_info->cs_size == 0x20000000))
			{
				unsymmetry_mode_cur = DDR_6Gb_11_COL_MODE;
			}
			else if ((cs0_info->cs_size == 0x80000000) && (cs1_info->cs_size == 0x40000000))
			{
				unsymmetry_mode_cur = DDR_12Gb_MODE;
			}
			else
			{
				return -1;
			}
			ddr_chip_cur.unsymmetry = 1;
		}
	}
	else
	{
		ddr_chip_cur.unsymmetry = 0;
	}
	return 0;
}
#endif

#ifdef DDR_MR8_READ
int update_pin_swap_chip_type(u8 mr8)
{
#if defined(CONFIG_SOC_PIKE2)
     if ((mr8&0x3) == 0x3)
        {
		ddr_chip_cur.chip_type = DRAM_LPDDR3;
			if(mr8 & (1 << 7))
			{
				ddr_chip_cur.pcb_swap_type = LP3_DIE_LP2_SWAP_EMCP_LP2_T;
			}
			else
			{
				ddr_chip_cur.pcb_swap_type = EMCP_LP3_T;
			}
        }
        else if ((mr8&0x3)==0 || (mr8&0x3) == 1)
        {
			ddr_chip_cur.chip_type = DRAM_LPDDR2;
			if(mr8 & (1 << 7))
			{
				ddr_chip_cur.pcb_swap_type = EMCP_LP2_T;
			}
			else
			{
				ddr_chip_cur.pcb_swap_type = LP2_DIE_LP3_SWAP_EMCP_LP3_T;
			}
        }
        else
        {
                return -1;
        }
#elif defined(LP2_DIE_LP3_SWAP_EMCP_LP3_T_SUPPORT)
	ddr_chip_cur.pcb_swap_type = LP2_DIE_LP3_SWAP_EMCP_LP3_T;
	if(mr8 & (1 << 5))
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR3;
	}
	else
	{
		ddr_chip_cur.chip_type = DRAM_LPDDR2;
	}
#elif defined(LP3_DIE_LP2_SWAP_EMCP_LP2_T_SUPPORT)
	ddr_chip_cur.pcb_swap_type = LP3_DIE_LP2_SWAP_EMCP_LP2_T;
        if(mr8 & (1 << 5))
        {
                ddr_chip_cur.chip_type = DRAM_LPDDR3;
        }
        else
        {
                ddr_chip_cur.chip_type = DRAM_LPDDR2;
        }
#else
	//LP3
	if(mr8 & (1 << 5))
	{
		if(mr8 & (1 << 6))
		{
			ddr_chip_cur.pcb_swap_type = EMCP_LP3_T;
		}
		else
		{
			ddr_chip_cur.pcb_swap_type = DISCRETE_LP3_T;
		}
		ddr_chip_cur.chip_type = DRAM_LPDDR3;
	}
	else //LP2
	{
		if(mr8 & (1 << 0))
		{
			ddr_chip_cur.pcb_swap_type = EMCP_LP2_T;
		}
		else
		{
			ddr_chip_cur.pcb_swap_type = LP2_DIE_LP3_SWAP_DISCRETE_LP3_T;
		}
		ddr_chip_cur.chip_type = DRAM_LPDDR2;
	}
#endif
	return 0;
}
int lpddr_pre_powerup_init(void)
{
	unsigned char val = 0;
	u8 mr8;
	DRAM_JEDEC_INFO *cs0_info, *cs1_info;
	u32 regval;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;

	/*step 1): cke up*/
	pdmc->dmc_dcfg0 |= 1<<14;

	/*tINIT3 > 200us 100:99us*/
	dmc_sprd_delay(300);

	/*step 2): Issue reset DRAM command */
	dmc_mrw(CMD_CS_BOTH, 0x3f, 0);
	dmc_sprd_delay(10);

	/*step 3) DRAM zq calibration*/
	dram_zq_calibration();


	/*step 4)  After za calibration set  rf_phy_io_ds_dqs_rpull (default:0) bit[25:24]=1,for power*/
	regval = pdmc->dmc_io_dq_ctrl_ds;
	regval = u32_bits_set(regval, 24, 2, 1);
	pdmc->dmc_io_dq_ctrl_ds = regval;

	/*step 5) setting 166M latency*/
	mr_set_rlwl(3, 1);

	if (0 != dmc_mr8(0, 8, &mr8, 10000))
	{
		return -1;
	}
	dmc_print_str("Before swap\r\n");
	dmc_print_str("CS0_MR8:");
	dmc_print_str(toHex(mr8));
	dmc_print_str("\r\n");
	if (0 != update_pin_swap_chip_type(mr8))
	{
		return -1;
	}

	return 0;
}
#endif

#ifdef DDR_FREQ_AUTO_SEL
int mr_freq_select(u32 *ddr_clk)
{
	u8 mr5_val = 0,mr6_val = 0,mr7_val = 0,mr8_val = 0;
	int size = sizeof(mr_freq_detect)/sizeof(mr_freq_detect[0]);
	int i;
	dmc_mrr(0, 5, &mr5_val, 10000);
	dmc_mrr(0, 6, &mr6_val, 10000);
	dmc_mrr(0, 7, &mr7_val, 10000);
	dmc_mrr(0, 8, &mr8_val, 10000);
	if (0 != update_cs_num())
	{
		return -1;
	}
	/*
	dmc_print_str(toHex(mr5_val));
	dmc_print_str("\r\n");
	dmc_print_str(toHex(mr6_val));
	dmc_print_str("\r\n");
	dmc_print_str(toHex(mr7_val));
	dmc_print_str("\r\n");
	dmc_print_str(toHex(mr8_val));
	dmc_print_str("\r\n");
	dmc_print_str(toHex(ddr_chip_cur.cs_num));
	dmc_print_str("\r\n");
	*/
	for(i = 0; i < size; i++)
	{
		 if((mr_freq_detect[i].reg_val_mr5 == mr5_val) && (mr_freq_detect[i].reg_val_mr6 == mr6_val)
			&& (mr_freq_detect[i].reg_val_mr7 == mr7_val) && (mr_freq_detect[i].reg_val_mr8 == mr8_val)
			&& (ddr_chip_cur.cs_num == mr_freq_detect[i].ddr_cs_num))
		{
			*ddr_clk = mr_freq_detect[i].ddr_clk_sel;
			return 0;
		}
	}
	return -1;
}
#endif

int lpddr_powerup_init(u32 ddr_clk)
{
	unsigned char val = 0;
	u32 regval;
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;

	/*step 1): cke up*/
	pdmc->dmc_dcfg0 |= 1<<14;

	/*tINIT3 > 200us 100:99us*/
	dmc_sprd_delay(300);

	/*step 2): Issue reset DRAM command */
	dmc_mrw(CMD_CS_BOTH, 0x3f, 0);
	dmc_sprd_delay(10);

	/*step 3) DRAM zq calibration*/
	dram_zq_calibration();


	/*step 4)  After za calibration set  rf_phy_io_ds_dqs_rpull (default:0) bit[25:24]=1,for power*/
	regval = pdmc->dmc_io_dq_ctrl_ds;
	regval = u32_bits_set(regval, 24, 2, 1);
	pdmc->dmc_io_dq_ctrl_ds = regval;

	if (ddr_chip_cur.chip_type == DRAM_LPDDR2)
	{
		if ((ddr_clk > 466) && (ddr_clk <= 533))
		{
			lpddr2_mr_info.rl = 8;
			lpddr2_mr_info.wl = 4;
		}
		else if (ddr_clk > 400)
		{
			lpddr2_mr_info.rl = 7;
			lpddr2_mr_info.wl = 4;
		}
		else if (ddr_clk > 333)
		{
			lpddr2_mr_info.rl = 6;
			lpddr2_mr_info.wl = 3;
		}
		else if (ddr_clk > 266)
		{
			lpddr2_mr_info.rl = 5;
			lpddr2_mr_info.wl = 2;
		}
		else if (ddr_clk > 200)
		{
			lpddr2_mr_info.rl = 4;
			lpddr2_mr_info.wl = 2;
		}
		else
		{
			lpddr2_mr_info.rl = 3;
			lpddr2_mr_info.wl = 1;
		}

		/* step 5) issue MRW,MR2,set WL/RL*/
		if (0 != mr_set_rlwl(lpddr2_mr_info.rl, lpddr2_mr_info.wl))
		{
			return -1;
		}

		/*step 6)  issue MRW,MR1,set burst length*/
		switch(lpddr2_mr_info.bl)
		{
			case 4:
				val = 2;
				break;
			case 8:
				val = 3;
				break;
			case 16:
				val = 4;
				break;
			default:
				return -1;
		}
		/*burst type:sequential*/
		if (lpddr2_mr_info.bt == 1)
		{
			val |= 1<<3;
		}
		/*WC:wrap*/
		if (lpddr2_mr_info.wc == 1)
		{
			val |= 1<<4;
		}
		/*nwr:3*/
		if (lpddr2_mr_info.nwr<3 || lpddr2_mr_info.nwr>7)
		{
			return -1;
		}
		val |= (lpddr2_mr_info.nwr-2)<<5;
		dmc_mrw(CMD_CS_BOTH, 0x1, val);
		/*driver strength*/
		dmc_sprd_delay(10);
		if (0 != mr_set_drv(lpddr2_mr_info.ds))
		{
			return -1;
		}
		dmc_sprd_delay(10);
		/*step 7) If DRAM is lpddr2, issue AUTO REF command */
		/* TODO: issue AUTO REF command for LPDDR2 */
		pdmc->dmc_dcfg1 = 0x80200000;
		/* wait until [26:20]==0 */
		while(((pdmc->dmc_dcfg1 >> 20) & 0x7f) != 0);
	}
	else
	{
		/* Only lpddr3 is considered  temporarily. Lpddr2 will be completed in future when request. */
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
			lpddr3_mr_info.rl = 3;
			lpddr3_mr_info.wl = 1;
		}

		/* step 5) issue MRW,MR2,set WL/RL*/
		if (0 != mr_set_rlwl(lpddr3_mr_info.rl, lpddr3_mr_info.wl))
		{
			return -1;
		}

		/*step 6)  issue MRW,MR1,set burst length*/
		switch(lpddr3_mr_info.bl)
		{
			case 4:
				val = 2;
				break;
			case 8:
				val = 3;
				break;
			case 16:
				val = 4;
				break;
			default:
				return -1;
		}
		/*burst type:sequential*/
		if (lpddr3_mr_info.bt == 1)
		{
			val |= 1<<3;
		}
		/*WC:wrap*/
		if (lpddr3_mr_info.wc == 1)
		{
			val |= 1<<4;
		}
		/*nwr:3*/
		if (lpddr3_mr_info.nwr<3 || lpddr3_mr_info.nwr>7)
		{
			return -1;
		}
		val |= (lpddr3_mr_info.nwr-2)<<5;
		dmc_mrw(CMD_CS_BOTH, 0x1, val);

		/*driver strength*/
		dmc_sprd_delay(10);
		if (0 != mr_set_drv(lpddr3_mr_info.ds))
		{
			return -1;
		}
		dmc_sprd_delay(10);
	}
	return 0;
}

int lpddr3_ac_train_reset(void)
{
	DMC_R3P0_REG_INFO_PTR pdmc = (DMC_R3P0_REG_INFO_PTR)PUB_DMC_BASE;
	unsigned char val = 0;

	pdmc->dmc_dcfg3 &= ~(1<<12);

	/*reset ddr*/
	dmc_mrw(CMD_CS_BOTH, 0x3f, 0);
	/*burst length:4*/
	switch(lpddr3_mr_info.bl)
	{
		case 4:
			val = 2;
			break;
		case 8:
			val = 3;
			break;
		case 16:
			val = 4;
			break;
		default:
			return -1;
	}
	/*burst type:sequential*/
	if (lpddr3_mr_info.bt == 1)
	{
		val |= 1<<3;
	}
	/*WC:wrap*/
	if (lpddr3_mr_info.wc == 1)
	{
		val |= 1<<4;
	}
	/*nwr:3*/
	if (lpddr3_mr_info.nwr<3 || lpddr3_mr_info.nwr>7)
	{
		return -1;
	}
	val |= (lpddr3_mr_info.nwr-2)<<5;
	dmc_sprd_delay(10);
	dmc_mrw(CMD_CS_BOTH, 0x1, val);

	/*read latency:6*/
	/*write latency:3*/
	dmc_sprd_delay(10);
	if (0 != mr_set_rlwl(lpddr3_mr_info.rl, lpddr3_mr_info.wl))
	{
		return -1;
	}
	/*driver strength*/
	dmc_sprd_delay(10);
	if (0 != mr_set_drv(lpddr3_mr_info.ds))
	{
		return -1;
	}
	dmc_sprd_delay(10);

	/*zq calication*/
	dmc_sprd_delay(10);
	dram_zq_calibration();

	/*hardware auto refresh enable*/
	pdmc->dmc_dcfg3 |= 1<<12;
	return 0;
}
