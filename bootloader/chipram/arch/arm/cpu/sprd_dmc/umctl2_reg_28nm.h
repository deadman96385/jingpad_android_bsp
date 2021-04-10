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
#define PUBL_RIDR           (PUBL_REG_BASE+0x00*4) // R   - Revision Identification Register
#define PUBL_PIR            (PUBL_REG_BASE+0x01*4) // R/W - PHY Initialization Register
#define PUBL_PGCR0          (PUBL_REG_BASE+0x02*4) // R/W - PHY General Configuration Register
#define PUBL_PGCR1          (PUBL_REG_BASE+0x03*4) // R/W - PHY General Configuration Register
#define PUBL_PGCR2          (PUBL_REG_BASE+0x04*4) // R/W - PHY General Configuration Register
#define PUBL_PGCR3          (PUBL_REG_BASE+0x05*4) // R/W - PHY General Configuration Registe
#define PUBL_PGSR0          (PUBL_REG_BASE+0x06*4) // R   - PHY General Status Register
#define PUBL_PGSR1          (PUBL_REG_BASE+0x07*4) // R   - PHY General Status Register
#define PUBL_PLLCR          (PUBL_REG_BASE+0x08*4) // R   - PHY General Status Register
#define PUBL_PTR0           (PUBL_REG_BASE+0x09*4) // R/W - PHY Timing Register 0
#define PUBL_PTR1           (PUBL_REG_BASE+0x0A*4) // R/W - PHY Timing Register 1
#define PUBL_PTR2           (PUBL_REG_BASE+0x0B*4) // R/W - PHY Timing Register 2
#define PUBL_PTR3           (PUBL_REG_BASE+0x0C*4) // R/W - PHY Timing Register 1
#define PUBL_PTR4           (PUBL_REG_BASE+0x0D*4) // R/W - PHY Timing Register 2
#define PUBL_ACMDLR         (PUBL_REG_BASE+0x0E*4) // R/W - PHY Timing Register 2
#define PUBL_ACLCDLR        (PUBL_REG_BASE+0x0F*4) // R/W - PHY Timing Register 2
#define PUBL_ACBDLR0        (PUBL_REG_BASE+0x10*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR1        (PUBL_REG_BASE+0x11*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR2        (PUBL_REG_BASE+0x12*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR3        (PUBL_REG_BASE+0x13*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR4        (PUBL_REG_BASE+0x14*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR5        (PUBL_REG_BASE+0x15*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR6        (PUBL_REG_BASE+0x16*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR7        (PUBL_REG_BASE+0x17*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR8        (PUBL_REG_BASE+0x18*4) // R/W - AC I/O Configuration Register
#define PUBL_ACBDLR9        (PUBL_REG_BASE+0x19*4) // R/W - AC I/O Configuration Register
#define PUBL_ACIOCR0        (PUBL_REG_BASE+0x1A*4) // R/W - AC I/O Configuration Register
#define PUBL_ACIOCR1        (PUBL_REG_BASE+0x1B*4) // R/W - AC I/O Configuration Register
#define PUBL_ACIOCR2        (PUBL_REG_BASE+0x1C*4) // R/W - AC I/O Configuration Register
#define PUBL_ACIOCR3        (PUBL_REG_BASE+0x1D*4) // R/W - AC I/O Configuration Register
#define PUBL_ACIOCR4        (PUBL_REG_BASE+0x1E*4) // R/W - AC I/O Configuration Register
#define PUBL_ACIOCR5        (PUBL_REG_BASE+0x1F*4) // R/W - AC I/O Configuration Register
#define PUBL_DXCCR          (PUBL_REG_BASE+0x20*4) // R/W - DATX8 I/O Configuration Register
#define PUBL_DSGCR          (PUBL_REG_BASE+0x21*4) // R/W - DFI Configuration Register
#define PUBL_DCR            (PUBL_REG_BASE+0x22*4) // R/W - DRAM Configuration Register
#define PUBL_DTPR0          (PUBL_REG_BASE+0x23*4) // R/W - SDRAM Timing Parameters Register 0
#define PUBL_DTPR1          (PUBL_REG_BASE+0x24*4) // R/W - SDRAM Timing Parameters Register 1
#define PUBL_DTPR2          (PUBL_REG_BASE+0x25*4) // R/W - SDRAM Timing Parameters Register 2
#define PUBL_DTPR3          (PUBL_REG_BASE+0x26*4) // R/W - SDRAM Timing Parameters Register 2
#define PUBL_MR0            (PUBL_REG_BASE+0x27*4) // R/W - Mode Register
#define PUBL_MR1            (PUBL_REG_BASE+0x28*4) // R/W - Ext}ed Mode Register
#define PUBL_MR2            (PUBL_REG_BASE+0x29*4) // R/W - Ext}ed Mode Register 2
#define PUBL_MR3            (PUBL_REG_BASE+0x2A*4) // R/W - Ext}ed Mode Register 3
#define PUBL_ODTCR          (PUBL_REG_BASE+0x2B*4) // R/W - ODT Configuration Register
#define PUBL_DTCR           (PUBL_REG_BASE+0x2C*4) // R/W - Data Training Address Register
#define PUBL_DTAR0          (PUBL_REG_BASE+0x2D*4) // R/W - Data Training Address Register
#define PUBL_DTAR1          (PUBL_REG_BASE+0x2E*4) // R/W - Data Training Address Register
#define PUBL_DTAR2          (PUBL_REG_BASE+0x2F*4) // R/W - Data Training Address Register
#define PUBL_DTAR3          (PUBL_REG_BASE+0x30*4) // R/W - Data Training Address Register
#define PUBL_DTDR0          (PUBL_REG_BASE+0x31*4) // R/W - Data Training Data Register 0
#define PUBL_DTDR1          (PUBL_REG_BASE+0x32*4) // R/W - Data Training Data Register 1
#define PUBL_DTEDR0         (PUBL_REG_BASE+0x33*4) // R/W - Data Training Data Register 0
#define PUBL_DTEDR1         (PUBL_REG_BASE+0x34*4) // R/W - Data Training Data Register 1
#define PUBL_RDIMMGCR0      (PUBL_REG_BASE+0x35*4) // R/W - Data Training Data Register 0
#define PUBL_RDIMMGCR1      (PUBL_REG_BASE+0x36*4) // R/W - Data Training Data Register 0
#define PUBL_RDIMMCR0       (PUBL_REG_BASE+0x37*4) // R/W - Data Training Data Register 0
#define PUBL_RDIMMCR1       (PUBL_REG_BASE+0x38*4) // R/W - Data Training Data Register 0
#define PUBL_GPR0           (PUBL_REG_BASE+0x39*4) // R/W - Data Training Data Register 1
#define PUBL_GPR1           (PUBL_REG_BASE+0x3A*4) // R/W - Data Training Data Register 1
#define PUBL_GPR0           (PUBL_REG_BASE+0x3B*4) // R/W - Data Training Data Register 1
#define PUBL_GPR1           (PUBL_REG_BASE+0x3C*4) // R/W - Data Training Data Register 1
#define PUBL_DQSDR          (PUBL_REG_BASE+0x3D*4) // R/W - Data Training Data Register 1
#define PUBL_DTMR0          (PUBL_REG_BASE+0x3E*4) // R/W - Data Training Data Register 1
#define PUBL_DTMR1          (PUBL_REG_BASE+0x3F*4) // R/W - Data Training Data Register 1
#define PUBL_DCUAR          (PUBL_REG_BASE+0X60*4) // R/W - DCU Address Resiter
#define PUBL_DCUDR          (PUBL_REG_BASE+0x61*4) // R/W - DCU Data Register
#define PUBL_DCURR          (PUBL_REG_BASE+0x62*4) // R/W - DCU Run Register
#define PUBL_DCULR          (PUBL_REG_BASE+0x63*4) // R/W - DCU Loop Register
#define PUBL_DCUGCR         (PUBL_REG_BASE+0x64*4) // R/W - DCU General Configuration Register
#define PUBL_DCUTPR         (PUBL_REG_BASE+0x65*4) // R/W - DCU Timing Parameters Registers
#define PUBL_DCUSR0         (PUBL_REG_BASE+0x66*4) // R   - DCU Status Register 0
#define PUBL_DCUSR1         (PUBL_REG_BASE+0x67*4) // R   - DCU Status Register 1
#define PUBL_MR11           (PUBL_REG_BASE+0x68*4) // R   - DCU Status Register 1

