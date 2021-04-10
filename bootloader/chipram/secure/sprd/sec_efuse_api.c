#include <common.h>
#include <security/sec_efuse_api.h>
#include "security/sec_efuse.h"

/*---------------------------
        MACRO DEFINITIONS
----------------------------------*/

/*  minimum version anti-rollback conters */
#define ALL_ONES_VALUE 0xffffffffUL
#define ALL_ONES_NUM_BITS 32
#define SW_REVOCATION_MAX_NUM_OF_BITS_CNTR1 31
#define SW_REVOCATION_MAX_NUM_OF_BITS_CNTR2 223

/* Life cycle state definitions */
#define CHIP_MANUFACTURE_LCS     0x0
#define DEVICE_MANUFACTURE_LCS   0x1
#define SECURITY_DISABLED_LCS    0x3
#define SECURE_LCS               0x5
#define RMA_LCS                  0x7

/* SW version definition */
#define VERSION_COUNTER1_WIDTH    1
#define VERSION_COUNTER2_WIDTH    7
#define BITS_WITHIN_WORD          32

#define HUK_LOCK_MASK    0x0000F
#define ROTPK0_LOCK_MASK 0x00F00
#define ROTPK1_LOCK_MASK 0xF0000

/* MACRO to count one bits */
#define COUNT_ONE_BITS(number, BitCount) \
do \
{ \
      uint32_t tmp_num = number; \
      BitCount = 0; \
      while (tmp_num) \
      { \
        tmp_num = tmp_num & (tmp_num - 1); \
        BitCount = BitCount + 1; \
      }\
} while (0)

static unsigned int sec_efuse_read(unsigned int block_id, unsigned int *read_ptr)
{
    /* Check input variables */
    if (read_ptr == NULL)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    return sprd_ce_efuse_read(block_id, read_ptr);
}

static int sec_efuse_write(unsigned int block_id, unsigned int write_data)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int read_data;
    unsigned int wd_data;

    ret = sprd_ce_efuse_read(block_id, &read_data);
    if (ret)
        return ret;

    wd_data = write_data & (~read_data);

    if (!wd_data)
        return SEC_EFUSE_OK;

    /* write secure efuse block */
    ret = sprd_ce_efuse_program(block_id, wd_data);
    if (ret)
        return SEC_EFUSE_WRITE_FAIL_ERR;

    return ret;
}

/*
 * write a specific secure efuse block and check if it is written correctly
 */
static unsigned int sec_efuse_write_and_check(unsigned int block_id, unsigned int write_data)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int read_data = 0, read_org = 0;

    ret = sec_efuse_read(block_id, &read_org);
    if (ret)
        return SEC_EFUSE_READ_FAIL_ERR;

    /* write secure efuse block */
    ret = sec_efuse_write(block_id, write_data);
    if (ret)
        return SEC_EFUSE_WRITE_FAIL_ERR;

    /*read secure efuse block*/
    ret = sec_efuse_read(block_id, &read_data);
    if (ret)
        return SEC_EFUSE_READ_FAIL_ERR;

    /*check write data */
    if ((read_org | write_data) != read_data)
        return SEC_EFUSE_WRITE_CHECK_ERR;

    return ret;
}

/* write Lock bits */
static unsigned int set_lock_bits(unsigned int start_id, unsigned int end_id)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int bits_data0 = 0;
    unsigned int bits_data1 = 0;

    /* check input variables */
    if (start_id > end_id)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    ret = sprd_get_lock_bits(start_id, end_id, &bits_data0, &bits_data1);
    if (ret)
        return SEC_EFUSE_LOCK_BIT_ERR;

    if(bits_data0)
    {
        ret = sec_efuse_write(LOCK_BIT_BLOCK, bits_data0);
        if(ret)
        {
            return ret;
        }
    }

    if(bits_data1)
    {
        ret = sec_efuse_write(LOCK_BIT_BLOCK+1, bits_data1);
    }

    return ret;
}

/*
 * write Write multiple continuous blocks
 */
