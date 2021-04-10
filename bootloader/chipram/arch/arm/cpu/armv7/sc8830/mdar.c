
#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <adi.h>
#include <asm/arch/sprd_reg.h>

/*----------------------------------------------------------------------------*/
//\u5b8f\u5b9a\u4e49
//

#define CHIP_REG_OR(reg_addr, value)    (*(volatile uint32 *)(reg_addr) |= (uint32)(value))
#define CHIP_REG_AND(reg_addr, value)   (*(volatile uint32 *)(reg_addr) &= (uint32)(value))
#define CHIP_REG_GET(reg_addr)          (*(volatile uint32 *)(reg_addr))
#define CHIP_REG_SET(reg_addr, value)   (*(volatile uint32 *)(reg_addr)  = (uint32)(value))

#define		CTL_BASE_AON_APB	0x402E0000
#define		REG_AON_APB_EB1		( CTL_BASE_AON_APB + 0x0004 )
#define		REG_AON_APB_RST1	( CTL_BASE_AON_APB + 0x000C )

#define		MDAR_EB			(BIT_14)
#define		RFTI_SBI_EB		(BIT_15)
#define		MDAR_SOFT_RST		(BIT_12)	//pike aon_apb
#define		RFTI_SBI_SOFT_RST	(BIT_13)

/*----------------------------------------------------------------------------*/
//\u679a\u4e3e\u5b9a\u4e49
//
typedef enum {
	RFSPI1_CEN0 = 0,
	RFSPI1_CEN1,
} SBI_CEN_E;

/*udelay(1000) means about 1.65ms*/
#define udelay(x)	\
	do { \
		volatile int i; \
		int cnt = x; \
		for (i=0; i<cnt; i++);\
	} while(0);

/*----------------------------------------------------------------------------*/
// Timer_2\u7684Delay\u51fd\u6570
//
void DelayUs(uint32 us)
{
	udelay(us);
}

/*----------------------------------------------------------------------------*/
//MDAR SPI \u83b7\u53d6channel\u63a7\u5236\u6743
//

void MDAR_RFlvds_Spi_channel_get(void)
{
	uint32 reg_val;

	reg_val = CHIP_REG_GET(REG_MDAR_CFG0);
	reg_val &= ~(0x1 << 31);
	CHIP_REG_SET(REG_MDAR_CFG0, reg_val);

	reg_val = CHIP_REG_GET(REG_MDAR_RFSPI_CFG);
	reg_val &= ~(0x7 << 10);
	CHIP_REG_SET(REG_MDAR_RFSPI_CFG, reg_val);

	reg_val = CHIP_REG_GET(REG_MDAR_RFSPI_CFG);
	reg_val &= ~(0x7 << 13);
	CHIP_REG_SET(REG_MDAR_RFSPI_CFG, reg_val);

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_CFG0);
	reg_val |= (0x1 << 31);
	CHIP_REG_SET(REG_MDAR_RFTI_CFG0, reg_val);

}

/*----------------------------------------------------------------------------*/
//MDAR SPI Channel release
//

void MDAR_RFlvds_Spi_channel_release(void)
{
	uint32 reg_val;

	reg_val = CHIP_REG_GET(REG_MDAR_CFG0);
	reg_val &= ~(0x1 << 31);
	CHIP_REG_SET(REG_MDAR_CFG0, reg_val);

	reg_val = CHIP_REG_GET(REG_MDAR_RFSPI_CFG);
	reg_val &= ~(0x7 << 10);
	CHIP_REG_SET(REG_MDAR_RFSPI_CFG, reg_val);

	reg_val = CHIP_REG_GET(REG_MDAR_RFSPI_CFG);
	reg_val &= ~(0x7 << 13);
	CHIP_REG_SET(REG_MDAR_RFSPI_CFG, reg_val);

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_CFG0);
	reg_val &= ~(0x1 << 31);
	CHIP_REG_SET(REG_MDAR_RFTI_CFG0, reg_val);

}

/*----------------------------------------------------------------------------*/
//MDAR\u6a21\u5757\u7684\u521d\u59cb\u5316\u51fd\u6570
//

int32 MDAR_init(void)
{
	uint32 i;

	//enable MDAR
	REG32(REG_AON_APB_EB1) |= (MDAR_EB | RFTI_SBI_EB);
	REG32(REG_AON_APB_RST1) |= (MDAR_SOFT_RST | RFTI_SBI_SOFT_RST);
	for (i = 0; i < 100; i++) ;
	REG32(REG_AON_APB_RST1) &= ~(MDAR_SOFT_RST | RFTI_SBI_SOFT_RST);

	MDAR_RFlvds_Spi_channel_get();

	return 0;
}

/*----------------------------------------------------------------------------*/
//MDAR\u6a21\u5757\u7684deinit
//
int32 MDAR_deinit(void)
{
	uint32 i;

	MDAR_RFlvds_Spi_channel_release();

	REG32(REG_AON_APB_EB1) &= ~(MDAR_EB | RFTI_SBI_EB);

	return 0;
}

/*----------------------------------------------------------------------------*/
//MDAR \u7528\u5185\u90e8spi \u8bfb
//

