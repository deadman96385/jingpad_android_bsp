#include "ddr_timing.h"

#ifdef DRAM_LPDDR3
//========================================CANDS_CTL_TIMING_INFO_LP3========================================//
const CANDS_CTL_TIMING_T CANDS_CTL_TIMING_INFO_LP3[] =
{
#if 0
	{
	156,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0,            13,        2,     2,     0,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       3,    0,        0,        0,       0,       0,       3,      0,       0,       0,       0,      0,       8,    1,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  1,          0,      8,    0,   16,    0x79E0, 0x9C,   0x614,  4,    1,    10,   10,   3,     0,        3,     0,    5,             0x2AA7,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  7,        4,      12,  4,    4,   0x256,0x21, 2,    4,    0,   0,             0,            0,          4,   4,    0x24,  0x24, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      7,     4,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  0,      2,          0,          2,          2,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               0,                       0,                      0,             3,                        2,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  0,                               0,                    0,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  6,          0,               0,             2,         3,              0,              2,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  1,     0,         2,              0,              3,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  8,                  26,            3,             0,              0,               2,               0x2ecc,                0x4a0,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0xc0,            7,            20,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0x4ae,             0x95c,            0x4ae,            0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               20,            1,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  0,            24,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0xF,  0x39, 0x9C,   0x8,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0x83,     0x1,      0x2,      0,         0,         0,         0,         0,                           0,                   0,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},

	{
	311,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0,            13,        2,     2,     0,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       3,    0,        0,        0,       0,       0,       5,      0,       0,       0,       0,      0,       13,   1,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  2,          0,      16,   0,   32,    0xF2F8, 0x137,  0xC22,  4,    1,    10,   10,   8,     0,        3,     0,    5,             0x5509,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  14,       8,      24,  7,    7,   0x49E,0x42, 4,    4,    0,   0,             0,            0,          5,   4,    0x46,  0x46, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      0xD,   0x8,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  0,      4,          1,          2,          2,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               0,                       0,                      0,             3,                        2,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  0,                               0,                    0,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  12,         0,               0,             4,         4,              0,              2,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  3,     2,         2,              0,              3,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  9,                  27,            3,             0,              0,               2,               0x5dfc,                0x966,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0xc0,            7,            25,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0x966,             0x12cc,           0x966,            0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               20,            3,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  0,            24,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0x1C, 0x70, 0x137,  0x10,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0x83,     0x4,      0x2,      0,         0,         0,         0,         0,                           0,                   0,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},

	{
	466,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0,            13,        2,     2,     0,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       4,    0,        0,        0,       0,       0,       7,      0,       0,       0,       0,      0,       18,   2,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  3,          0,      24,   0,   47,    0x16C10,0x1D2,  0x1230, 4,    2,    10,   10,   12,    0,        4,     0,    5,             0x7F6B,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  20,       11,     36,  10,   10,  0x705,0x62, 5,    4,    0,   0,             0,            0,          7,   4,    0x68,  0x68, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      0x13,  0xC,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  0,      7,          2,          2,          3,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               0,                       0,                      0,             3,                        2,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  0,                               0,                    0,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  16,         0,               0,             4,         4,              0,              2,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  4,     3,         2,              0,              3,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  11,                 29,            3,             0,              0,               2,               0xbc98,                0xe1a,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0x20,            7,            29,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0xe1a,             0x1c34,           0xe1a,            0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               20,            3,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  1,            24,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0x2A, 0xA8, 0x1D2,  0x18,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0xC3,     0x6,      0x2,      3,         0,         0,         0,         0,                           0,                   0,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},
#endif
#if 1
	{
	233,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0,            3,        2,     2,     0x2f,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       3,    0,        0,        0,       0,       0,       4,      0,       0,       0,       0,      0,       0xb,    1,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  2,          0,      0xc,    0,   0x18,    0xb648, 0xea,   0x91e,  4,    1,    10,   10,   5,     0,        3,     0,    5,             0x1f89,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  10,        5,      0xf,  5,    5,   0x380,0x31, 3,    4,    0,   0,             0,            0,          4,   4,    0x34,  0x34, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      0x28,     0xd,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  1,      5,          2,          1,          7,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               2,                       0,                      0,             6,                        8,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  7,                               3,                    2,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  0xc,          0,               0,             5,         2,              0,              2,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  3,     2,         2,              0,              1,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  8,                  26,            3,             0,              0,               2,               0x4664,                0x70a,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0xc0,            7,            0x17,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0x70a,             0xe14,            0x70a,            0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               20,            1,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  1,            24,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0x7fff,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0x15,  0x54, 0xea,   0xc,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0x83,     0x4,      0x2,      0,         0,         0,         0,         0,                           0,                   0xffff,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},
#endif
#if 0
//156M
	{
	233,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0,            13,        2,     2,     0,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       3,    0,        0,        0,       0,       0,       3,      0,       0,       0,       0,      0,       8,    1,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  1,          0,      8,    0,   16,    0x79E0, 0x9C,   0x614,  4,    1,    10,   10,   3,     0,        3,     0,    5,             0x2AA7,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  7,        4,      12,  4,    4,   0x256,0x21, 2,    4,    0,   0,             0,            0,          4,   4,    0x24,  0x24, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      7,     4,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  0,      2,          0,          2,          2,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               0,                       0,                      0,             3,                        2,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  0,                               0,                    0,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  6,          0,               0,             2,         3,              0,              2,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  1,     0,         2,              0,              3,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  8,                  26,            3,             0,              0,               2,               0x2ecc,                0x4a0,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0xc0,            7,            20,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0x4ae,             0x95c,            0x4ae,            0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               20,            1,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  0,            24,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0xF,  0x39, 0x9C,   0x8,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0x83,     0x1,      0x2,      0,         0,         0,         0,         0,                           0,                   0,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},
#endif
	{
	368,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0,            3,        2,     2,     0x2f,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       3,    0,        0,        0,       0,       0,       6,      0,       0,       0,       0,      0,       0xd,    1,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  3,          0,      0x13,    0,   0x25,    0x11f8b, 0x171,   0xe61,  4,    2,    10,   10,   7,     0,        3,     0,    5,             0x3274,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  0x10,        8,      0x18,  7,    7,   0x593,0x4e, 4,    4,    0,   0,             0,            0,          6,   4,    0x51,  0x51, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      0x28,     0xd,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  1,      4,          1,          2,          7,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               0,                       0,                      0,             6,                        8,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  7,                               3,                    2,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  0xc,          0,               0,             4,         2,              0,              2,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  3,     2,         2,              0,              1,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  10,                  0x1c,            3,             0,              0,               2,               0x6f7c,                0xb26,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0xc0,            7,            0x1a,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0xb26,             0x164c,            0xb26,            0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               20,            1,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  1,            24,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0x22,  0x85, 0x171,   0x13,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0x83,     0x4,      0x2,      0,         0,         0,         0,         0,                          0,                   0xffff,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},


	{
	622,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0x4f,            3,        2,     2,     0x20,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       5,    0,        0,        0,       0,       0,       0xa,      0,       0,       0,       0,      0,       0x16,   2,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  4,          0,      0x20,   0x9c,   0x3f,    0x1e5db,0x26e,  0x184b, 4,    2,    10,   10,   0xc,    0,        5,     0,    5,             0x540c,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  0x1b,       0x0e,     0x28,  0xc,   0xc,  0x957,0x83, 7,    5,    0,   0x3f,             0x7d,            0x9c,          0xa,   5,    0x89,  0x89, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      0x28,  0xd,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  0,      8,          3,          3,          7,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               0,                       0,                      0,             6,                        8,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  0,                               0,                    0,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  0x14,         0,               0,             6,         2,              0,              3,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  6,     5,         3,              0,              1,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  11,                 29,            3,             0,              0,               2,               0xbcd4,                0x12e2,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0xc0,            7,            0x1f,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0x12e2,             0x25c4,           0x12e2,            0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               20,            5,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  0,            24,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0x38, 0xe0, 0x26e,  0x20,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0x3,     0x18,      0x2,      0,         0,         0,         0,         0,                           0,                   0xffff,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},


	{
	933,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW,
	  0,            3,        2,     2,     0x20,          4,                 10,     10,      10,      10,     20,     4,    0,
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN,
	  0,       7,    0,        0,        0,       0,       0,       14,     0,       0,       0,       0,      0,       0x1f,   3,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX,
	  6,          0,      0x2f,   0,   0x5c,    0x2ceb9,0x398,  0x23f0, 4,    3,    10,   10,   0x11,    0,        7,     0,    5,             0x7e24,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL,
	  0x27,       0x14,     0x3a,  0x11,   0x11,  0xdfb,0xC2, 10,   7,    0,   0,             0,            0,          14,  7,    0xCb,  0xCb, 0,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN,
	  0,      0,      0x26,  0x18,

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR,
	  0,      12,         4,          3,          4,        7,

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP,
	  0,               0,               0,                       0,                      0,             6,                        8,
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT,
	  0,                               0,                    0,                    3,               4,                4,

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY,
	  0x1c,         0,               0,             8,         2,              0,              3,              2,              0,
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY,
	  8,     7,         1,              0,              1,              0,

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX,
	  0xf,                 0x21,            3,             0,              0,               2,               0x1179c,               0x1bf6,
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT,
	  0x8,              2,                     3,                    0x400,              0xc0,            7,            0x25,
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1,
	  1,               0,              0x1bf6,            0x37ec,           0x1bf6,           0x200,             0x200,
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT,
	  0x200,             0x200,             0,              3,             0,              0,               0x14,            9,
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
	  2,            0x18,            3,             0,               0,

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD,
	  0,                   0,                          0,                          0,                   0,                          0,
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET,
	  0,                    0,                    0,             0x53, 0x14c,0x398,  0x2e,

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD,
	  0x83,     0x1C,     0x2,      0,         0,         0,         0,         0,                           0,                   0xffff,
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD,
	  0,                     0,

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD,
	  1,              0,                     0,                    0,                     0,                             0,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD,
	  0,                          0,                   4,                                0,
	},

};