static unsigned int sec_efuse_write_blocks(unsigned int start_id, unsigned int end_id, unsigned int *pwrite_data)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int block_id;
    unsigned int* write_ptr = NULL;

    /* check input variables */
    if (pwrite_data == NULL)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    write_ptr = pwrite_data;

    /* write efuse blocks */
    for (block_id = start_id; block_id <= end_id; block_id++)
    {
        ret = sec_efuse_write(block_id, *write_ptr);
        if (ret)
            return ret;

        write_ptr++;
    }

    /* set lock bits*/
    return set_lock_bits(start_id, end_id);
}

/*
 * write Write multiple continuous blocks and check if it is written correctly
 */
static unsigned int sec_efuse_write_blocks_and_check(unsigned int start_id, unsigned int end_id, unsigned int *pwrite_data)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int block_id;
    unsigned int* write_ptr = NULL;

    /* check input variables */
    if (pwrite_data == NULL)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    write_ptr = pwrite_data;

    /* write efuse blocks */
    for (block_id = start_id; block_id <= end_id; block_id++)
    {
        ret = sec_efuse_write_and_check(block_id, *write_ptr);
        if (ret)
            return ret;

        write_ptr++;
    }

    return set_lock_bits(start_id, end_id);
}

/*
 * get a bit value in the specific block
 */
static unsigned int sec_efuse_get_bit(unsigned int block_id, int pos, unsigned int *bit)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int read_data = 0;

    ret = sec_efuse_read(block_id, &read_data);
    if (ret)
        return ret;

    *bit = (read_data >> pos) & 0x1;

    return ret;
}

/*
 * set a bit in the specific block
 */
static unsigned int sec_efuse_set_bit(unsigned int block_id, int pos)
{
    unsigned int write_data = 0;

    write_data = 1 << pos;

    return sec_efuse_write(block_id, write_data);
}

/*
 * write Hardware Unique Key (HUK)
 */
void sprd_huk_program(void)
{
    /* write HUK to efuse*/
    sprd_ce_efuse_huk_program();

    /* set lock bits*/
    set_lock_bits(HUK_BLOCK_START, HUK_BLOCK_END);
}

/*
 * write KCE efuse blocks
 */
unsigned int sprd_kce_program(unsigned int* pKceData)
{
    return sec_efuse_write_blocks(KCE_BLOCK_START, KCE_BLOCK_END, pKceData);
}

unsigned int sprd_rotpk0_program(unsigned int* pRotpkData)
{
    /* write Root of Trust Public Key Hash(ROTPK0) blocks */
    return sec_efuse_write_blocks_and_check(ROTPK0_BLOCK_START, ROTPK0_BLOCK_END, pRotpkData);
}

unsigned int sprd_rotpk1_program(unsigned int* pArotpkData)
{
    /* write Another Root of Trust Public Key Hash(ROTPK1) blocks */
    return sec_efuse_write_blocks_and_check(ROTPK1_BLOCK_START, ROTPK1_BLOCK_END, pArotpkData);
}

unsigned int sprd_get_version(sw_version_id_t counterId, unsigned int* swVersion)
{
    unsigned int i, reg_value, ret = SEC_EFUSE_OK;
    unsigned int version_bit_count = 0;
    unsigned int cntr_width, cntr_offset, cntr_sw_version;

    /* check input variables */
    if (swVersion == NULL)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    /* check for legal counter number */
    switch(counterId) {
    case SW_VERSION_COUNTER1:
        return sec_efuse_read(SEC_VERSION_BLOCK, swVersion);

    case SW_VERSION_COUNTER2:
        cntr_width  = VERSION_COUNTER2_WIDTH;
        cntr_offset = NSEC_VER_BLOCK_START;
        break;
    default:
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;
    }

    /* Read the SW version from the OTP, and accumulate number of ones */
    reg_value = 0;
    cntr_sw_version = 0;
    for(i = 0; i < cntr_width; i++) {
        ret = sec_efuse_read(cntr_offset + i, &reg_value);
        if (ret)
            return ret;

        /* return the number of 1 bits */
        COUNT_ONE_BITS(reg_value, version_bit_count);
        cntr_sw_version += version_bit_count;
    }

    *swVersion = cntr_sw_version;

    return ret;
}