uint16 MDAR_SBI1_rd(SBI_CEN_E sbi_cen, uint16 spi_raddr)
{
	uint32 reg_val, reg_val_spi = 0;
	uint16 spi_rdata;

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_SBI1_CMD1);

	if (sbi_cen == RFSPI1_CEN1) {
		reg_val |= 0x1 << 0;
		CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD1, reg_val);
	} else {
		reg_val &= ~(0x1 << 0);
		CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD1, reg_val);
	}

	reg_val_spi |= (spi_raddr << 16 | BIT_31);
	reg_val_spi &= 0xffff0000;
	CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD0, reg_val_spi);

	CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD2, 0x1);

	DelayUs(10);
	do {
		reg_val = CHIP_REG_GET(REG_MDAR_RFTI_SBI1_RDATA);

	} while ((reg_val & BIT_31) == 1);

	spi_rdata = (uint16) (reg_val & 0xffff);

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_SBI1_CMD1);
	reg_val &= ~(0x1 << 0);
	CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD1, reg_val);

	return spi_rdata;

}

uint16 MDAR_Private_Spi1_rd(SBI_CEN_E rfti1_sle1, uint16 spi_raddr)
{
	uint32 reg_val, reg_val_rd;
	uint16 spi_rdata;

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_CFG0);

	if (rfti1_sle1 == RFSPI1_CEN1) {
		reg_val |= (0x1 << 30);
		CHIP_REG_SET(REG_MDAR_RFTI_CFG0, reg_val);
		spi_rdata = MDAR_SBI1_rd(RFSPI1_CEN1, spi_raddr);
	} else {
		reg_val &= ~(0x1 << 30);
		CHIP_REG_SET(REG_MDAR_RFTI_CFG0, reg_val);
		spi_rdata = MDAR_SBI1_rd(RFSPI1_CEN0, spi_raddr);
	}

	return spi_rdata;
}

/*----------------------------------------------------------------------------*/
//MDAR \u7528\u5185\u90e8spi \u8bfb
//

uint16 MDAR_SBI1_wr(SBI_CEN_E sbi_cen, uint16 spi_waddr, uint16 spi_wdata)
{
	uint32 reg_val, reg_val_spi = 0;

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_SBI1_CMD1);

	if (sbi_cen == RFSPI1_CEN1) {
		reg_val |= (0x1 << 0);
		CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD1, reg_val);
	} else {
		reg_val &= ~(0x1 << 0);
		CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD1, reg_val);
	}

	reg_val_spi |= (spi_waddr << 16) | (spi_wdata << 0);
	reg_val_spi &= ~BIT_31;
	CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD0, reg_val_spi);

	CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD2, 0x1);

	DelayUs(10);
	do {
		reg_val = CHIP_REG_GET(REG_MDAR_RFTI_SBI1_RDATA);

	} while ((reg_val & BIT_31) == 1);

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_SBI1_CMD1);
	reg_val &= ~(0x1 << 0);
	CHIP_REG_SET(REG_MDAR_RFTI_SBI1_CMD1, reg_val);

}

int32 MDAR_Private_Spi1_wr(SBI_CEN_E rfti1_sle1, uint16 spi_waddr,
			   uint16 spi_wdata)
{
	uint32 reg_val;

	reg_val = CHIP_REG_GET(REG_MDAR_RFTI_CFG0);

	if (rfti1_sle1 == RFSPI1_CEN1) {
		reg_val |= (0x1 << 30);
		CHIP_REG_SET(REG_MDAR_RFTI_CFG0, reg_val);
		MDAR_SBI1_wr(RFSPI1_CEN1, spi_waddr, spi_wdata);
	} else {
		reg_val &= ~(0x1 << 30);
		CHIP_REG_SET(REG_MDAR_RFTI_CFG0, reg_val);
		MDAR_SBI1_wr(RFSPI1_CEN0, spi_waddr, spi_wdata);
	}

}

void set_3532_26M_out(void)
{
	uint16 rreg;

	CHIP_REG_SET(0x402A0020,0x5E000);
	CHIP_REG_SET(0x402A0024,0x5E000);
	CHIP_REG_SET(0x402A0028,0x5E000);
	MDAR_init();
}