#define PUBL_BISTRR         (PUBL_REG_BASE+0x70*4) // R/W - BIST Run Register
#define PUBL_BISTWCR        (PUBL_REG_BASE+0x71*4) // R/W - BIST Word Count Register
#define PUBL_BISTMSKR0      (PUBL_REG_BASE+0x72*4) // R/W - BIST Mask Register 0
#define PUBL_BISTMSKR1      (PUBL_REG_BASE+0x73*4) // R/W - BIST Mask Register 1
#define PUBL_BISTMSKR2      (PUBL_REG_BASE+0x74*4) // R/W - BIST Mask Register 1
#define PUBL_BISTLSR        (PUBL_REG_BASE+0x75*4) // R/W - BIST LFSR Seed Register
#define PUBL_BISTAR0        (PUBL_REG_BASE+0x76*4) // R/W - BIST Address Register 0
#define PUBL_BISTAR1        (PUBL_REG_BASE+0x77*4) // R/W - BIST Address Register 1
#define PUBL_BISTAR2        (PUBL_REG_BASE+0x78*4) // R/W - BIST Address Register 2
#define PUBL_BISTUDPR       (PUBL_REG_BASE+0x79*4) // R/W - BIST User Data Pattern Register
#define PUBL_BISTGSR        (PUBL_REG_BASE+0x7A*4) // R   - BIST General Status Register
#define PUBL_BISTWER        (PUBL_REG_BASE+0x7B*4) // R   - BIST Word Error Register
#define PUBL_BISTBER0       (PUBL_REG_BASE+0x7C*4) // R   - BIST Bit Error Register 0
#define PUBL_BISTBER1       (PUBL_REG_BASE+0x7D*4) // R   - BIST Bit Error Register 1
#define PUBL_BISTBER2       (PUBL_REG_BASE+0x7E*4) // R   - BIST Bit Error Register 2
#define PUBL_BISTBER3       (PUBL_REG_BASE+0x7F*4) // R   - BIST Bit Error Register 2

