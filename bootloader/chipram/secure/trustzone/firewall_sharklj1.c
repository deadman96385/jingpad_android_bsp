#include <common.h>
#include<security/trustzone/trustzone.h>

//add AonRamSec set
#define REG_TZMA_FIRST_ADDR   0x4042F000
#define REG_TZMA_LAST_ADDR    0x4042F004

#define MEM_FIRST_ADDR (0x0)
#define MEM_LAST_ADDR (0x5000FFFF)

//add secure rd wr reg
#define REG_MASTER_FW_AP_RD   0x40421E00
#define REG_MASTER_FW_AP_WR   0x40421E04

//add emmc usb sd ce1 set
#define BIT(x) (1<<(x))

#define SD_RD_SEC (BIT(13)|BIT(12))
#define SD_WR_SEC (BIT(13)|BIT(12))

#define EMMC_RD_SEC (BIT(15)|BIT(14))
#define EMMC_WR_SEC (BIT(15)|BIT(14))

#define USB_RD_SEC (BIT(16))
#define USB_WR_SEC (BIT(16))

#define CE1_RD_SEC (BIT(18)|BIT(17))
#define CE1_WR_SEC (BIT(18)|BIT(17))

#define CE0_RD_SEC (BIT(20)|BIT(19))
#define CE0_WR_SEC (BIT(20)|BIT(19))

#define NAND_RD_SEC (BIT(1)|BIT(0))
#define NAND_WR_SEC (BIT(1)|BIT(0))

#ifdef CONFIG_ATF_BOOT_TOS
#define MEM_FW_GPU_CPU_CP_SEGMENT0 0x40427060
#define OFFSET 4
#define REGION_ADDRESS_SHIFT_BITS	  12
#define SET_START_VALUE(X) ((X)-0x80000000)>>REGION_ADDRESS_SHIFT_BITS
#define SET_END_VALUE(X) (((X)-0x80000000-1)>>REGION_ADDRESS_SHIFT_BITS)
#endif

//add secure ddr

#define REG_SLAVE_FW_AON_BASE 0x40421800
#define REG_SLAVE_FW_AON_WR_SEC5 0x50
#define DDR_ATTR_MASK	(BIT(4)|BIT(5))
#define DDR_ATTR_WR		(0x1 << 4)

#define REG_DDR_CONTROLLER_BASE_PHY 0x30000000
#define REG_DDR_CONTROLLER_PHY_SIZE 0x800
//add modem ctrl
#define REG_FW_PMU_BASE 0x40428100
#define REG_FW_PMU_BASE_ARRAY_ADDRESS_OFFSET 0x30
#define REG_FW_ARRY_ADD_OFFSET 0x40

#define REG_FW_AON_BASE 0x40428000
#define REG_FW_AON_BASE_ARRAY_ADDRESS_OFFSET 0x30

#define MASTER_CTRL_CA53 0x40422400
#define DAP_BYPASS_MODE  0x1
static void aon_iram_sec(void)
{
	/***aon iram sec set***/
	*(volatile uint32_t*)(REG_TZMA_FIRST_ADDR) = MEM_FIRST_ADDR;
	*(volatile uint32_t*)(REG_TZMA_LAST_ADDR) = MEM_LAST_ADDR;
}

static void dis_emmc_sec(void)
{
	/***disable emmc secure set***/
	*(volatile uint32_t*)(REG_MASTER_FW_AP_RD) &= ~EMMC_RD_SEC;
	*(volatile uint32_t*)(REG_MASTER_FW_AP_WR) &= ~EMMC_WR_SEC;
}

static void dis_sd_sec(void)
{
	/***disable sd secure set***/
	*(volatile uint32_t*)(REG_MASTER_FW_AP_RD) &= ~SD_RD_SEC;
	*(volatile uint32_t*)(REG_MASTER_FW_AP_WR) &= ~SD_WR_SEC;
}

static void dis_usb_sec(void)
{
	/***disable usb secure set***/
	*(volatile uint32_t*)(REG_MASTER_FW_AP_RD) &= ~USB_RD_SEC;
	*(volatile uint32_t*)(REG_MASTER_FW_AP_WR) &= ~USB_WR_SEC;
}
static void dap_bypass(void)
{
	/***dap bypass mode***/
	*(volatile uint32_t*)(MASTER_CTRL_CA53) |= DAP_BYPASS_MODE;
	*(volatile uint32_t*)(MASTER_CTRL_CA53 + 4) |= DAP_BYPASS_MODE;
}
static void dis_nand_sec(void)
{
	/***disable usb secure set***/
	*(volatile uint32_t*)(REG_MASTER_FW_AP_RD) &= ~NAND_RD_SEC;
	*(volatile uint32_t*)(REG_MASTER_FW_AP_WR) &= ~NAND_WR_SEC;
}

