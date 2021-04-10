#include "ddr_timing.h"

#ifdef DRAM_LPDDR4

//========================================CANDS_CTL_TIMING_INFO_LP4========================================//
const CANDS_CTL_TIMING_T CANDS_CTL_TIMING_INFO_LP4[] =
{
	{
	26,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW, 
	  0xd,          3,         3,     3,     0x6,        4,                 10,     10,      10,      7,      0x14,   8,    32, 
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN, 
	  3,       4,    3,        3,        3,       5,       5,       4,      4,       4,       3,       1,      1,       9,    0,          
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX, 
	  1,          1,      2,    0x7, 0x1450,0xCB20, 5,      0x34,   8,    1,    10,   10,   0,     10,       5,     4,    5,             0x390, 
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL, 
	  3,        3,      6,   4,    3,   0x56, 10,   4,    8,    3,   2,             5,            5,          6,   8,    8,     8,    0x1A,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN, 
	  3,      8,      40,    20,      

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR, 
	  0,      0x4,        0x3,        0,          0x0,      0x1,      

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, 
	  0,               0,               0,                       0,                      0,             3,                        2,             
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT, 
	  7,                               3,                    2,                    3,               4,                4,                  

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY, 
	  12,         0,               0,             0x5,       2,              0,              8,              8,              8,          
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, 
	  4,     2,         0,              0x0,            0xd,            0,              

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX, 
	  0x6,                0x18,          0x3,           0x0,            0x0,             0x2,             0x744,                 0xba,             
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT, 
	  0x8,              0x2,                   0x3,                  0x400,              0x20,            0x7,          0x14,           
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, 
	  0x2,             0,              0xba,              0x174,            0xba,             0x200,             0x200,             
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT, 
	  0x200,             0x200,             0,              0x3,           0x0,            0x0,             0x14,          0x1,          
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX, 
	  0x1,          0x18,          0x3,           0x0,             0x0,            

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD, 
	  0,                   0,                          0,                          0,                   0,                          0,                    
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET, 
	  0,                    0,                    0,             0x40, 0x100,0x200,  3,       

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA,MR22_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD, 
	  0x4,      0x0,      0x31,     0,         0x72,         0,   0,      0,                          0,                   0,                          
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD, 
	  0,                     0,                     

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD, 
	  1,              0,                     0,                    0,                     0,                             0xffff, 
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD, 
	  0xffff,                     5,                   4,                                0,                                
	},


	{
	200,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW, 
	  0xd,          3,         3,     3,     0x6,        4,                 10,     10,      10,      50,     0x14,   8,    32, 
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN, 
	  3,       4,    3,        3,        3,       5,       5,       4,      4,       4,       3,       1,      1,       11,   0,
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX, 
	  1,          1,      8,    0x32,0x9C40,0x61A80,5,      0x190,  8,    1,    10,   10,   0,     10,       5,     4,    5,             0x1B6C,
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL, 
	  9,        5,      15,  4,    5,   0x2FD,0x3A, 4,    8,    3,   0x14,          0x28,         0x31,       6,   8,    0x3A,  0x3A, 0xC8,
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN, 
	  3,      8,      40,    20,      

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR, 
	  0,      0x4,        0x3,        0,          0x0,      0x1,      

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, 
	  0,               0,               0,                       0,                      0,             3,                        2,             
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT, 
	  7,                               3,                    2,                    3,               4,                4,                  

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY, 
	  12,         0,               0,             0x5,       2,              0,              8,              8,              8, 
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, 
	  6,     4,         0,              0x0,            0xd,            0,              

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX, 
	  0x8,                0x1a,          0x3,           0x0,            0x0,             0x2,             0x3c50,                0x608, 
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT, 
	  0x8,              0x2,                   0x3,                  0x400,              0x20,            0x7,          0x16,  
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, 
	  0x2,             0,              0x608,             0xc10,            0x608,            0x200,             0x200, 
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT, 
	  0x200,             0x200,             0,              0x3,           0x0,            0x0,             0x14,          0x1,          
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX, 
	  0x1,          0x18,          0x3,           0x0,             0x0,            

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD, 
	  0,                   0,                          0,                          0,                   0,                          0,                    
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET, 
	  0,                    0,                    0,             0x40, 0x100,0x200,  10,      

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA,MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD, 
	  0x4,      0x8,      0x31,     0,         0x72,         0,   0,      0,                          0,                   0,                          
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD, 
	  0,                     0,                     

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD, 
	  1,              0,                     0,                    0,                     0,                             0xffff,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD, 
	  0xffff,                     5,                   4,                                0,                                
	},

	{
	400,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW, 
	  0xd,          3,         3,     3,     0x6,        4,                 10,     10,      10,      100,    0x14,   8,    32,     
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN, 
	  3,       4,    3,        3,        3,       5,       5,       4,      4,       4,       3,       1,      1,       18,   0,          
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX, 
	  2,          1,      16,   0x64,0x13880,0xC3500,5,      0x320,  8,    1,    10,   10,   0,     10,       5,     4,    5,             0x36D8,   
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL, 
	  18,       10,     29,  8,    10,  0x5FA,0x72, 5,    8,    6,   0x28,          0x50,         0x63,       8,   8,    0x73,  0x73, 0x190,  
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN, 
	  3,      12,     40,    20,      

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR, 
	  0,      0x7,        0x4,        0,          0x0,      0x1,      

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, 
	  0,               0,               0,                       0,                      0,             3,                        2,             
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT, 
	  7,                               3,                    2,                    3,               4,                4,                  

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY, 
	  20,         0,               0,             0x7,       2,              0,              0xa,            0xa,            8,          
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, 
	  6,     4,         0,              0x0,            0xe,            0,              

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX, 
	  0xa,                0x1c,          0x3,           0x0,            0x0,             0x2,             0x7940,                0xc20,            
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT, 
	  0x8,              0x2,                   0x3,                  0x400,              0x20,            0x7,          0x1a,           
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, 
	  0x2,             0,              0xc20,             0x1840,           0xc20,            0x200,             0x200,             
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT, 
	  0x200,             0x200,             0,              0x3,           0x0,            0x0,             0x14,          0x5,          
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX, 
	  0x3,          0x18,          0x3,           0x0,             0x0,            

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD, 
	  0,                   0,                          0,                          0,                   0,                          0,                    
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET, 
	  0,                    0,                    0,             0x40, 0x100,0x200,  20,      

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA,MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD, 
	  0x14,     0x9,      0x31,     0,         0x72,         0,      0,   0,                          0,                   0,                          
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD, 
	  0,                     0,                     

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD, 
	  1,              0,                     0,                    0,                     0,                             0xffff, 
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD, 
	  0xffff,                     5,                   4,                                0,                                
	},


	{
	600,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW, 
	  0xd,          3,         5,     3,     0x6,        4,                 10,     10,      10,      150,    0x14,   8,    32, 
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN, 
	  5,       5,    5,        5,        4,       5,       5,       5,      4,       4,       3,       2,      2,       25,   0,          
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX, 
	  3,          2,      24,   0x96,0x1D4C0,0x124F80,5,      0x4B0,  8,    1,    10,   10,   0,     10,       5,     4,    5,             0x5244, 
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL, 
	  27,       14,     43,  12,   14,  0x8F7,0xAA, 8,    8,    9,   0x3C,          0x78,         0x95,       11,  8,    0xAD,  0xAD, 0x258,  
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN, 
	  3,      18,     40,    20,      

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR, 
	  0,      0xa,        0x5,        0,          0x0,      0x1,      

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, 
	  0,               0,               0,                       0,                      0,             3,                        2,             
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT, 
	  7,                               3,                    2,                    3,               4,                4,                  

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY, 
	  28,         0,               0,             0x9,       2,              0,              0xc,            0xc,            8,          
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, 
	  8,     6,         1,              0x0,            0xf,            0,              

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX, 
	  0xc,                0x1e,          0x3,           0x0,            0x0,             0x2,             0xb5cc,                0x122e,           
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT, 
	  0x8,              0x2,                   0x3,                  0x400,              0x20,            0x7,          0x1e,           
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, 
	  0x2,             0,              0x122e,            0x245c,           0x122e,           0x200,             0x200,             
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT, 
	  0x200,             0x200,             0,              0x3,           0x0,            0x0,             0x14,          0x9,          
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX, 
	  0x0,          0x18,          0x3,           0x0,             0x0,            

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD, 
	  0,                   0,                          0,                          0,                   0,                          0,                    
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET, 
	  0,                    0,                    0,             0x40, 0x100,0x200,  30,      

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA,MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD, 
	  0x24,     0x12,     0x31,     0,         0x72,         0,     0,    0,                          0,                   0,                          
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD, 
	  0,                     0,                     

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD, 
	  1,              0,                     0,                    0,                     0,                             0xffff,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD, 
	  0xffff,                     5,                   4,                                0,                                
	},

#if 0
	{
	768,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW, 
	  0xd,          3,         7,     3,     0x6,        4,                 10,     10,      10,      192,    0x14,   8,    32,     
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN, 
	  6,       6,    6,        6,        5,       5,       5,       6,      5,       5,       3,       2,      2,       32,   1,          
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX, 
	  3,          2,      31,   0xC0,0x25800,0x177000,5,      0x600,  8,    2,    10,   10,   0,     11,       6,     4,    5,             0x694C,   
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL, 
	  34,       18,     55,  16,   18,  0xB79,0xDA, 10,   8,    12,  0x4C,          0x99,         0xBF,       14,  8,    0xDD,  0xDD, 0x300,  
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN, 
	  3,      24,     40,    20,      

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR, 
	  0,      0xa,        0x5,        0,          0x0,      0x1,      

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, 
	  0,               0,               0,                       0,                      0,             3,                        2,             
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT, 
	  7,                               3,                    2,                    3,               4,                4,                  

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY, 
	  28,         0,               0,             0x9,       2,              0,              0xb,            0xb,            8,          
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, 
	  8,     6,         2,              0x0,            0xf,            0,              

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX, 
	  0xe,                0x20,          0x3,           0x0,            0x0,             0x2,             0xe7f4,                0x1732,           
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT, 
	  0x8,              0x2,                   0x3,                  0x400,              0x20,            0x7,          0x20,           
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, 
	  0x2,             0,              0x1732,            0x2e64,           0x1732,           0x200,             0x200,             
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT, 
	  0x200,             0x200,             0,              0x3,           0x0,            0x0,             0x14,          0x11,         
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX, 
	  0x0,          0x18,          0x3,           0x0,             0x0,            

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD, 
	  0,                   0,                          0,                          0,                   0,                          0,                    
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET, 
	  0,                    0,                    0,             0x40, 0x100,0x200,  39,      

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD, 
	  0x24,     0x12,     0x31,     0,         0,         0,         0,                          0,                   0,                          
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD, 
	  0,                     0,                     

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD, 
	  1,              0,                     0,                    0,                     0,                             0xffff,
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD, 
	  0xffff,                     5,                   4,                                0,                                
	},
#endif

	{
	1200,

	//***ctl ac timing
	//CKE_INACTIVE, CKE_DELAY, CKSRE, CKSRX, TRST_PWRON, TBST_INT_INTERVAL, TCAEXT, TCACKEL, TCACKEH, TCAENT, TCAMRD, TCCD, TCCDMW, 
	  0xd,          3,         9,     3,     0x6,        4,                 10,     10,      10,      300,    0x14,   8,    32,     
	//TCKCKEL, TCKE, TCKEHCMD, TCKELCMD, TCKELPD, TCKELCS, TCKEHCS, TCKESR, TCKFSPX, TCKFSPE, TCMDCKE, TCSCKE, TCSCKEH, TDAL, TDQSCK_MIN, 
	  9,       9,    9,        9,        9,       6,       9,       9,      9,       9,       3,       3,      3,       50,   1,          
	//TDQSCK_MAX, TESCKE, TFAW, TFC, TINIT, TINIT3, TINIT4, TINIT5, TMRR, TMRZ, TMOD, TMRD, TMRRI, TMRWCKEL, TPDEX, TPPD, TREF_INTERVAL, TRAS_MAX, 
	  5,          3,      48,   0x12C,0x3A980,0x249F00,5,      0x960,  8,    2,    12,   12,   0,     17,       9,     4,    5,             0xA488,   
	//TRAS_MIN, TRP_AB, TRC, TRCD, TRP, TREF, TRFC, TRRD, TRTP, TSR, TVRCG_DISABLE, TVRCG_ENABLE, TVREF_LONG, TWR, TWTR, TXSNR, TXSR, TZQCAL, 
	  53,       28,     85,  24,   28,  0x11EE,0x152,15,   9,    18,  0x78,          0xF0,         0x12B,      22,  12,   0x159, 0x159,0x4B0,  
	//TZQCKE, TZQLAT, WLMRD, WLDQSEN, 
	  3,      36,     40,    20,      

	//***ctl odt
	//ODT_EN, RD_TO_ODTH, WR_TO_ODTH, TODTL_2CMD, TODTH_RD, TODTH_WR, 
	  1,      0x12,       0x7,        0,          0x0,      0x1,      

	//***ctl low power
	//LP_AUTO_PD_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SRPD_LITE_IDLE, LPI_PD_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, 
	  0,               0,               0,                       0,                      0,             3,                        2,             
	//LPI_SRPD_DEEP_MCCLK_GATE_WAKEUP, LPI_SRPD_DEEP_WAKEUP, LPI_SRPD_LITE_WAKEUP, LPI_TIMER_COUNT, LPI_TIMER_WAKEUP, LPI_WAKEUP_TIMEOUT, 
	  7,                               3,                    2,                    3,               4,                4,                  

	//***ctl delay&latency
	//CASLAT_LIN, DLL_RST_ADJ_DLY, DLL_RST_DELAY, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY, RW2MRW_DLY, 
	  48,         0,               0,             0xe,       2,              0,              0xb,            0xb,            9,          
	//WRLAT, WRLAT_ADJ, W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, 
	  12,    0xa,       7,              0x0,            0x5,            0,              

	//***ctl dfi
	//TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_MAX, TDFI_CALVL_RESP, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL, TDFI_CTRLUPD_MAX, 
	  0x12,               0x24,          0x3,           0x0,            0x0,             0x2,             0x16a08,               0x2434,           
	//TDFI_CTRLUPD_MIN, TDFI_DRAM_CLK_DISABLE, TDFI_DRAM_CLK_ENABLE, TDFI_INIT_COMPLETE, TDFI_INIT_START, TDFI_LP_RESP, TDFI_PHY_RDLAT, 
	  0x8,              0x2,                   0x3,                  0x400,              0x20,            0x7,          0x28,           
	//TDFI_PHY_WRDATA, TDFI_PHY_WRLAT, TDFI_PHYMSTR_RESP, TDFI_PHYMSTR_MAX, TDFI_PHYUPD_RESP, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, 
	  0x2,             0,              0x2434,            0x4868,           0x2434,           0x200,             0x200,             
	//TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_RDDATA_EN, TDFI_RDLVL_EN, TDFI_RDLVL_MAX, TDFI_RDLVL_RESP, TDFI_RDLVL_RR, TDFI_RDCSLAT, 
	  0x200,             0x200,             0,              0x3,           0x0,            0x0,             0x14,          0x13,         
	//TDFI_WRCSLAT, TDFI_WRLVL_WW, TDFI_WRLVL_EN, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX, 
	  0x4,          0x18,          0x3,           0x0,             0x0,            

	//***ctl zq
	//ZQ_CALLATCH_TIMEOUT, ZQ_CALLATCH_HIGH_THRESHOLD, ZQ_CALSTART_HIGH_THRESHOLD, ZQ_CALSTART_TIMEOUT, ZQ_CALSTART_NORM_THRESHOLD, ZQ_CS_HIGH_THRESHOLD, 
	  0,                   0,                          0,                          0,                   0,                          0,                    
	//ZQ_CS_NORM_THRESHOLD, ZQ_PROMOTE_THRESHOLD, ZQ_CS_TIMEOUT, ZQCS, ZQCL, ZQINIT, ZQRESET, 
	  0,                    0,                    0,             0x40, 0x100,0x200,  60,      

	//***ctl mode register
	//MR1_DATA, MR2_DATA, MR3_DATA, MR11_DATA, MR12_DATA, MR14_DATA, MR22_DATA,MRR_TEMPCHK_HIGH_THRESHOLD, MRR_TEMPCHK_TIMEOUT, MRR_TEMPCHK_NORM_THRESHOLD, 
	  0x44,     0x24,     0x31,     0x6,       0x72,         0,      0x6,   0,                          0,                   0,                          
	//MRR_PROMOTE_THRESHOLD, MRW_PROMOTE_THRESHOLD, 
	  0,                     0,                     

	//***ctl others
	//CA_DEFAULT_VAL, DFS_PROMOTE_THRESHOLD, HW_PROMOTE_THRESHOLD, LPC_PROMOTE_THRESHOLD, PHYMSTR_DFI_PROMOTE_THRESHOLD, UPD_CTRLUPD_NORM_THRESHOLD, 
	 1,               0,                     0,                    0,                     0,                             0xffff, 
	//UPD_CTRLUPD_HIGH_THRESHOLD, UPD_CTRLUPD_TIMEOUT, UPD_CTRLUPD_SW_PROMOTE_THRESHOLD, UPD_PHYUPD_DFI_PROMOTE_THRESHOLD, 
	  0xffff,                     5,                   4,                                0,                                
	},

};

