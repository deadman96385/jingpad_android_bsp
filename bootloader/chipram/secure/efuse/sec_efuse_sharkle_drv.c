#include <security/sec_efuse_sharkle.h>
#include <timer.h>
#include <asm/arch/sprd_reg.h>
#include <asm/arch/chip_sharkle/aon_sec_apb.h>
#include <asm/arch/chip_sharkle/aon_apb.h>

static inline void set_reg_bit(uint64 addr, uint32 bit)
{
	(*(volatile uint32 *)(addr)) |= 1<<bit;
}

static inline void clr_reg_bit(uint64 addr, uint32 bit)
{
	(*(volatile uint32 *)(addr)) &= BIT_MASK(bit);
}

static inline void write32(uint64 addr, uint32 val)
{
    *(volatile uint32_t *)addr = val;
}

static inline uint32_t read32(uint64 addr)
{
    return *(volatile uint32_t *)addr;
}

static void msleep(uint32 ms)
{
	mdelay(ms);
}

static void efuse_lock(void)
{

}

static void efuse_unlock(void)
{

}

Efuse_Result_Ret efuse_write_drv(uint32 start_id, uint32 end_id, uint32 *pReadData,uint32 Isdouble)
{
	uint32  i, j;
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;
	efuse_lock();
	efuse_enable();
	write32(EFUSE_SEC_MAGIC_NUM, EFUSE_MAGIC);			// SET magic number
	write32(EFUSE_SEC_FLAG_CLR, ERR_FLAG_MASK);			// CLR err flag
	set_reg_bit(EFUSE_SEC_EN, 4);					// SET lock bit
	set_reg_bit(EFUSE_PW_SWT, 2);					// SET PG_EN
	clr_reg_bit(EFUSE_PW_SWT, 1);					// CLR enk2
	msleep(1);							// SLP
	set_reg_bit(EFUSE_PW_SWT, 0);					// SET enk1
	msleep(1);							// SLP
	set_reg_bit(EFUSE_SEC_EN, 1);					// SET auto check
	if(Isdouble)
		set_reg_bit(EFUSE_SEC_EN, 2);				// SET doublt bit en
	else
		clr_reg_bit(EFUSE_SEC_EN, 2);				// CLR doublt bit en

	for (i = start_id, j = 0; i <= end_id; i++, j++)
	{
		write32(BLOCK_MAP + (i << 2), pReadData[j]);
	}

	if (read32(EFUSE_SEC_ERR_FLAG) != 0)				// Read err register
	{
		ret = EFUSE_WR_ERROR;
	}

	clr_reg_bit(EFUSE_PW_SWT, 0);					// CLR enk1
	msleep(1);							// SLP
	set_reg_bit(EFUSE_PW_SWT, 1);					// SET enk2
	msleep(1);							// SLP
	clr_reg_bit(EFUSE_PW_SWT, 2);					// CLR PG_EN
	clr_reg_bit(EFUSE_SEC_EN, 4);					// CLR lock bit
	write32(EFUSE_SEC_MAGIC_NUM, 0X0);				// CLR magic number
	efuse_disable();
	efuse_unlock();
	return ret;
}

Efuse_Result_Ret efuse_read_drv(uint32 start_id, uint32 end_id, uint32 *pReadData,uint32 Isdouble)
{
	uint32  i, j;
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;
	efuse_lock();
	efuse_enable();
	write32(EFUSE_SEC_MAGIC_NUM, EFUSE_MAGIC);		// SET magic number
	write32(EFUSE_SEC_FLAG_CLR, ERR_FLAG_MASK);		// CLR err flag
	set_reg_bit(EFUSE_SEC_EN, 0);					// SET vdd on
	if (Isdouble)
		set_reg_bit(EFUSE_SEC_EN, 2);					// SET doublt bit en
	else
		clr_reg_bit(EFUSE_SEC_EN, 2);					// CLR doublt bit en

	for (i = start_id, j = 0; i <= end_id; i++, j++)
	{
		pReadData[j] = read32(BLOCK_MAP + (i << 2));
	}

	if (read32(EFUSE_SEC_ERR_FLAG) != 0)			// Read err register
	{
		ret = EFUSE_RD_ERROR;
	}

	clr_reg_bit(EFUSE_SEC_EN, 0);					// CLR vdd on
	write32(EFUSE_SEC_MAGIC_NUM, 0X0);				// CLR magic number
  	efuse_disable();
	efuse_unlock();
	return ret;
}


