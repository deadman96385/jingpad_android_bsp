/******************************************************************************
 ** File Name:    sprd_reg_ahb.h                                            *
 ** Author:       Daniel.Ding                                                 *
 ** DATE:         11/13/2005                                                  *
 ** Copyright:    2005 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 11/13/2005    Daniel.Ding     Create.                                     *
 ** 05/07/2010    Mingwei.zhang   Modify it for SC8800G.                      *
 ******************************************************************************/
#ifndef _SPRD_REG_AHB_H_
#define _SPRD_REG_AHB_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **-------------------------------------------------------------------------- */

/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **---------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**----------------------------------------------------------------------------*
**                               Micro Define                                 **
**----------------------------------------------------------------------------*/

#define  AHB_EB         (AHB_REG_BASE + 0x0000)
#define  AHB_SOFT_RST   (AHB_REG_BASE + 0x0004)
#define  AHB_CA7_RST    (AHB_REG_BASE + 0x0008)
#define  AHB_CA7_CKG    (AHB_REG_BASE + 0x000C)
#define  AHB_MISC_CFG   (AHB_REG_BASE + 0x0018)
#define  CHIP_ID			  (AHB_REG_BASE + 0x00fc)

#define  AHB_USB_RST        BIT_5
#define  AHB_USB_UTMI_RST   BIT_6
#define  AHB_USB_PHY_RST    BIT_7
#define  AHB_SDIO0_RST      BIT_11
#define  AHB_EMMC_RST       BIT_14

#ifdef   __cplusplus
}
#endif
/**---------------------------------------------------------------------------*/
#endif
// End
