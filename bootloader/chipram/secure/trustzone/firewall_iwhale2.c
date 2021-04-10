#include <common.h>
#include <sci_types.h>
#include <security/trustzone/trustzone.h>

/***
add AonRamSec set
***/

#define SPRD_MEM_FW_RAM_BASE (0xE4809000)

#define MEM_FIRST_ADDR_SEG0 (0xE6000000)
#define MEM_LAST_ADDR_SEG0 (0xE6002000)

#define MEM_FIRST_ADDR_SEG1 (0xE6030000)
#define MEM_LAST_ADDR_SEG1 (0xE6031000)

#define MEM_FW_REG_OFFSET (48)

#define ALL_MST_ID_CAN_ACCESS (0xFFFFFFFF)
#define MST_ID_MAX_NUM (8)

#define IRAM_MAX_ADDR (0xFFFFFFFF)
/*slv firewall config*/
#define SPRD_SLV_FW_AON_BASE	(0xE4800600)
#define WR_SEC_04		(0x28)
#define WR_SEC_05		(0x2C)

/*reg firewall config*/
/*
 * cp register define
 * stop
 * 0xe42b0020 bit24->0, bit25->1
 * 0xe42c0000 bit1->1, bit15->1
 * Start
 * 0xe42b014c bit13->0, bit24->0, bit26->0, bit1->0
 * 0xe42b0020 bit24->0, bit25->0
 * 0xe42c0000 bit1->0, bit15->0
 * *************************************
 * reg_fw3:0xe4800c00---->0xe42c0000
 * reg_fw4:0xe4800d00---->0xe42b0000
 */
#define BIT(x)	(1<<(x))
#define SPRD_REG_FW3_BASE	(0xE4800C00)
#define SPRD_REG_FW4_BASE	(0xE4800D00)

#define REG_FW3_ADDR_ARRAY0_OFF	(0x0010)
#define REG_FW3_ARRAY0_OFF	(0x0050)

#define REG_FW4_ADDR_ARRAY0_OFF	(0x0028)
#define REG_FW4_ARRAY0_OFF	(0x0068)
#define REG_FW4_ADDR_ARRAY1_OFF	(0x002C)
#define REG_FW4_ARRAY1_OFF	(0x006C)

#define SYS_SOFT_RESET		(0x0000) //0xe42c0000
#define PD_PUBCP_PWR_CONFIG	(0x0020) //0xe42b0020
#define PUBCP_SYS_SLEEP_CTRL	(0x014c) //0xe42b014c

#define SYS_SOFT_RESET_BITS		(BIT(1)|BIT(15))
#define PD_PUBCP_PWR_CONFIG_BITS	(BIT(25))
#define PUBCP_SYS_SLEEP_CTRL_BITS	(BIT(1)|BIT(13)|BIT(24)|BIT(26))
/***
**
***/
#define REG_READ(reg_addr,value)\
do{\
	value = *(volatile uint32*)(reg_addr);\
}while(0)

#define REG_WRITE(reg_addr,value)\
do{\
	*(volatile uint32*)(reg_addr) = (value);\
}while(0)

#define REG_OR(reg_addr,or_mask)\
do{\
	*(volatile uint32*)(reg_addr) |= (or_mask);\
}while(0)

#define REG_AND(reg_addr,and_mask)\
do{\
	*(volatile uint32*)(reg_addr) &= (and_mask);\
}while(0)

#define REG_BIT(reg_addr,bit,value)\
do{\
	*(volatile uint32*)(reg_addr) |= ((value)<<(bit));\
}while(0)
/***
**
***/

/***
mem fw congfig
***/
typedef struct {
	uint32 first_addr;
	uint32 last_addr;
	uint32 mst_id[MST_ID_MAX_NUM];
	uint32 rd_attr;
	uint32 wr_attr;
}sprd_mem_fw_cfg;
/***
mem fw read/write attr
***/
typedef enum {
	ALL_NOT_ACCESS = 0,
	SEC_ACCESS,
	NSEC_ACCESS,
	ALL_ACCESS
}sprd_mem_fw_rw_attr;