#define PUBL_BISTWCSR       (PUBL_REG_BASE+0x80*4) // R   - BIST Word Count Status Register
#define PUBL_BISTFWR0       (PUBL_REG_BASE+0x81*4) // R   - BIST Fail Word Register 0
#define PUBL_BISTFWR1       (PUBL_REG_BASE+0x82*4) // R   - BIST Fail Word Register 1
#define PUBL_BISTFWR2       (PUBL_REG_BASE+0x83*4) // R   - BIST Fail Word Register 1

#define PUBL_IOVCR0         (PUBL_REG_BASE+0x8E*4) // R   - BIST Fail Word Register 1
#define PUBL_IOVCR1         (PUBL_REG_BASE+0x8F*4) // R   - BIST Fail Word Register 1

#define PUBL_ZQCR           (PUBL_REG_BASE+0x90*4) // R/W - ZQ 0 Impedance Control Register 0

#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x91*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ0DR          (PUBL_REG_BASE+0x92*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ0SR          (PUBL_REG_BASE+0x93*4) // R/W - ZQ 0 Impedance Control Register 0

#define PUBL_ZQ1PR          (PUBL_REG_BASE+0x95*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ1DR          (PUBL_REG_BASE+0x96*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ1SR          (PUBL_REG_BASE+0x97*4) // R/W - ZQ 0 Impedance Control Register 0

#define PUBL_ZQ2PR          (PUBL_REG_BASE+0x99*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ2DR          (PUBL_REG_BASE+0x9A*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ2SR          (PUBL_REG_BASE+0x9B*4) // R/W - ZQ 0 Impedance Control Register 0

#define PUBL_ZQ3PR          (PUBL_REG_BASE+0x9D*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ3DR          (PUBL_REG_BASE+0x9E*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0#define PUBL_ZQ0PR          (PUBL_REG_BASE+0x60*4) // R/W - ZQ 0 Impedance Control Register 0
#define PUBL_ZQ3SR          (PUBL_REG_BASE+0x9F*4) // R/W - ZQ 0 Impedance Control Register 0