unsigned int sprd_set_version(sw_version_id_t counterId, unsigned int swVersion)
{
    unsigned int i, reg_value, ret = SEC_EFUSE_OK;
    unsigned int cntr_width, cntr_offset;

    if (!swVersion)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    /* check for legal counter number */
    switch(counterId) {
    case SW_VERSION_COUNTER1:
        return sec_efuse_write_and_check(SEC_VERSION_BLOCK, swVersion);

    case SW_VERSION_COUNTER2:
        if (swVersion > SW_REVOCATION_MAX_NUM_OF_BITS_CNTR2)
            return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;
        cntr_width  = VERSION_COUNTER2_WIDTH;
        cntr_offset = NSEC_VER_BLOCK_START;
        break;
    default:
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;
    }

    /* Write new SW version to efuse */
    for(i=0; i < cntr_width; i++) {
        if (!swVersion)
            break;
        /* convert to base-1 representation */
        reg_value = ALL_ONES_VALUE >> (ALL_ONES_NUM_BITS - min(swVersion, ALL_ONES_NUM_BITS));
        swVersion -= min(swVersion, ALL_ONES_NUM_BITS);

        ret = sec_efuse_write_and_check(cntr_offset + i, reg_value);
        /* in case of failure in efuse write...*/
        if (ret)
            return ret;
    }

    return ret;
}

unsigned int sprd_endorkey_program(unsigned int* pEndorkeyData)
{
    /* write endorsement key */
    return sec_efuse_write_blocks_and_check(ENDORKEY_BLOCK_START, ENDORKEY_BLOCK_END, pEndorkeyData);
}

static unsigned int is_secure_boot_enable(void)
{
    return sprd_get_secure_boot_enable();
}

/* get device life cycle state.
 * CM: lock bit register is all 0.
 * DM: HUK lock bits is 1.
 * SECURE: HUK rotpk lock bits is 1.
 * RMA: LCS block bit0 is 1.
 */
#ifndef CONFIG_SOC_ORCA
unsigned int sprd_get_lcs(unsigned *pLcs)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int read_data = 0;
    unsigned int read_data1 = 0;
    unsigned int rma_bit = 0;
    unsigned int huk_bit = 0, huk_bit1 = 0;
    unsigned int rotpk0_bit = 0, rotpk0_bit1 = 0;
    unsigned int rotpk1_bit = 0, rotpk1_bit1 = 0;

    if (pLcs == NULL)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    ret = sec_efuse_read(LOCK_BIT_BLOCK, &read_data);
    if (ret)
        return ret;

    /* check lifecycle is CM */
    if (read_data == 0)
        *pLcs = CHIP_MANUFACTURE_LCS;

    sprd_get_lock_bits(HUK_BLOCK_START, HUK_BLOCK_END, &huk_bit, &huk_bit1);
    sprd_get_lock_bits(ROTPK0_BLOCK_START, ROTPK0_BLOCK_END, &rotpk0_bit, &rotpk0_bit1);
    sprd_get_lock_bits(ROTPK1_BLOCK_START, ROTPK1_BLOCK_END, &rotpk1_bit, &rotpk1_bit1);

    /* check lifecycle is DM */
    if ((read_data & huk_bit) == huk_bit)
        *pLcs = DEVICE_MANUFACTURE_LCS;

    if ((huk_bit1 != 0) || (rotpk0_bit1 !=0) || (rotpk1_bit1 != 0))
        sec_efuse_read(LOCK_BIT_BLOCK + 1, &read_data1);

    /* check lifecycle is sucrity */
    if ((((read_data & (huk_bit | rotpk0_bit)) == (huk_bit | rotpk0_bit))
        && ((read_data1 & (huk_bit1 | rotpk0_bit1)) == (huk_bit1 | rotpk0_bit1)))
        || (((read_data & (huk_bit | rotpk1_bit)) == (huk_bit | rotpk1_bit))
        && ((read_data1 & (huk_bit1 | rotpk1_bit1)) == (huk_bit1 | rotpk1_bit1))))
            *pLcs = SECURE_LCS;

    /* check lifecycle is rma */
    ret = sec_efuse_get_bit(CYCLE_STATE_BLOCK, RMA_MODE_BIT, &rma_bit);
    if (ret)
        return ret;

    if (rma_bit)
        *pLcs = RMA_LCS;
    return ret;
}
#else
unsigned int sprd_get_lcs(unsigned *pLcs)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int lock_buf[4] = {0};
    unsigned int lock_bit = 0xffff0;

    if (pLcs == NULL)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    efuse_read_lock_bits_map(lock_buf);
    if((lock_buf[0] & lock_bit) == lock_bit)
    {
        *pLcs = SECURE_LCS;
    }
    else
    {
        *pLcs = CHIP_MANUFACTURE_LCS;
    }
    return ret;
}
#endif