Efuse_Result_Ret efuse_rewrite_double_bit(uint32 block_id, uint32 writeData)
{
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;
	efuse_lock();
	efuse_enable();
	write32(EFUSE_SEC_MAGIC_NUM, EFUSE_MAGIC);		// SET magic number
	write32(EFUSE_SEC_FLAG_CLR, ERR_FLAG_MASK);		// CLR err flag
	set_reg_bit(EFUSE_PW_SWT, 2);					// SET PG_EN
	clr_reg_bit(EFUSE_PW_SWT, 1);					// CLR enk2
	msleep(1);										// SLP
	set_reg_bit(EFUSE_PW_SWT, 0);					// SET enk1
	msleep(1);										// SLP
	clr_reg_bit(EFUSE_SEC_EN, 1);					// clear auto check
	set_reg_bit(EFUSE_SEC_EN, 2);					// SET doublt bit en

	write32(BLOCK_MAP + (block_id << 2), writeData);

	if (read32(EFUSE_SEC_ERR_FLAG) != 0)			// Read err register
	{
		ret = EFUSE_WR_ERROR;
	}

	clr_reg_bit(EFUSE_PW_SWT, 0);					// CLR enk1
	msleep(1);										// SLP
	set_reg_bit(EFUSE_PW_SWT, 1);					// SET enk2
	msleep(1);										// SLP
	clr_reg_bit(EFUSE_PW_SWT, 2);					// CLR PG_EN
	write32(EFUSE_SEC_MAGIC_NUM, 0X0);				// CLR magic number
	efuse_disable();
	efuse_unlock();
	return ret;
}

Efuse_Result_Ret efuse_huk_program(void)
{
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;

	efuse_lock();
	efuse_enable();
	write32(EFUSE_SEC_MAGIC_NUM, EFUSE_MAGIC);		// SET magic number
	write32(EFUSE_SEC_FLAG_CLR, ERR_FLAG_MASK);		// CLR err flag
	set_reg_bit(EFUSE_SEC_EN, 4);					// SET lock bit
	set_reg_bit(EFUSE_PW_SWT, 2);					// SET PG_EN
	clr_reg_bit(EFUSE_PW_SWT, 1);					// CLR enk2
	msleep(1);										// SLP
	set_reg_bit(EFUSE_PW_SWT, 0);					// SET enk1
	msleep(1);										// SLP
	set_reg_bit(EFUSE_SEC_EN, 1);					// SET auto check
	set_reg_bit(EFUSE_SEC_EN, 2);					// SET doublt bit en

	set_reg_bit(REG_AP_AHB_CE_SEC_EB,0);			// enable ce module

	write32(CE_CLK_EB_REG, 0x20);					// enable trng clk
	write32(CE_RNG_EB_REG, 0x02);					// enable trng ring
	write32(CE_RNG_EB_REG, 0x03);					// enable trng module

	/*enable ce secure key trng write */
	set_reg_bit(CE_SEC_KEY_USE_WAY_REG, 31);

	while (((*(volatile uint32*)(CE_SEC_KEY_USE_WAY_REG)) & (0x1 << 31)) != 0x0);
													// Poll for write huk finish
	write32(CE_RNG_EB_REG, 0x0);					// disable trng ring
	write32(CE_CLK_EB_REG, 0x0);					// disable trng clk
	clr_reg_bit(REG_AP_AHB_CE_SEC_EB,0); 			// disable ce module

	if (read32(EFUSE_SEC_ERR_FLAG) != 0)			// Read err register
	{
		ret = EFUSE_WR_ERROR;
	}

	clr_reg_bit(EFUSE_PW_SWT, 0);					// CLR enk1
	msleep(1);										// SLP
	set_reg_bit(EFUSE_PW_SWT, 1);					// SET enk2
	msleep(1);										// SLP
	clr_reg_bit(EFUSE_PW_SWT, 2);					// CLR PG_EN
	clr_reg_bit(EFUSE_SEC_EN, 4);					// CLR lock bit
	write32(EFUSE_SEC_MAGIC_NUM, 0X0);				// CLR magic number
	efuse_disable();
	efuse_unlock();
	return ret;
}

void efuse_enable(void)
{
	set_reg_bit(REG_AON_SEC_APB_EFUSE_SEC_ENABLE, 0);	//enable sec efuse
}

void efuse_disable(void)
{
	clr_reg_bit(REG_AON_SEC_APB_EFUSE_SEC_ENABLE, 0);	//disable sec efuse
}


