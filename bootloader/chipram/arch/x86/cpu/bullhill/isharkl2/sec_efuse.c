#include <common.h>
#include <linux/types.h>
#include <asm/io.h>
#include <asm/arch/sprd_reg.h>
#include <security/sec_efuse.h>

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

#ifndef BIT
#define BIT(x)  (1<<(x))
#endif

/**********************efuse macro define**********************/
#define EFUSE_REG_BASE         (SPRD_UIDEFUSE_BASE) //0xE4240000

#define EFUSE_DATA_RD          (EFUSE_REG_BASE + 0x0000)
#define EFUSE_DATA_WR          (EFUSE_REG_BASE + 0x0004)

#define EFUSE_BLOCK_INDEX      (EFUSE_REG_BASE + 0x0008)
#define EFUSE_CFG0             (EFUSE_REG_BASE + 0x000C)
#define EFUSE_OP_CFG           (EFUSE_REG_BASE + 0x001C)
#define EFUSE_MODE_CTRL        (EFUSE_REG_BASE + 0x0024)
#define EFUSE_STATUS           (EFUSE_REG_BASE + 0x0028)

/**********************CE macro define**********************/
#define CTL_AP_BASE_CE                 (SPRD_CE0_BASE) //0xC0D00000
#define CTL_CE_EFUSE_APB               (SPRD_CE_EFUSE_BASE) //0xC0D80000

/*ce module enable register*/
#define CE_CLK_EB_REG  (CTL_AP_BASE_CE + 0x0018)

/*ce module enable*/
#define CE_RNG_EB_REG    (CTL_AP_BASE_CE + 0x0200)

/*ce secure key work mode register*/
#define CE_SEC_KEY_USE_WAY_REG   (CTL_AP_BASE_CE + 0x0340)

/*
 *	address:0xc0d80030
 *	CS Efuse status register. only secure APB can read and write the reg.
 *	bit[0] Efuse write finish flag, set to 1 when write process finish.
 *	bit[1] Efuse read finish flag, set to 1 when read process finish.
 *	bit[2] Efuse write error flag, efuse controller will aytomatically
 *	       read the data back and check the correctness. Set to 1 when
 *	       the data in efuse is different from it in iram.
 *	bit[7] Efuse status clear. Write 1 to clear bit[2:0]
 *	bit[8] Efuse VDD ON. Set this bit will open 0.9V static power supply
 *	       for secure efuse memory. Once this bit is cleared, the efuse
 *	       will go to power down mode.
*/
#define REG_EFUSE_SECURE_STS           (CTL_CE_EFUSE_APB + 0x0030)
#define REG_CE_SECURE_KEY_USE_WAY      (CTL_AP_BASE_CE + 0x0340)

#define RF_CE_SECURE_CPU_ACCESS         BIT(30)

#define CE_FUSE_RW_START_ADDRESS       (CTL_AP_BASE_CE + 0x0440)
#define CE_FUSE_RW_END_ADDRESS         (CTL_AP_BASE_CE + 0x04FC)

#define EFUSE_READ_DONE                 BIT(1)

#define REG_CE_SECURE_KEY_START_END_SYNC_ADDR      (CTL_AP_BASE_CE + 0x0344)
#define RF_CE_SECURE_KEY_START_SYNC_ADDR           (0x01<<4)
#define RF_CE_SECURE_KEY_END_SYNC_ADDR             (0x3f<<8)
#define RF_SECURE_KEY_DATA_SYNC_EN                 BIT(29)

#define EFUSE_LDO_VOL_UP_TIMEOUT      (CTL_CE_EFUSE_APB + 0x003c)
#define EFUSE_LDO_VOL_DOWN_TIMEOUT    (CTL_CE_EFUSE_APB + 0x0040)

/*******************LDO macro define**********************/
#define CTL_AP_BASE_LDO            (SPRD_ANLG_PHY_G2)  //0xE4100000

/**********************CE efuse LDO delay**************************/
#define CE_EFUSE_BASE_LDO_DELAY     (0xE42C0000)
#define CE_EFUSE_LDO_DELAY_1    	(CE_EFUSE_BASE_LDO_DELAY + 0xF0)
#define CE_EFUSE_LDO_DELAY_2    	(CE_EFUSE_BASE_LDO_DELAY + 0xF4)
#define CE_EFUSE_LDO_DELAY_3    	(CE_EFUSE_BASE_LDO_DELAY + 0xF8)
#define CE_EFUSE_LDO_DELAY_4    	(CE_EFUSE_BASE_LDO_DELAY + 0xEC)
#define CE_EFUSE_LDO_DELAY_5    	(CE_EFUSE_BASE_LDO_DELAY + 0xE4)