/*
 * write reserved blocks
 */
unsigned int sprd_reserved_efuse_program(unsigned int start_id, unsigned int end_id, unsigned int* pReservedData)
{
    if ((start_id < RESERVED_BLOCK_START) || (end_id > RESERVED_BLOCK_END))
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

    return sec_efuse_write_blocks_and_check(start_id, end_id, pReservedData);
}

unsigned int sprd_sec_efuse_blocks_read(unsigned int start_id, unsigned int end_id, unsigned int *readData)
{
    unsigned int ret = SEC_EFUSE_OK;
    unsigned int block_id;
    unsigned int *read_ptr = NULL;

    if (readData == NULL)
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;
#ifndef CONFIG_SOC_ORCA
    if (( start_id <= HUK_BLOCK_END) || (end_id <= HUK_BLOCK_END)
            || (start_id >= KCE_BLOCK_START && start_id <= KCE_BLOCK_END)
            || (end_id >= KCE_BLOCK_START && end_id <= KCE_BLOCK_END))
        return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;
#endif

    read_ptr = readData;
    for (block_id = start_id; block_id <= end_id; block_id++) {
        if (read_ptr == NULL)
            return SEC_EFUSE_POINTER_ERR;

        ret = sec_efuse_read(block_id, read_ptr);
        if (ret)
            return ret;
        read_ptr++;
    }

    return ret;
}

unsigned int sprd_sec_efuse_rotpk0_read(unsigned int *readData)
{
	return sprd_sec_efuse_blocks_read(ROTPK0_BLOCK_START, ROTPK0_BLOCK_END, readData);
}

unsigned int sprd_sec_efuse_rotpk1_read(unsigned int *readData)
{
	return sprd_sec_efuse_blocks_read(ROTPK1_BLOCK_START, ROTPK1_BLOCK_END, readData);
}

unsigned int sprd_sec_efuse_endorkey_read(unsigned int *readData)
{
	return sprd_sec_efuse_blocks_read(ENDORKEY_BLOCK_START, ENDORKEY_BLOCK_END, readData);
}

unsigned int sprd_sec_efuse_reserverd_read(unsigned int startOffset, unsigned int *readData, unsigned int len)
{
	int i, ret = SEC_EFUSE_OK;
	int start_block_id = RESERVED_BLOCK_START + startOffset;
	int end_offset = (len + ALL_ONES_NUM_BITS - 1)  / ALL_ONES_NUM_BITS - 1;
	int end_block_id = start_block_id + end_offset;
	int bit_mask = 0;
	int tmp_len = len % ALL_ONES_NUM_BITS;

	if ((len == 0) || (readData == NULL))
                return SEC_EFUSE_ILLEGAL_INPUT_PARAM_ERR;

	ret = sprd_sec_efuse_blocks_read(start_block_id, end_block_id, readData);
	if (ret)
		return ret;

	for (i = 0; i < tmp_len; i++)
	{
		bit_mask |= 1 << i;
	}
	readData[end_offset] &= bit_mask;
	return ret;
}

unsigned int sprd_sec_efuse_rotpk_select(unsigned int *rpkFlag)
{
    return sec_efuse_get_bit(CYCLE_STATE_BLOCK, 1, rpkFlag);
}