#define PUBL_DX0GCR0        (PUBL_REG_BASE+0xA0*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX0GCR1        (PUBL_REG_BASE+0xA1*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX0GCR2        (PUBL_REG_BASE+0xA2*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX0GCR3        (PUBL_REG_BASE+0xA3*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX0GSR0        (PUBL_REG_BASE+0xA4*4) // R   - DATX8 0 General Status Register
#define PUBL_DX0GSR1        (PUBL_REG_BASE+0xA5*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX0GSR2        (PUBL_REG_BASE+0xA6*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX0BDLCR0      (PUBL_REG_BASE+0xA7*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0BDLCR1      (PUBL_REG_BASE+0xA8*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0BDLCR2      (PUBL_REG_BASE+0xA9*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0BDLCR3      (PUBL_REG_BASE+0xAA*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0BDLCR4      (PUBL_REG_BASE+0xAB*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0BDLCR5      (PUBL_REG_BASE+0xAC*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0BDLCR6      (PUBL_REG_BASE+0xAD*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX0LCDLR0      (PUBL_REG_BASE+0xAE*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0LCDLR1      (PUBL_REG_BASE+0xAF*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0LCDLR2      (PUBL_REG_BASE+0xB0*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0MDLR        (PUBL_REG_BASE+0xB1*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX0GTR         (PUBL_REG_BASE+0xB2*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register


#define PUBL_DX1GCR0        (PUBL_REG_BASE+0xC0*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX1GCR1        (PUBL_REG_BASE+0xC1*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX1GCR2        (PUBL_REG_BASE+0xC2*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX1GCR3        (PUBL_REG_BASE+0xC3*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX1GSR0        (PUBL_REG_BASE+0xC4*4) // R   - DATX8 0 General Status Register
#define PUBL_DX1GSR1        (PUBL_REG_BASE+0xC5*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX1GSR2        (PUBL_REG_BASE+0xC6*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX1BDLCR0      (PUBL_REG_BASE+0xC7*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1BDLCR1      (PUBL_REG_BASE+0xC8*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1BDLCR2      (PUBL_REG_BASE+0xC9*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1BDLCR3      (PUBL_REG_BASE+0xCA*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1BDLCR4      (PUBL_REG_BASE+0xCB*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1BDLCR5      (PUBL_REG_BASE+0xCC*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1BDLCR6      (PUBL_REG_BASE+0xCD*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX1LCDLR0      (PUBL_REG_BASE+0xCE*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1LCDLR1      (PUBL_REG_BASE+0xCF*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1LCDLR2      (PUBL_REG_BASE+0xD0*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1MDLR        (PUBL_REG_BASE+0xD1*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX1GTR         (PUBL_REG_BASE+0xD2*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register



#define PUBL_DX2GCR0        (PUBL_REG_BASE+0xE0*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX2GCR1        (PUBL_REG_BASE+0xE1*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX2GCR2        (PUBL_REG_BASE+0xE2*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX2GCR3        (PUBL_REG_BASE+0xE3*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX2GSR0        (PUBL_REG_BASE+0xE4*4) // R   - DATX8 0 General Status Register
#define PUBL_DX2GSR1        (PUBL_REG_BASE+0xE5*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX2GSR2        (PUBL_REG_BASE+0xE6*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX2BDLCR0      (PUBL_REG_BASE+0xE7*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2BDLCR1      (PUBL_REG_BASE+0xE8*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2BDLCR2      (PUBL_REG_BASE+0xE9*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2BDLCR3      (PUBL_REG_BASE+0xEA*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2BDLCR4      (PUBL_REG_BASE+0xEB*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2BDLCR5      (PUBL_REG_BASE+0xEC*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2BDLCR6      (PUBL_REG_BASE+0xED*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX2LCDLR0      (PUBL_REG_BASE+0xEE*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2LCDLR1      (PUBL_REG_BASE+0xEF*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2LCDLR2      (PUBL_REG_BASE+0xF0*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2MDLR        (PUBL_REG_BASE+0xF1*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX2GTR         (PUBL_REG_BASE+0xF2*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register



