/*
 * Copyright (c) 2015, Spreadtrum.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */
#include <common.h>
#include <asm/io.h>
#include <linux/types.h>
#include <sci_types.h>
#include <security/sec_efuse.h>
#include <timer.h>

extern void sci_efuse_poweron(void);
extern void sci_efuse_poweroff(void);
extern int sci_efuse_read(unsigned blk);

uint32_t sec_efuse_gettickcnt(void)
{
    return sprd_get_syscnt();
}

void sec_efuse_mdelay(uint32_t val)
{
    uint32_t pre_tick, cur_tick;
    pre_tick = sec_efuse_gettickcnt();	/*set start tick value */
    cur_tick = pre_tick;
    while (cur_tick - pre_tick < val) {
        cur_tick = sec_efuse_gettickcnt();
    }
}

#if 0
static inline void sec_efuse_udelay(uint32_t usec)
{
    uint32_t i;
    for (i = 0; i < usec; i++);
}
#endif

static inline void write32(uint32_t val, uint32_t addr)
{
    *(volatile uint32_t *)addr = val;
}

static inline uint32_t read32(uint32_t addr)
{
    return *(volatile uint32_t *)addr;
}

static void sec_efuse_open(uint32_t op_type)
{
    uint32_t ce_reg_data;

    //enable secure efuse & sec ce
    ce_reg_data = read32(REG_AP_AHB_EN);
    ce_reg_data |=  BIT(6) | BIT(12) | BIT(23);
    write32(ce_reg_data, REG_AP_AHB_EN);

    //enable ce efuse controller
    ce_reg_data = read32(SEC_CE_EFUSE_REG_CFG0);
    ce_reg_data |= BIT(30);
    write32(ce_reg_data, SEC_CE_EFUSE_REG_CFG0);

    if(op_type == SEC_EFUSE_OP_WRITE)
    {
        ce_reg_data = read32(SEC_CE_EFUSE_REG_CFG0);
        ce_reg_data &= ~(BIT(29));
        write32(ce_reg_data, SEC_CE_EFUSE_REG_CFG0);

        sec_efuse_mdelay(1);

        ce_reg_data = read32(SEC_CE_EFUSE_REG_CFG0);
        ce_reg_data |= BIT(28);
        write32(ce_reg_data, SEC_CE_EFUSE_REG_CFG0);

        sec_efuse_mdelay(1);
    }
}

static void sec_efuse_close(uint32_t op_type)
{
    uint32_t ce_reg_data;

    //disable ce efuse controller
    if(op_type == SEC_EFUSE_OP_WRITE)
    {
        ce_reg_data = read32(SEC_CE_EFUSE_REG_CFG0);
        ce_reg_data &= ~(BIT(28));
        write32(ce_reg_data, SEC_CE_EFUSE_REG_CFG0);

        sec_efuse_mdelay(1);

        ce_reg_data = read32(SEC_CE_EFUSE_REG_CFG0);
        ce_reg_data |= BIT(29);
        write32(ce_reg_data, SEC_CE_EFUSE_REG_CFG0);
    }

    ce_reg_data = read32(SEC_CE_EFUSE_REG_CFG0);
    ce_reg_data &= ~(BIT(30));
    write32(ce_reg_data, SEC_CE_EFUSE_REG_CFG0);

    //disable secure efuse & sec ce
    ce_reg_data = read32(REG_AP_AHB_EN);
    ce_reg_data &= ~( BIT(6) | BIT(12) | BIT(23));
    write32(ce_reg_data, REG_AP_AHB_EN);
}

static Efuse_Result_Ret sprd_ce_efuse_set_protect_flag(uint32_t start_id, uint32_t end_id)
{
    uint32_t ce_reg_data;
    uint32_t block_id_mask0 = 0;
    uint32_t block_id_mask1 = 0;
    uint32_t i;

    sec_efuse_open(SEC_EFUSE_OP_WRITE);

    if((start_id > SEC_EFUSE_PROT_BLOCK_MAX_ID) ||
            (end_id > SEC_EFUSE_PROT_BLOCK_MAX_ID) ||
            (start_id > end_id))
    {
        return EFUSE_PARAM_ERROR;
    }

    for(i=start_id; i<=end_id; i++)
    {
        if(i < 32)
        {
            block_id_mask0 |= BIT(i);
        }
        else
        {
            block_id_mask1 |= BIT(i-32);
        }
    }

    if(!block_id_mask0)
    {
        sprd_ce_efuse_read(SEC_EFUSE_BLOCK_WR_PROT0, &ce_reg_data);
        ce_reg_data |= block_id_mask0;
        sprd_ce_efuse_program(SEC_EFUSE_BLOCK_WR_PROT0, ce_reg_data);
    }

    if(!block_id_mask1)
    {
        sprd_ce_efuse_read(SEC_EFUSE_BLOCK_WR_PROT1, &ce_reg_data);
        ce_reg_data |= block_id_mask1;
        sprd_ce_efuse_program(SEC_EFUSE_BLOCK_WR_PROT1, ce_reg_data);
    }

    sec_efuse_close(SEC_EFUSE_OP_WRITE);

    return EFUSE_RESULT_SUCCESS;
}