//========================================CANDS_PI_TIMING_INFO_LP3========================================//
const CANDS_PI_TIMING_T CANDS_PI_TIMING_INFO_LP3[] =
{
#if 0
	{
	156,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  6,                2,               1,           0,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0xa,            1,                0x1c,                         0,         10,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         1,          0x2AA7,         7,              4,          0x256,      5,                0x21,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  4,         4,          0,                 0,                4,         4,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0x4a0,                  0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0x95c,                  0x4ae,                   4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 1,                0x14,             0,                  0,                 0,                 0,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x1A,                0x8,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  6,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0x4A0,                  0x2ECC,                      4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           1,                0,                0,                0x2,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0x83,           0x1,            0x2,            0x0,             0x4D,            0x4D,            0,
	},


	{
	311,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  12,               4,               3,           2,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0xc,            2,                0x23,                         0,         10,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         1,          0x5509,         14,             7,          0x49E,      5,                0x42,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  8,         4,          0,                 0,                5,         4,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0x966,                  0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0x12cc,                 0x966,                   4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 1,                0x14,             0,                  0,                 0,                 2,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x1b,                0x9,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  6,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0x966,                  0x5dfc,                      4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           2,                0,                1,                0x4,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0x83,           0x4,            0x2,            0x0,             0x4D,            0x4D,            0,
	},

	{
	466,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  16,               4,               4,           3,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0xd,            3,                0x27,                         0,         10,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         2,          0x7F6B,         20,             10,         0x705,      5,                0x62,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  11,        4,          0,                 0,                7,         4,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0xe1a,                  0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0x1c34,                 0xe1a,                   4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 1,                0x14,             0,                  0,                 0,                 2,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x1D,                0xb,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  6,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0xE1A,                  0x8D04,                      4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           2,                0,                2,                0x6,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0xC3,           0x6,            0x2,            0x3,             0x4D,            0x4D,            0,
	},
#endif
#if 1
	{
	233,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  0xc,                5,               3,           2,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0xb,            2,                0x22,                         0,         10,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         1,          0x1f89,         10,              5,          0x380,      5,                0x31,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  5,         4,          0,                 0,                4,         4,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0x70a,                  0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0xe14,                  0x70a,                   4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 3,                0x14,             0,                  0,                 0,                 1,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x1A,                0x8,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  6,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0x70a,                  0x4664,                      4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           1,                0,                2,                0x5,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0x83,           0x4,            0x2,            0x0,             0x4D,            0x4D,            0,
	},
#endif
#if 0
//156M
	{
	233,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  6,                2,               1,           0,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0xa,            1,                0x1c,                         0,         10,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         1,          0x2AA7,         7,              4,          0x256,      5,                0x21,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  4,         4,          0,                 0,                4,         4,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0x4a0,                  0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0x95c,                  0x4ae,                   4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 1,                0x14,             0,                  0,                 0,                 0,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x1A,                0x8,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  6,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0x4A0,                  0x2ECC,                      4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           1,                0,                0,                0x2,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0x83,           0x1,            0x2,            0x0,             0x4D,            0x4D,            0,
	},
#endif
	{
	368,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  0xc,                4,               3,           2,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0xc,            3,                0x24,                         0,         10,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         2,          0x3274,         0x10,              7,          0x593,      5,                0x4e,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  8,         4,          0,                 0,                6,         4,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0xb26,                  0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0x164c,                  0xb26,                   4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 3,                0x14,             0,                  0,                 0,                 1,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x1c,                0xa,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  6,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0xb26,                  0x6f7c,                      4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           1,                0,                1,                0x4,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0x83,           0x4,            0x2,            0x0,             0x4D,            0x4D,            0,
	},

	{
	622,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  0x14,               6,               6,           5,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0xf,            4,                0x2b,                         0x9c,         9,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         2,          0x540c,         0x1b,             0xc,         0x957,      5,                0x83,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  0xe,        5,          0,                 0,                0xa,         5,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0x12e2,                  0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0x25c4,                 0x12e2,                   4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 1,                0x14,             0,                  0,                 0,                 0,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x1e,                0xc,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  7,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0x12e2,                  0xbcd4,                      4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           2,                0,                2,                0x6,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0x3,           0x18,            0x2,            0x0,             0x4D,            0x4D,            0,
	},


	{
	933,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT,
	  0x1c,               8,               8,           7,               10,         20,        10,         10,        10,
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx,
	  4,       32,           2,          0x12,           6,                0x33,                         0,         0xd,
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx,
	  4,       10,         3,          0x7e24,         0x27,             0x11,         0xdfb,      5,                0xC2,
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx,
	  0x14,        7,          0,                 0,                0xe,        7,

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx,
	  0x1bf6,                 0x200,                   0x200,                   0x200,                   0x200,
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP,
	  0x37ec,                 0x1bf6,                  4,                     3,                0x18,             0,
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx,
	  0,                 3,                0x14,             0,                  0,                 0,                 2,
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX,
	  1,                  0x17,             0x21,                0xf,                      0,                  0,
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx,
	  7,                       0,                 1,                0x10,                   5,                         0xc0,
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX,
	  0x1000,                   0x4A,              0x4B,              0x34,              0,                   0,
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START,
	  0x1bf6,                 0x1179C,                     4,                                    4,

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx,
	  0,            0,            7,           7,           4,                0,                4,                0xC,

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm,
	  0x83,           0x1C,           0x2,            0x0,             0x4D,            0x4D,            0,
	},

};

