/******************************************************************************
 ** File Name:      umctl2_reg.h                                              *
 ** Author:         changde                                                   *
 ** DATE:           01/06/2013                                                *
 ** Copyright:      2010 Spreatrum, Incoporated. All Rights Reserved.         *
 ** Description:    Refer to uMCTL2 databook for detail                       *
 ******************************************************************************

 ******************************************************************************
 **                        Edit History                                       *
 ** ------------------------------------------------------------------------- *
 ** DATE           NAME             DESCRIPTION                               *
 ** 01/06/2013     changde.li       Create.                                   *
 ******************************************************************************/

#ifndef _UMCTL2_REG_H_
#define _UMCTL2_REG_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **------------------------------------------------------------------------- */
#include <sci_types.h>
/* delete sc_reg_h */
/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **--------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif

/**---------------------------------------------------------------------------*
 **                         Debugging Flag                                    *
 **---------------------------------------------------------------------------*/
/**---------------------------------------------------------------------------*
**                               Micro Define                                **
**---------------------------------------------------------------------------*/
#define UMCTL_REG_BASE (0x30000000)
#define PUBL_REG_BASE  (0x30010000)

#define UMCTL2_REG_(x) (UMCTL_REG_BASE+(x))

/*
 *uMCTL2 DDRC registers
*/
#define UMCTL_MSTR       UMCTL2_REG_(0x0000) /*master*/
#define UMCTL_STAT       UMCTL2_REG_(0x0004) /*oeration mode status*/
#define UMCTL_MRCTRL0    UMCTL2_REG_(0x0010)/*mode register read/werite control*/
#define UMCTL_MRCTRL1    UMCTL2_REG_(0x0014)
#define UMCTL_MRSTAT     UMCTL2_REG_(0x0018)/*mode register read/weite status*/

#define UMCTL_DERATEEN   UMCTL2_REG_(0x0020)/*temperature derate enable*/
#define UMCTL_DERATEINT  UMCTL2_REG_(0x0024)/*temperature derate interval*/
#define UMCTL_PWRCTL     UMCTL2_REG_(0x0030)/*low power control*/
#define UMCTL_PWRTMG     UMCTL2_REG_(0x0034)/*low power timing*/
#define UMCTL_HWLPCTL    UMCTL2_REG_(0x0038)/*low power timing*/


#define UMCTL_RFSHCTL0   UMCTL2_REG_(0x0050)/*refresh control0*/
#define UMCTL_RFSHCTL1   UMCTL2_REG_(0x0054)
#define UMCTL_RFSHCTL2   UMCTL2_REG_(0x0058)
#define UMCTL_RFSHCTL3   UMCTL2_REG_(0x0060)
#define UMCTL_RFSHTMG    UMCTL2_REG_(0x0064)/*refresh Timing*/
#define UMCTL_ECCCFG0    UMCTL2_REG_(0x0070)/*ecc configuration*/
#define UMCTL_ECCCFG1    UMCTL2_REG_(0x0074)
#define UMCTL_ECCSTAT    UMCTL2_REG_(0x0078)/*ecc status*/
#define UMCTL_ECCCLR     UMCTL2_REG_(0x007C)/*ecc clear*/
#define UMCTL_ECCERRCNT  UMCTL2_REG_(0x0080)/*ecc error counter*/

#define UMCTL_ECCADDR0   UMCTL2_REG_(0x0084)/*ecc corrected error address reg0*/
#define UMCTL_ECCADDR1   UMCTL2_REG_(0x0088)
#define UMCTL_ECCSYN0    UMCTL2_REG_(0x008C)/*ecc corected syndrome reg0*/
#define UMCTL_ECCSYN1    UMCTL2_REG_(0x0090)
#define UMCTL_ECCSYN2    UMCTL2_REG_(0x0094)
#define UMCTL_ECCBITMASK0    UMCTL2_REG_(0x0098)
#define UMCTL_ECCBITMASK1    UMCTL2_REG_(0x009C)
#define UMCTL_ECCBITMASK2    UMCTL2_REG_(0x00A0)
#define UMCTL_ECCUADDR0      UMCTL2_REG_(0x00A4)/*ecc uncorrected error address reg0*/
#define UMCTL_ECCUADDR1      UMCTL2_REG_(0x00A8)
#define UMCTL_ECCUSYN0       UMCTL2_REG_(0x00AC)/*ecc UNcorected syndrome reg0*/
#define UMCTL_ECCUSYN1       UMCTL2_REG_(0x00B0)
#define UMCTL_ECCUSYN2       UMCTL2_REG_(0x00B4)
#define UMCTL_ECCPOISONADDR0 UMCTL2_REG_(0x00B8)/*ecc data poisoning address reg0*/
#define UMCTL_ECCPOISONADDR1 UMCTL2_REG_(0x00BC)