void set_rfti(int clock_in,int tune)
{
/*chiparm size exceed limit,comment the function*/
#if 0
	/*step 1: configration to 26M*/
	uint16 rreg;
	//MDAR_Private_Spi1_wr(RFSPI1_CEN0, 0x0040, 0x5);
	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F1D);//Open clocks. clkk_rflvds_impedence_cal ,clk_lth,clk_xo;
        MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F1D,
                             rreg | (1 << 4) | (1 << 1) | (1 << 0));
        rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F45);//Change the RFLVDS-PLL to integer mode.
        MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F45, rreg & (~(1 << 0)));
        rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F42);
        MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F42, rreg & (~(3 << 4)));
        rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F10);
        MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F10, rreg | (1 << 2));
        rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F72);
        MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F72, rreg & (~(7 << 0)));//change RPLL to integer mode

	if(26000000 == clock_in){//input 26M untune
		MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F78, (0x20<<8));
		MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F74, 0x20);
	}

	if(32000000 == clock_in){//input 32M
		MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F78, (0x20<<8));
		MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F74, 0x1A);
	}
	/*RPLL power on*/
	rreg = REG32(REG_AON_APB_RPLL_CFG0);
	REG32(REG_AON_APB_RPLL_CFG0) = rreg | (BITS_RPLL_PD_CTRL(2));
	DelayUs(500);

	/*step2 config PLL/clock  to 26M */
	rreg = REG32(REG_AON_APB_RPLL_CFG0);
	REG32(REG_AON_APB_RPLL_CFG0) = rreg | (BIT_CLK26MHZ_MUXTUNE_EN);

	/*step 3 config LVDSRF_PLL */
        rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F42);
        MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F42, rreg | (1 << 6));

	rreg = REG32(REG_AON_APB_RPLL_CFG0);
	REG32(REG_AON_APB_RPLL_CFG0) = rreg & ~(BIT_LVDS_LVPLL_REF_SEL_CTRL);

	if(tune){
	/* LVDS_PLL is 32M */
		REG32(REG_AON_APB_RPLL_CFG0) = rreg & ~(BIT_LVDS_LVPLL_REF_SEL);
	}
	else{
	/* from untuned 26m */
		REG32(REG_AON_APB_RPLL_CFG0) = rreg & ~(BIT_LVDS_LVPLL_REF_SEL);
	}

        rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F42);
        MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F42, rreg & (~(1 << 6)));
#endif
}

void set_rfti_untune26(void)
{
	uint16 rreg;
	volatile uint32 reg_val;

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F7E);
	rreg &= ~(0x1 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F7E, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F78);
	rreg &= ~((0xf << 0) | (0x3f << 8));
	rreg |= ((0x4 << 0) | (0x28 << 8));
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F78, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F75);
	rreg &= ~(0x3f << 0);
	rreg |= (0x28 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F75, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F76);
	rreg &= ~(0x7f << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F76, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F77);
	rreg &= ~(0xffff << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F77, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F79);
	rreg &= ~(0x7fff << 0);
	rreg |= (0x3ffc << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F79, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F7B);
	rreg &= ~(0xfff << 0);
	rreg |= (0x800 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F7B, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F7C);
	rreg &= ~(0xfff << 0);
	rreg |= (0x800 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F7C, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F7D);
	rreg &= ~(0xffff << 0);
	rreg |= (0x8000 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F7D, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F7A);
	rreg &= ~(0xffff << 0);
	rreg |= (0x8000 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F7A, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F70);
	rreg &= ~(0x1 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F70, rreg);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F71);
	rreg &= ~(0x1 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F71, rreg);
	DelayUs(20);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F71);
	rreg |= (0x1 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F71, rreg);
	DelayUs(20);

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F71);
	rreg &= ~(0x1 << 0);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F71, rreg);
	/*RPLL power on*/
	rreg = REG32(REG_AON_APB_RPLL_CFG0);
	REG32(REG_AON_APB_RPLL_CFG0) = rreg | (BITS_RPLL_PD_CTRL(2));
	DelayUs(500);

	/*step2 config PLL/clock  to 26M */
	rreg = REG32(REG_AON_APB_RPLL_CFG0);
	REG32(REG_AON_APB_RPLL_CFG0) = rreg | (BIT_CLK26MHZ_MUXTUNE_EN);

	/*step 3 config LVDSRF_PLL */
	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F42);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F42, rreg | (1 << 6));

	rreg = REG32(REG_AON_APB_RPLL_CFG0);
	REG32(REG_AON_APB_RPLL_CFG0) = rreg & ~(BIT_LVDS_LVPLL_REF_SEL_CTRL);
	REG32(REG_AON_APB_RPLL_CFG0) = rreg | BIT_LVDS_LVPLL_REF_SEL;

	rreg = MDAR_Private_Spi1_rd(RFSPI1_CEN1, 0x3F42);
	MDAR_Private_Spi1_wr(RFSPI1_CEN1, 0x3F42, rreg & (~(1 << 6)));

	/*CLK26M_SEL[0] choose untuned26m for safe consideration*/
	reg_val = REG32(REG_AON_APB_CLK26M_CFG);
	reg_val &= ~1;
	REG32(REG_AON_APB_CLK26M_CFG) = reg_val;
}

void sine1_config(int type)
{
	volatile uint32 reg_val;
	set_3532_26M_out();

	reg_val = REG32(REG_AON_APB_CLK26M_CFG);
        reg_val |= 1;
        REG32(REG_AON_APB_CLK26M_CFG) = reg_val;

	CHIP_REG_SET(0x402B010c,CHIP_REG_GET(0x402B010C) &(~ 0x01));
	if (CONFIG_SIN1_32M_TUNED == type) {
		set_rfti(32000000,1);
	} else if(CONFIG_SIN1_26M_UNTUNED == type) {
		set_rfti_untune26();
	}
	CHIP_REG_SET(0x402B0134,CHIP_REG_GET(0x402B0134) | 0x02);
}