#define PUBL_DX3GCR0        (PUBL_REG_BASE+0x100*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX3GCR1        (PUBL_REG_BASE+0x101*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX3GCR2        (PUBL_REG_BASE+0x102*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX3GCR3        (PUBL_REG_BASE+0x103*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX3GSR0        (PUBL_REG_BASE+0x104*4) // R   - DATX8 0 General Status Register
#define PUBL_DX3GSR1        (PUBL_REG_BASE+0x105*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX3GSR2        (PUBL_REG_BASE+0x106*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX3BDLCR0      (PUBL_REG_BASE+0x107*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3BDLCR1      (PUBL_REG_BASE+0x108*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3BDLCR2      (PUBL_REG_BASE+0x109*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3BDLCR3      (PUBL_REG_BASE+0x10A*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3BDLCR4      (PUBL_REG_BASE+0x10B*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3BDLCR5      (PUBL_REG_BASE+0x10C*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3BDLCR6      (PUBL_REG_BASE+0x10D*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX3LCDLR0      (PUBL_REG_BASE+0x10E*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3LCDLR1      (PUBL_REG_BASE+0x10F*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3LCDLR2      (PUBL_REG_BASE+0x110*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3MDLR        (PUBL_REG_BASE+0x111*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX3GTR         (PUBL_REG_BASE+0x112*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#if 0
#define PUBL_DX4GCR0        (PUBL_REG_BASE+0x10*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX4GCR1        (PUBL_REG_BASE+0x10*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX4GCR2        (PUBL_REG_BASE+0x10*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX4GCR3        (PUBL_REG_BASE+0x10*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX4GSR0        (PUBL_REG_BASE+0x10*4) // R   - DATX8 0 General Status Register
#define PUBL_DX4GSR1        (PUBL_REG_BASE+0x10*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX4GSR2        (PUBL_REG_BASE+0x10*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX4BDLCR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4BDLCR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4BDLCR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4BDLCR3      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4BDLCR4      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4BDLCR5      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4BDLCR6      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX4LCDLR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4LCDLR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4LCDLR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4MDLR        (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX4GTR         (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register


#define PUBL_DX5GCR0        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX5GCR1        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX5GCR2        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX5GCR3        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX5GSR0        (PUBL_REG_BASE+0x71*4) // R   - DATX8 0 General Status Register
#define PUBL_DX5GSR1        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX5GSR2        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX5BDLCR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5BDLCR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5BDLCR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5BDLCR3      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5BDLCR4      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5BDLCR5      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5BDLCR6      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX5LCDLR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5LCDLR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5LCDLR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5MDLR        (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX5GTR         (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX6GCR0        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX6GCR1        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX6GCR2        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX6GCR3        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX6GSR0        (PUBL_REG_BASE+0x71*4) // R   - DATX8 0 General Status Register
#define PUBL_DX6GSR1        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX6GSR2        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX6BDLCR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6BDLCR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6BDLCR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6BDLCR3      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6BDLCR4      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6BDLCR5      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6BDLCR6      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX6LCDLR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6LCDLR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6LCDLR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6MDLR        (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX6GTR         (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register


#define PUBL_DX7GCR0        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX7GCR1        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX7GCR2        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX7GCR3        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX7GSR0        (PUBL_REG_BASE+0x71*4) // R   - DATX8 0 General Status Register
#define PUBL_DX7GSR1        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX7GSR2        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX7BDLCR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7BDLCR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7BDLCR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7BDLCR3      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7BDLCR4      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7BDLCR5      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7BDLCR6      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX7LCDLR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7LCDLR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7LCDLR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7MDLR        (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX7GTR         (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register


#define PUBL_DX8GCR0        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX8GCR1        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX8GCR2        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register
#define PUBL_DX8GCR3        (PUBL_REG_BASE+0x70*4) // R/W - DATX8 0 General Configuration Register

#define PUBL_DX8GSR0        (PUBL_REG_BASE+0x71*4) // R   - DATX8 0 General Status Register
#define PUBL_DX8GSR1        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1
#define PUBL_DX8GSR2        (PUBL_REG_BASE+0x72*4) // R   - DATX8 0 General Status Register 1

#define PUBL_DX8BDLCR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8BDLCR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8BDLCR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8BDLCR3      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8BDLCR4      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8BDLCR5      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8BDLCR6      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register

#define PUBL_DX8LCDLR0      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8LCDLR1      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8LCDLR2      (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8MDLR        (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
#define PUBL_DX8GTR         (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register#define PUBL_DX0DLLCR       (PUBL_REG_BASE+0x73*4) // R   - DATX8 0 DLL Control Register
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

