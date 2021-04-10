#include <common.h>
#include<security/trustzone/trustzone.h>

//add AonRamSec set
#define REG_TZMA_FIRST_ADDR   0x4042F000
#define REG_TZMA_LAST_ADDR    0x4042F004

#define MEM_FIRST_ADDR (0x0)
#define MEM_LAST_ADDR (0x2000)

//add secure rd wr reg
#define REG_MASTER_FW_AP_RD   0x40421100
#define REG_MASTER_FW_AP_WR   0x40421104

//add emmc usb sd ce1 set
#define BIT(x) (1<<(x))

#define SD_RD_SEC (BIT(10)|BIT(11))
#define SD_WR_SEC (BIT(10)|BIT(11))

#define EMMC_RD_SEC (BIT(12)|BIT(13))
#define EMMC_WR_SEC (BIT(12)|BIT(13))

#define USB_RD_SEC (BIT(14))
#define USB_WR_SEC (BIT(14))

#define CE1_RD_SEC (BIT(16)|BIT(17))
#define CE1_WR_SEC (BIT(16)|BIT(17))

#define CE0_RD_SEC (BIT(18)|BIT(19))
#define CE0_WR_SEC (BIT(18)|BIT(19))



#ifdef CONFIG_ATF_BOOT_TOS
#define MEM_FW_CA7_SEGMENT0 0x40427014
#define OFFSET 4
#define REGION_ADDRESS_SHIFT_BITS	  22
#define MIDDLE_COMPUTE_4M(X) (((X) & 0xf00000)>>(REGION_ADDRESS_SHIFT_BITS-2))
#define ALIGIMENT_4M_START(X) ((MIDDLE_COMPUTE_4M(X))%4==0)?(X):(X)+((4-((MIDDLE_COMPUTE_4M(X))%4))<<(REGION_ADDRESS_SHIFT_BITS-2));

#define SET_START_VALUE(X) (X)>>REGION_ADDRESS_SHIFT_BITS
#define SET_END_VALUE(X) (((X)>>REGION_ADDRESS_SHIFT_BITS)-1)
#endif
//add secure ddr
#define REG_SLAVE_FW_AON_BASE 0x40420900
#define REG_SLAVE_FW_AON_FIRSTID_OFFSET 0x0018

#define REG_DDR_CONTROLLER_BASE_PHY 0x30000000
#define REG_DDR_CONTROLLER_PHY_SIZE 0x800

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
void sml_tos_secure(void)
{
#ifdef CONFIG_ATF_BOOT_TOS
	uint32_t a,b;
	a = ALIGIMENT_4M_START(CONFIG_SML_LDADDR_START);
	b = SET_START_VALUE(a);
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 0) = b;
	b = SET_END_VALUE(CONFIG_SML_LDADDR_START + CONFIG_SML_TOS_RUNNING_SIZE);
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 1) = b;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 2) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 3) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 4) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 5) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 6) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 7) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 8) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 9) = 0XFFFFFFFF;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 10) = 0X1;
	*(volatile uint32_t*)(MEM_FW_CA7_SEGMENT0 + OFFSET * 11) = 0X1;
#endif
}
void ddr_controller_secure(void)
{
#ifdef CONFIG_ATF_BOOT_TOS
	*(volatile uint32_t*)(REG_SLAVE_FW_AON_BASE + REG_SLAVE_FW_AON_FIRSTID_OFFSET) = REG_DDR_CONTROLLER_BASE_PHY;
	*(volatile uint32_t*)(REG_SLAVE_FW_AON_BASE + REG_SLAVE_FW_AON_FIRSTID_OFFSET + 4) = REG_DDR_CONTROLLER_BASE_PHY + REG_DDR_CONTROLLER_PHY_SIZE;
	*(volatile uint32_t*)(REG_SLAVE_FW_AON_BASE + REG_SLAVE_FW_AON_FIRSTID_OFFSET + 8) = 0xFFFFFFFF;
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
	sml_tos_secure();
	ddr_controller_secure();
}
