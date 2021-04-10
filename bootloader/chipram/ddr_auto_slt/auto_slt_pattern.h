#include <common.h>

//#define ARM_BURST_PATTERN_SUPPORT_ON
//#define PRODUCT_AUTO_SLT_CODE_SUPPORT_ON
#define DDR_BIST_TEST_SUPPORT_ON
//#define DDR_DCU_SUPPORT_ON
#define PI_SI_CASE		1

#define PATTERN_SIA_0			0x00000000
#define PATTERN_SIA_1			0xffffffff

#define PI_SI_MAGIC_HEADER		0x7777bbbb
#define PI_SI_MAGIC_END			0xbbbb7777

#define DCU_MAGIC_HEADER		0x6666dddd
#define DCU_MAGIC_END			0xdddd6666

#ifdef CONFIG_SCX35LT8
#define DEBUG_INFO_BASE		0x101f20
#else
#define DEBUG_INFO_BASE		0x1f20
#endif

typedef struct{
    volatile unsigned int magic_header;
	volatile unsigned int pi_si_case_num;
    volatile unsigned int magic_end;
}PI_SI_PATTERN_TYP;

typedef struct
{
	volatile unsigned int umctl_mstr;	/* 0x0000 master register*/
	volatile unsigned int umctl_stat;	/* 0x0004 operating mode status*/
	volatile unsigned int umctl_resv0[2];	/* 0x0008 ~ 0x000c*/
	volatile unsigned int umctl_mrctrl[2];	/* 0x0010 ~ 0x0014 mode register control*/
	volatile unsigned int umctl_mrstat;	/* 0x0018 mode register status*/
	volatile unsigned int umctl_resv1;	/* 0x001c */
	volatile unsigned int umctl_derateen;	/* 0x0020 temperature derate enable*/
	volatile unsigned int umctl_derateint;	/* 0x0024 temperature derate interval*/
	volatile unsigned int umctl_resv2[2];	/* 0x0028 ~ 0x002c */
	volatile unsigned int umctl_pwrctl;	/* 0x0030 low power control*/
	volatile unsigned int umctl_pwrtmg;	/* 0x0034 low power timing*/
	volatile unsigned int umctl_hwlpctl;	/* 0x0038 hardware low power control*/
	volatile unsigned int umctl_resv3[5];	/* 0x003c ~ 0x004c */
	volatile unsigned int umctl_rfshctl[3];	/* 0x0050 ~ 0x0058 refresh control*/
	volatile unsigned int umctl_resv4;	/* 0x005c */
	volatile unsigned int umctl_rfshctl3;	/* 0x0060 refresh control*/
	volatile unsigned int umctl_rfshtmg;	/* 0x0064 refresh timing*/
	volatile unsigned int umctl_resv5[2];	/* 0x0068 ~ 0x006c */
	volatile unsigned int umctl_ecccfg[2];	/* 0x0070 ~ 0x0074 ecc configruation*/
	volatile unsigned int umctl_eccstat;	/* 0x0078 ecc status*/
	volatile unsigned int umctl_eccclr;	/* 0x007c ecc clear*/
	volatile unsigned int umctl_eccerrcnt;	/* 0x0080 ecc error count*/
	volatile unsigned int umctl_ecccaddr[2];/* 0x0084 ~ 0x0088 ecc corrected error address*/
	volatile unsigned int umctl_ecccsyn[3];	/* 0x008c ~ 0x0094 ecc corrected syndrome*/
	volatile unsigned int umctl_eccbitmask[3];	/* 0x0098 ~ 0x00a0 ecc corrected data bit mask*/
	volatile unsigned int umctl_eccuaddr[2];/* 0x00a4 ~ 0x00a8 ecc unorrected error address*/
	volatile unsigned int umctl_eccusyn[3];	/* 0x00ac ~ 0x00b4 ecc uncorrected syndrome*/
	volatile unsigned int umctl_eccpoisonaddr[2];	/* 0x00b8 ~ 0x00bc ecc data poisoning address*/
	volatile unsigned int umctl_parctl;	/* 0x00c0 parity control*/
	volatile unsigned int umctl_parstat;	/* 0x00c4 parity status*/
	volatile unsigned int umctl_resv6[2];	/* 0x00c8 ~ 0x00cc */
	volatile unsigned int umctl_init[8];	/* 0x00d0 ~ 0x00ec sdram initialization*/
	volatile unsigned int umctl_dimmctl;	/* 0x00f0 dimm control*/
	volatile unsigned int umctl_rankctl;	/* 0x00f4 rank control*/
	volatile unsigned int umctl_resv7[2];	/* 0x00f8 ~ 0x00fc*/
	volatile unsigned int umctl_dramtmg[12];/* 0x0100 ~ 0x012c sdram timing*/
	volatile unsigned int umctl_resv8[20];	/* 0x0130 ~ 0x017c */
	volatile unsigned int umctl_zqctl[3];	/* 0x0180 ~ 0x0188 zq control*/
	volatile unsigned int umctl_zqstat;	/* 0x018c zq status*/
	volatile unsigned int umctl_dfitmg[2];	/* 0x0190 ~ 0x0194 dfi timing*/
	volatile unsigned int umctl_dfilpcfg[2];/* 0x0198 ~ 0x019c dfi low power configruation*/
	volatile unsigned int umctl_dfiupd[4];	/* 0x01a0 ~ 0x01ac dfi update*/
	volatile unsigned int umctl_dfimisc;	/* 0x01b0 dfi miscellaneous control*/
	volatile unsigned int umctl_resv9[3];	/* 0x01b4 ~ 0x01bc */
	volatile unsigned int umctl_dbictl;	/* 0x01c0 dm/dbi control*/
	volatile unsigned int umctl_resv10[3];	/* 0x01c4 ~ 0x01cc */
	volatile unsigned int umctl_trainctl[3];/* 0x01d0 ~ 0x01d8 phy eval training control*/
	volatile unsigned int umctl_trainstat;	/* 0x01dc phy eval training status */
	volatile unsigned int umctl_resv11[8];	/* 0x01e0 ~ 0x01fc */
	volatile unsigned int umctl_addrmap[9];	/* 0x0200 ~ 0x0220 address map */
	volatile unsigned int umctl_resv12[7];	/* 0x0224 ~ 0x023c */
	volatile unsigned int umctl_odtcfg;	/* 0x0240 odt configruation */
	volatile unsigned int umctl_odtmap;	/* 0x0244 odt/rank map */
	volatile unsigned int umctl_resv13[2];	/* 0x0248 ~ 0x024c */
	volatile unsigned int umctl_sched;	/* 0x0250 scheduler control */
	volatile unsigned int umctl_resv14;	/* 0x0254 */
	volatile unsigned int umctl_perfhpr[2];	/* 0x0258 ~ 0x025c high priority read*/
	volatile unsigned int umctl_perflpr[2];	/* 0x0260 ~ 0x0264 low priority read */
	volatile unsigned int umctl_perfwr[2];	/* 0x0268 ~ 0x026c write cam */
	volatile unsigned int umctl_resv15[36];	/* 0x0270 ~ 0x02fc */
	volatile unsigned int umctl_dbg[2];	/* 0x0300 ~ 0x0304 debug*/
	volatile unsigned int umctl_dbgcam;	/* 0x0308 cam debug*/
	volatile unsigned int umctl_resv16[60];	/* 0x030c ~ 0x03f8 */
	volatile unsigned int umctl_pstat;	/* 0x03fc */
	volatile unsigned int umctl_pccfg;	/* 0x0400 port common configruation*/
	volatile unsigned int umctl_pcfgr0;	/* 0x0404 port 0 configruation read */
	volatile unsigned int umctl_pcfgw0;	/* 0x0408 port 0 configruation write*/
	volatile unsigned int umctl_pcfgc0;	/* 0x040c port 0 common configruation*/
	volatile unsigned int umctl_pcfgidmaskch0_0;	/* 0x0410 channel 0 port 0 configruation*/
	volatile unsigned int umctl_pcfgidvaluech0_0;	/* 0x0414 channel 0 port 0 configruation*/
	volatile unsigned int umctl_resv17[30];	/* 0x0418 ~ 0x048c */
	volatile unsigned int umctl_pctrl0;	/* 0x0490 port control */
}DMC_UMCTL_REG_INFO_T,*DMC_UMCTL_REG_INFO_PTR_T;