//========================================CANDS_PI_TIMING_INFO_LP4========================================//
const CANDS_PI_TIMING_T CANDS_PI_TIMING_INFO_LP4[] =
{
	{
	26,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT, 
	  12,               0x5,             4,           2,               10,         0x14,      10,         7,         10,        
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx, 
	  8,       32,           3,          1,              1,                0x25,                         0x7,       10,         
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx, 
	  8,       10,         1,          0x390,          3,              4,          0x56,       5,                10,         
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx, 
	  3,         8,          1,                 5,                6,         8,          

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx, 
	  0xba,                   0x200,                   0x200,                   0x200,                   0x200,                   
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP, 
	  0x174,                  0xba,                    0x4,                   0x3,              0x18,             0x0,                
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx, 
	  0x0,               0x3,              0x1e,             0x0,                0x0,               0x0,               0x1,                
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX, 
	  0x2,                0x17,             0x18,                0x6,                      0x0,                0x0,               
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx, 
	  0x6,                     0x0,               0x1,              0x10,                   0x5,                       0x20,                  
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX, 
	  0x1000,                   0x4A,              0x4B,              0x34,              0x0,                 0x0,                
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START, 
	  0xBA,                   0x744,                       0x4,                                  0x4,                        

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx, 
	  1,            0,            1,           0,           0,                0,                3,                0x4,              

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm, 
	  0x4,            0x0,            0x31,           0x0,             0x72,            0x4D,            0x0,              
	},


	{
	200,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT, 
	  12,               0x5,             4,           2,               10,         0x14,      10,         50,        10,        
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx, 
	  8,       32,           3,          2,              1,                0x27,                         0x32,      10,         
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx, 
	  8,       10,         1,          0x1B6C,         9,              4,          0x2FD,      5,                0x3A,       
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx, 
	  5,         8,          0xF,               0x31,             6,         8,          

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx, 
	  0x608,                  0x200,                   0x200,                   0x200,                   0x200,                   
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP, 
	  0xc10,                  0x608,                   0x4,                   0x3,              0x18,             0x0,                
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx, 
	  0x0,               0x3,              0x1e,             0x0,                0x0,               0x0,               0x1,                
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX, 
	  0x2,                0x17,             0x1A,                0x8,                      0x0,                0x0,               
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx, 
	  0x6,                     0x0,               0x1,              0x10,                   0x5,                       0x20,                  
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX, 
	  0x1000,                   0x4A,              0x4B,              0x34,              0x0,                 0x0,                
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START, 
	  0x608,                  0x3c50,                      0x4,                                  0x4,                        

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx, 
	  1,            0,            1,           0,           0,                0,                3,                0x4,              

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm, 
	  0x4,            0x8,            0x31,           0x0,             0x72,            0x4D,            0x0,              
	},


	{
	400,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT, 
	  20,               0x7,             6,           4,               10,         0x14,      10,         100,       10,        
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx, 
	  8,       32,           3,          4,              2,                0x2d,                         0x64,      10,         
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx, 
	  8,       10,         1,          0x36D8,         18,             8,          0x5FA,      5,                0x72,       
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx, 
	  10,        8,          0x1F,              0x63,             8,         8,          

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx, 
	  0xC20,                  0x200,                   0x200,                   0x200,                   0x200,                   
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP, 
	  0x1840,                 0xc20,                   0x4,                   0x3,              0x18,             0x0,                
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx, 
	  0x0,               0x3,              0x1e,             0x0,                0x0,               0x0,               0x3,                
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX, 
	  0x2,                0x17,             0x1c,                0xa,                      0x0,                0x0,               
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx, 
	  0x6,                     0x0,               0x1,              0x10,                   0x5,                       0x20,                  
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX, 
	  0x1000,                   0x4A,              0x4B,              0x34,              0x0,                 0x0,                
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START, 
	  0xc20,                  0x7940,                      0x4,                                  0x4,                        

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx, 
	  1,            0,            1,           0,           0,                0,                4,                0x7,              

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm, 
	  0x14,           0x9,            0x31,           0x0,             0x72,            0x4D,            0x0,              
	},


	{
	600,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT, 
	  28,               0x9,             8,           6,               10,         0x14,      10,         150,       10,        
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx, 
	  8,       32,           3,          6,              3,                0x33,                         0x96,      10,         
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx, 
	  8,       10,         1,          0x5244,         27,             11,         0x8F7,      5,                0xAA,       
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx, 
	  14,        8,          0x2F,              0x95,             11,        8,          

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx, 
	  0x122e,                 0x200,                   0x200,                   0x200,                   0x200,                   
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP, 
	  0x245c,                 0x122e,                  0x4,                   0x3,              0x18,             0x0,                
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx, 
	  0x0,               0x3,              0x1e,             0x0,                0x0,               0x0,               0x2,                
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX, 
	  0x2,                0x17,             0x1e,                0xc,                      0x0,                0x0,               
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx, 
	  0x7,                     0x0,               0x1,              0x10,                   0x5,                       0x20,                  
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX, 
	  0x1000,                   0x4A,              0x4B,              0x34,              0x0,                 0x0,                
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START, 
	  0x122e,                 0xB5cc,                      0x4,                                  0x4,                        

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx, 
	  1,            0,            1,           0,           0,                0,                5,                0xA,              

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm, 
	  0x24,           0x12,           0x31,           0x0,             0x72,            0x4D,            0x0,              
	},

#if 0
	{
	768,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT, 
	  28,               0x9,             8,           6,               10,         0x14,      10,         192,       10,        
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx, 
	  8,       32,           3,          8,              3,                0x34,                         0xC0,      11,         
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx, 
	  8,       10,         2,          0x694C,         34,             14,         0xB79,      5,                0xDA,       
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx, 
	  18,        8,          0x3C,              0xBF,             14,        8,          

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx, 
	  0x1732,                 0x200,                   0x200,                   0x200,                   0x200,                   
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP, 
	  0x2e64,                 0x1732,                  0x4,                   0x3,              0x18,             0x0,                
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx, 
	  0x0,               0x3,              0x1e,             0x0,                0x0,               0x0,               0x2,                
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX, 
	  0x2,                0x17,             0x20,                0xe,                      0x0,                0x0,               
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx, 
	  0x7,                     0x0,               0x1,              0x10,                   0x5,                       0x20,                  
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX, 
	  0x1000,                   0x4A,              0x4B,              0x34,              0x0,                 0x0,                
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START, 
	  0x1732,                 0xE7F4,                      0x4,                                  0x4,                        

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx, 
	  1,            0,            1,           0,           0,                0,                5,                0xA,              

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm, 
	  0x24,           0x12,           0x31,           0x0,             0x4D,            0x4D,            0x0,              
	},
#endif

	{
	1200,

	//***pi ac timing
	//PI_CASLAT_LIN_Fx, PI_RDLAT_ADJ_Fx, PI_WRLAT_Fx, PI_WRLAT_ADJ_Fx, PI_TCACKEL, PI_TCAMRD, PI_TCACKEH, PI_TCAENT, PI_TCAEXT, 
	  48,               0xe,             12,          10,              10,         0x14,      10,         300,       10,        
	//PI_TCCD, PI_TCCDMW_Fx, PI_TCKCKEH, PI_TCKEHDQS_Fx, PI_TDQSCK_MAX_Fx, PI_TDELAY_RDWR_2_BUS_IDLE_Fx, PI_TFC_Fx, PI_TMRD_Fx, 
	  8,       32,           3,          12,             5,                0x42,                         0x12C,     12,         
	//PI_TMRR, PI_TMRW_Fx, PI_TMRZ_Fx, PI_TRAS_MAX_Fx, PI_TRAS_MIN_Fx, PI_TRCD_Fx, PI_TREF_Fx, PI_TREF_INTERVAL, PI_TRFC_Fx, 
	  8,       12,         2,          0xA488,         53,             22,         0x11EE,     5,                0x152,      
	//PI_TRP_Fx, PI_TRTP_Fx, PI_TVREF_SHORT_Fx, PI_TVREF_LONG_Fx, PI_TWR_Fx, PI_TWTR_Fx, 
	  28,        9,          0x5F,              0x12B,            22,        12,         

	//***pi dfi timing
	//PI_TDFI_PHYUPD_RESP_Fx, PI_TDFI_PHYUPD_TYPE0_Fx, PI_TDFI_PHYUPD_TYPE1_Fx, PI_TDFI_PHYUPD_TYPE2_Fx, PI_TDFI_PHYUPD_TYPE3_Fx, 
	  0x2434,                 0x200,                   0x200,                   0x200,                   0x200,                   
	//PI_TDFI_PHYMSTR_MAX_Fx, PI_TDFI_PHYMSTR_RESP_Fx, PI_TDFI_CTRL_DELAY_Fx, PI_TDFI_WRLVL_EN, PI_TDFI_WRLVL_WW, PI_TDFI_WRLVL_RESP, 
	  0x4868,                 0x2434,                  0x4,                   0x3,              0x18,             0x0,                
	//PI_TDFI_WRLVL_MAX, PI_TDFI_RDLVL_EN, PI_TDFI_RDLVL_RR, PI_TDFI_RDLVL_RESP, PI_TDFI_RDLVL_MAX, PI_TDFI_RDDATA_EN, PI_TDFI_WRCSLAT_Fx, 
	  0x0,               0x3,              0x1e,             0x0,                0x0,               0x0,               0x4,                
	//PI_TDFI_PHY_WRDATA, PI_TDFI_CALVL_EN, PI_TDFI_CALVL_CC_Fx, PI_TDFI_CALVL_CAPTURE_Fx, PI_TDFI_CALVL_RESP, PI_TDFI_CALVL_MAX, 
	  0x2,                0x17,             0x24,                0x12,                     0x0,                0x0,               
	//PI_TDFI_CALVL_STROBE_Fx, PI_TDFI_CACSCA_Fx, PI_TDFI_CASEL_Fx, PI_TDFI_INIT_START_MIN, PI_TDFI_INIT_COMPLETE_MIN, PI_TDFI_INIT_START_Fx, 
	  0x8,                     0x0,               0x1,              0x10,                   0x5,                       0x20,                  
	//PI_TDFI_INIT_COMPLETE_Fx, PI_TDFI_WDQLVL_WR, PI_TDFI_WDQLVL_RW, PI_TDFI_WDQLVL_EN, PI_TDFI_WDQLVL_RESP, PI_TDFI_WDQLVL_MAX, 
	  0x1000,                   0x4A,              0x4B,              0x34,              0x0,                 0x0,                
	//PI_TDFI_CTRLUPD_MAX_Fx, PI_TDFI_CTRLUPD_INTERVAL_Fx, PI_INIT_STARTORCOMPLETE_2_CLKDISABLE, PI_CLKDISABLE_2_INIT_START, 
	  0x2434,                 0x16A08,                     0x4,                                  0x4,                        

	//***pi odt timing
	//PI_ODT_EN_Fx, PI_ODTLON_Fx, PI_TODTH_WR, PI_TODTH_RD, PI_TODTL_2CMD_Fx, PI_TODTON_MIN_Fx, PI_WR_TO_ODTH_Fx, PI_RD_TO_ODTH_Fx, 
	  1,            0,            1,           0,           0,                0,                7,                0x12,             

	//***pi mode register
	//PI_MR1_DATA_Fx, PI_MR2_DATA_Fx, PI_MR3_DATA_Fx, PI_MR11_DATA_Fx, PI_MR12_DATA_Fx, PI_MR14_DATA_Fx, PI_MR13_DATA_CSm, 
	  0x44,           0x24,           0x31,           0x6,             0x72,            0x4D,            0x0,              
	},

};

