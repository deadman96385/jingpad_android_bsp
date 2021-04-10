#include "ddr_timing.h"


#ifndef CANDS_DEF_SETTING


//==============================whale LP3-1600 DDR Controller timing setting==============================//
const CANDS_CTL_TIMING_T CANDS_CTL_TIMING_INFO[] =
{
{
	CLK_166MHZ_FN, 166,
//***ac timing
// ADDITIVE_LAT, CASLAT_LIN, CKE_DELAY, CKE_INACTIVE, CKSRE, CKSRX, DLL_RST_ADJ_DLY, DLL_RST_DELAY, TCAENT, TCAEXT,
   0,            3,          0,         0,            2,     2,     0,               0,             10,     10,

// TCACKEL, TCACKEH, TCAMRD, TCCD, TCKE, TCKESR, TDLL, TDAL, TDQSCK_MAX, TDQSCK_MIN, TFAW, TINIT, TINIT3, TINIT4, TINIT5, TMOD,
   10,      10,      20,     4,    3,    4,      0,    12,   1,          1,          10,   18,    0x81B2, 0xA8,   0x5D6,  11,

// TMRD, TMRR, TMRZ, TMRRI, TPDEX, TRAS_MAX, TRAS_MIN, TRC, TRCD, TREF, TREF_INTERVAL, TRFC, TRP, TRP_AB_CSx, TRRD, TRST_PWRON,
   11,   5,    1,    3,     4,     0x2D5A,   9,        14,  6,    0x27D, 5,             23,   6,   6,          2,    0,

// TRTP, TWR, TWTR, TXPDLL, TXSNR, TXSR, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY,
   5,    5,   5,    0,      25,    25,   2,         1,              0,              2,              8,

// W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, WRLAT, WRLAT_ADJ, ZQINIT, ZQCS, ZQCL, ZQRESET,
   2,              0,              1,              0,              1,     1,         166,    16,   83,   10,

// ZQ_INTERVAL, //***dfi low power
// LPI_TIMER_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, LPI_PD_WAKEUP, TDFI_LP_RESP, LPI_WAKEUP_TIMEOUT,
   64,          4,                3,                        2,             0,             7,            4,

// LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_PD_IDLE,
   0,                       0,               0,

//***odt timing
// TODTH_WR, TODTL_2CMD, TODTH_RD, WR_TO_ODTH, RD_TO_ODTH,
   7,        1,          7,        0,          2,

//***dfi timing
// TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_RESP, TDFI_CALVL_MAX, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL,
   8,                  18,            3,             0,               0,              2,               6420,

// TDFI_CTRLUPD_MAX, TDFI_DRAM_CLK_ENABLE, TDFI_DRAM_CLK_DISABLE, TDFI_INIT_START, TDFI_INIT_COMPLETE, TDFI_PHY_RDLAT,
   1284,             3,                    1,                     32,              1024,               16,

// TDFI_PHY_WRDATA, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_PHYUPD_RESP,
   1,               512,               512,               512,               512,               1284,

// TDFI_RDLVL_RR, TDFI_RDLVL_EN, TDFI_RDLVL_RESP, TDFI_RDLVL_MAX, TDFI_RDCSLAT, TDFI_WRCSLAT, TDFI_WRLVL_EN,
   15,            10,            0,               0,              2,            0,            10,

// TDFI_WRLVL_WW, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
   18,            0,               0,

//***leveling timing
// CALVL_INTERVAL, RDLVL_INTERVAL, RDLVL_GATE_INTERVAL, WRLVL_INTERVAL,
   0,              0,              0,                   0,

//***mode register
// MR0_DATA_CSn, MR1_DATA_CSn, MR2_DATA_CSn, MR3_DATA_CSn, MR11_DATA_CSn, MR16_DATA_CSn, MR17_DATA_CSn,
   0,            0x83,         0x1,          1,            0x0,           0,             0,


},
{
	CLK_400MHZ_FN, 400,



//***ac timing
// ADDITIVE_LAT, CASLAT_LIN, CKE_DELAY, CKE_INACTIVE, CKSRE, CKSRX, DLL_RST_ADJ_DLY, DLL_RST_DELAY, TCAENT, TCAEXT,
   0,            6,          0,         0,            2,     2,     0,               0,             10,     10,

// TCACKEL, TCACKEH, TCAMRD, TCCD, TCKE, TCKESR, TDLL, TDAL, TDQSCK_MAX, TDQSCK_MIN, TFAW, TINIT, TINIT3, TINIT4, TINIT5, TMOD,
   10,      10,      20,     4,    3,    7,      0,    21,   3,          1,          21,   41,    0x13882, 0x192,  0xEFA,  11,

// TMRD, TMRR, TMRZ, TMRRI, TPDEX, TRAS_MAX, TRAS_MIN, TRC, TRCD, TREF, TREF_INTERVAL, TRFC, TRP, TRP_AB_CSx, TRRD, TRST_PWRON,
   11,   5,    2,    10,    4,     0x6D56,   19,       32,  12,   0x60E, 5,             53,   12,  13,         5,    0,

// TRTP, TWR, TWTR, TXPDLL, TXSNR, TXSR, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY,
   5,    7,   5,    0,      57,    57,   2,         1,              0,              2,              11,

// W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, WRLAT, WRLAT_ADJ, ZQINIT, ZQCS, ZQCL, ZQRESET,
   2,              0,              1,              0,              3,     3,         400,    37,   200,  21,

// ZQ_INTERVAL, //***dfi low power
// LPI_TIMER_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, LPI_PD_WAKEUP, TDFI_LP_RESP, LPI_WAKEUP_TIMEOUT,
   64,          4,                3,                        2,             0,             7,            4,

// LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_PD_IDLE,
   0,                       0,               0,

//***odt timing
// TODTH_WR, TODTL_2CMD, TODTH_RD, WR_TO_ODTH, RD_TO_ODTH,
   7,        2,          7,        1,          4,

//***dfi timing
// TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_RESP, TDFI_CALVL_MAX, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL,
   10,                 20,            3,             0,               0,              2,               15520,

// TDFI_CTRLUPD_MAX, TDFI_DRAM_CLK_ENABLE, TDFI_DRAM_CLK_DISABLE, TDFI_INIT_START, TDFI_INIT_COMPLETE, TDFI_PHY_RDLAT,
   3104,             3,                    1,                     32,              4000,               21,

// TDFI_PHY_WRDATA, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_PHYUPD_RESP,
   1,               512,               512,               512,               512,               3104,

// TDFI_RDLVL_RR, TDFI_RDLVL_EN, TDFI_RDLVL_RESP, TDFI_RDLVL_MAX, TDFI_RDCSLAT, TDFI_WRCSLAT, TDFI_WRLVL_EN,
   15,            10,            0,               0,              5,            2,            10,

// TDFI_WRLVL_WW, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
   18,            0,               0,

//***leveling timing
// CALVL_INTERVAL, RDLVL_INTERVAL, RDLVL_GATE_INTERVAL, WRLVL_INTERVAL,
   0,              0,              0,                   0,

//***mode register
// MR0_DATA_CSn, MR1_DATA_CSn, MR2_DATA_CSn, MR3_DATA_CSn, MR11_DATA_CSn, MR16_DATA_CSn, MR17_DATA_CSn,
   0,            0x83,         0x4,          1,            0x0,           0,             0,


},
{
	CLK_640MHZ_FN, 640,


//***ac timing
// ADDITIVE_LAT, CASLAT_LIN, CKE_DELAY, CKE_INACTIVE, CKSRE, CKSRX, DLL_RST_ADJ_DLY, DLL_RST_DELAY, TCAENT, TCAEXT,
   0,            10,         0,         0,            2,     2,     0,               0,             10,     10,

// TCACKEL, TCACKEH, TCAMRD, TCCD, TCKE, TCKESR, TDLL, TDAL, TDQSCK_MAX, TDQSCK_MIN, TFAW, TINIT, TINIT3, TINIT4, TINIT5, TMOD,
   10,      10,      0x04,     4,    6,    11,     0,    32,   5,          3,          33,   66,    0x1F442, 0x2C2,  0x1665, 11,

// TMRD, TMRR, TMRZ, TMRRI, TPDEX, TRAS_MAX, TRAS_MIN, TRC, TRCD, TREF, TREF_INTERVAL, TRFC, TRP, TRP_AB_CSx, TRRD, TRST_PWRON,
   11,   5,    3,    0x13,    7,     0xAC65,   0x1F,       0x35,  0x13,   0x97E, 5,             0x089,   0x13,  20,         0xA,    0,

// TRTP, TWR, TWTR, TXPDLL, TXSNR, TXSR, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY,
   6,    0xC,  6,    0,      0x8F,    0x8F,   4,         1,              0,              2,              2,

// W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, WRLAT, WRLAT_ADJ, ZQINIT, ZQCS, ZQCL, ZQRESET,
   2,              0,              1,              0,              6,     6,         640,    59,   0x74,  33,

// ZQ_INTERVAL, //***dfi low power
// LPI_TIMER_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, LPI_PD_WAKEUP, TDFI_LP_RESP, LPI_WAKEUP_TIMEOUT,
   64,          4,                3,                        2,             0,             7,            4,

// LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_PD_IDLE,
   0,                       0,               0,

//***odt timing
// TODTH_WR, TODTL_2CMD, TODTH_RD, WR_TO_ODTH, RD_TO_ODTH,
   7,        3,          7,        3,          8,

//***dfi timing
// TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_RESP, TDFI_CALVL_MAX, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL,
   13,                 23,            3,             0,               0,              2,               24760,

// TDFI_CTRLUPD_MAX, TDFI_DRAM_CLK_ENABLE, TDFI_DRAM_CLK_DISABLE, TDFI_INIT_START, TDFI_INIT_COMPLETE, TDFI_PHY_RDLAT,
   4952,             3,                    1,                     32,              4000,               26,

// TDFI_PHY_WRDATA, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_PHYUPD_RESP,
   1,               512,               512,               512,               512,               4952,

// TDFI_RDLVL_RR, TDFI_RDLVL_EN, TDFI_RDLVL_RESP, TDFI_RDLVL_MAX, TDFI_RDCSLAT, TDFI_WRCSLAT, TDFI_WRLVL_EN,
   15,            10,            0,               0,              9,            5,            10,

// TDFI_WRLVL_WW, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
   18,            0,               0,

//***leveling timing
// CALVL_INTERVAL, RDLVL_INTERVAL, RDLVL_GATE_INTERVAL, WRLVL_INTERVAL,
   0,              0,              0,                   0,

//***mode register
// MR0_DATA_CSn, MR1_DATA_CSn, MR2_DATA_CSn, MR3_DATA_CSn, MR11_DATA_CSn, MR16_DATA_CSn, MR17_DATA_CSn,
   0,            0x3,          0x18,         1,            0x0,           0,             0,


},
{
	CLK_800MHZ_FN, 800,


//***ac timing
// ADDITIVE_LAT, CASLAT_LIN, CKE_DELAY, CKE_INACTIVE, CKSRE, CKSRX, DLL_RST_ADJ_DLY, DLL_RST_DELAY, TCAENT, TCAEXT,
   0,            12,         0,         0,            2,     2,     0,               0,             10,     10,

// TCACKEL, TCACKEH, TCAMRD, TCCD, TCKE, TCKESR, TDLL, TDAL, TDQSCK_MAX, TDQSCK_MIN, TFAW, TINIT, TINIT3, TINIT4, TINIT5, TMOD,
   10,      10,      0x4,     4,    7,    13,     0,    39,  0x6,        0x3,        41,   0x52,    0x27150, 0x370,  0x2AF8, 11,

// TMRD, TMRR, TMRZ, TMRRI, TPDEX, TRAS_MAX, TRAS_MIN, TRC,  TRCD, TREF, TREF_INTERVAL, TRFC, TRP, TRP_AB_CSx, TRRD, TRST_PWRON,
   11,   4,    4,    0x17,  8,     0xD7A0,   0x26,     0x41, 0x17, 0xBE0, 5,            0xAA,  0x17,  25,       0xc,    0,

// TRTP, TWR, TWTR, TXPDLL, TXSNR, TXSR, RDLAT_ADJ, R2R_DIFFCS_DLY, R2R_SAMECS_DLY, R2W_DIFFCS_DLY, R2W_SAMECS_DLY,
   7,    13,  7,    0,      0xB2,  0xB2, 4,         2,              0,              2,              0x11,

// W2R_DIFFCS_DLY, W2R_SAMECS_DLY, W2W_DIFFCS_DLY, W2W_SAMECS_DLY, WRLAT, WRLAT_ADJ, ZQINIT, ZQCS, ZQCL, ZQRESET,
   0,              0,              2,              0,              6,     6,         0x3E8,  73,   0x1F4,  41,

// ZQ_INTERVAL, //***dfi low power
// LPI_TIMER_WAKEUP, LPI_SR_MCCLK_GATE_WAKEUP, LPI_SR_WAKEUP, LPI_PD_WAKEUP, TDFI_LP_RESP, LPI_WAKEUP_TIMEOUT,
   0x64,          4,                3,                        2,             0,             7,            4,

// LP_AUTO_SR_MC_GATE_IDLE, LP_AUTO_SR_IDLE, LP_AUTO_PD_IDLE,
   0,                       0,               0,

//***odt timing
// TODTH_WR, TODTL_2CMD, TODTH_RD, WR_TO_ODTH, RD_TO_ODTH,
   7,        3,          7,        3,          10,

//***dfi timing
// TDFI_CALVL_CAPTURE, TDFI_CALVL_CC, TDFI_CALVL_EN, TDFI_CALVL_RESP, TDFI_CALVL_MAX, TDFI_CTRL_DELAY, TDFI_CTRLUPD_INTERVAL,
   15,                 25,            3,             0,               0,              2,               31120,

// TDFI_CTRLUPD_MAX, TDFI_DRAM_CLK_ENABLE, TDFI_DRAM_CLK_DISABLE, TDFI_INIT_START, TDFI_INIT_COMPLETE, TDFI_PHY_RDLAT,
   6224,             3,                    1,                     32,              4000,               30,

// TDFI_PHY_WRDATA, TDFI_PHYUPD_TYPE0, TDFI_PHYUPD_TYPE1, TDFI_PHYUPD_TYPE2, TDFI_PHYUPD_TYPE3, TDFI_PHYUPD_RESP,
   1,               512,               512,               512,               512,               6224,

// TDFI_RDLVL_RR, TDFI_RDLVL_EN, TDFI_RDLVL_RESP, TDFI_RDLVL_MAX, TDFI_RDCSLAT, TDFI_WRCSLAT, TDFI_WRLVL_EN,
   15,            10,            0,               0,              11,           5,            10,

// TDFI_WRLVL_WW, TDFI_WRLVL_RESP, TDFI_WRLVL_MAX,
   18,            0,               0,

//***leveling timing
// CALVL_INTERVAL, RDLVL_INTERVAL, RDLVL_GATE_INTERVAL, WRLVL_INTERVAL,
   0,              0,              0,                   0,

//***mode register
// MR0_DATA_CSn, MR1_DATA_CSn, MR2_DATA_CSn, MR3_DATA_CSn, MR11_DATA_CSn, MR16_DATA_CSn, MR17_DATA_CSn,
   0,            0x43,         0x1A,         1,            0x0,           0,             0,


},
};


