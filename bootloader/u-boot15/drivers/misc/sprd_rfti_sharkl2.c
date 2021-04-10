/*
  * sprd_rfti_sharkl2.c , add for Ap read wcdma transciver chipid
  */
#include <common.h>

#include <asm/arch/common.h>
#include <asm/arch/sprd_reg.h>


#define RFTI_APB_CFG_RFSPI_EN_ADDR     (SPRD_MDAR_PHYS + 0x2C)
#define RFTI_APB_RFTI_SPI_CTRL_ADDR    (SPRD_MDAR_PHYS + 0x30)
#define RFTI_APB_PAD_RFTI_SPI_SEL_ADDR (SPRD_MDAR_PHYS + 0xf0)

#define RFTI_APB_RFTI_SBI_CMD0_ADDR    (SPRD_MDAR_PHYS + 0x240)
#define RFTI_APB_RFTI_SBI_CMD1_ADDR    (SPRD_MDAR_PHYS + 0x244)
#define RFTI_APB_RFTI_SBI_RDATA_ADDR   (SPRD_MDAR_PHYS + 0x248)

#define INVALID_CHIP_ID (0xFFFFFFFF)
#define PUBCP_POWERON_MASK (BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN\
	| BIT_PMU_APB_PD_PUBCP_SYS_AUTO_SHUTDOWN_EN)

/* #define MDAR_DEBUG */

#define debugreg(reg) debugf("reg = 0x%x, value = 0x%x\n" , reg, REG32(reg))

/* reg must support bit op */
#define REG32_SET_BIT(reg, bit)  REG32(reg + 0x1000) = bit
#define REG32_CLR_BIT(reg, bit)  REG32(reg + 0x2000) = bit

static u32 back_regs[5];
static u32 g_rfchipId = INVALID_CHIP_ID;

static void mdar_debugreg(void)
{
	debugreg(SPRD_PIN_PHYS+0x30);
	debugreg(SPRD_PIN_PHYS+0x34);
	debugreg(SPRD_PIN_PHYS+0x38);

	debugreg(RFTI_APB_CFG_RFSPI_EN_ADDR);
	debugreg(RFTI_APB_RFTI_SPI_CTRL_ADDR);
	debugreg(RFTI_APB_PAD_RFTI_SPI_SEL_ADDR);

	debugreg(REG_PMU_APB_PD_PUBCP_SYS_CFG);
}

static void mdar_rfti_sbi_enter(void)
{
#ifdef MDAR_DEBUG
	mdar_debugreg();
	debugf("\n");
#endif

	/* backup some reg */
	back_regs[0] = REG32(REG_AON_APB_APB_EB1);
	back_regs[1] = REG32(REG_AON_APB_CLK_EB0);
	back_regs[2] = REG32(RFTI_APB_PAD_RFTI_SPI_SEL_ADDR);
	back_regs[3] = REG32(RFTI_APB_CFG_RFSPI_EN_ADDR);
	back_regs[4] = REG32(RFTI_APB_RFTI_SPI_CTRL_ADDR);

	/* enable sbi */
	REG32_SET_BIT(REG_AON_APB_APB_EB1, BIT_AON_APB_MDAR_EB);
	REG32_SET_BIT(REG_AON_APB_CLK_EB0, BIT_AON_APB_RFTI_SBI_EB);

	/* reset sbi */
	CHIP_REG_OR(REG_AON_APB_APB_RST1, BIT_AON_APB_MDAR_SOFT_RST);
	CHIP_REG_OR(REG_AON_APB_MDAR_SOFT_RST, BIT_AON_APB_RFTI_SBI_SOFT_RST);
	udelay(50);
	CHIP_REG_AND(REG_AON_APB_APB_RST1, ~BIT_AON_APB_MDAR_SOFT_RST);
	CHIP_REG_AND(REG_AON_APB_MDAR_SOFT_RST, ~BIT_AON_APB_RFTI_SBI_SOFT_RST);

	/* init spi */
	REG32(RFTI_APB_PAD_RFTI_SPI_SEL_ADDR) = 0x1;
	REG32(RFTI_APB_CFG_RFSPI_EN_ADDR) = 0x1;
	REG32(RFTI_APB_RFTI_SPI_CTRL_ADDR) = 0x5;

#ifdef MDAR_DEBUG
	mdar_debugreg();
#endif
}