/***
4: 4 segs
2: first&last addr
***/
uint32 mem_fw_ram_addr[4][2];

/***
func:mem_fw_ram_sec
mem_fw_ram protect 2 segs IRAM:
1: PM 0-8K 0xE600_0000-0xE600_1FFF
2: reserved 24K 0xE600_2000-0xE600_7FFF
***/
static void mem_fw_ram_sec(void)
{
	sprd_mem_fw_cfg *mem_fw_base = 0;
	uint32 i,cont;

	mem_fw_ram_addr[0][0] = MEM_FIRST_ADDR_SEG0;
	mem_fw_ram_addr[0][1] = MEM_LAST_ADDR_SEG0;
	mem_fw_ram_addr[1][0] = MEM_FIRST_ADDR_SEG1;
	mem_fw_ram_addr[1][1] = MEM_LAST_ADDR_SEG1;
	/***set mem-fw-ram for 2 segs***/
	for(i=0;i<2;i++)
	{
		mem_fw_base = (sprd_mem_fw_cfg *)(SPRD_MEM_FW_RAM_BASE + (i*MEM_FW_REG_OFFSET));

		/***set start&last addr***/
		REG_WRITE(&(mem_fw_base->first_addr),(IRAM_MAX_ADDR>>2));
		REG_WRITE(&(mem_fw_base->last_addr),(mem_fw_ram_addr[i][1]>>2));

		for(cont=0;cont<MST_ID_MAX_NUM;cont++)
		{
			REG_WRITE(&(mem_fw_base->mst_id[cont]),ALL_MST_ID_CAN_ACCESS);
		}

		REG_WRITE(&(mem_fw_base->rd_attr),SEC_ACCESS);
		REG_WRITE(&(mem_fw_base->wr_attr),SEC_ACCESS);

		REG_WRITE(&(mem_fw_base->first_addr),(mem_fw_ram_addr[i][0]>>2));
	}
}

static void slv_fw_sec(void)
{
#ifdef CONFIG_MOBILEVISOR
	/*config write attr: secure access only*/
	/*pub1 ddr controller
	bit23 bit22: 00 sec/no-sec can not access
				01 sec access only
				10 no-sec access only
				11 sec/no-sec can access
	*/
	REG_AND((SPRD_SLV_FW_AON_BASE+WR_SEC_04),~(BIT(23)));
	/*pub0 ddr controller
	bit11 bit10: 00 sec/no-sec can not access
				01 sec access only
				10 no-sec access only
				11 sec/no-sec can access
	*/
	REG_AND((SPRD_SLV_FW_AON_BASE+WR_SEC_05),~(BIT(11)));
#endif
}

static void reg_fw_sec(void)
{
#ifdef CONFIG_SPRD_SECBOOT
	/*0xe42c0000 bit1, bit15*/
	REG_WRITE((SPRD_REG_FW3_BASE+REG_FW3_ADDR_ARRAY0_OFF),SYS_SOFT_RESET);
	REG_WRITE((SPRD_REG_FW3_BASE+REG_FW3_ARRAY0_OFF),SYS_SOFT_RESET_BITS);
	/*0xe42b0020 bit24, bit25*/
	REG_WRITE((SPRD_REG_FW4_BASE+REG_FW4_ADDR_ARRAY0_OFF),PD_PUBCP_PWR_CONFIG);
	REG_WRITE((SPRD_REG_FW4_BASE+REG_FW4_ARRAY0_OFF),PD_PUBCP_PWR_CONFIG_BITS);
	/*0xe42b014c bit13, bit24, bit26, bit1*/
	REG_WRITE((SPRD_REG_FW4_BASE+REG_FW4_ADDR_ARRAY1_OFF),PUBCP_SYS_SLEEP_CTRL);
	REG_WRITE((SPRD_REG_FW4_BASE+REG_FW4_ARRAY1_OFF),PUBCP_SYS_SLEEP_CTRL_BITS);
#endif
}

void sprd_firewall_config_pre (void)
{
}

void sprd_firewall_config(void)
{
	mem_fw_ram_sec();
	slv_fw_sec();
	reg_fw_sec();
}