#define UMCTL_PARCTL     UMCTL2_REG_(0x00C0)/*parity control register*/
#define UMCTL_PARSTAT    UMCTL2_REG_(0x00C4)/*parity status register*/

#define UMCTL_INIT0      UMCTL2_REG_(0x00D0)/*SDRAM initialization register0*/
#define UMCTL_INIT1      UMCTL2_REG_(0x00D4)
#define UMCTL_INIT2      UMCTL2_REG_(0x00D8)
#define UMCTL_INIT3      UMCTL2_REG_(0x00DC)
#define UMCTL_INIT4      UMCTL2_REG_(0x00E0)
#define UMCTL_INIT5      UMCTL2_REG_(0x00E4)


#define UMCTL_DIMMCTL    UMCTL2_REG_(0x00F0)/*DIMM control register*/
#define UMCTL_RANKCTL    UMCTL2_REG_(0x00F4)

#define UMCTL_DRAMTMG0   UMCTL2_REG_(0x0100)/*SDRAM timing register0*/
#define UMCTL_DRAMTMG1   UMCTL2_REG_(0x0104)
#define UMCTL_DRAMTMG2   UMCTL2_REG_(0x0108)
#define UMCTL_DRAMTMG3   UMCTL2_REG_(0x010C)
#define UMCTL_DRAMTMG4   UMCTL2_REG_(0x0110)
#define UMCTL_DRAMTMG5   UMCTL2_REG_(0x0114)
#define UMCTL_DRAMTMG6   UMCTL2_REG_(0x0118)
#define UMCTL_DRAMTMG7   UMCTL2_REG_(0x011C)
#define UMCTL_DRAMTMG8   UMCTL2_REG_(0x0120)

#define UMCTL_ZQCTL0     UMCTL2_REG_(0x0180)/*ZQ control register0*/
#define UMCTL_ZQCTL1     UMCTL2_REG_(0x0184)
#define UMCTL_ZQCTL2     UMCTL2_REG_(0x0188)
#define UMCTL_ZQSTAT     UMCTL2_REG_(0x018C)


#define UMCTL_DFITMG0    UMCTL2_REG_(0x0190)/*DFI timing register0*/
#define UMCTL_DFITMG1    UMCTL2_REG_(0x0194)

#define UMCTL_DFILPCFG0  UMCTL2_REG_(0x0198)/*DFI low power configuration*/
#define UMCTL_DFIUPD0    UMCTL2_REG_(0x01A0)/*DFI update register0*/
#define UMCTL_DFIUPD1    UMCTL2_REG_(0x01A4)
#define UMCTL_DFIUPD2    UMCTL2_REG_(0x01A8)
#define UMCTL_DFIUPD3    UMCTL2_REG_(0x01AC)

#define UMCTL_DFIMISC    UMCTL2_REG_(0x01B0)

#define UMCTL_TRAINCTL0  UMCTL2_REG_(0x01D0)/*PHY eval training control reg0*/
#define UMCTL_TRAINCTL1  UMCTL2_REG_(0x01D4)
#define UMCTL_TRAINCTL2  UMCTL2_REG_(0x01D8)
#define UMCTL_TRAINSTAT  UMCTL2_REG_(0x01DC)

#define UMCTL_ADDRMAP0   UMCTL2_REG_(0x0200)/*address map register0*/
#define UMCTL_ADDRMAP1   UMCTL2_REG_(0x0204)
#define UMCTL_ADDRMAP2   UMCTL2_REG_(0x0208)
#define UMCTL_ADDRMAP3   UMCTL2_REG_(0x020C)
#define UMCTL_ADDRMAP4   UMCTL2_REG_(0x0210)
#define UMCTL_ADDRMAP5   UMCTL2_REG_(0x0214)
#define UMCTL_ADDRMAP6   UMCTL2_REG_(0x0218)

#define UMCTL_ODTCFG     UMCTL2_REG_(0x0240)/*ODT configuration register*/
#define UMCTL_ODTMAP     UMCTL2_REG_(0x0244)

