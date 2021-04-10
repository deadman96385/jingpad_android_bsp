/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef __H_REGS_AON_DBG_APB_HEADFILE_H__
#define __H_REGS_AON_DBG_APB_HEADFILE_H__



#define REG_AON_DBG_APB_CA53_PROT_CTRL      SCI_ADDR(REGS_AON_DBG_APB_BASE, 0x0000 )
#define REG_AON_DBG_APB_CA53_COMM_CTRL      SCI_ADDR(REGS_AON_DBG_APB_BASE, 0x0004 )
#define REG_AON_DBG_APB_CSSYS_CFG           SCI_ADDR(REGS_AON_DBG_APB_BASE, 0x0008 )
#define REG_AON_DBG_APB_SEC_MUX_DBG_EN      SCI_ADDR(REGS_AON_DBG_APB_BASE, 0x000C )
#define REG_AON_DBG_APB_DEBUG_BOND_OPTION   SCI_ADDR(REGS_AON_DBG_APB_BASE, 0x0010 )
#define REG_AON_DBG_APB_CR5_PROT_CTRL       SCI_ADDR(REGS_AON_DBG_APB_BASE, 0x0014 )
#define REG_AON_DBG_APB_CCI_PROT_CTRL       SCI_ADDR(REGS_AON_DBG_APB_BASE, 0x0018 )

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_CA53_PROT_CTRL
// Register Offset : 0x0000
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_CA53_BIG_SPNIDEN(x)                        (((x) & 0xF) << 28)
#define BIT_AON_DBG_APB_CA53_BIG_SPIDEN(x)                         (((x) & 0xF) << 24)
#define BIT_AON_DBG_APB_CA53_BIG_NIDEN(x)                          (((x) & 0xF) << 20)
#define BIT_AON_DBG_APB_CA53_BIG_DBGEN(x)                          (((x) & 0xF) << 16)
#define BIT_AON_DBG_APB_CA53_LIT_SPNIDEN(x)                        (((x) & 0xF) << 12)
#define BIT_AON_DBG_APB_CA53_LIT_SPIDEN(x)                         (((x) & 0xF) << 8)
#define BIT_AON_DBG_APB_CA53_LIT_NIDEN(x)                          (((x) & 0xF) << 4)
#define BIT_AON_DBG_APB_CA53_LIT_DBGEN(x)                          (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_CA53_COMM_CTRL
// Register Offset : 0x0004
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_CA53_BIG_ACINATCM                          BIT(26)
#define BIT_AON_DBG_APB_CA53_BIG_DBGL1RSTDISABLE                   BIT(25)
#define BIT_AON_DBG_APB_CA53_BIG_L2RSTDISABLE                      BIT(24)
#define BIT_AON_DBG_APB_CA53_BIG_CFGTE(x)                          (((x) & 0xF) << 20)
#define BIT_AON_DBG_APB_CA53_BIG_AA64NAA32(x)                      (((x) & 0xF) << 16)
#define BIT_AON_DBG_APB_CA53_LIT_ACINATCM                          BIT(10)
#define BIT_AON_DBG_APB_CA53_LIT_DBGL1RSTDISABLE                   BIT(9)
#define BIT_AON_DBG_APB_CA53_LIT_L2RSTDISABLE                      BIT(8)
#define BIT_AON_DBG_APB_CA53_LIT_CFGTE(x)                          (((x) & 0xF) << 4)
#define BIT_AON_DBG_APB_CA53_LIT_AA64NAA32(x)                      (((x) & 0xF))

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_CSSYS_CFG
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_DAP_DEVICEEN                               BIT(31)
#define BIT_AON_DBG_APB_DAP_DBGEN                                  BIT(30)
#define BIT_AON_DBG_APB_DAP_SPIDBGEN                               BIT(29)
#define BIT_AON_DBG_APB_CC_SPIDEN                                  BIT(10)
#define BIT_AON_DBG_APB_SOFT_CM3_DEBUG_EN                          BIT(7)
#define BIT_AON_DBG_APB_DJTAG_EN                                   BIT(6)
#define BIT_AON_DBG_APB_AG_JTAG_EN                                 BIT(5)
#define BIT_AON_DBG_APB_MJTAG_EN                                   BIT(4)
#define BIT_AON_DBG_APB_CSSYS_NIDEN                                BIT(3)
#define BIT_AON_DBG_APB_CSSYS_SPNIDEN                              BIT(2)
#define BIT_AON_DBG_APB_CSSYS_SPIDEN                               BIT(1)
#define BIT_AON_DBG_APB_CSSYS_DBGEN                                BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_SEC_MUX_DBG_EN
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_DAP_DEVICEEN_S                             BIT(25)
#define BIT_AON_DBG_APB_DAP_DBGEN_S                                BIT(24)
#define BIT_AON_DBG_APB_DAP_SPIDBGEN_S                             BIT(23)
#define BIT_AON_DBG_APB_CC_SPIDEN_S                                BIT(22)
#define BIT_AON_DBG_APB_CM3_DBGEN_S                                BIT(19)
#define BIT_AON_DBG_APB_CCI_NIDEN_S                                BIT(18)
#define BIT_AON_DBG_APB_CCI_SPNIDEN_S                              BIT(17)
#define BIT_AON_DBG_APB_CR5_DBGEN_S                                BIT(16)
#define BIT_AON_DBG_APB_CR5_NIDEN_S                                BIT(15)
#define BIT_AON_DBG_APB_CSSYS_NIDEN_S                              BIT(14)
#define BIT_AON_DBG_APB_CSSYS_SPNIDEN_S                            BIT(13)
#define BIT_AON_DBG_APB_CSSYS_SPIDEN_S                             BIT(12)
#define BIT_AON_DBG_APB_CSSYS_DBGEN_S                              BIT(11)
#define BIT_AON_DBG_APB_CA53_LIT_DBGEN_S                           BIT(10)
#define BIT_AON_DBG_APB_CA53_LIT_NIDEN_S                           BIT(9)
#define BIT_AON_DBG_APB_CA53_LIT_SPIDEN_S                          BIT(8)
#define BIT_AON_DBG_APB_CA53_LIT_SPNIDEN_S                         BIT(7)
#define BIT_AON_DBG_APB_CA53_BIG_DBGEN_S                           BIT(6)
#define BIT_AON_DBG_APB_CA53_BIG_NIDEN_S                           BIT(5)
#define BIT_AON_DBG_APB_CA53_BIG_SPIDEN_S                          BIT(4)
#define BIT_AON_DBG_APB_CA53_BIG_SPNIDEN_S                         BIT(3)
#define BIT_AON_DBG_APB_DJTAG_EN_S                                 BIT(2)
#define BIT_AON_DBG_APB_AG_JTAG_EN_S                               BIT(1)
#define BIT_AON_DBG_APB_MJTAG_EN_S                                 BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_DEBUG_BOND_OPTION
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_JTAG_BOND_OPT_EFS                          BIT(30)
#define BIT_AON_DBG_APB_DBG_DEFAULT_BOND_OFF                       BIT(29)
#define BIT_AON_DBG_APB_FUNCDMA2CC_BOND_OFF                        BIT(28)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_CR5_PROT_CTRL
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_CR5_NIDEN                                  BIT(1)
#define BIT_AON_DBG_APB_CR5_DBGEN                                  BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_AON_DBG_APB_CCI_PROT_CTRL
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_AON_DBG_APB_CCI_NIDEN                                  BIT(1)
#define BIT_AON_DBG_APB_CCI_SPNIDEN                                BIT(0)

#endif