//==============================whale LP3-1600 DDR PHY timing setting==============================//
const CANDS_PHY_TIMING_T CANDS_PHY_TIMING_INFO[] =
{
{
	CLK_166MHZ_FN, 166,


//***silice 0~3 = byte0~3, slice 4 = addr/cmd
// DEN_PHY_DQ_TIMING_REG, DEN_PHY_DQS_TIMING_REG, DEN_PHY_GATE_LPBK_CTRL_REG, DEN_PHY_READ_CTRL_REG, PHY_DLL_MASTER_CTRL_REG,
   0x412,                 0x414,                  0x80010068,                 4,                     0xA12005A,

// PHY_DLL_SLAVE_CTRL_REG, DEN_PHY_IE_TIMING_REG, PHY_LVL_DBG_CONT_REG, PHY_LVL_CONFIG_REG, PHY_WRLVL_CONFIG_REG,
   0x4040,                 0x40000821,            0,                    0x818A,             0x4240F000,

//***phy core
// DEN_PHY_CTRL_REG, DEN_PHY_DESKEW_CTRL_REG, DEN_PHY_DESKEW_BYPASS_REG, DEN_PHY_CALVL_CTRL_REG, DEN_PHY_LP_WAKEUP_REG,
   0x11926,          0x64522,                 0,                         0xA401338,              0x200,

// DEN_PHY_PAD_TSEL_REG, PHY_PAD_DRIVE_REG_0, PHY_PAD_DRIVE_REG_1, PHY_PAD_DRIVE_REG_2, PHY_PAD_TERM_REG_0,
   0x3DEF799D,           0x20110011,          0x20EE00EE,            0x20EE00EE,            0x0F111200,

// PHY_PAD_CAL_CTRL_REG0, PHY_PAD_ATB_CTRL_REG_AC, PHY_PAD_VREF_CTRL_REG_AC, PHY_CDN_CAL_INTERVAL_REG_AC_0,
   0x80050820,            0,                       0x10F,                    0x2710,

// PHY_CDN_CAL_INTERVAL_REG_AC_1,
   0,
},
{
	CLK_400MHZ_FN, 400,
//***silice 0~3 = byte0~3, slice 4 = addr/cmd
// DEN_PHY_DQ_TIMING_REG, DEN_PHY_DQS_TIMING_REG, DEN_PHY_GATE_LPBK_CTRL_REG, DEN_PHY_READ_CTRL_REG, PHY_DLL_MASTER_CTRL_REG,
   0x412,                 0x414,                  0xA0010090,                 5,                     0xC120024,

// PHY_DLL_SLAVE_CTRL_REG, DEN_PHY_IE_TIMING_REG, PHY_LVL_DBG_CONT_REG, PHY_LVL_CONFIG_REG, PHY_WRLVL_CONFIG_REG,
   0x4040,                 0xA0004924,            0,                    0x818A,             0x4240F000,

//***phy core
// DEN_PHY_CTRL_REG, DEN_PHY_DESKEW_CTRL_REG, DEN_PHY_DESKEW_BYPASS_REG, DEN_PHY_CALVL_CTRL_REG, DEN_PHY_LP_WAKEUP_REG,
   0x41927,          0x64322,                 0,                         0xA401338,              0,

// DEN_PHY_PAD_TSEL_REG, PHY_PAD_DRIVE_REG_0, PHY_PAD_DRIVE_REG_1, PHY_PAD_DRIVE_REG_2, PHY_PAD_TERM_REG_0,
   0x3DEF799D,           0x20110011,          0xEE00EE,            0xEE00EE,            0x1010100,

// PHY_PAD_CAL_CTRL_REG0, PHY_PAD_ATB_CTRL_REG_AC, PHY_PAD_VREF_CTRL_REG_AC, PHY_CDN_CAL_INTERVAL_REG_AC_0,
   0x80050820,            0,                       0x10F,                    0x2710,

// PHY_CDN_CAL_INTERVAL_REG_AC_1,
   0,
},
{
	CLK_640MHZ_FN, 640,
//***silice 0~3 = byte0~3, slice 4 = addr/cmd
// DEN_PHY_DQ_TIMING_REG, DEN_PHY_DQS_TIMING_REG, DEN_PHY_GATE_LPBK_CTRL_REG, DEN_PHY_READ_CTRL_REG, PHY_DLL_MASTER_CTRL_REG,
   0x412,                 0x434,                  0xA0010090,                 7,                     0x10120015,

// PHY_DLL_SLAVE_CTRL_REG, DEN_PHY_IE_TIMING_REG, PHY_LVL_DBG_CONT_REG, PHY_LVL_CONFIG_REG, PHY_WRLVL_CONFIG_REG,
   0x4040,                 0xE0004D36,            0,                    0x818A,             0x4240F000,

//***phy core
// DEN_PHY_CTRL_REG, DEN_PHY_DESKEW_CTRL_REG, DEN_PHY_DESKEW_BYPASS_REG, DEN_PHY_CALVL_CTRL_REG, DEN_PHY_LP_WAKEUP_REG,
   0x61929,          0x64122,                 0,                         0xA401338,              0,

// DEN_PHY_PAD_TSEL_REG, PHY_PAD_DRIVE_REG_0, PHY_PAD_DRIVE_REG_1, PHY_PAD_DRIVE_REG_2, PHY_PAD_TERM_REG_0,
   0x3DEF799D,           0x20110011,          0xEE00EE,            0xEE00EE,            0x1010100,

// PHY_PAD_CAL_CTRL_REG0, PHY_PAD_ATB_CTRL_REG_AC, PHY_PAD_VREF_CTRL_REG_AC, PHY_CDN_CAL_INTERVAL_REG_AC_0,
   0x80050820,            0,                       0x10F,                    0x2710,

// PHY_CDN_CAL_INTERVAL_REG_AC_1,
   0,
},
{
	CLK_800MHZ_FN, 800,
//***silice 0~3 = byte0~3, slice 4 = addr/cmd
// DEN_PHY_DQ_TIMING_REG, DEN_PHY_DQS_TIMING_REG, DEN_PHY_GATE_LPBK_CTRL_REG, DEN_PHY_READ_CTRL_REG, PHY_DLL_MASTER_CTRL_REG,
   0x412,                 0x434,                  0xA00100B9,                 0x8,                     0x12120012,

// PHY_DLL_SLAVE_CTRL_REG, DEN_PHY_IE_TIMING_REG, PHY_LVL_DBG_CONT_REG, PHY_LVL_CONFIG_REG, PHY_WRLVL_CONFIG_REG,
   0x4040,                 0xE0005148,            0,                    0x818A,             0x4240F000,

//***phy core
// DEN_PHY_CTRL_REG, DEN_PHY_DESKEW_CTRL_REG, DEN_PHY_DESKEW_BYPASS_REG, DEN_PHY_CALVL_CTRL_REG, DEN_PHY_LP_WAKEUP_REG,
   0x8192A,          0x64122,                 0,                         0xA401338,              0,

// DEN_PHY_PAD_TSEL_REG, PHY_PAD_DRIVE_REG_0, PHY_PAD_DRIVE_REG_1, PHY_PAD_DRIVE_REG_2, PHY_PAD_TERM_REG_0,
   0x3DEF799D,           0x20110011,          0xEE00EE,            0xEE00EE,            0x1010100,

// PHY_PAD_CAL_CTRL_REG0, PHY_PAD_ATB_CTRL_REG_AC, PHY_PAD_VREF_CTRL_REG_AC, PHY_CDN_CAL_INTERVAL_REG_AC_0,
   0x8005F070,            0,                       0x10F,                    0x2710,

// PHY_CDN_CAL_INTERVAL_REG_AC_1,
   0x20000,
},
};



CANDS_CTL_TIMING_T *__get_ctl_timing_info()
{
	return (CANDS_CTL_TIMING_T *)(&CANDS_CTL_TIMING_INFO[0]);
}

CANDS_PHY_TIMING_T *__get_phy_timing_info()
{
	return (CANDS_PHY_TIMING_T *)(&CANDS_PHY_TIMING_INFO[0]);
}

#else

uint32 cands_ctl_reg_init(void)
{
    uint32 i = 0;

    for(i = 0; i < sizeof(CANDS_CTL_DEF_REG)/sizeof(uint32) ;i++)
    {
            REG32(CANDS_CTL_DEF_REG[i].addr) = CANDS_CTL_DEF_REG[i].data;
    }

    return 0;

}

uint32 cands_phy_reg_init(void)
{
    uint32 i = 0;

    for(i = 0;i < sizeof(CANDS_PHY_DEF_REG)/sizeof(uint32) ;i++)
    {
        for(i = 0; i < sizeof(CANDS_PHY_DEF_REG)/sizeof(uint32) ;i++)
        {
                REG32(CANDS_PHY_DEF_REG[i].addr) = CANDS_PHY_DEF_REG[i].data;
        }
    }

    return 0;
}

#endif