#define UMCTL_SCHED      UMCTL2_REG_(0x0250)/*scheduler control register*/
#define UMCTL_PERFHPR0   UMCTL2_REG_(0x0258)/*high priority read CAM reg0*/
#define UMCTL_PERFHPR1   UMCTL2_REG_(0x025C)
#define UMCTL_PERFLPR0   UMCTL2_REG_(0x0260)
#define UMCTL_PERFLPR1   UMCTL2_REG_(0x0264)

#define UMCTL_PERFWR0    UMCTL2_REG_(0x0268)/*write CAM reg0*/
#define UMCTL_PERFWR1    UMCTL2_REG_(0x026C)
#define UMCTL_DBG0       UMCTL2_REG_(0x0300)/*debug register0*/
#define UMCTL_DBG1       UMCTL2_REG_(0x0304)
#define UMCTL_DBGCAM     UMCTL2_REG_(0x0308)/*cam debug register*/


/*
 *uMCTL2 Multi-Port registers
*/
#define UMCTL_PCCFG      UMCTL2_REG_(0x0400)/*port common configuration*/

#define UMCTL_PCFGR_0    UMCTL2_REG_(0x0404+(0x00)*0xB0)/*Port n configuration read reg*/
#define UMCTL_PCFGR_1    UMCTL2_REG_(0x0404+(0x01)*0xB0)
#define UMCTL_PCFGR_2    UMCTL2_REG_(0x0404+(0x02)*0xB0)
#define UMCTL_PCFGR_3    UMCTL2_REG_(0x0404+(0x03)*0xB0)
#define UMCTL_PCFGR_4    UMCTL2_REG_(0x0404+(0x04)*0xB0)
#define UMCTL_PCFGR_5    UMCTL2_REG_(0x0404+(0x05)*0xB0)
#define UMCTL_PCFGR_6    UMCTL2_REG_(0x0404+(0x06)*0xB0)
#define UMCTL_PCFGR_7    UMCTL2_REG_(0x0404+(0x07)*0xB0)
#define UMCTL_PCFGR_8    UMCTL2_REG_(0x0404+(0x08)*0xB0)
#define UMCTL_PCFGR_9    UMCTL2_REG_(0x0404+(0x09)*0xB0)
#define UMCTL_PCFGR_10   UMCTL2_REG_(0x0404+(0x0A)*0xB0)
#define UMCTL_PCFGR_11   UMCTL2_REG_(0x0404+(0x0B)*0xB0)
#define UMCTL_PCFGR_12   UMCTL2_REG_(0x0404+(0x0C)*0xB0)
#define UMCTL_PCFGR_13   UMCTL2_REG_(0x0404+(0x0D)*0xB0)
#define UMCTL_PCFGR_14   UMCTL2_REG_(0x0404+(0x0E)*0xB0)
#define UMCTL_PCFGR_15   UMCTL2_REG_(0x0404+(0x0F)*0xB0)


#define UMCTL_PCFGW(_x_) UMCTL2_REG_(0x0408+(_x_)*0xB0)


#define UMCTL_PCFGW_0    UMCTL2_REG_(0x0408+(0x00)*0xB0)/*Port n configuration write reg*/
#define UMCTL_PCFGW_1    UMCTL2_REG_(0x0408+(0x01)*0xB0)
#define UMCTL_PCFGW_2    UMCTL2_REG_(0x0408+(0x02)*0xB0)
#define UMCTL_PCFGW_3    UMCTL2_REG_(0x0408+(0x03)*0xB0)
#define UMCTL_PCFGW_4    UMCTL2_REG_(0x0408+(0x04)*0xB0)
#define UMCTL_PCFGW_5    UMCTL2_REG_(0x0408+(0x05)*0xB0)
#define UMCTL_PCFGW_6    UMCTL2_REG_(0x0408+(0x06)*0xB0)
#define UMCTL_PCFGW_7    UMCTL2_REG_(0x0408+(0x07)*0xB0)
#define UMCTL_PCFGW_8    UMCTL2_REG_(0x0408+(0x08)*0xB0)
#define UMCTL_PCFGW_9    UMCTL2_REG_(0x0408+(0x09)*0xB0)
#define UMCTL_PCFGW_10   UMCTL2_REG_(0x0408+(0x0A)*0xB0)
#define UMCTL_PCFGW_11   UMCTL2_REG_(0x0408+(0x0B)*0xB0)
#define UMCTL_PCFGW_12   UMCTL2_REG_(0x0408+(0x0C)*0xB0)
#define UMCTL_PCFGW_13   UMCTL2_REG_(0x0408+(0x0D)*0xB0)
#define UMCTL_PCFGW_14   UMCTL2_REG_(0x0408+(0x0E)*0xB0)
#define UMCTL_PCFGW_15   UMCTL2_REG_(0x0408+(0x0F)*0xB0)