typedef struct
{
	volatile unsigned int publ_ridr;	/* 0x0000 revision identification*/
	volatile unsigned int publ_pir;		/* 0x0004 phy initialization*/
	volatile unsigned int publ_pgcr[4];	/* 0x0008 ~ 0x0014 phy general configruation*/
	volatile unsigned int publ_pgsr[2];	/* 0x0018 ~ 0x001c phy general status*/
	volatile unsigned int publ_pllcr;	/* 0x0020 pll control*/
	volatile unsigned int publ_ptr[5];	/* 0x0024 ~ 0x0034 phy timing*/
	volatile unsigned int publ_acmdlr;	/* 0x0038 ac master delay line*/
	volatile unsigned int publ_aclcdlr;	/* 0x003c ac local calibrated delay line*/
	volatile unsigned int publ_acbdlr[10];	/* 0x0040 ~ 0x0064 ac bit delay line*/
	volatile unsigned int publ_aciocr[6];	/* 0x0068 ~ 0x007c ac i/o configruation*/
	volatile unsigned int publ_dxccr;	/* 0x0080 datx8 common configruation*/
	volatile unsigned int publ_dsgcr;	/* 0x0084 datx8 system general configruation*/
	volatile unsigned int publ_dcr;		/* 0x0088 dram configruation*/
	volatile unsigned int publ_dtpr[4];	/* 0x008c ~ 0x0098 dram timing parameters*/
	volatile unsigned int publ_mr[4];	/* 0x009c ~ 0x00a8 mode register*/
	volatile unsigned int publ_odtcr;	/* 0x00ac odt configruation*/
	volatile unsigned int publ_dtcr;	/* 0x00b0 data training configruation*/
	volatile unsigned int publ_dtar[4];	/* 0x00b4 ~ 0x00c0 data training address*/
	volatile unsigned int publ_dtdr[2];	/* 0x00c4 ~ 0x00c8 data training data*/
	volatile unsigned int publ_dtedr[2];	/* 0x00cc ~ 0x00d0 data training address */
	volatile unsigned int publ_rdimmgcr[2];	/* 0x00d4 ~ 0x00d8 rdimm general configruation*/
	volatile unsigned int publ_rdimmcr[2];	/* 0x00dc ~ 0x00e0 rdimm control*/
	volatile unsigned int publ_gpr[2];	/* 0x00e4 ~ 0x00e8 general purpose*/
	volatile unsigned int publ_catr[2];	/* 0x00ec ~ 0x00f0 catr*/
	volatile unsigned int publ_dqsdr;	/* 0x00f4 dqs drift detection */
	volatile unsigned int publ_dtmr[2];	/* 0x00f8 ~ 0x00fc data training mask*/
	volatile unsigned int publ_resv0[32];	/* 0x0100 ~ 0x017c */
	volatile unsigned int publ_dcuar;	/* 0x0180 DCU address*/
	volatile unsigned int publ_dcudr;	/* 0x0184 DCU data*/
	volatile unsigned int publ_dcurr;	/* 0x0188 DCU run*/
	volatile unsigned int publ_dculr;	/* 0x018c DCU loop*/
	volatile unsigned int publ_dcugcr;	/* 0x0190 DCU general configruation*/
	volatile unsigned int publ_dcutpr;	/* 0x0194 DCU timing parameters*/
	volatile unsigned int publ_dcusr[2];	/* 0x0198 ~ 0x019c DCU status*/
	volatile unsigned int publ_resv1[8];	/* 0x01a0 ~ 0x01bc */
	volatile unsigned int publ_bistrr;	/* 0x01c0 BIST run*/
	volatile unsigned int publ_bistwcr;	/* 0x01c4 BIST word count*/
	volatile unsigned int publ_bistmskr[3];	/* 0x01c8 ~ 0x01d0 BIST mask*/
	volatile unsigned int publ_bistlsr;	/* 0x01d4 BIST LFSR seed*/
	volatile unsigned int publ_bistar[3];	/* 0x01d8 ~ 0x01e0 BIST address*/
	volatile unsigned int publ_bistudpr;	/* 0x01e4 BIST User data pattern*/
	volatile unsigned int publ_bistgsr;	/* 0x01e8 BIST general status*/
	volatile unsigned int publ_bistwer;	/* 0x01ec BIST word error*/
	volatile unsigned int publ_bistber[4];	/* 0x01f0 ~ 0x01fc BIST bit error*/
	volatile unsigned int publ_bistwcsr;	/* 0x0200 BIST word count status*/
	volatile unsigned int publ_bistfwr[3];	/* 0x0204 ~ 0x020c BIST fail word*/
	volatile unsigned int publ_resv2[10];	/* 0x0210 ~ 0x0234 catr*/
	volatile unsigned int publ_iovcr[2];	/* 0x0238 ~ 0x023c IO VREF control*/
	volatile unsigned int publ_zqcr;	/* 0x0240 zq impedance control*/
	volatile unsigned int publ_zq0pr;	/* 0x0244 zq impedance program*/
	volatile unsigned int publ_zq0dr;	/* 0x0248 zq impedance data*/
	volatile unsigned int publ_zq0sr;	/* 0x024c zq impedance status*/
	volatile unsigned int publ_resv3;	/* 0x0250 */
	volatile unsigned int publ_zq1pr;	/* 0x0254 zq impedance program*/
	volatile unsigned int publ_zq1dr;	/* 0x0258 zq impedance data*/
	volatile unsigned int publ_zq1sr;	/* 0x025c zq impedance status*/
	volatile unsigned int publ_resv4;	/* 0x0260 */
	volatile unsigned int publ_zq2pr;	/* 0x0264 zq impedance program*/
	volatile unsigned int publ_zq2dr;	/* 0x0268 zq impedance data*/
	volatile unsigned int publ_zq2sr;	/* 0x026c zq impedance status*/
	volatile unsigned int publ_resv5;	/* 0x0270 */
	volatile unsigned int publ_zq3pr;	/* 0x0274 zq impedance program*/
	volatile unsigned int publ_zq3dr;	/* 0x0278 zq impedance data*/
	volatile unsigned int publ_zq3sr;	/* 0x027c zq impedance status*/
	volatile unsigned int publ_dx0gcr[4];	/* 0x0280 ~ 0x028c datx8 general config*/
	volatile unsigned int publ_dx0gsr[3];	/* 0x0290 ~ 0x0298 datx8 general status*/
	volatile unsigned int publ_dx0bdlr[7];	/* 0x029c ~ 0x02b4 datx8 bit delay line*/
	volatile unsigned int publ_dx0lcdlr[3];	/* 0x02b8 ~ 0x02c0 datx8 local cal*/
	volatile unsigned int publ_dx0mdlr;	/* 0x02c4 datx8 master delay line*/
	volatile unsigned int publ_dx0gtr;	/* 0x02c8 datx8 general timing*/
	volatile unsigned int publ_resv6[13];	/* 0x02cc ~ 0x02fc */
	volatile unsigned int publ_dx1gcr[4];	/* 0x0300 ~ 0x030c datx8 general config*/
	volatile unsigned int publ_dx1gsr[3];	/* 0x0310 ~ 0x0318 datx8 general status*/
	volatile unsigned int publ_dx1bdlr[7];	/* 0x031c ~ 0x0334 datx8 bit delay line*/
	volatile unsigned int publ_dx1lcdlr[3];	/* 0x0338 ~ 0x0340 datx8 local cal*/
	volatile unsigned int publ_dx1mdlr;	/* 0x0344 datx8 master delay line*/
	volatile unsigned int publ_dx1gtr;	/* 0x0348 datx8 general timing*/
	volatile unsigned int publ_resv7[13];	/* 0x034c ~ 0x037c */
	volatile unsigned int publ_dx2gcr[4];	/* 0x0380 ~ 0x038c datx8 general config*/
	volatile unsigned int publ_dx2gsr[3];	/* 0x0390 ~ 0x0398 datx8 general status*/
	volatile unsigned int publ_dx2bdlr[7];	/* 0x039c ~ 0x03b4 datx8 bit delay line*/
	volatile unsigned int publ_dx2lcdlr[3];	/* 0x03b8 ~ 0x03c0 datx8 local cal*/
	volatile unsigned int publ_dx2mdlr;	/* 0x03c4 datx8 master delay line*/
	volatile unsigned int publ_dx2gtr;	/* 0x03c8 datx8 general timing*/
	volatile unsigned int publ_resv8[13];	/* 0x03cc ~ 0x03fc */
	volatile unsigned int publ_dx3gcr[4];	/* 0x0400 ~ 0x040c datx8 general config*/
	volatile unsigned int publ_dx3gsr[3];	/* 0x0410 ~ 0x0418 datx8 general status*/
	volatile unsigned int publ_dx3bdlr[7];	/* 0x041c ~ 0x0434 datx8 bit delay line*/
	volatile unsigned int publ_dx3lcdlr[3];	/* 0x0438 ~ 0x0440 datx8 local cal*/
	volatile unsigned int publ_dx3mdlr;	/* 0x0444 datx8 master delay line*/
	volatile unsigned int publ_dx3gtr;	/* 0x0448 datx8 general timing*/
	volatile unsigned int publ_resv9[13];	/* 0x044c ~ 0x047c */
	volatile unsigned int publ_dx4gcr[4];	/* 0x0480 ~ 0x048c datx8 general config*/
	volatile unsigned int publ_dx4gsr[3];	/* 0x0490 ~ 0x0498 datx8 general status*/
	volatile unsigned int publ_dx4bdlr[7];	/* 0x049c ~ 0x04b4 datx8 bit delay line*/
	volatile unsigned int publ_dx4lcdlr[3];	/* 0x04b8 ~ 0x04c0 datx8 local cal*/
	volatile unsigned int publ_dx4mdlr;	/* 0x04c4 datx8 master delay line*/
	volatile unsigned int publ_dx4gtr;	/* 0x04c8 datx8 general timing*/
	volatile unsigned int publ_resv10[13];	/* 0x04cc ~ 0x04fc */
	volatile unsigned int publ_dx5gcr[4];	/* 0x0500 ~ 0x050c datx8 general config*/
	volatile unsigned int publ_dx5gsr[3];	/* 0x0510 ~ 0x0518 datx8 general status*/
	volatile unsigned int publ_dx5bdlr[7];	/* 0x051c ~ 0x0534 datx8 bit delay line*/
	volatile unsigned int publ_dx5lcdlr[3];	/* 0x0538 ~ 0x0540 datx8 local cal*/
	volatile unsigned int publ_dx5mdlr;	/* 0x0544 datx8 master delay line*/
	volatile unsigned int publ_dx5gtr;	/* 0x0548 datx8 general timing*/
	volatile unsigned int publ_resv11[13];	/* 0x054c ~ 0x057c */
	volatile unsigned int publ_dx6gcr[4];	/* 0x0580 ~ 0x058c datx8 general config*/
	volatile unsigned int publ_dx6gsr[3];	/* 0x0590 ~ 0x0598 datx8 general status*/
	volatile unsigned int publ_dx6bdlr[7];	/* 0x059c ~ 0x05b4 datx8 bit delay line*/
	volatile unsigned int publ_dx6lcdlr[3];	/* 0x05b8 ~ 0x05c0 datx8 local cal*/
	volatile unsigned int publ_dx6mdlr;	/* 0x05c4 datx8 master delay line*/
	volatile unsigned int publ_dx6gtr;	/* 0x05c8 datx8 general timing*/
	volatile unsigned int publ_resv12[13];	/* 0x05cc ~ 0x05fc */
	volatile unsigned int publ_dx7gcr[4];	/* 0x0600 ~ 0x060c datx8 general config*/
	volatile unsigned int publ_dx7gsr[3];	/* 0x0610 ~ 0x0618 datx8 general status*/
	volatile unsigned int publ_dx7bdlr[7];	/* 0x061c ~ 0x0634 datx8 bit delay line*/
	volatile unsigned int publ_dx7lcdlr[3];	/* 0x0638 ~ 0x0640 datx8 local cal*/
	volatile unsigned int publ_dx7mdlr;	/* 0x0644 datx8 master delay line*/
	volatile unsigned int publ_dx7gtr;	/* 0x0648 datx8 general timing*/
	volatile unsigned int publ_resv13[13];	/* 0x064c ~ 0x067c */
	volatile unsigned int publ_dx8gcr[4];	/* 0x0680 ~ 0x068c datx8 general config*/
	volatile unsigned int publ_dx8gsr[3];	/* 0x0690 ~ 0x0698 datx8 general status*/
	volatile unsigned int publ_dx8bdlr[7];	/* 0x069c ~ 0x06b4 datx8 bit delay line*/
	volatile unsigned int publ_dx8lcdlr[3];	/* 0x06b8 ~ 0x06c0 datx8 local cal*/
	volatile unsigned int publ_dx8mdlr;	/* 0x06c4 datx8 master delay line*/
	volatile unsigned int publ_dx8gtr;	/* 0x06c8 datx8 general timing*/
	volatile unsigned int publ_resv14[13];	/* 0x06cc ~ 0x06fc */
}DMC_PUBL_REG_INFO_T,*DMC_PUBL_REG_INFO_PTR_T;


typedef struct{
	unsigned int rpt;
	unsigned int dtp;
	unsigned int tag;
	unsigned int cmd;
	unsigned int rank;
	unsigned int bank;
	unsigned int addr;
	unsigned int mask;
	unsigned int data[4];
}DCU_CMD_CACHE_TYP;

typedef struct{
    volatile unsigned int magic_header;
	uint32 dcu_pattern0[4];
	uint32 dcu_pattern1[4];
	uint32 dcu_pattern2[4];
	uint32 dcu_pattern3[4];
	uint32 dcu_pattern4[4];
	uint32 dcu_pattern5[4];
	uint32 dcu_pattern6[4];
	uint32 dcu_pattern7[4];
    volatile unsigned int magic_end;
}DCU_PATTERN_TYP;

