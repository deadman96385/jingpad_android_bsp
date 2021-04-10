#include <config.h>

#ifndef SCI_ADDR
#define SCI_ADDR(_b_, _o_)		((unsigned int)(_b_) + (_o_))
#endif

#define REGS_AON_APB_BASE				0x402e0000
#define REG_AON_APB_VSP_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x315c)/*VSP_NOC_CTRL*/
#define REG_AON_APB_CAM_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x3160)/*CAM_NOC_CTRL*/
#define REG_AON_APB_DISP_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x3164)/*DISP_NOC_CTRL*/
#define REG_AON_APB_GSP_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x3168)/*GSP_NOC_CTRL*/
#define REG_AON_APB_WTL_CP_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x316C)/*WTL_CP_NOC_CTRL*/
#define REG_AON_APB_LACC_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x3170)/*LACC_NOC_CTRL*/
#define REG_AON_APB_AGCP_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x3174)/*AGCP_NOC_CTRL*/
#define REG_AON_APB_PCP_NOC_CTRL			SCI_ADDR(REGS_AON_APB_BASE, 0x3178)/*PCP_NOC_CTRL*/

#define REGS_AON_SEC_APB_BASE				0x40880000
#define REG_AON_SEC_APB_CA53_NOC_CTRL			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0054)/*CA53_NOC_CTRL*/
#define REG_AON_SEC_APB_AP_NOC_CTRL			SCI_ADDR(REGS_AON_SEC_APB_BASE, 0x0058)/*AP_NOC_CTRL*/

typedef enum {
	DDR_8G = 0,
	DDR_1G,
	DDR_1_5G,
	DDR_2G,
	DDR_3G,
	DDR_4G
} DDR_CAPACITY;

typedef enum {
	NORMAL_MODE = 0,
	FULL_MODE,
	MIXED_MODE
} INTERLEAVE_MODE;

typedef enum {
	SIZE_64 = 0,
	SIZE_128
} INTERLEAVE_SEL;

#define DDR_CAPACITY_OFFSET	9
#define DDR_CAPACITY_MASK	(0x7 << DDR_CAPACITY_OFFSET)

#define INTERLEAVE_MODE_OFFSET	1
#define INTERLEAVE_MODE_MASK	(0x3 << INTERLEAVE_MODE_OFFSET)

#define INTERLEAVE_SEL_OFFSET	0
#define INTERLEAVE_SEL_MASK	(0x1 << INTERLEAVE_SEL_OFFSET)

/*
 * when config CA53 noc ctrl register, cpu should be in security mode
 */
void ca53_noc_ctrl(unsigned int cap, unsigned int mode, unsigned int sel)
{
	unsigned int val;

	val = *(volatile unsigned int *)REG_AON_SEC_APB_CA53_NOC_CTRL;
	val &= ~(DDR_CAPACITY_MASK | INTERLEAVE_MODE_MASK |
		INTERLEAVE_SEL_MASK);
	val |= (cap << DDR_CAPACITY_OFFSET) | (mode << INTERLEAVE_MODE_OFFSET)
		| (sel << INTERLEAVE_SEL_OFFSET);
	*(volatile unsigned int *)REG_AON_SEC_APB_CA53_NOC_CTRL = val;
}

void misc_noc_ctrl(unsigned long base, unsigned int mode, unsigned int sel)
{
	unsigned int val;

	val = *(volatile unsigned int *)base;
	val &= ~(INTERLEAVE_MODE_MASK | INTERLEAVE_SEL_MASK);
	val |= (mode << INTERLEAVE_MODE_OFFSET) |
		(sel << INTERLEAVE_SEL_OFFSET);
	*(volatile unsigned int *)base = val;
}

void noc_init(void)
{
	/*
	 * DDR_CAPACITY=2G, MIXED_MODE, 64 Bytes interleave size
	 */
#ifdef CONFIG_DUAL_DDR_3G
	ca53_noc_ctrl(DDR_3G, MIXED_MODE, SIZE_64);
#else
	ca53_noc_ctrl(DDR_2G, MIXED_MODE, SIZE_64);
#endif
	/*
	 * Other subsystem noc config
	 */
	misc_noc_ctrl(REG_AON_SEC_APB_AP_NOC_CTRL, MIXED_MODE, SIZE_64);
#ifdef CONFIG_SP9860_3GFHD
	/* special board, MM need to be set as MIXED_MODE for saving power */
	misc_noc_ctrl(REG_AON_APB_VSP_NOC_CTRL, MIXED_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_CAM_NOC_CTRL, MIXED_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_GSP_NOC_CTRL, MIXED_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_DISP_NOC_CTRL, MIXED_MODE, SIZE_64);
#else
	misc_noc_ctrl(REG_AON_APB_VSP_NOC_CTRL, FULL_MODE, SIZE_64);
	#ifdef CONFIG_WHALE2
	misc_noc_ctrl(REG_AON_APB_CAM_NOC_CTRL, FULL_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_GSP_NOC_CTRL, FULL_MODE, SIZE_64);
	#else
	misc_noc_ctrl(REG_AON_APB_CAM_NOC_CTRL, MIXED_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_GSP_NOC_CTRL, MIXED_MODE, SIZE_64);
	#endif
	misc_noc_ctrl(REG_AON_APB_DISP_NOC_CTRL, FULL_MODE, SIZE_64);
#endif

	misc_noc_ctrl(REG_AON_APB_WTL_CP_NOC_CTRL, MIXED_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_LACC_NOC_CTRL, MIXED_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_AGCP_NOC_CTRL, MIXED_MODE, SIZE_64);
	misc_noc_ctrl(REG_AON_APB_PCP_NOC_CTRL, MIXED_MODE, SIZE_64);
}