#define UMCTL_PORT_EN(_x_) UMCTL2_REG_(0x0490+(_x_)*0xB0)

#define UMCTL_PORT_EN_0    UMCTL2_REG_(0x0490+(0x00)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_1    UMCTL2_REG_(0x0490+(0x01)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_2    UMCTL2_REG_(0x0490+(0x02)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_3    UMCTL2_REG_(0x0490+(0x03)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_4    UMCTL2_REG_(0x0490+(0x04)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_5    UMCTL2_REG_(0x0490+(0x05)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_6    UMCTL2_REG_(0x0490+(0x06)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_7    UMCTL2_REG_(0x0490+(0x07)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_8    UMCTL2_REG_(0x0490+(0x08)*0xB0)/*Port n enable reg*/
#define UMCTL_PORT_EN_9    UMCTL2_REG_(0x0490+(0x09)*0xB0)/*Port n enable reg*/


/*
#define UMCTL2_PCFGIDMASKCH_m_N
#define UMCTL2_PCFGIDVALUECH_m_N
*/


/*
 *Refer to PUBL databook 1.44a for detail,Chapter3.3 Registers.
*/
#if defined(CONFIG_FPGA)

#define REG_AON_TOP_DDR_PHY_RET_CFG	(0x402b0000 + 0x130)
#define REG_AON_TOP_DDR_OP_MODE_CFG	(0x402b0000 + 0x12C)
#define REG_AON_TOP_DDR_SLEEP_CTRL	(0x402b0000 + 0x0D0)
#define REG_AON_TOP_DDR_CHN_SLEEP_CTRL0	(0x402b0000 + 0x0F8)


#define PUBL_DTAR0	(PUBL_REG_BASE + 0xb4)
#define PUBL_PIR	(PUBL_REG_BASE + 0x04)
#define PUBL_PGCR	(PUBL_REG_BASE + 0x08)
#define PUBL_PGCR1	(PUBL_REG_BASE + 0x0c)
#define PUBL_PGSR0	(PUBL_REG_BASE + 0x18)
#define PUBL_PGCR3	(PUBL_REG_BASE + 0x14)
#define PUBL_PLLCR	(PUBL_REG_BASE + 0x20)
#define PUBL_PTR0	(PUBL_REG_BASE + 0x24)
#define PUBL_PTR1	(PUBL_REG_BASE + 0x28)
#define PUBL_PTR2	(PUBL_REG_BASE + 0x2c)
#define PUBL_ACIOCR1	(PUBL_REG_BASE + 0x6c)
#define PUBL_ACIOCR2	(PUBL_REG_BASE + 0x70)
#define PUBL_ACIOCR3	(PUBL_REG_BASE + 0x74)
#define PUBL_ACIOCR4	(PUBL_REG_BASE + 0x78)
#define PUBL_ACIOCR5	(PUBL_REG_BASE + 0x7c)
#define	PUBL_IOVCR0	(PUBL_REG_BASE + 0x238)
#define	PUBL_IOVCR1	(PUBL_REG_BASE + 0x23C)
#define	PUBL_DX0GCR1	(PUBL_REG_BASE + 0x284)
#define	PUBL_DX0GCR2	(PUBL_REG_BASE + 0x288)
#define	PUBL_DX0GCR3	(PUBL_REG_BASE + 0x28C)
#define	PUBL_DX1GCR1	(PUBL_REG_BASE + 0x304)
#define	PUBL_DX1GCR2	(PUBL_REG_BASE + 0x308)
#define	PUBL_DX1GCR3	(PUBL_REG_BASE + 0x30C)
#define	PUBL_DX2GCR1	(PUBL_REG_BASE + 0x384)
#define	PUBL_DX2GCR2	(PUBL_REG_BASE + 0x388)
#define	PUBL_DX2GCR3	(PUBL_REG_BASE + 0x38C)
#define	PUBL_DX3GCR1	(PUBL_REG_BASE + 0x404)
#define	PUBL_DX3GCR2	(PUBL_REG_BASE + 0x408)
#define	PUBL_DX3GCR3	(PUBL_REG_BASE + 0x40C)

#define PUBL_DXCCR	(PUBL_REG_BASE + 0x80)

#define PUBL_DSGCR	(PUBL_REG_BASE + 0x84)
#define PUBL_DCR	(PUBL_REG_BASE + 0x88)