Efuse_Result_Ret sprd_ce_efuse_program(unsigned int block_id, unsigned int WriteData)
{
    uint32_t ce_reg_addr;
    uint32_t ce_reg_data;

    if((block_id < SEC_EFUSE_BLOCK_ENWR_START_ID) || (block_id > SEC_EFUSE_BLOCK_MAX_ID))
    {
        return EFUSE_ID_ERROR;
    }

    sec_efuse_open(SEC_EFUSE_OP_WRITE);

    ce_reg_addr = REG_AP_CE_KEY_BASE_OFFSET + block_id*0x4;

    //init config
    ce_reg_data = read32(SEC_CE_REG_KEY_USE_WAY);

    ce_reg_data |= BIT(30) | BIT(29);
    write32(ce_reg_data, SEC_CE_REG_KEY_USE_WAY);

    //block id set
    ce_reg_data = 0;
    ce_reg_data |= (block_id<<0) | (block_id<<8);
    write32(ce_reg_data, SEC_CE_REG_KEY_SYNC_ADDR);

    //write
    write32(WriteData, ce_reg_addr);
    ce_reg_data = read32(ce_reg_addr);

    //sync data to efuse
    ce_reg_data = read32(SEC_CE_REG_KEY_USE_WAY);

    ce_reg_data &= ~(BIT(29));
    write32(ce_reg_data, SEC_CE_REG_KEY_USE_WAY);

    ce_reg_data |= BIT(29);
    write32(ce_reg_data, SEC_CE_REG_KEY_USE_WAY);

    while(((*(volatile uint32_t*)(SEC_CE_EFUSE_REG_STATUS))&(BIT(5))) != 0x00);

#ifdef SEFUSE_DEBUG
    //read back data
    ce_reg_data = 0;
    ce_reg_data |= (block_id<<0) | (block_id<<8);
    write32(ce_reg_data, SEC_CE_EFUSE_REG_RD_INDEX);

    ce_reg_data = read32(SEC_CE_EFUSE_REG_MODE_CTRL);
    ce_reg_data |= BIT(3);
    write32(ce_reg_data, SEC_CE_EFUSE_REG_MODE_CTRL);

    //read back data efuse
    ce_reg_data = read32(ce_reg_addr);
#endif

    //release & check read prot & err status
    ce_reg_data = read32(SEC_CE_EFUSE_REG_STATUS_ERR);
    //clear pro status
    write32(0xFFFFFFFF, SEC_CE_EFUSE_REG_CLR_ERR);

    ce_reg_data = read32(SEC_CE_EFUSE_REG_STATUS_PROT);
    //clear err status
    write32(0xFFFFFFFF, SEC_CE_EFUSE_REG_CLR_PROT);

    sec_efuse_close(SEC_EFUSE_OP_WRITE);
    return EFUSE_RESULT_SUCCESS;
}