/*******************AP AHB Control Register**********************/
#define AP_AHB_CTL_REG_BASE               (SPRD_AHB_BASE) //(0xE2210000)

/*AHB enable register
 *	bit[24] CE0_EB
 *		CE0 Enable. Active High
 *		0: Disable Crypto Engine
 *		1: enable Crypto Engine
 *	bit[25] CE1_EB
 *		CE1 Enable. Active High
 *		0: Disable Crypto Engine
 *		1: enable Crypto Engine
 *	bit[26] CE_EFS_EB
 *		CE EFS Enable. Active High
 *		0: Disable CE EFS.
 *		1: enable CE EFS.
*/
#define AP_AHB_EB_REG                     (AP_AHB_CTL_REG_BASE + 0x0)
#define CE0_EB     BIT(24)
#define CE1_EB     BIT(25)
#define CE_EFS_EB  BIT(26)

/*AHB reset register
 *	bit[25] CE0_SOFT_RST
 *		CE0 Reset. Active High
 *		0: Keep Crypto Engine in normal mode.
 *		1: Reset Crypto Engine.
 *	bit[26] CE1_SOFT_RST
 *		CE1 Reset. Active High
 *		0: Keep Crypto Engine in normal mode.
 *		1: Reset Crypto Engine.
 *	bit[27] CE_EFS_SOFT_RST
 *		CE EFS Reset. Active High
 *		0: Keep CE EFS in normal mode.
 *		1: Reset CE EFS Engine.
 */
#define AP_AHB_RST_REG               (AP_AHB_CTL_REG_BASE + 0x04)
#define CE_EFS_SOFT_RST       BIT(27)

#define SEC_EFUSE_BASE_ADDR   (0xC0D00400)


#define udelay(x) \
	do { \
		volatile int i; \
		int cnt = 200 * (x); \
		for (i=0; i<cnt; i++);\
	} while(0);

#define msleep(ms) udelay(ms*1000)

/*
   function name: void en_ce_clk(void)
input:no
output:no
ret:no
 */
static void en_ce_clk(void)
{
	REG_OR(AP_AHB_EB_REG, CE0_EB);
	REG_OR(AP_AHB_EB_REG, CE_EFS_EB);
}

/*
   function name: void dis_ce_clk(void)
input:no
output:no
ret:no
 */
static void dis_ce_clk(void)
{
	REG_AND(AP_AHB_EB_REG, ~CE0_EB);
	REG_AND(AP_AHB_EB_REG, ~CE_EFS_EB);
}

/*
   function name: Efuse_Result_Ret ce_efuse_read(unsigned int pCeDataAddr, unsigned int *pReadData)
input:pCeDataAddr
output:pReadData
ret:EFUSE_RESULT_SUCCESS  EFUSE_ID_ERROR
 */
static Efuse_Result_Ret ce_efuse_read(unsigned int block_id, unsigned int *pReadData)
{
	unsigned int pCeDataAddr = SEC_EFUSE_BASE_ADDR;

	pCeDataAddr += (block_id<<0x2);

	en_ce_clk();

	if((pCeDataAddr < CE_FUSE_RW_START_ADDRESS ) || (pCeDataAddr > CE_FUSE_RW_END_ADDRESS))
	{
		dis_ce_clk();
		return EFUSE_ID_ERROR;
	}

	REG_OR(REG_CE_SECURE_KEY_USE_WAY,RF_CE_SECURE_CPU_ACCESS);
	REG_AND(REG_EFUSE_SECURE_STS,~BIT(1));
	REG_READ(pCeDataAddr,*pReadData);

	dis_ce_clk();

	return EFUSE_RESULT_SUCCESS;
}

/*
   function name: Efuse_Result_Ret ce_efuse_program(unsigned int pCeDataAddr, unsigned int pWriteData)
input:pCeDataAddr
output:pWriteData
ret:EFUSE_RESULT_SUCCESS
 */