#define PUBL_DTPR0	(PUBL_REG_BASE + 0x8c)
#define PUBL_DTPR1	(PUBL_REG_BASE + 0x90)
#define PUBL_DTPR2	(PUBL_REG_BASE + 0x94)
#define PUBL_DTPR3	(PUBL_REG_BASE + 0x98)

#define PUBL_MR0	(PUBL_REG_BASE + 0x9c)
#define PUBL_MR1	(PUBL_REG_BASE + 0xa0)
#define PUBL_MR2	(PUBL_REG_BASE + 0xa4)
#define PUBL_MR3	(PUBL_REG_BASE + 0xa8)

#define PUBL_DTCR	(PUBL_REG_BASE + 0xb0)

#define PUBL_DX0DQTR	(PUBL_REG_BASE + 0x1d0)
#define PUBL_DX0DQSTR	(PUBL_REG_BASE + 0x1d4)
#define PUBL_DX1DQTR	(PUBL_REG_BASE + 0x210)
#define PUBL_DX1DQSTR	(PUBL_REG_BASE + 0x214)
#define PUBL_DX2DQTR	(PUBL_REG_BASE + 0x250)
#define PUBL_DX2DQSTR	(PUBL_REG_BASE + 0x254)
#define PUBL_DX3DQTR	(PUBL_REG_BASE + 0x290)
#define PUBL_DX3DQSTR	(PUBL_REG_BASE + 0x294)

#define PUBL_DX0GCR		(PUBL_REG_BASE + 0x1c0)
#define PUBL_DX1GCR		(PUBL_REG_BASE + 0x200)
#define PUBL_DX2GCR		(PUBL_REG_BASE + 0x240)
#define PUBL_DX3GCR		(PUBL_REG_BASE + 0x280)

#define PUBL_DX0GCR0	(PUBL_REG_BASE + 0x280)
#define PUBL_DX1GCR0	(PUBL_REG_BASE + 0x300)
#define PUBL_DX2GCR0	(PUBL_REG_BASE + 0x380)
#define PUBL_DX3GCR0	(PUBL_REG_BASE + 0x400)