static void mdar_rfti_sbi_exit(void)
{
	/* restore some reg */
	REG32(REG_AON_APB_APB_EB1) = back_regs[0];
	REG32(REG_AON_APB_CLK_EB0) = back_regs[1];
	REG32(RFTI_APB_PAD_RFTI_SPI_SEL_ADDR) = back_regs[2];
	REG32(RFTI_APB_CFG_RFSPI_EN_ADDR) = back_regs[3];
	REG32(RFTI_APB_RFTI_SPI_CTRL_ADDR) = back_regs[4];

#ifdef MDAR_DEBUG
	debugf("\n");
	mdar_debugreg();
#endif
}

static void mdar_rfti_sbi_write(u16 addr, u16 data)
{
	u32 i;
	u32 reg_val,reg_val_spi = 0;

#ifdef MDAR_DEBUG
	debugf("addr = 0x%x, data = 0x%x\n", addr, data);
#endif

	reg_val_spi = (addr << 16) | (data << 0);
	reg_val_spi &= ~(1<<31);
	REG32(RFTI_APB_RFTI_SBI_CMD0_ADDR) = reg_val_spi;/* write data */
	REG32(RFTI_APB_RFTI_SBI_CMD1_ADDR) = 0x1;/* triger send start */
	for(i = 0; i < 100; i++);
	do{
		reg_val = CHIP_REG_GET(RFTI_APB_RFTI_SBI_RDATA_ADDR);
	}while(reg_val & (1<<31));
}

static u32 mdar_rfti_sbi_read(u16 addr)
{
	u16 data;
	u32 i, reg_val, reg_val_spi = 0;

	reg_val_spi = (addr << 16);
	reg_val_spi |= (1 << 31);
	REG32(RFTI_APB_RFTI_SBI_CMD0_ADDR) = reg_val_spi;
	REG32(RFTI_APB_RFTI_SBI_CMD1_ADDR) = 0x1;

	for(i = 0; i < 100; i++);
	do{
		reg_val = CHIP_REG_GET(RFTI_APB_RFTI_SBI_RDATA_ADDR);
	}while(reg_val & (1<<31));

	data = reg_val & 0xffff;
	printf("addr = 0x%x, reg_val = 0x%x, data = 0x%x\n", addr, reg_val, data);

	return data;
}


static u32 DRV_RF_ReadChipID (void)
{
	u32 id;
	int b_pubcp_powerdown;
	int retry = 5;

	if (INVALID_CHIP_ID != g_rfchipId)
		return g_rfchipId;

	//init mdar spi control reg
	mdar_rfti_sbi_enter();

	/* read rfchip id, must make sure pubcp ower on */
	b_pubcp_powerdown = (REG32(REG_PMU_APB_PD_PUBCP_SYS_CFG)
		& BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN);
	if (b_pubcp_powerdown) {
		REG32_CLR_BIT(REG_PMU_APB_PD_PUBCP_SYS_CFG,
			BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN);
#ifdef MDAR_DEBUG
		debugreg(REG_PMU_APB_PD_PUBCP_SYS_CFG);
#endif
		udelay(1000); /* must delay enough time */
	}

	//init RFIC SPI control
	mdar_rfti_sbi_write(0x1001, 0x0001);
	//SPIA -> CoreA
	mdar_rfti_sbi_write (0x1000, 0x0002);

	/* if id ==0, try 5 times agian */
	id = mdar_rfti_sbi_read(0x7F);
	while(id == 0 && retry) {
		mdar_debugreg();
		id = mdar_rfti_sbi_read(0x7F);
		retry--;
	}

	/* restore pubcp power */
	if (b_pubcp_powerdown) {
		REG32_SET_BIT(REG_PMU_APB_PD_PUBCP_SYS_CFG,
			BIT_PMU_APB_PD_PUBCP_SYS_FORCE_SHUTDOWN);
	}

#ifdef MDAR_DEBUG
	debugf("chipid = 0x%x\n", id);
#endif

	g_rfchipId = (id&0xFFFF);

	mdar_rfti_sbi_exit();

	return g_rfchipId;
}

/*
Navajo: 0x742,0x743,0x744, (0x740 ~ 0x74f) return 1
Boca:	0x6c0,0x6c1, (0x6c0~0x6cf)return 0
other: return 0xff
*/
u8 DRV_RF_Get_Type(void)
{
	u32 id;
	u8 type = 0xff; /* default value, not a invalid type */

	id = DRV_RF_ReadChipID();

	if (id > 0x73F && id < 0x750)
		type = 1;
	else if (id > 0x6BF && id < 0x6D0)
		type = 0;

	debugf("rf id = 0x%x, type = %d\n", id, type);

	return type;
}