/*Efuse_Result_Ret ce_efuse_program(unsigned int pCeDataAddr, unsigned int pWriteData)
  {
  en_ce_clk();

  REG_OR(REG_CE_SECURE_KEY_START_END_SYNC_ADDR,RF_CE_SECURE_KEY_START_SYNC_ADDR);
  REG_OR(REG_CE_SECURE_KEY_START_END_SYNC_ADDR,RF_CE_SECURE_KEY_END_SYNC_ADDR);

  REG_OR(REG_CE_SECURE_KEY_USE_WAY,RF_CE_SECURE_CPU_ACCESS);
  REG_OR(REG_CE_SECURE_KEY_USE_WAY,RF_SECURE_KEY_DATA_SYNC_EN);

  REG_WRITE(pCeDataAddr,pWriteData);

  REG_AND(REG_CE_SECURE_KEY_USE_WAY,~RF_CE_SECURE_CPU_ACCESS);

  dis_ce_clk();

  return EFUSE_RESULT_SUCCESS;
  }*/

/*
   function name : ce_efuse_program
input         : block_id, pWriteData
output        : no
ret           : Efuse_Result_Ret
 */
static Efuse_Result_Ret ce_efuse_program(unsigned int block_id, unsigned int pWriteData)
{
	unsigned int pCeDataAddr = SEC_EFUSE_BASE_ADDR;//block base addr

	/*enable CE0, CE1, CE_EFS*/
	*(volatile uint32*)(AP_AHB_EB_REG) |= (0x7<<24);//en_clk

	/*set ce efuse delay time*/
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_1) = 0x03400040;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_2) = 0x00400300;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_3) = 0x002000ff;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_4) = 0x00000010;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_5) = 0x00600060;//adjust efuse clk

	/*reset ce efuse controller*/
	*(volatile uint32*)(AP_AHB_RST_REG) = 0x08000000;
	*(volatile uint32*)(AP_AHB_RST_REG) = 0x00000000;

	msleep(10);//delay 10ms

	/*Auto trigger writting operation when up voltage time out*/
	*(volatile uint32*)(EFUSE_LDO_VOL_UP_TIMEOUT)   = 0x001f4000;//adjust efuse clk
	/*Auto trigger finish writting operation when down voltage time out*/
	*(volatile uint32*)(EFUSE_LDO_VOL_DOWN_TIMEOUT) = 0x001f4000;//adjust efuse clk

	/*open efuse LDO*/
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0068) &= ~(0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x006C) &= ~(0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0078) |= ((0x1 << 5)|(0x1 << 7));

	*(volatile uint32*)(REG_EFUSE_SECURE_STS) = 0x180;//clear efuse status

	*(volatile uint32*)(pCeDataAddr+(block_id<<0x2)) = pWriteData;//write data

	*(volatile uint32*)(REG_CE_SECURE_KEY_START_END_SYNC_ADDR) = ((block_id<<0x8)|block_id);//sync block

	*(volatile uint32*)(REG_CE_SECURE_KEY_USE_WAY) = 0x60000000;//enable efuse write

	*(volatile uint32*)(REG_CE_SECURE_KEY_USE_WAY) = 0x20000000;//enable efuse write

	while(((*(volatile uint32*)(REG_EFUSE_SECURE_STS))&0x01) != 0x01);

	*(volatile uint32*)(REG_EFUSE_SECURE_STS) = 0x180;//clear efuse status

	*(volatile uint32*)(REG_CE_SECURE_KEY_USE_WAY) = 0x40000000;//restoring independence status

	msleep(10);//delay 10ms

	/*close efuse LDO*/
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0068) |= (0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x006C) |= (0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0078) &= ~((0x1 << 5)|(0x1 << 7));

	/*disable CE0, CE1, CE_EFS*/
	*(volatile uint32*)(AP_AHB_EB_REG) &= ~(0x7<<24);//dis_clk

	return EFUSE_RESULT_SUCCESS;
}

Efuse_Result_Ret sprd_ce_efuse_read(unsigned int block_id, unsigned int *pReadData)
{
	int ret = 0;

	//spink_lock();
	//power_on();
	ret = ce_efuse_read(block_id, pReadData);
	//power_off();
	//spink_unlock();

	return ret;
}

/*
   We will not write efuse when the block has been writted.
   Call sprd_ce_efuse_read function to read the efuse fristly,
   if the reading data is all 0, we will call ce_efuse_program to
   wirte the pWriteData to the efuse, therwise, return EFUSE_WR_ERROR.
 */
