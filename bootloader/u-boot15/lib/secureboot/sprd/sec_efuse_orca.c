#include <secureboot/sec_efuse_orca.h>

const int map0_block_index[36] = {
         45,46,                                  //BONDING_PUB_EFUSE
         33,34,35,36,37,38,39,40,41,42,43,44,   //ANA_PUB_EFUSE
         32,                            	//DIG1_LPDDR
         31,                            	//DIG2_PCIE_EP
         23,24,25,26,27,28,29,30,       	//SECUREBOOT_PUB_EFUSE
         13,14,                         	//CP_SIMLOCK_PUBKEY
	 11,					//SEC_VERSION
	 10,					//LCS
          2, 3, 4, 5, 6, 7, 8, 9  		//ROTPK
};

const int *pmap = map0_block_index;

Efuse_Result_Ret efuse_read_lock_bits_map(uint32 *pReadData)
{
    Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;

    ret = efuse_read_drv(0, 3, pReadData, 0);

    return ret;
}

static inline uint32 is_bit_set(uint32 * pdata, uint32 bit_pos)
{
    uint32 ret;
    ret = pdata[bit_pos / 32] & (1 << (bit_pos % 32));
    if (ret == 0)
        return 0;
    else
        return 1;
}

static int is_huk_write(void)
{
    return 1;//just for compile,no use
}

static int is_rotpk_write(void)
{
    return 0;//just for compile,no use
}

static int is_backup_rotpk_write(void)
{
	uint32 bitmap[4] = {0};
	int ret = 1;
	int i, block_id;

	efuse_read_lock_bits_map(bitmap);

	for (i = ROTPK1_BLOCK_START; i <= ROTPK1_BLOCK_END; i++)
	{
		block_id = pmap[i];
		ret = ret & (is_bit_set(bitmap, (block_id << 1)));
	}

	return ret;
}

static int is_zero_bitmap(void)
{
	uint32 bitmap[4] = {0};
	int ret = 0;

	efuse_read_lock_bits_map(bitmap);
	ret = !(bitmap[0] | bitmap[1] | bitmap[2] | bitmap[3]);

	return ret;
}

Efuse_Result_Ret sprd_ce_efuse_huk_program(void)
{
	return 	EFUSE_RESULT_SUCCESS;
}

Efuse_Result_Ret sprd_get_lock_bits(unsigned int start_id, unsigned int end_id, unsigned int *bits_data, unsigned int *bits_data1)
{
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;

	if (ROTPK1_BLOCK_START == start_id)
		*bits_data = *bits_data1 = 0XF0000;

	return ret;
}

Efuse_Result_Ret sprd_ce_efuse_read(unsigned int block_id, unsigned int *read_ptr)
{
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;
	uint32 real_block;

	if (block_id > LOCK_BIT_BLOCK + 1)
	{
		return EFUSE_PARAM_ERROR;
	}

	if (block_id == LOCK_BIT_BLOCK || block_id == (LOCK_BIT_BLOCK + 1))
	{
		if (is_zero_bitmap())
			*read_ptr = 0;
		if (is_backup_rotpk_write())
			*read_ptr |= (0XF << 16);
		return ret;
	}

	real_block = pmap[block_id];
	ret = efuse_read_drv(real_block, real_block, read_ptr, 1);

	return ret;
}

Efuse_Result_Ret sprd_ce_efuse_program(unsigned int block_id, unsigned int WriteData)
{
	Efuse_Result_Ret ret = EFUSE_RESULT_SUCCESS;
	uint32 real_block;

	if (block_id > LOCK_BIT_BLOCK + 1)
	{
		return EFUSE_PARAM_ERROR;
	}

	if (block_id == LOCK_BIT_BLOCK || block_id == (LOCK_BIT_BLOCK + 1))
	{
		return ret;
	}

	if (block_id == CYCLE_STATE_BLOCK || block_id == SEC_VERSION_BLOCK)
	{
		real_block = pmap[block_id];
		ret = efuse_rewrite_double_bit(real_block, WriteData);//write but not set lockbit
		return ret;
	}

	if (block_id >= ROTPK1_BLOCK_START && block_id <= ROTPK1_BLOCK_END)
	{
		real_block = pmap[block_id];
		ret = efuse_write_drv(real_block, real_block, &WriteData,1);//write and set lockbit
		return ret;
	}

	real_block = pmap[block_id];
	ret = efuse_rewrite_double_bit(real_block, WriteData);//write but not set lockbit

	return ret;
}

unsigned int sprd_get_secure_boot_enable(void)
{
	return 0;//just for compile,no use
}