//========================================CANDS_PHY_TIMING_INFO_LP3========================================//
const CANDS_PHY_TIMING_T CANDS_PHY_TIMING_INFO_LP3[] =
{
#if 0
	{
	156,

	//***pll
	//phy_pll_ctrl,
	  #ifdef PHY_PLL_BYPASS
	  0x1500,
	  #else
	  0x00a40460,
	  #endif
	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x41,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x41,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x0,                       0x0,                             0xf,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x1,                 0x0,                    0x0,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0x30,                         0x1,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x1,           0x4,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1D0,                             0x0,                                0xC,                  0x0,                          0x18,
	},

	{
	311,

	//***pll
	//phy_pll_ctrl,
	  0x01440260,

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x41,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x41,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x2,                       0x0,                             0xF,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x2,                 0x0,                    0x1,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0x146,                        0x1,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x0,           0x4,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1D0,                             0x0,                                0xC,                  0x0,                          0x18,
	},

	{
	466,

	//***pll
	//phy_pll_ctrl,  ??need to be checked
	  0x1c40160,

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x41,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x41,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x1,                       0x0,                             0xF,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x4,                 0x0,                    0x3,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0x5b,                         0x2,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x0,           0x4,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1D0,                             0x0,                                0xC,                  0x0,                          0x18,
	},
#endif
#if 1
	{
	233,

	//***pll
	//phy_pll_ctrl,
	  0x00e40260,

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x52,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x51,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x0,                       0x0,                             0xf,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x1,                 0x0,                    0x0,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0xbb,                         0x1,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x0,           0x4,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1D0,                             0x0,                                0xC,                  0x0,                          0x18,
	},
#endif
#if 0
//156M
	{
	233,

	//***pll
	//phy_pll_ctrl,
	  #ifdef PHY_PLL_BYPASS
	  0x1500,
	  #else
	  0x00a40460,
	  #endif
	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x41,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x41,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x0,                       0x0,                             0xf,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x1,                 0x0,                    0x0,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0x30,                         0x1,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x1,           0x4,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1D0,                             0x0,                                0xC,                  0x0,                          0x18,
	},
#endif
	{
	368,

	//***pll
	//phy_pll_ctrl,
	  0x018401E0,

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x52,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x51,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x0,                       0x0,                             0xf,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x2,                 0x0,                    0x1,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0x1ad,                         0x1,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x0,           0x4,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1D0,                             0x0,                                0xC,                  0x0,                          0x18,
	},

	{
	622,

	//***pll
	//phy_pll_ctrl,
	  0x02640160,

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x52,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x51,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x1,                       0x0,                             0xF,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x4,                 0x0,                    0x3,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0x174,                         0x2,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x0,           0x5,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1D0,                             0x0,                                0xC,                  0x0,                          0x18,
	},


	{
	933,

	//***pll
	//phy_pll_ctrl,
	  0x038400e0,

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z,
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X,
	  0x280,                      0x280,                        0x0,

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X,
	  0xC0,               0x52,               0x51,                    0x51,

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X,
	  0xC0,                0x51,                0x50,                     0x51,

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X,
	  0x140,                 0xC,                  0x100,                  0x3,                       0x0,                             0xF,

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X,
	  0x10,                     0x8,                     0x42,

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X,
	  0x6,                 0x0,                    0x5,                      0x0,                      0x80,                            0x80,
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X,
	  0x80,                              0x80,                             0x18a,                        0x3,

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X,
	  0xC,                  0x0,

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X,
	  0x0,           0x5,               0x0,                  0x0,

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X,
	  0x1d0,                             0x0,                                0xC,                  0x0,                          0x18,
	},

};


CANDS_CTL_TIMING_T*__get_cands_ctl_timing_info()
{
	return (CANDS_CTL_TIMING_T*)(&CANDS_CTL_TIMING_INFO_LP3[0]);
}
CANDS_PI_TIMING_T*__get_cands_pi_timing_info()
{
	return (CANDS_PI_TIMING_T*)(&CANDS_PI_TIMING_INFO_LP3[0]);
}
CANDS_PHY_TIMING_T*__get_cands_phy_timing_info()
{
	return (CANDS_PHY_TIMING_T*)(&CANDS_PHY_TIMING_INFO_LP3[0]);
}
#endif