Efuse_Result_Ret sprd_ce_efuse_read(unsigned int block_id, unsigned int *pReadData)
{
    uint32_t ce_reg_addr;
    uint32_t ce_reg_data;

    if(!pReadData)
    {
        return EFUSE_PARAM_ERROR;
    }

    if(block_id > SEC_EFUSE_BLOCK_MAX_ID)
    {
        return EFUSE_ID_ERROR;
    }

    if( block_id <=  KCE_BLOCK_END )
    {
        *pReadData = 0;
        return EFUSE_RESULT_SUCCESS;
    }

    sec_efuse_open(SEC_EFUSE_OP_READ);

    ce_reg_addr = REG_AP_CE_KEY_BASE_OFFSET + block_id*0x4;

    //init config
    ce_reg_data = read32(SEC_CE_REG_KEY_USE_WAY);

    ce_reg_data |= BIT(30) | BIT(29);
    write32(ce_reg_data, SEC_CE_REG_KEY_USE_WAY);

    //block id set
    ce_reg_data = 0;
    ce_reg_data |= (block_id<<0) | (block_id<<8);
    write32(ce_reg_data, SEC_CE_REG_KEY_SYNC_ADDR);

    //write for read back
    write32(0x00, ce_reg_addr);
    ce_reg_data = read32(ce_reg_addr);

    //sync data to efuse
    ce_reg_data = 0;
    ce_reg_data |= (block_id<<0) | (block_id<<8);
    write32(ce_reg_data, SEC_CE_EFUSE_REG_RD_INDEX);

    ce_reg_data = read32(SEC_CE_EFUSE_REG_MODE_CTRL);
    ce_reg_data |= BIT(3);
    write32(ce_reg_data, SEC_CE_EFUSE_REG_MODE_CTRL);

    while(((*(volatile uint32_t*)(SEC_CE_EFUSE_REG_STATUS))&(BIT(4))) != 0x00);

    //read back data efuse
    *pReadData = read32(ce_reg_addr);

    //release & check read prot & err status
    ce_reg_data = read32(SEC_CE_EFUSE_REG_STATUS_ERR);
    //clear pro status
    write32(0xfffffffff, SEC_CE_EFUSE_REG_CLR_ERR);

    ce_reg_data = read32(SEC_CE_EFUSE_REG_STATUS_PROT);
    //clear err status
    write32(0xfffffffff, SEC_CE_EFUSE_REG_CLR_PROT);

    sec_efuse_close(SEC_EFUSE_OP_READ);
    return EFUSE_RESULT_SUCCESS;
}

Efuse_Result_Ret sprd_ce_efuse_huk_program(void)
{
    uint32_t ce_reg_data;
    uint32_t cnt = 0;

    sec_efuse_open(SEC_EFUSE_OP_WRITE);

    //setup clk
    ce_reg_data = read32(SEC_CE_REG_CLK_EN);

    ce_reg_data |= BIT(5);
    write32(ce_reg_data, SEC_CE_REG_CLK_EN);

    //rng config
    ce_reg_data = read32(SEC_CE_REG_RNG_EN);

    ce_reg_data |= (BIT(1));
    write32(ce_reg_data, SEC_CE_REG_RNG_EN);

    ce_reg_data = read32(SEC_CE_REG_RNG_EN);

    ce_reg_data |= (BIT(0));
    write32(ce_reg_data, SEC_CE_REG_RNG_EN);

    //start huk write
    ce_reg_data = read32(SEC_CE_REG_KEY_USE_WAY);

    ce_reg_data |= BIT(31);
    write32(ce_reg_data, SEC_CE_REG_KEY_USE_WAY);

    while(1)
    {
        ce_reg_data = read32(SEC_CE_REG_KEY_USE_WAY);

        if(!(ce_reg_data & BIT(31)))
        {
            //debug("huk write done. \n");
            sprd_ce_efuse_set_protect_flag(HUK_BLOCK_START, HUK_BLOCK_END);
            break;
        }
        if(cnt > 32)
        {
            //debug("wait for op complete,  time out... \n");
            return EFUSE_WR_ERROR;
        }
        cnt++;
    }

    //release
    ce_reg_data = read32(SEC_CE_REG_CLK_EN);
    ce_reg_data &= ~(BIT(5));
    write32(ce_reg_data, SEC_CE_REG_CLK_EN);

    ce_reg_data = read32(SEC_CE_REG_RNG_EN);
    ce_reg_data &= ~(BIT(0) | BIT(1));
    write32(ce_reg_data, SEC_CE_REG_RNG_EN);

    sec_efuse_close(SEC_EFUSE_OP_WRITE);
    return EFUSE_RESULT_SUCCESS;
}

Efuse_Result_Ret sprd_get_lock_bits(unsigned int start_id, unsigned int end_id, unsigned int *bits_data, unsigned int *bits_data1)
{
    uint32_t block_id_mask0 = 0;
    uint32_t block_id_mask1 = 0;
    uint32_t i;

    if((start_id > SEC_EFUSE_PROT_BLOCK_MAX_ID) ||
            (end_id > SEC_EFUSE_PROT_BLOCK_MAX_ID) ||
            (start_id > end_id))
    {
        return EFUSE_PARAM_ERROR;
    }

    for(i=start_id; i<=end_id; i++)
    {
        if(i < 32)
        {
            block_id_mask0 |= BIT(i);
        }
        else
        {
            block_id_mask1 |= BIT(i-32);
        }
    }

    *bits_data = block_id_mask0;
    *bits_data1 = block_id_mask1;

    return EFUSE_RESULT_SUCCESS;
}

unsigned int sprd_get_secure_boot_enable(void)
{
    uint32_t read_bit;

    sci_efuse_poweron();

    read_bit = sci_efuse_read(PUBLIC_EFUSE_BLOCK2);

    read_bit &= 1;

    sci_efuse_poweroff();
    return read_bit;
}
