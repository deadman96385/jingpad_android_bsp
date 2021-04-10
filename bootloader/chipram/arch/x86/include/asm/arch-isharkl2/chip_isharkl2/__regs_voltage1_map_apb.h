/*
 * Copyright (C) 2015 Spreadtrum Communications Inc.
 *
 * This file is dual-licensed: you can use it either under the terms
 * of the GPL or the X11 license, at your option. Note that this dual
 * licensing only applies to this file, and not this project as a
 * whole.
 *
 */


#ifndef _VOLTAGE1_MAP_APB_REG_H
#define _VOLTAGE1_MAP_APB_REG_H

#define CTL_BASE_VOLTAGE1_MAP_APB SPRD_VOLTAGE1_MAP_APB


#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_CONFIG         ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0000 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_STATUS         ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0004 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_FLAG_CLR       ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0008 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_TRAN_DONE_CLR  ( CTL_BASE_VOLTAGE1_MAP_APB + 0x000C )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_INT_CLR        ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0010 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_DELAY      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0014 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_DELAY      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0018 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_0      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0020 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_1      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0024 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_2      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0028 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_3      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x002C )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_4      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0030 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_5      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0034 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_6      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0038 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_7      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x003C )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_0      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0040 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_1      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0044 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_2      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0048 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_3      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x004C )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_4      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0050 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_5      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0054 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_6      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0058 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_7      ( CTL_BASE_VOLTAGE1_MAP_APB + 0x005C )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_DELAY2     ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0060 )
#define REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_DELAY3     ( CTL_BASE_VOLTAGE1_MAP_APB + 0x0064 )

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_CONFIG
// Register Offset : 0x0000
// Description     : reg_switch
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_BAD(x)                              (((x) & 0xFFFF) << 16)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_TABLE_LOCK                                   BIT(7)
#define BIT_VOLTAGE1_MAP_APB_REG_DVFS_PWD_ADI_EN                                  BIT(6)
#define BIT_VOLTAGE1_MAP_APB_REG_DVFS_PWD_EN                                      BIT(5)
#define BIT_VOLTAGE1_MAP_APB_REG_BAD_REQUEST_IRQ_EN                               BIT(4)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_TRANS_IRQ_EN                             BIT(3)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_CH_BUSY_IRQ_EN                           BIT(2)
#define BIT_VOLTAGE1_MAP_APB_REG_SWITCH(x)                                        (((x) & 0x3))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_STATUS
// Register Offset : 0x0004
// Description     : baseia voltage code 3-bit
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_BAD_REQUEST_IRQ_STS                              BIT(7)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_TRANS_IRQ_STS                            BIT(6)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_CH_BUSY_IRQ_STS                          BIT(5)
#define BIT_VOLTAGE1_MAP_APB_REG_DEFAULT_RESPONSE_FLAG                            BIT(4)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_CH_BUSY                                  BIT(3)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_CODE(x)                                  (((x) & 0x7))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_FLAG_CLR
// Register Offset : 0x0008
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_DEFAULT_RESPONSE_FLAG_CLR                        BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_TRAN_DONE_CLR
// Register Offset : 0x000C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_TRANS_DONE_CLR                                   BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_INT_CLR
// Register Offset : 0x0010
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_BAD_REQUEST_IRQ_CLR                              BIT(2)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_TRANS_IRQ_CLR                            BIT(1)
#define BIT_VOLTAGE1_MAP_APB_REG_VOLTAGE_CH_BUSY_IRQ_CLR                          BIT(0)

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_DELAY
// Register Offset : 0x0014
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_DELAY(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_DELAY
// Register Offset : 0x0018
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_DELAY(x)                                     (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_0
// Register Offset : 0x0020
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_0                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_0(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_1
// Register Offset : 0x0024
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_1                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_1(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_2
// Register Offset : 0x0028
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_2                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_2(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_3
// Register Offset : 0x002C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_3                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_3(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_4
// Register Offset : 0x0030
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_4                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_4(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_5
// Register Offset : 0x0034
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_5                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_5(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_6
// Register Offset : 0x0038
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_6                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_6(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_MAP_7
// Register Offset : 0x003C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VALID_7                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_ADI_MAP_VOLT_7(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_0
// Register Offset : 0x0040
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_0                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_0(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_1
// Register Offset : 0x0044
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_1                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_1(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_2
// Register Offset : 0x0048
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_2                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_2(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_3
// Register Offset : 0x004C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_3                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_3(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_4
// Register Offset : 0x0050
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_4                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_4(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_5
// Register Offset : 0x0054
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_5                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_5(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_6
// Register Offset : 0x0058
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_6                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_6(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_IIC_MAP_7
// Register Offset : 0x005C
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VALID_7                                  BIT(31)
#define BIT_VOLTAGE1_MAP_APB_REG_IIC_MAP_VOLT_7(x)                                (((x) & 0xFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_DELAY2
// Register Offset : 0x0060
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_DELAY2(x)                                    (((x) & 0xFFFFFFFF))

/*---------------------------------------------------------------------------
// Register Name   : REG_VOLTAGE1_MAP_APB_VOLT_MAP_ADI_DELAY3
// Register Offset : 0x0064
// Description     : 
---------------------------------------------------------------------------*/

#define BIT_VOLTAGE1_MAP_APB_REG_ADI_DELAY3(x)                                    (((x) & 0xFFFFFFFF))


#endif // _VOLTAGE1_MAP_APB_REG_H