#define PUBL_DX0BDLR2	(PUBL_REG_BASE + 0x2a4)
#define PUBL_DX1BDLR2	(PUBL_REG_BASE + 0x324)
#define PUBL_DX2BDLR2	(PUBL_REG_BASE + 0x3a4)
#define PUBL_DX3BDLR2	(PUBL_REG_BASE + 0x424)
#else
#define PUBL_RIDR           (PUBL_REG_BASE+0x00*4) // R   - Revision Identification Register
#define PUBL_PIR            (PUBL_REG_BASE+0x01*4) // R/W - PHY Initialization Register
#define PUBL_PGCR           (PUBL_REG_BASE+0x02*4) // R/W - PHY General Configuration Register
#define PUBL_PGSR           (PUBL_REG_BASE+0x03*4) // R   - PHY General Status Register
#define PUBL_DLLGCR         (PUBL_REG_BASE+0x04*4) // R/W - DLL General Control Register
#define PUBL_ACDLLCR        (PUBL_REG_BASE+0x05*4) // R/W - AC DLL Control Register
#define PUBL_PTR0           (PUBL_REG_BASE+0x06*4) // R/W - PHY Timing Register 0
#define PUBL_PTR1           (PUBL_REG_BASE+0x07*4) // R/W - PHY Timing Register 1
#define PUBL_PTR2           (PUBL_REG_BASE+0x08*4) // R/W - PHY Timing Register 2
#define PUBL_ACIOCR         (PUBL_REG_BASE+0x09*4) // R/W - AC I/O Configuration Register
#define PUBL_DXCCR          (PUBL_REG_BASE+0x0A*4) // R/W - DATX8 I/O Configuration Register
#define PUBL_DSGCR          (PUBL_REG_BASE+0x0B*4) // R/W - DFI Configuration Register
#define PUBL_DCR            (PUBL_REG_BASE+0x0C*4) // R/W - DRAM Configuration Register
#define PUBL_DTPR0          (PUBL_REG_BASE+0x0D*4) // R/W - SDRAM Timing Parameters Register 0
#define PUBL_DTPR1          (PUBL_REG_BASE+0x0E*4) // R/W - SDRAM Timing Parameters Register 1
#define PUBL_DTPR2          (PUBL_REG_BASE+0x0F*4) // R/W - SDRAM Timing Parameters Register 2
#define PUBL_MR0            (PUBL_REG_BASE+0x10*4) // R/W - Mode Register
#define PUBL_MR1            (PUBL_REG_BASE+0x11*4) // R/W - Ext}ed Mode Register
#define PUBL_MR2            (PUBL_REG_BASE+0x12*4) // R/W - Ext}ed Mode Register 2
#define PUBL_MR3            (PUBL_REG_BASE+0x13*4) // R/W - Ext}ed Mode Register 3
#define PUBL_ODTCR          (PUBL_REG_BASE+0x14*4) // R/W - ODT Configuration Register
#define PUBL_DTAR           (PUBL_REG_BASE+0x15*4) // R/W - Data Training Address Register
#define PUBL_DTDR0          (PUBL_REG_BASE+0x16*4) // R/W - Data Training Data Register 0
#define PUBL_DTDR1          (PUBL_REG_BASE+0x17*4) // R/W - Data Training Data Register 1
#define PUBL_DCUAR          (PUBL_REG_BASE+0X30*4) // R/W - DCU Address Resiter
#define PUBL_DCUDR          (PUBL_REG_BASE+0x31*4) // R/W - DCU Data Register
#define PUBL_DCURR          (PUBL_REG_BASE+0x32*4) // R/W - DCU Run Register
#define PUBL_DCULR          (PUBL_REG_BASE+0x33*4) // R/W - DCU Loop Register
#define PUBL_DCUGCR         (PUBL_REG_BASE+0x34*4) // R/W - DCU General Configuration Register
#define PUBL_DCUTPR         (PUBL_REG_BASE+0x35*4) // R/W - DCU Timing Parameters Registers
#define PUBL_DCUSR0         (PUBL_REG_BASE+0x36*4) // R   - DCU Status Register 0
#define PUBL_DCUSR1         (PUBL_REG_BASE+0x37*4) // R   - DCU Status Register 1
#define PUBL_BISTRR         (PUBL_REG_BASE+0x40*4) // R/W - BIST Run Register
#define PUBL_BISTMSKR0      (PUBL_REG_BASE+0x41*4) // R/W - BIST Mask Register 0
#define PUBL_BISTMSKR1      (PUBL_REG_BASE+0x42*4) // R/W - BIST Mask Register 1
#define PUBL_BISTWCR        (PUBL_REG_BASE+0x43*4) // R/W - BIST Word Count Register
#define PUBL_BISTLSR        (PUBL_REG_BASE+0x44*4) // R/W - BIST LFSR Seed Register
#define PUBL_BISTAR0        (PUBL_REG_BASE+0x45*4) // R/W - BIST Address Register 0
#define PUBL_BISTAR1        (PUBL_REG_BASE+0x46*4) // R/W - BIST Address Register 1
#define PUBL_BISTAR2        (PUBL_REG_BASE+0x47*4) // R/W - BIST Address Register 2
#define PUBL_BISTUDPR       (PUBL_REG_BASE+0x48*4) // R/W - BIST User Data Pattern Register
#define PUBL_BISTGSR        (PUBL_REG_BASE+0x49*4) // R   - BIST General Status Register
#define PUBL_BISTWER        (PUBL_REG_BASE+0x4A*4) // R   - BIST Word Error Register
#define PUBL_BISTBER0       (PUBL_REG_BASE+0x4B*4) // R   - BIST Bit Error Register 0
#define PUBL_BISTBER1       (PUBL_REG_BASE+0x4C*4) // R   - BIST Bit Error Register 1
#define PUBL_BISTBER2       (PUBL_REG_BASE+0x4D*4) // R   - BIST Bit Error Register 2
#define PUBL_BISTWCSR       (PUBL_REG_BASE+0x4E*4) // R   - BIST Word Count Status Register
#define PUBL_BISTFWR0       (PUBL_REG_BASE+0x4F*4) // R   - BIST Fail Word Register 0
#define PUBL_BISTFWR1       (PUBL_REG_BASE+0x50*4) // R   - BIST Fail Word Register 1
#define PUBL_ZQ0CR0         (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ0CR1         (PUBL_REG_BASE+0x61*4) // R/W - ZQ 0 Impedance Control Register 1
#define PUBL_ZQ0SR0         (PUBL_REG_BASE+0x62*4) // R   - ZQ 0 Impedance Status Register 0
#define PUBL_ZQ0SR1         (PUBL_REG_BASE+0x63*4) // R   - ZQ 0 Impedance Status Register 1
#define PUBL_ZQ1CR0         (PUBL_REG_BASE+0x64*4) // R/W - ZQ 1 Impedance Control Register 0
#define PUBL_ZQ1CR1         (PUBL_REG_BASE+0x65*4) // R/W - ZQ 1 Impedance Control Register 1
#define PUBL_ZQ1SR0         (PUBL_REG_BASE+0x66*4) // R   - ZQ 1 Impedance Status Register 0
#define PUBL_ZQ1SR1         (PUBL_REG_BASE+0x67*4) // R   - ZQ 1 Impedance Status Register 1
#define PUBL_ZQ2CR0         (PUBL_REG_BASE+0x68*4) // R/W - ZQ 2 Impedance Control Register 0
#define PUBL_ZQ2CR1         (PUBL_REG_BASE+0x69*4) // R/W - ZQ 2 Impedance Control Register 1
#define PUBL_ZQ2SR0         (PUBL_REG_BASE+0x6A*4) // R   - ZQ 2 Impedance Status Register 0
#define PUBL_ZQ2SR1         (PUBL_REG_BASE+0x6B*4) // R   - ZQ 2 Impedance Status Register 1
#define PUBL_ZQ3CR0         (PUBL_REG_BASE+0x6C*4) // R/W - ZQ 3 Impedance Control Register 0
#define PUBL_ZQ3CR1         (PUBL_REG_BASE+0x6D*4) // R/W - ZQ 3 Impedance Control Register 1
#define PUBL_ZQ3SR0         (PUBL_REG_BASE+0x6E*4) // R   - ZQ 3 Impedance Status Register 0
#define PUBL_ZQ3SR1         (PUBL_REG_BASE+0x6F*4) // R   - ZQ 3 Impedance Status Register 1
#define PUBL_DX0GCR         (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX0GSR0        (PUBL_REG_BASE+0x71*4) // R   - DATX8 0 General Status Register
#define PUBL_DX0GSR1        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0DQTR        (PUBL_REG_BASE+0x74*4) // R/W - DATX8 0 DQ Timing Register
#define PUBL_DX0DQSTR       (PUBL_REG_BASE+0x75*4) // R/W - DATX8 0 DQS Timing Register
#define PUBL_DX1GCR         (PUBL_REG_BASE+0x80*4) // R   - DATX8 1 General Configration Register
#define PUBL_DX1GSR0        (PUBL_REG_BASE+0x81*4) // R   - DATX8 1 General Status Register
#define PUBL_DX1GSR1        (PUBL_REG_BASE+0x82*4) // R   - DATX8 1 General Status Register
#define PUBL_DX1DLLCR       (PUBL_REG_BASE+0x83*4) // R   - DATX8 1 DLL Control Register
#define PUBL_DX1DQTR        (PUBL_REG_BASE+0x84*4) // R/W - DATX8 1 DQ Timing Register
#define PUBL_DX1DQSTR       (PUBL_REG_BASE+0x85*4) // R/W - DATX8 1 DQS Timing Register
#define PUBL_DX2GCR         (PUBL_REG_BASE+0x90*4) // R   - DATX8 2 General Configration Register
#define PUBL_DX2GSR0        (PUBL_REG_BASE+0x91*4) // R   - DATX8 2 General Status Register
#define PUBL_DX2GSR1        (PUBL_REG_BASE+0x92*4) // R   - DATX8 2 General Status Register
#define PUBL_DX2DLLCR       (PUBL_REG_BASE+0x93*4) // R   - DATX8 2 DLL Control Register
#define PUBL_DX2DQTR        (PUBL_REG_BASE+0x94*4) // R/W - DATX8 2 DQ Timing Register
#define PUBL_DX2DQSTR       (PUBL_REG_BASE+0x95*4) // R/W - DATX8 2 DQS Timing Register
#define PUBL_DX3GCR         (PUBL_REG_BASE+0xA0*4) // R   - DATX8 3 General Configration Register
#define PUBL_DX3GSR0        (PUBL_REG_BASE+0xA1*4) // R   - DATX8 3 General Status Register
#define PUBL_DX3GSR1        (PUBL_REG_BASE+0xA2*4) // R   - DATX8 3 General Status Register
#define PUBL_DX3DLLCR       (PUBL_REG_BASE+0xA3*4) // R   - DATX8 3 DLL Control Register
#define PUBL_DX3DQTR        (PUBL_REG_BASE+0xA4*4) // R/W - DATX8 3 DQ Timing Register
#define PUBL_DX3DQSTR       (PUBL_REG_BASE+0xA5*4) // R/W - DATX8 3 DQS Timing Register
#define PUBL_DX4GCR         (PUBL_REG_BASE+0xB0*4) // R   - DATX8 4 General Configration Register
#define PUBL_DX4GSR0        (PUBL_REG_BASE+0xB1*4) // R   - DATX8 4 General Status Register
#define PUBL_DX4GSR1        (PUBL_REG_BASE+0xB2*4) // R   - DATX8 4 General Status Register
#define PUBL_DX4DLLCR       (PUBL_REG_BASE+0xB3*4) // R   - DATX8 4 DLL Control Register
#define PUBL_DX4DQTR        (PUBL_REG_BASE+0xB4*4) // R/W - DATX8 4 DQ Timing Register
#define PUBL_DX4DQSTR       (PUBL_REG_BASE+0xB5*4) // R/W - DATX8 4 DQS Timing Register
#define PUBL_DX5GCR         (PUBL_REG_BASE+0xC0*4) // R   - DATX8 5 General Configration Register
#define PUBL_DX5GSR0        (PUBL_REG_BASE+0xC1*4) // R   - DATX8 5 General Status Register
#define PUBL_DX5GSR1        (PUBL_REG_BASE+0xC2*4) // R   - DATX8 5 General Status Register
#define PUBL_DX5DLLCR       (PUBL_REG_BASE+0xC3*4) // R   - DATX8 5 DLL Control Register
#define PUBL_DX5DQTR        (PUBL_REG_BASE+0xC4*4) // R/W - DATX8 5 DQ Timing Register
#define PUBL_DX5DQSTR       (PUBL_REG_BASE+0xC5*4) // R/W - DATX8 5 DQS Timing Register
#define PUBL_DX6GCR         (PUBL_REG_BASE+0xD0*4) // R   - DATX8 6 General Configration Register
#define PUBL_DX6GSR0        (PUBL_REG_BASE+0xD1*4) // R   - DATX8 6 General Status Register
#define PUBL_DX6GSR1        (PUBL_REG_BASE+0xD2*4) // R   - DATX8 6 General Status Register
#define PUBL_DX6DLLCR       (PUBL_REG_BASE+0xD3*4) // R   - DATX8 6 DLL Control Register
#define PUBL_DX6DQTR        (PUBL_REG_BASE+0xD4*4) // R/W - DATX8 6 DQ Timing Register
#define PUBL_DX6DQSTR       (PUBL_REG_BASE+0xD5*4) // R/W - DATX8 6 DQS Timing Register
#define PUBL_DX7GCR         (PUBL_REG_BASE+0xE0*4) // R   - DATX8 7 General Configration Register
#define PUBL_DX7GSR0        (PUBL_REG_BASE+0xE1*4) // R   - DATX8 7 General Status Register
#define PUBL_DX7GSR1        (PUBL_REG_BASE+0xE2*4) // R   - DATX8 7 General Status Register
#define PUBL_DX7DLLCR       (PUBL_REG_BASE+0xE3*4) // R   - DATX8 7 DLL Control Register
#define PUBL_DX7DQTR        (PUBL_REG_BASE+0xE4*4) // R/W - DATX8 7 DQ Timing Register
#define PUBL_DX7DQSTR       (PUBL_REG_BASE+0xE5*4) // R/W - DATX8 7 DQS Timing Register
#define PUBL_DX8GCR         (PUBL_REG_BASE+0xF0*4) // R   - DATX8 8 General Configration Register
#define PUBL_DX8GSR0        (PUBL_REG_BASE+0xF1*4) // R   - DATX8 8 General Status Register
#define PUBL_DX8GSR1        (PUBL_REG_BASE+0xF2*4) // R   - DATX8 8 General Status Register
#define PUBL_DX8DLLCR       (PUBL_REG_BASE+0xF3*4) // R   - DATX8 8 DLL Control Register
#define PUBL_DX8DQTR        (PUBL_REG_BASE+0xF4*4) // R/W - DATX8 8 DQ Timing Register
#define PUBL_DX8DQSTR       (PUBL_REG_BASE+0xF5*4) // R/W - DATX8 8 DQS Timing Register
#endif

/******************************************************************************
                            Structure define
******************************************************************************/


/**----------------------------------------------------------------------------*
**                         Compiler Flag                                      **
**----------------------------------------------------------------------------*/
#ifdef   __cplusplus
}
#endif
/**---------------------------------------------------------------------------*/
#endif
// End