//========================================CANDS_PHY_TIMING_INFO_LP4========================================//
const CANDS_PHY_TIMING_T CANDS_PHY_TIMING_INFO_LP4[] =
{
	{
	26,

	//***pll
	//phy_pll_ctrl, 
	  #ifdef PHY_PLL_BYPASS
	  0x1b00,
	  #else
	  0x1b02,
	  #endif

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z, 
	  0x10,                       0x8,                       0x42,                      0xc,                    0x300,                 

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X, 
	  0x280,                      0x280,                        0x0,                         

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X, 
	  0xC0,               0x61,               0x51,                    0x61,                    

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X, 
	  0xC0,                0x61,                0x50,                     0x61,                     

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
	  0x80,                              0x80,                             0x13a,                        0x0,                        

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X, 
	  0xC,                  0x0,                                

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X, 
	  0x0,           0x4,               0xC,                  0x0, 

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X, 
	  0x180,                             0x0,                                0xC,                  0x1,                          0x18,                      
	},


	{
	200,

	//***pll
	//phy_pll_ctrl,
	  #ifdef PHY_PLL_BYPASS
	  0x1500,
	  #else
	  0x1502,
	  #endif

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z, 
	  0x10,                       0x8,                       0x42,                      0xc,                    0x300,

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X, 
	  0x280,                      0x280,                        0x0,                         

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X, 
	  0xC0,               0x61,               0x51,                    0x61,                    

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X, 
	  0xC0,                0x61,                0x50,                     0x61,                     

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
	  0x80,                              0x80,                             0x19,                         0x1,                        

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X, 
	  0xC,                  0x0,                                

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X, 
	  0x0,           0x4,               0xC,                  0x0, 

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X, 
	  0x180,                             0x0,                                0xC,                  0x1,                          0x18,                      
	},


	{
	400,

	//***pll
	//phy_pll_ctrl, 
	  #ifdef PHY_PLL_BYPASS
	  0x1300,
	  #else
	  0x1302,
	  #endif       

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z, 
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,                 

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X, 
	  0x280,                      0x280,                        0x0,                         

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X, 
	  0xC0,               0x61,               0x51,                    0x61,                    

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X, 
	  0xC0,                0x61,                0x50,                     0x61,                     

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X, 
	  0x140,                 0xC,                  0x100,                  0x0,                       0x0,                             0xf,                       

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X, 
	  0x10,                     0x8,                     0x42,                    

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X, 
	  0x3,                 0x0,                    0x2,                      0x0,                      0x80,                            0x80,                            
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X, 
	  0x80,                              0x80,                             0x119,                        0x1,                        

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X, 
	  0xC,                  0x0,                                

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X, 
	  0x0,           0x4,               0x0,                  0x0, 

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X, 
	  0x180,                             0x0,                                0xC,                  0x1,                          0x18,                      
	},


	{
	600,

	//***pll
	//phy_pll_ctrl, 
	  0x1302,       

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z, 
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,                 

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X, 
	  0x280,                      0x280,                        0x0,                         

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X, 
	  0xC0,               0x61,               0x51,                    0x61,                    

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X, 
	  0xC0,                0x61,                0x50,                     0x61,                     

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X, 
	  0x140,                 0xC,                  0x100,                  0x0,                       0x0,                             0xF,                       

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X, 
	  0x10,                     0x8,                     0x42,                    

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X, 
	  0x5,                 0x0,                    0x4,                      0x0,                      0x80,                            0x80,                            
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X, 
	  0x80,                              0x80,                             0x13,                         0x2,                        

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X, 
	  0xC,                  0x0,                                

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X, 
	  0x0,           0x5,               0x0,                  0x0, 

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X, 
	  0x180,                             0x0,                                0xC,                  0x1,                          0x18,                      
	},

#if 0
	{
	768,

	//***pll
	//phy_pll_ctrl, 
	  0x1102,       

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z, 
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,                 

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X, 
	  0x280,                      0x280,                        0x0,                         

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X, 
	  0xC0,               0x61,               0x51,                    0x61,                    

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X, 
	  0xC0,                0x61,                0x50,                     0x61,                     

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X, 
	  0x140,                 0xC,                  0x100,                  0x0,                       0x0,                             0xF,                       

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X, 
	  0x10,                     0x8,                     0x42,                    

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X, 
	  0x6,                 0x0,                    0x5,                      0x0,                      0x80,                            0x80,                            
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X, 
	  0x80,                              0x80,                             0xea,                         0x2,                        

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X, 
	  0xC,                  0x0,                                

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X, 
	  0x0,           0x5,               0x0,                  0x0,                      

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X, 
	  0x180,                             0x0,                                0xC,                  0x1,                          0x18,                      
	},
#endif

	{
	1200,

	//***pll
	//phy_pll_ctrl, 
	  0x1102,       

	//***Address/Control Slice
	//phy_adr_master_delay_start, phy_adr_master_delay_step, phy_adr_master_delay_wait, phy_adr_sw_master_mode, phy_grp_slave_delay_Z, 
	  0x10,                       0x8,                       0x42,                      0x0,                    0x300,                 

	//***Data Slice Parameters for clk_wr settings
	//phy_clk_wrdm_slave_delay_X, phy_clk_wrdqZ_slave_delay_X , phy_clk_wrdqs_slave_delay_X, 
	  0x280,                      0x280,                        0x0,                         

	//***Data Slice Parameters for DQ
	//phy_dq_ie_timing_X, phy_dq_oe_timing_X, phy_dq_tsel_rd_timing_X, phy_dq_tsel_wr_timing_X, 
	  0xC0,               0x61,               0x51,                    0x61,                    

	//***Data Slice Parameters for DQS
	//phy_dqs_ie_timing_X, phy_dqs_oe_timing_X, phy_dqs_tsel_rd_timing_X, phy_dqs_tsel_wr_timing_X, 
	  0xC0,                0x61,                0x50,                     0x61,                     

	//***Data Slice Parameters for Gate Leveling
	//phy_gtlvl_back_step_X, phy_gtlvl_dly_step_X, phy_gtlvl_final_step_X, phy_gtlvl_lat_adj_start_X, phy_gtlvl_rddqs_slv_dly_start_X, phy_gtlvl_resp_wait_cnt_X, 
	  0x140,                 0xC,                  0x100,                  0x1,                       0x0,                             0xF,                       

	//***Data Slice Parameters for Master Delay
	//phy_master_delay_start_X, phy_master_delay_step_X, phy_master_delay_wait_X, 
	  0x10,                     0x8,                     0x42,                    

	//***Data Slice Parameters for Read DQ/DQS
	//phy_rddata_en_dly_X, phy_rddata_en_ie_dly_X, phy_rddata_en_tsel_dly_X, phy_rddqZ_slave_delay_X , phy_rddqs_dm_fall_slave_delay_X, phy_rddqs_dm_rise_slave_delay_X, 
	  0xa,                 0x0,                    0x9,                      0x0,                      0x80,                            0x80,                            
	//phy_rddqs_dqZ_fall_slave_delay_X , phy_rddqs_dqZ_rise_slave_delay_X, phy_rddqs_gate_slave_delay_X, phy_rddqs_latency_adjust_X, 
	  0x80,                              0x80,                             0x10d,                        0x3,                        

	//***Data Slice Parameters for Read Leveling
	//phy_rdlvl_dly_step_X, phy_rdlvl_rddqs_dq_slv_dly_start_X, 
	  0xC,                  0x0,                                

	//***Data Slice Parameters
	//phy_ie_mode_X, phy_rptr_update_X, phy_sw_master_mode_X, phy_write_path_lat_add_X, 
	  0x0,           0x6,               0x0,                  0x0, 

	//***Data Slice Parameters for Write Leveling
	//phy_wrlvl_delay_early_threshold_X, phy_wrlvl_delay_period_threshold_X, phy_wrlvl_dly_step_X, phy_wrlvl_early_force_zero_X, phy_wrlvl_resp_wait_cnt_X, 
	  0x180,                             0x0,                                0xC,                  0x1,                          0x18,                      
	},

};


CANDS_CTL_TIMING_T*__get_cands_ctl_timing_info()
{
	return (CANDS_CTL_TIMING_T*)(&CANDS_CTL_TIMING_INFO_LP4[0]);
}
CANDS_PI_TIMING_T*__get_cands_pi_timing_info()
{
	return (CANDS_PI_TIMING_T*)(&CANDS_PI_TIMING_INFO_LP4[0]);
}
CANDS_PHY_TIMING_T*__get_cands_phy_timing_info()
{
	return (CANDS_PHY_TIMING_T*)(&CANDS_PHY_TIMING_INFO_LP4[0]);
}
#endif
