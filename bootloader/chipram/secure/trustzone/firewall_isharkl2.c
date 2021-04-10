#include <common.h>
#include <sci_types.h>
#include <security/trustzone/trustzone.h>

/***
add AonRamSec set
***/

#define SPRD_MEM_FW_RAM_BASE (0xE4809000)

#define MEM_FIRST_ADDR_SEG0 (0xE6000000)
#define MEM_LAST_ADDR_SEG0 (0xE6001FFF)

#define MEM_FIRST_ADDR_SEG1 (0xE602F000)
#define MEM_LAST_ADDR_SEG1 (0xE6030FFF)

#define MEM_FW_REG_OFFSET (72)

#define MST_ID_MAX_NUM (4)

#define IRAM_MIN_ADDR (0x0)

#define DDR_RAM_OFF		(0x24)

#define ADDR_SHIFT_BITS		(2)
/*slv firewall config*/
#define SPRD_SLV_FW_AON_BASE	(0xE4800600)
#define WR_SEC_05		(0x5C)

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

#define REG_FW3_ADDR_ARRAY0_OFF	(0x0018)
#define REG_FW3_ARRAY0_OFF	(0x0058)

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
	volatile uint32_t first_addr;
	volatile uint32_t last_addr;
	volatile uint32_t mst_id_rd_sec[MST_ID_MAX_NUM];
	volatile uint32_t mst_id_rd_nsec[MST_ID_MAX_NUM];
	volatile uint32_t mst_id_wr_sec[MST_ID_MAX_NUM];
	volatile uint32_t mst_id_wr_nsec[MST_ID_MAX_NUM];
}sprd_mem_fw_cfg;

/***
4: 4 segs
2: first&last addr
***/
uint32 mem_fw_ram_addr[4][2];

/*mst id bit
fw_ram_mstid[0]:0-31
fw_ram_mstid[1]:32-63
fw_ram_mstid[2]:64-95
fw_ram_mstid[3]:96-127
*/
uint32 fw_ram_mstid[4] = {0x0103,0,0,0x80000000};

/***
func:mem_fw_ram_sec
mem_fw_ram protect 2 segs IRAM:
1: PM 0-8K 0xE600_0000-0xE600_1FFF
2: reserved 8K 0xE602_F000-0xE603_1000
***/
static void mem_fw_ram_sec(void)
{
	sprd_mem_fw_cfg *mem_fw_base = 0;
	uint32 i;

	mem_fw_ram_addr[0][0] = MEM_FIRST_ADDR_SEG0;
	mem_fw_ram_addr[0][1] = MEM_LAST_ADDR_SEG0;
	mem_fw_ram_addr[1][0] = MEM_FIRST_ADDR_SEG1;
	mem_fw_ram_addr[1][1] = MEM_LAST_ADDR_SEG1;

	for(i=0;i<2;i++)
	{
		/***set mem-fw-ram for 2 segs***/
		mem_fw_base = (sprd_mem_fw_cfg *)(SPRD_MEM_FW_RAM_BASE + DDR_RAM_OFF + (i*MEM_FW_REG_OFFSET));

		/***set start&last addr***/
		REG_WRITE(&(mem_fw_base->last_addr),(IRAM_MIN_ADDR>>ADDR_SHIFT_BITS));
		REG_WRITE(&(mem_fw_base->first_addr),(mem_fw_ram_addr[i][0]>>ADDR_SHIFT_BITS));

		REG_WRITE(&(mem_fw_base->mst_id_rd_sec[0]),(fw_ram_mstid[0]));
		REG_WRITE(&(mem_fw_base->mst_id_rd_sec[3]),(fw_ram_mstid[3]));
		REG_WRITE(&(mem_fw_base->mst_id_wr_sec[0]),(fw_ram_mstid[0]));
		REG_WRITE(&(mem_fw_base->mst_id_wr_sec[3]),(fw_ram_mstid[3]));

		REG_WRITE(&(mem_fw_base->last_addr),(mem_fw_ram_addr[i][1]>>ADDR_SHIFT_BITS));
	}

}

static void slv_fw_sec(void)
{
#ifdef CONFIG_MOBILEVISOR
	/*pub0 ddr controller default value = 0x3
	bit5 bit4:	00 sec/no-sec can not access
			01 sec access only
			10 no-sec access only
			11 sec/no-sec can access
	*/
	REG_AND((SPRD_SLV_FW_AON_BASE+WR_SEC_05),~(BIT(5)));
#endif
}

static void reg_fw_sec(void)
{
#ifdef CONFIG_SPRD_SECBOOT

#if (!(defined CONFIG_KBC_BYPASS_SECURE_BOOT))
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

