/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _AON_DBG_APB_REG_H
#define _AON_DBG_APB_REG_H

#define CTL_BASE_AON_DBG_APB SPRD_AON_DBG_BASE


#define REG_AON_DBG_APB_CSSYS_DAP_CFG           ( CTL_BASE_AON_DBG_APB + 0x0000 )
#define REG_AON_DBG_APB_SECURE_DEBUG_PROT_CTRL  ( CTL_BASE_AON_DBG_APB + 0x0004 )
#define REG_AON_DBG_APB_NON_SECURE_DEBUG_EN     ( CTL_BASE_AON_DBG_APB + 0x0008 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_CSSYS_DAP_CFG
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_DAP_DEVICEEN                                   BIT(31)
#define BIT_AON_DBG_APB_DAP_DBGEN                                      BIT(30)
#define BIT_AON_DBG_APB_DAP_SPIDBGEN                                   BIT(29)
#define BIT_AON_DBG_APB_MJTAG_EN                                       BIT(4)
#define BIT_AON_DBG_APB_CSSYS_NIDEN                                    BIT(3)
#define BIT_AON_DBG_APB_CSSYS_SPNIDEN                                  BIT(2)
#define BIT_AON_DBG_APB_CSSYS_SPIDEN                                   BIT(1)
#define BIT_AON_DBG_APB_CSSYS_DBGEN                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_SECURE_DEBUG_PROT_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_DAP2CS_DBGEN                                   BIT(15)
#define BIT_AON_DBG_APB_DAP2AP_DBGEN                                   BIT(14)
#define BIT_AON_DBG_APB_GPU_DBGEN                                      BIT(13)
#define BIT_AON_DBG_APB_DJTAG_DBGEN                                    BIT(12)
#define BIT_AON_DBG_APB_AGDSP_DBGEN                                    BIT(11)
#define BIT_AON_DBG_APB_LDSP_DBGEN                                     BIT(10)
#define BIT_AON_DBG_APB_TGDSP_DBGEN                                    BIT(9)
#define BIT_AON_DBG_APB_BLK_CTMR_VSB_DBGEN                             BIT(8)
#define BIT_AON_DBG_APB_OVRD_CTMR_VSB_DBGEN                            BIT(7)
#define BIT_AON_DBG_APB_BLK_INTEL_PRPT_DBGEN                           BIT(6)
#define BIT_AON_DBG_APB_APSYS_M_DBGEN                                  BIT(5)
#define BIT_AON_DBG_APB_CM4_M_DBGEN                                    BIT(4)
#define BIT_AON_DBG_APB_CM4_S_DBGEN                                    BIT(3)
#define BIT_AON_DBG_APB_CR5_M_DBGEN                                    BIT(2)
#define BIT_AON_DBG_APB_CR5_S_NIDEN                                    BIT(1)
#define BIT_AON_DBG_APB_CR5_S_DBGEN                                    BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_NON_SECURE_DEBUG_EN
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_DAP2CS_NON_SEC_DBGEN                           BIT(15)
#define BIT_AON_DBG_APB_DAP2AP_NON_SEC_DBGEN                           BIT(14)
#define BIT_AON_DBG_APB_GPU_NON_SEC_DBGEN                              BIT(13)
#define BIT_AON_DBG_APB_DJTAG_NON_SEC_DBGEN                            BIT(12)
#define BIT_AON_DBG_APB_AGDSP_NON_SEC_DBGEN                            BIT(11)
#define BIT_AON_DBG_APB_LDSP_NON_SEC_DBGEN                             BIT(10)
#define BIT_AON_DBG_APB_TGDSP_NON_SEC_DBGEN                            BIT(9)
#define BIT_AON_DBG_APB_BLK_CTMR_VSB_NON_SEC_DBGEN                     BIT(8)
#define BIT_AON_DBG_APB_OVRD_CTMR_VSB_NON_SEC_DBGEN                    BIT(7)
#define BIT_AON_DBG_APB_BLK_INTEL_PRPT_NON_SEC_DBGEN                   BIT(6)
#define BIT_AON_DBG_APB_APSYS_M_NON_SEC_DBGEN                          BIT(5)
#define BIT_AON_DBG_APB_CM4_M_NON_SEC_DBGEN                            BIT(4)
#define BIT_AON_DBG_APB_CM4_S_NON_SEC_DBGEN                            BIT(3)
#define BIT_AON_DBG_APB_CR5_M_NON_SEC_DBGEN                            BIT(2)
#define BIT_AON_DBG_APB_CR5_S_NON_SEC_NIDEN                            BIT(1)
#define BIT_AON_DBG_APB_CR5_S_NON_SEC_DBGEN                            BIT(0)


#endif // _AON_DBG_APB_REG_H