Efuse_Result_Ret sprd_ce_efuse_program(unsigned int blocked_id, unsigned int pWriteData)
{
	int ret = 0;

	//spink_lock();
	//power_on();
	ret = ce_efuse_program(blocked_id, pWriteData);
	//power_off();
	//spink_unlock();

	return ret;
}

static Efuse_Result_Ret ce_efuse_huk_program(void)
{
	unsigned int pCeDataAddr = SEC_EFUSE_BASE_ADDR;//block base addr

	*(volatile uint32*)(AP_AHB_EB_REG) |= (0x7<<24);//en_clk

	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_1) = 0x03400040;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_2) = 0x00400300;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_3) = 0x002000ff;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_4) = 0x00000010;//adjust efuse clk
	*(volatile uint32*)(CE_EFUSE_LDO_DELAY_5) = 0x00600060;//adjust efuse clk

	//reset efuse controller
	*(volatile uint32*)(AP_AHB_RST_REG) = 0x08000000;
	*(volatile uint32*)(AP_AHB_RST_REG) = 0x00000000;

	msleep(10);//delay 10ms

	/*Auto trigger writting operation when up voltage time out*/
	*(volatile uint32*)(EFUSE_LDO_VOL_UP_TIMEOUT) = 0x001f4000;//adjust efuse clk
	/*Auto trigger finish writting operation when down voltage time out*/
	*(volatile uint32*)(EFUSE_LDO_VOL_DOWN_TIMEOUT) = 0x001f4000;//adjust efuse clk

	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0068) &= ~(0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x006C) &= ~(0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0078) |= ((0x1 << 5)|(0x1 << 7));

	*(volatile uint32*)(REG_EFUSE_SECURE_STS) = 0x180;//clear efuse status

	*(volatile uint32*)(CE_CLK_EB_REG) = 0x20; //enable trng clk
	*(volatile uint32*)(CE_RNG_EB_REG) = 0x02; //only enable trng ring
	*(volatile uint32*)(CE_RNG_EB_REG) = 0x03; //enable trng module

	*(volatile uint32*)(CE_SEC_KEY_USE_WAY_REG) |= (0x1<<31);//enable ce secure key trng write

	while(((*(volatile uint32*)(CE_SEC_KEY_USE_WAY_REG))&(0x1<<31)) != 0x0);//wait for 0

	*(volatile uint32*)(CE_RNG_EB_REG) = 0x0; //disable trng ring

	*(volatile uint32*)(CE_CLK_EB_REG) = 0x0;//disable trng clk


	while(((*(volatile uint32*)(REG_EFUSE_SECURE_STS))&0x01) != 0x01);

	*(volatile uint32*)(REG_EFUSE_SECURE_STS) = 0x180;//clear efuse status

	*(volatile uint32*)(REG_CE_SECURE_KEY_USE_WAY) = 0x40000000;//restoring independence status

	msleep(10);//delay 10ms

	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0068) |= (0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x006C) |= (0x1 << 7);
	*(volatile uint32*)(CTL_AP_BASE_LDO + 0x0078) &= ~((0x1 << 5)|(0x1 << 7));

	*(volatile uint32*)(AP_AHB_RST_REG) &= ~(0x7<<24);//dis_clk

    return EFUSE_RESULT_SUCCESS;
}

Efuse_Result_Ret sprd_ce_efuse_huk_program(void)
{
	int ret = 0;

	//spink_lock();
	//power_on();
	ret = ce_efuse_huk_program();
	//power_off();
	//spink_unlock();

	return ret;
}

/* 64bits per lock bit */
Efuse_Result_Ret sprd_get_lock_bits(unsigned int start_id, unsigned int end_id, unsigned int *bits_data)
{
    unsigned int i;
    unsigned int start_bit, end_bit;

	if (bits_data == NULL)
		return EFUSE_PARAM_ERROR;

    start_bit = (start_id + 1) / 2;
    end_bit = (end_id - 1) / 2;

    if (start_bit > end_bit)
        return EFUSE_RESULT_SUCCESS;

    for (i = start_bit; i <= end_bit; i++)
    {
        *bits_data |= 1 << i;
    }

	return EFUSE_RESULT_SUCCESS;
}

unsigned int sprd_get_secure_boot_enable(void)
{
	unsigned int read_bit = 0;

    read_bit = sprd_ap_efuse_read(PUBLIC_EFUSE_BLOCK2);

    read_bit &= 1;

    return read_bit;
}