/*only protect the tos here for the time beging */
void tos_secure(void)
{
#ifdef CONFIG_ATF_BOOT_TOS
	uint32_t b,i;
	b = SET_START_VALUE(CONFIG_TOS_LDADDR_START);
	*(volatile uint32_t*)(MEM_FW_GPU_CPU_CP_SEGMENT0 + OFFSET * 0) = b;
	b = SET_END_VALUE(CONFIG_TOS_LDADDR_START + CONFIG_SML_TOS_RUNNING_SIZE);
	*(volatile uint32_t*)(MEM_FW_GPU_CPU_CP_SEGMENT0 + OFFSET * 1) = b;
	for(i=0;i<4;i++)
		*(volatile uint32_t*)(MEM_FW_GPU_CPU_CP_SEGMENT0 + OFFSET * (i + 2)) = 0xFFFFFFFF;
	for(i=0;i<4;i++)
		*(volatile uint32_t*)(MEM_FW_GPU_CPU_CP_SEGMENT0 + OFFSET * (i + 6)) = 0x0;
	for(i=0;i<4;i++)
		*(volatile uint32_t*)(MEM_FW_GPU_CPU_CP_SEGMENT0 + OFFSET * (i + 10)) = 0xFFFFFFFF;
	for(i=0;i<4;i++)
		*(volatile uint32_t*)(MEM_FW_GPU_CPU_CP_SEGMENT0 + OFFSET * (i + 14)) = 0x0;
#endif
}

void ddr_controller_secure(void)
{
#ifdef CONFIG_ATF_BOOT_TOS
	*(volatile uint32_t*)(REG_SLAVE_FW_AON_BASE + REG_SLAVE_FW_AON_WR_SEC5)  &= ~DDR_ATTR_MASK;
	*(volatile uint32_t*)(REG_SLAVE_FW_AON_BASE + REG_SLAVE_FW_AON_WR_SEC5)  |=  DDR_ATTR_WR;
#endif
}

void modem_control(void)
{
#ifdef CONFIG_SECBOOT
	*(volatile uint32_t*)(REG_FW_PMU_BASE + REG_FW_PMU_BASE_ARRAY_ADDRESS_OFFSET )  = 0x402b0048;
	*(volatile uint32_t*)(REG_FW_PMU_BASE + REG_FW_PMU_BASE_ARRAY_ADDRESS_OFFSET + REG_FW_ARRY_ADD_OFFSET )  = BIT(25);

	*(volatile uint32_t*)(REG_FW_PMU_BASE + REG_FW_PMU_BASE_ARRAY_ADDRESS_OFFSET + 4)  = 0x402b00cc;
	*(volatile uint32_t*)(REG_FW_PMU_BASE + REG_FW_PMU_BASE_ARRAY_ADDRESS_OFFSET + REG_FW_ARRY_ADD_OFFSET + 4)  = BIT(18);

	*(volatile uint32_t*)(REG_FW_AON_BASE + REG_FW_AON_BASE_ARRAY_ADDRESS_OFFSET )  = 0x402e0284;
	*(volatile uint32_t*)(REG_FW_AON_BASE + REG_FW_AON_BASE_ARRAY_ADDRESS_OFFSET + REG_FW_ARRY_ADD_OFFSET )  = BIT(10);

	*(volatile uint32_t*)(REG_FW_PMU_BASE + REG_FW_PMU_BASE_ARRAY_ADDRESS_OFFSET + 8)  = 0x402b00b0;
	*(volatile uint32_t*)(REG_FW_PMU_BASE + REG_FW_PMU_BASE_ARRAY_ADDRESS_OFFSET + REG_FW_ARRY_ADD_OFFSET + 8)  = BIT(1);
#endif
}
void sprd_firewall_config_pre (void)
{
}

void sprd_firewall_config(void)
{
	aon_iram_sec();
	dis_emmc_sec();
	dis_sd_sec();
	dis_usb_sec();
	dis_nand_sec();
	tos_secure();
	ddr_controller_secure();
	modem_control();
	dap_bypass();
}

