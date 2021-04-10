/*
 * Copyright (C) 2014 Spreadtrum Communications Inc.
 *
 * This software is licensed under the terms of the GNU General Public
 * License version 2, as published by the Free Software Foundation, and
 * may be copied, distributed, and modified under those terms.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */
#define SPRDNAND_UBOOT

#ifdef SPRDNAND_UBOOT
#include <config.h>
#include <asm/io.h>
#include <linux/types.h>
#include <nand.h>
#include <linux/mtd/nand.h>
#include <common.h>
#include <malloc.h>
#include <asm/errno.h>
#include "sprd_nand.h"
#include <asm/arch/sprd_reg.h>
#include <asm/arch/pinmap.h>

#define SPRD_ASSERT(cond) { if (!(cond)) while(1); }
#define STATIC_FUNC
#define DPRINT printf
#include "sprd_nand_param.h"
#include "nfc_base.h"

#endif

//#define _DEBUG_NAND_
#ifdef _DEBUG_NAND_
#define _END_FLAG 0x4E414E44
#endif

extern uint32_t 	address_debug;

typedef struct {
	uint8_t id[NFC_MAX_ID_LEN];
	uint32_t nBlkCnt;
	uint32_t nPagePerBlk;
	uint32_t nSectPerPage;
	uint32_t nSecSize;
	uint32_t nSpareSize;

	uint32_t badFlag_pos;
	uint32_t badFlag_len;
	uint32_t ecc_mode;
	uint32_t ecc_pos;
	uint32_t ecc_size;
	uint32_t info_pos;
	uint32_t info_size;

	uint8_t nBusWidth;
	uint8_t nCycle;

	// ACS
	uint32_t T_als;		// ale enable --> 1st we enable
	uint32_t T_cls;		// cle enable --> 1st we enable
	// ACE
	uint32_t T_clh;		// last we disable --> cle disable
	uint32_t T_alh;		// last we disable --> ale disable
	// RWS
	uint32_t T_rr;		// RB busy --> re enable when read
	uint32_t T_adl;		// last addr we --> 1st data we enable when write
	// RWE
	//uint32_t              // 5ns when read
	//uint32_t;             // 0 when write
	// RWH & RWL
	uint32_t T_wh;		// we high when write
	uint32_t T_wp;		// we low       when wirte
	uint32_t T_reh;		// re high when read
	uint32_t T_rp;		// re low when read
} NAND_PARAM;

typedef struct {
// resource0: interrupt id & clock name & register bass address
	uint32_t irq;
	uint32_t frequence;
	void __iomem *ioaddr;
// resource1: nand param & mtd ecclayout & risk threshold & nessisary const value
	NAND_PARAM param;
	uint32_t eccModeReg;
	uint32_t risk_threshold;
	uint32_t cs[_CFG0_CS_MAX];
	uint32_t csNum;

	uint32_t csDis;
	uint32_t sectPerPgShift;
	uint32_t sectShift;
	uint32_t sectMsk;
	uint32_t pageShift;
	uint32_t blkShift;
	uint32_t bufShift;
// resource3: local DMA buffer
	uint8_t *mBuf_p;
	uint8_t *mBuf_v;
	uint8_t *sBuf_p;
	uint8_t *sBuf_v;
	uint8_t *stsBuf_p;
	uint8_t *stsBuf_v;
// resource4: register base value. some value is const while operate on nand flash, we store it to local valuable.
// Time & cfg & status mach. It is different with operation R W E.
	uint32_t NFC_Time0_R;
	uint32_t NFC_Time0_W;
	uint32_t NFC_Time0_E;
	uint32_t NFC_start;
	uint32_t NFC_cfg0;
	uint32_t NFC_cfg1;
	uint32_t NFC_cfg2;

	uint32_t NFC_time0_val;
	uint32_t NFC_cfg0_val;
	uint32_t NFC_sts_mach_val;
} NAND_CTL;
// there is only one nand controller, So we define it here as globe.
STATIC_FUNC NAND_CTL controller;
STATIC_FUNC NFC_BASE_T nfc_base;

#ifndef SPRD_NAND_CLOCK
#define SPRD_NAND_CLOCK	(195)
#endif
static struct sprd_nand_timing default_timing = {10, 25, 15};

static uint32_t mMcInsNum;
typedef struct {
	uint8_t *programName;
	uint32_t cnt;
	uint32_t step_tag;
	uint32_t intBits;	// if use interrupt , this bitMap indicate which interrupt will be used
	uint32_t inst[NFC_MAX_MC_INST_NUM];
} NAND_INST;

#define _cmd_init(x,name,intBits_p)	{\
	memset(&x,0,sizeof(NAND_INST));\
	x.programName = name;\
	x.intBits=(intBits_p);\
}
#define _cmd_add(x,inst_p)	{\
	x.inst[x.cnt] = (inst_p);\
	x.cnt++;\
}
#define _cmd_tag(x)	{x.step_tag=x.cnt;}
#define _cmd_change(x,pg)	{\
	x->inst[x->step_tag] = _INST_ADDR(((pg)&0xFF),1);	\
	x->inst[x->step_tag+1] = _INST_ADDR((((pg)>>8)&0xFF),0);	\
	if(5 == this->param.nCycle)	{\
		x->inst[x->step_tag+2] = _INST_ADDR((((pg)>>16)&0xFF),0);	\
	}\
}
#define  SEED_TBL_SIZE 64
#define  SEED_TBL_MAX  68
uint32_t seedBuf[SEED_TBL_MAX];

static const uint32_t seedTbl[SEED_TBL_SIZE] = {
	0x056c,		0x1bc77,	0x5d356,	0x1f645d,
	0x0fbc,		0x0090c,	0x7f880,	0x3d9e86,
	0x1717,		0x1e1ad,	0x6db67,	0x7d7ea0,
	0x0a52,		0x0d564,	0x6fbac,	0x6823dd,
	0x07cf,		0x1cb3b,	0x37cd1,	0x5c91f0,
	0x064e,		0x167a7,	0x0f1d2,	0x506be8,
	0x098c,		0x1bd54,	0x2c2af,	0x4b5fb7,
	0x1399,		0x11690,	0x1d310,	0x27e53b,
	0x1246,		0x14794,	0x0f34f,	0x347bc4,
	0x0150,		0x00787,	0x73450,	0x3d8927,
	0x11f1,		0x17bad,	0x46eaa,	0x5403f5,
	0x1026,		0x173ab,	0x79634,	0x01b987,
	0x1c45,		0x08b63,	0x42924,	0x4bf708,
	0x012a,		0x03a3a,	0x435d5,	0x1a7baa,
	0x0849,		0x1cb9b,	0x28350,	0x1e8309,
	0x1d4c,		0x0af6e,	0x0949e,	0x00193a,
};

void GenPageSeed(uint32_t pageId)
{
	uint32_t offset = 0;
	uint32_t numbit = 0;
	uint32_t mask = 0;
	uint32_t shift = 0;
	uint32_t remain = 0;
	uint32_t i = 0;
	uint32_t j = 0;

	if(pageId & (~0xff))
		return;

	memset(seedBuf,0,sizeof(seedBuf));
	offset = pageId >> 4;
	for(i = 0; i < SEED_TBL_SIZE;i++)
	{
		switch(i & 0x3)
		{
			case 0:numbit = 13;break;
			case 1:numbit = 17;break;
			case 2:numbit = 19;break;
			case 3:numbit = 23;break;
		}
		for(j = 0;j <= numbit - 1;j++)
		{
			if(seedTbl[i] & (1 << j))
			{
				seedBuf[i] |= 1 << (numbit - 1 - j);
			}
		}
		if(offset)
		{
			if(offset > numbit - 1)
			{
				shift = offset - numbit;
			}
			else
			{
				shift = offset;
			}
			mask = ((1 << numbit) - 1) >> shift;
			remain = seedBuf[i] & ~mask;
			remain >>= numbit - shift;
			seedBuf[i] &= mask;
			seedBuf[i] <<= shift;
			seedBuf[i] |= remain;			
		}
	}
	// 15
	seedBuf[SEED_TBL_SIZE] = seedBuf[0];
	seedBuf[SEED_TBL_SIZE+1] = seedBuf[1];
	seedBuf[SEED_TBL_SIZE+2] = seedBuf[2];
	seedBuf[SEED_TBL_SIZE+3] = seedBuf[3];
	
}

void NandSetRandomizer (NAND_CTL * this,uint32_t seedAddr)
{
	__32reg_write(NFC_POLY0_REG,0x100d);
	__32reg_write(NFC_POLY1_REG,0x10004);
	__32reg_write(NFC_POLY2_REG,0x40013);
	__32reg_write(NFC_POLY3_REG,0x400010);
	__32reg_write(NFC_POLY4_REG,0x100d);
	__32reg_write(NFC_POLY5_REG,0x10004);
	__32reg_write(NFC_POLY6_REG,0x40013);
	__32reg_write(NFC_POLY7_REG,0x400010);
	__32reg_write(NFC_SEED_ADDRH_REG,0);
	__32reg_write(NFC_SEED_ADDRL_REG,seedAddr);
	__32reg_write(NFC_CFG3_REG,_CFG3_RANDOM_EN | _CFG3_USE_POLY4R1_SEL(1) | _CFG3_DETECT_ALL_FF);//use 8 polynomial and enalbe randomizing
}

void nfc_dump(uint32_t nand_ctl){
	unsigned int i;

	printf( "=========== DDR  REGISTER DUMP ===========\n");
	for (i = 0; i < 0x40; i++) {
		printf("0x%08x | 0x%08x | 0x%08x | 0x%08x\n",
		       readl(nand_ctl + (i << 4)), readl(nand_ctl + 4 + (i << 4)),
		       readl(nand_ctl + 8 + (i << 4)), readl(nand_ctl + 12 + (i << 4)));
	}
	printf( " ===========================================\n");
	mdelay(10);
}

STATIC_FUNC void _cmd_exec(NAND_CTL * this, NAND_INST * program, uint32_t repeat, uint32_t ifUseInt)
{
	uint32_t i;
	this->NFC_cfg0_val |= _CFG0_SET_REPEAT_NUM(repeat);
	__32reg_write(NFC_CFG0_REG, this->NFC_cfg0_val);
	__32reg_write(NFC_TIMING0_REG, this->NFC_time0_val);
	__32reg_write(NFC_STAT_STSMCH_REG, this->NFC_sts_mach_val);

	for (i = 0; i < program->cnt; i += 2) {
		__32reg_write(NFC_INST0_REG + (i << 1), (program->inst[i] | (program->inst[i + 1] << 16)));
	}
//---
	if (!ifUseInt) {
		__int_dis_all();
		__int_clr_all();
	} else {
		__int_dis_all();
		__int_clr_all();
		__int_en(program->intBits);
	}
//---
	__32reg_write(NFC_START_REG, this->NFC_start | _CTRL_NFC_CMD_START);
}

STATIC_FUNC int _cmd_wait(NAND_CTL * this, NAND_INST * program, uint32_t ifUseInt)
{				//checked
	uint32_t regVal;
	int ret = -EIO;
	int32_t nfc_timeout_val = 0;
	int32_t soft_timeOut = 12000000;
	int32_t reset_soft_timeOut = 600000;

	if (program->programName == "_inst_reset") {
			nfc_timeout_val = reset_soft_timeOut;
	} else {
			nfc_timeout_val = soft_timeOut;
	}

	if (!ifUseInt) {
		do {
			regVal = __int_rawsts_get();
			if ((_INT_TO | _INT_STSMCH | _INT_WP) & regVal & program->intBits) {
				ret = -EIO;
				break;
			} else if (_INT_DONE & regVal & program->intBits) {
				ret = 0;
				break;
			}
		nfc_timeout_val--;
		} while (nfc_timeout_val > 0);
	} else {
		// to do something.
	}

	if (ret) {
		printk(KERN_ERR "sprd nand cmd %s fail\n", program->programName);
		print_hex_dump(KERN_ERR, "", DUMP_PREFIX_OFFSET, 32, 4, (void *)SPRD_NFC_BASE, 0x140, 1);
		dump_stack();
	}
	return ret;
}

STATIC_FUNC NAND_INST _inst_reset = {	//checked
	"_inst_reset",
	3, 0, _INT_TO | _INT_DONE, {
				    _INST_CMD(0xFF),
				    _INST_WRB0(),
				    _INST_DONE()
				    }
};

STATIC_FUNC NAND_INST _inst_readId = {	//checked
	"_inst_readId",
	5, 0, _INT_TO | _INT_DONE, {
				    _INST_CMD(0x90),
				    _INST_ADDR(0, 0),
				    _INST_INOP(10),
				    _INST_IDST(0x08),
				    _INST_DONE()
				    }
};

STATIC_FUNC NAND_INST _inst_nop = {	//checked
	"_inst_nop",
	2, 0, _INT_TO | _INT_DONE, {
				    _INST_INOP(2),
				    _INST_DONE()
				    }
};

STATIC_FUNC NAND_INST _inst_read_main_spare;
STATIC_FUNC NAND_INST _inst_read_main_raw;
STATIC_FUNC NAND_INST _inst_read_spare_raw;
STATIC_FUNC NAND_INST _inst_write_main_spare;
STATIC_FUNC NAND_INST _inst_write_main_raw;
STATIC_FUNC NAND_INST _inst_write_spare_raw;
STATIC_FUNC NAND_INST _inst_erase;

/*
	this is used for nand id and reset cmd
*/
STATIC_FUNC void _init_reg_state0(NAND_CTL * this)
{				//checked
	this->NFC_cfg0 = 0x0;
	__32reg_write(NFC_CFG0_REG, this->NFC_cfg0);
	__32reg_write(NFC_CFG4_REG, 0x1017e);

	__32reg_write(NFC_MAIN_ADDRH_REG, _RAM_MAIN_ADDR(-1));
	__32reg_write(NFC_MAIN_ADDRL_REG, _RAM_MAIN_ADDR(-1));
	__32reg_write(NFC_SPAR_ADDRH_REG, _RAM_SPAR_ADDR(-1));
	__32reg_write(NFC_SPAR_ADDRL_REG, _RAM_SPAR_ADDR(-1));
	__32reg_write(NFC_STAT_ADDRH_REG, _RAM_STAT_ADDR(-1));
	__32reg_write(NFC_STAT_ADDRL_REG, _RAM_STAT_ADDR(-1));

}

#ifdef _DEBUG_NAND_
STATIC_FUNC void _chkMem(NAND_CTL * this)
{
	uint32_t mBuf_size = (1 << this->bufShift);
	uint32_t sBuf_size = (1 << (this->bufShift - this->sectShift)) * this->param.nSpareSize;
	uint32_t stsBuf_size = (1 << (this->bufShift - this->sectShift));
	if ((_END_FLAG != *((uint32_t *) (&(this->mBuf_v[mBuf_size]))))
	    || (_END_FLAG != *((uint32_t *) (&(this->sBuf_v[sBuf_size]))))
	    || (_END_FLAG != *((uint32_t *) (&(this->stsBuf_v[stsBuf_size]))))
	    ) {
		printk(KERN_ERR "sprd nand memory overlapped");
	}
}
#endif

STATIC_FUNC void _selectCS(NAND_CTL * this, int cs)
{
	this->NFC_cfg0 = (this->NFC_cfg0 & _CFG0_CS_MSKCLR) | _CFG0_SET_CS_SEL(cs);
}

STATIC_FUNC int __reset(NAND_CTL * this)
{
	NAND_INST *inst = &_inst_reset;

	this->NFC_sts_mach_val = _DEF0_MATCH;
	this->NFC_time0_val = this->NFC_Time0_R;
	this->NFC_cfg0_val = this->NFC_cfg0 | _CFG0_SET_NFC_MODE(0x2);
	_cmd_exec(this, inst, 1, 0);
	return _cmd_wait(this, inst, 0);
}

STATIC_FUNC int __readId(NAND_CTL * this)
{
	NAND_INST *inst = &_inst_readId;
	int ret;
	uint32_t id0, id1;
	static uint32_t ifHasRead = 0;

	this->NFC_sts_mach_val = _DEF0_MATCH;
	//this->NFC_time0_val = this->NFC_Time0_R;
	this->NFC_cfg0_val = this->NFC_cfg0 | _CFG0_SET_NFC_MODE(0x2);
	//this->NFC_time0_val = (0x1f ) | (7 << 6) | (0x1f << 11) | (0x1f << 16) | (0x1f << 22) | (0x1f << 27);
	_cmd_exec(this, inst, 1, 0);
	ret = _cmd_wait(this, inst, 0);
	if (0 != ret) {
		return ret;
	}
	id0 = __32reg_read(NFC_STATUS0_REG);
	id1 = __32reg_read(NFC_STATUS1_REG);
	if (0 == ifHasRead) {
		ifHasRead = 1;
		this->param.id[0] = (uint8_t) (id0 & 0xFF);
		this->param.id[1] = (uint8_t) ((id0 >> 8) & 0xFF);
		this->param.id[2] = (uint8_t) ((id0 >> 16) & 0xFF);
		this->param.id[3] = (uint8_t) ((id0 >> 24) & 0xFF);
		this->param.id[4] = (uint8_t) (id1 & 0xFF);
		this->param.id[5] = (uint8_t) ((id1 >> 8) & 0xFF);
		this->param.id[6] = (uint8_t) ((id1 >> 16) & 0xFF);
		this->param.id[7] = (uint8_t) ((id1 >> 24) & 0xFF);
	} else if ((this->param.id[0] != (uint8_t) (id0 & 0xFF))
		   || (this->param.id[1] != (uint8_t) ((id0 >> 8) & 0xFF))
		   || (this->param.id[2] != (uint8_t) ((id0 >> 16) & 0xFF))
		   || (this->param.id[3] != (uint8_t) ((id0 >> 24) & 0xFF))
		   || (this->param.id[4] != (uint8_t) (id1 & 0xFF))
		   || (this->param.id[5] != (uint8_t) ((id1 >> 8) & 0xFF))
		   || (this->param.id[6] != (uint8_t) ((id1 >> 16) & 0xFF))
		   || (this->param.id[7] != (uint8_t) ((id1 >> 24) & 0xFF))) {
		return -EINVAL;
	}
	return ret;
}

STATIC_FUNC void _deSelectCS(NAND_CTL * this, int ret)
{
	if (-EIO == ret) {
		__32reg_write(NFC_START_REG, _CTRL_NFC_CMD_CLR);
		__reset(this);
	}
#ifndef _DEBUG_NAND_
	this->NFC_cfg0 = (this->NFC_cfg0 & _CFG0_CS_MSKCLR) | _CFG0_SET_CS_SEL(this->csDis);
	__32reg_write(NFC_CFG0_REG, this->NFC_cfg0);
#endif
}

STATIC_FUNC void nand_set_timing_config(NAND_CTL * this,struct sprd_nand_timing *timing  , uint32_t nfc_clk_MHz) {
	u32 reg_val, temp_val;

		reg_val = 0;

		/* get acs value : 0ns */
		reg_val |= ((2 & 0x1F) << NFC_ACS_OFFSET);

		/* temp_val: 0: 1clock, 1: 2clocks... */
		temp_val = timing->ace_ns * nfc_clk_MHz / 1000 - 1;
		if (((timing->ace_ns * nfc_clk_MHz) % 1000)  != 0) {
			temp_val++;
		}
		reg_val |= ((temp_val & 0x1F) << NFC_ACE_OFFSET);

		/* get rws value : 20 ns */
		temp_val = 20 * nfc_clk_MHz / 1000 - 1;
		reg_val |= ((temp_val & 0x3F) << NFC_RWS_OFFSET);

		/* get rwe value : 0 ns */
		reg_val |= ((2 & 0x1F) << NFC_RWE_OFFSET);

		/* get rwh value,if the remainder bigger than 500, then plus 1 for more accurate*/
		temp_val = timing->rwh_ns * nfc_clk_MHz / 1000 -1;
		if (((timing->rwh_ns * nfc_clk_MHz) % 1000)  >= 500) {
			temp_val++;
		}
		reg_val |= ((temp_val & 0x1F) << NFC_RWH_OFFSET);

		/* get rwl value,if the remainder bigger than 500, then plus 1 for more accurate*/
		temp_val = timing->rwl_ns * nfc_clk_MHz / 1000 - 1;
		if (((timing->rwh_ns * nfc_clk_MHz) % 1000)  >= 500) {
			temp_val++;
		}
		reg_val |= (temp_val & 0x3F);

		DPRINT("%s nand timing val: 0x%x, base clk:%d\n\r", __func__, reg_val, nfc_clk_MHz);

		this->NFC_Time0_R = reg_val ;
		this->NFC_Time0_W = reg_val;
		this->NFC_Time0_E = reg_val;

}

STATIC_FUNC int __param_init_nandHWInfo(NAND_CTL * this)
{				//pass
	struct sprd_nand_param *param;

// get base param info
	param = SprdGetNandParam(this->param.id);
	if (!param) {
		return -EINVAL;
	}
	nand_set_timing_config(this, &(param->sTiming), SPRD_NAND_CLOCK);
	this->param.nBlkCnt = param->nBlkNum;
	this->param.nPagePerBlk = param->nBlkSize / param->nPageSize;
	this->param.nSectPerPage = param->nPageSize / param->nSecSize;
	this->param.nSecSize = param->nSecSize;
	this->param.nSpareSize = param->sOOB.nOOBSize;

	this->param.badFlag_pos = 0;	// --- default:need fixed
	this->param.badFlag_len = 2;	// --- default:need fixed
	this->param.ecc_mode = param->sOOB.nEccBits;
	this->param.ecc_pos = param->sOOB.nEccPos;
	this->param.ecc_size = param->sOOB.nEccSize;
	this->param.info_pos = param->sOOB.nInfoPos;
	this->param.info_size = param->sOOB.nInfoSize;

	this->param.nBusWidth = param->nBusWidth;
	this->param.nCycle = param->nCycles;


// setting globe param seting
	switch (this->param.ecc_mode) {
	case 1:
		this->risk_threshold = 1;
		this->eccModeReg = 0;
		break;
	case 2:
		this->risk_threshold = 1;
		this->eccModeReg = 1;
		break;
	case 4:
		this->risk_threshold = 2;
		this->eccModeReg = 2;
		break;
	case 8:
		this->risk_threshold = 4;
		this->eccModeReg = 3;
		break;
	case 12:
		this->risk_threshold = 6;
		this->eccModeReg = 4;
		break;
	case 16:
		this->risk_threshold = 8;
		this->eccModeReg = 5;
		break;
	case 24:
		this->risk_threshold = 12;
		this->eccModeReg = 6;
		break;
	case 40:
		this->risk_threshold = 20;
		this->eccModeReg = 7;
		break;
	case 60:
		this->risk_threshold = 30;
		this->eccModeReg = 8;
		break;
	default:
		panic("sprd nand ecc mode not support!\n");
		return -EINVAL;
		break;
	}

	this->sectPerPgShift = ffs(this->param.nSectPerPage) - 1;
	this->sectShift = ffs(this->param.nSecSize) - 1;
	this->sectMsk = (1 << this->sectShift) - 1;
	this->pageShift = ffs(this->param.nSectPerPage << this->sectShift) - 1;
	this->blkShift = ffs(this->param.nPagePerBlk << this->pageShift) - 1;
	this->bufShift = ffs(NFC_MBUF_SIZE) - 1;
	this->bufShift = min(this->bufShift, this->blkShift);
	return 0;
}

STATIC_FUNC void __param_init_inst(NAND_CTL * this)
{
	uint32_t column = (1 << this->pageShift);
	if (BW_16 == this->param.nBusWidth) {
		column >>= 1;
	}
/*erase*/
	_cmd_init(_inst_erase, "_inst_erase", _INT_TO | _INT_DONE | _INT_WP | _INT_STSMCH);
	_cmd_add(_inst_erase, _INST_CMD(0x60));
	_cmd_tag(_inst_erase);
	_cmd_add(_inst_erase, _INST_ADDR(0, 1));
	_cmd_add(_inst_erase, _INST_ADDR(0, 0));
	if (5 == this->param.nCycle) {
		_cmd_add(_inst_erase, _INST_ADDR(0, 0));
	}
	_cmd_add(_inst_erase, _INST_CMD(0xD0));
	_cmd_add(_inst_erase, _INST_WRB0());
	_cmd_add(_inst_erase, _INST_CMD(0x70));
	_cmd_add(_inst_erase, _INST_IDST(1));
	_cmd_add(_inst_erase, _INST_DONE());
// read main+spare(info)+Ecc or Raw
	_cmd_init(_inst_read_main_spare, "_inst_read_main_spare", _INT_TO | _INT_DONE);
	_cmd_add(_inst_read_main_spare, _INST_CMD(0x00));
	_cmd_add(_inst_read_main_spare, _INST_ADDR((0xFF & column), 0));
	_cmd_add(_inst_read_main_spare, _INST_ADDR((0xFF & (column >> 8)), 0));
	_cmd_tag(_inst_read_main_spare);
	_cmd_add(_inst_read_main_spare, _INST_ADDR(0, 1));
	_cmd_add(_inst_read_main_spare, _INST_ADDR(0, 0));
	if (5 == this->param.nCycle) {
		_cmd_add(_inst_read_main_spare, _INST_ADDR(0, 0));
	}
	_cmd_add(_inst_read_main_spare, _INST_CMD(0x30));
	_cmd_add(_inst_read_main_spare, _INST_WRB0());
	_cmd_add(_inst_read_main_spare, _INST_SRDT());
	_cmd_add(_inst_read_main_spare, _INST_CMD(0x05));
	_cmd_add(_inst_read_main_spare, _INST_ADDR(0, 0));
	_cmd_add(_inst_read_main_spare, _INST_ADDR(0, 0));
	_cmd_add(_inst_read_main_spare, _INST_CMD(0xE0));
	_cmd_add(_inst_read_main_spare, _INST_MRDT());
	_cmd_add(_inst_read_main_spare, _INST_DONE());
// read main raw
	_cmd_init(_inst_read_main_raw, "_inst_read_main_raw", _INT_TO | _INT_DONE);
	_cmd_add(_inst_read_main_raw, _INST_CMD(0x00));
	_cmd_add(_inst_read_main_raw, _INST_ADDR(0, 0));
	_cmd_add(_inst_read_main_raw, _INST_ADDR(0, 0));
	_cmd_tag(_inst_read_main_raw);
	_cmd_add(_inst_read_main_raw, _INST_ADDR(0, 1));
	_cmd_add(_inst_read_main_raw, _INST_ADDR(0, 0));
	if (5 == this->param.nCycle) {
		_cmd_add(_inst_read_main_raw, _INST_ADDR(0, 0));
	}
	_cmd_add(_inst_read_main_raw, _INST_CMD(0x30));
	_cmd_add(_inst_read_main_raw, _INST_WRB0());
	_cmd_add(_inst_read_main_raw, _INST_MRDT());
	_cmd_add(_inst_read_main_raw, _INST_DONE());
// read spare raw: read only main or only spare data, it is read to main addr.
	_cmd_init(_inst_read_spare_raw, "_inst_read_spare_raw", _INT_TO | _INT_DONE);
	_cmd_add(_inst_read_spare_raw, _INST_CMD(0x00));
	_cmd_add(_inst_read_spare_raw, _INST_ADDR((0xFF & column), 0));
	_cmd_add(_inst_read_spare_raw, _INST_ADDR((0xFF & (column >> 8)), 0));
	_cmd_tag(_inst_read_spare_raw);
	_cmd_add(_inst_read_spare_raw, _INST_ADDR(0, 1));
	_cmd_add(_inst_read_spare_raw, _INST_ADDR(0, 0));
	if (5 == this->param.nCycle) {
		_cmd_add(_inst_read_spare_raw, _INST_ADDR(0, 0));
	}
	_cmd_add(_inst_read_spare_raw, _INST_CMD(0x30));
	_cmd_add(_inst_read_spare_raw, _INST_WRB0());
	_cmd_add(_inst_read_spare_raw, _INST_MRDT());
	_cmd_add(_inst_read_spare_raw, _INST_DONE());

// write main+spare(info)+ecc
	_cmd_init(_inst_write_main_spare, "_inst_write_main_spare", _INT_TO | _INT_DONE | _INT_WP | _INT_STSMCH);
	_cmd_add(_inst_write_main_spare, _INST_CMD(0x80));
	_cmd_add(_inst_write_main_spare, _INST_ADDR(0, 0));
	_cmd_add(_inst_write_main_spare, _INST_ADDR(0, 0));
	_cmd_tag(_inst_write_main_spare);
	_cmd_add(_inst_write_main_spare, _INST_ADDR(0, 1));
	_cmd_add(_inst_write_main_spare, _INST_ADDR(0, 0));
	if (5 == this->param.nCycle) {
		_cmd_add(_inst_write_main_spare, _INST_ADDR(0, 0));
	}
	_cmd_add(_inst_write_main_spare, _INST_MWDT());
//      _cmd_add(_inst_write_main_spare, _INST_CMD(0x85));
//      _cmd_add(_inst_write_main_spare, _INST_ADDR(0, 0));
//      _cmd_add(_inst_write_main_spare, _INST_ADDR(0, 0));
	_cmd_add(_inst_write_main_spare, _INST_SWDT());
	_cmd_add(_inst_write_main_spare, _INST_CMD(0x10));
	_cmd_add(_inst_write_main_spare, _INST_WRB0());
	_cmd_add(_inst_write_main_spare, _INST_CMD(0x70));
	_cmd_add(_inst_write_main_spare, _INST_IDST(1));
	_cmd_add(_inst_write_main_spare, _INST_DONE());
// write main raw
	_cmd_init(_inst_write_main_raw, "_inst_write_main_raw", _INT_TO | _INT_DONE | _INT_WP | _INT_STSMCH);
	_cmd_add(_inst_write_main_raw, _INST_CMD(0x80));
	_cmd_add(_inst_write_main_raw, _INST_ADDR(0, 0));
	_cmd_add(_inst_write_main_raw, _INST_ADDR(0, 0));
	_cmd_tag(_inst_write_main_raw);
	_cmd_add(_inst_write_main_raw, _INST_ADDR(0, 1));
	_cmd_add(_inst_write_main_raw, _INST_ADDR(0, 0));
	if (5 == this->param.nCycle) {
		_cmd_add(_inst_write_main_raw, _INST_ADDR(0, 0));
	}
	_cmd_add(_inst_write_main_raw, _INST_MWDT());
	_cmd_add(_inst_write_main_raw, _INST_CMD(0x10));
	_cmd_add(_inst_write_main_raw, _INST_WRB0());
	_cmd_add(_inst_write_main_raw, _INST_CMD(0x70));
	_cmd_add(_inst_write_main_raw, _INST_IDST(1));
	_cmd_add(_inst_write_main_raw, _INST_DONE());
// write spare raw
	_cmd_init(_inst_write_spare_raw, "_inst_write_spare_raw", _INT_TO | _INT_DONE | _INT_WP | _INT_STSMCH);
	_cmd_add(_inst_write_spare_raw, _INST_CMD(0x80));
	_cmd_add(_inst_write_spare_raw, _INST_ADDR((0xFF & column), 0));
	_cmd_add(_inst_write_spare_raw, _INST_ADDR((0xFF & (column >> 8)), 0));
	_cmd_tag(_inst_write_spare_raw);
	_cmd_add(_inst_write_spare_raw, _INST_ADDR(0, 1));
	_cmd_add(_inst_write_spare_raw, _INST_ADDR(0, 0));
	if (5 == this->param.nCycle) {
		_cmd_add(_inst_write_spare_raw, _INST_ADDR(0, 0));
	}
	_cmd_add(_inst_write_spare_raw, _INST_SWDT());
	_cmd_add(_inst_write_spare_raw, _INST_CMD(0x10));
	_cmd_add(_inst_write_spare_raw, _INST_WRB0());
	_cmd_add(_inst_write_spare_raw, _INST_CMD(0x70));
	_cmd_add(_inst_write_spare_raw, _INST_IDST(1));
	_cmd_add(_inst_write_spare_raw, _INST_DONE());
}

/*
	this is used for normal used nand
*/


STATIC_FUNC int __param_init_buf(NAND_CTL * this)
{
#ifdef SPRDNAND_KERNEL
	dma_addr_t phys_addr = 0;
	void *virt_ptr = 0;
#endif
	uint32_t mBuf_size = (1 << this->bufShift);
	uint32_t sBuf_size = (1 << (this->bufShift - this->sectShift)) * this->param.nSpareSize;
	uint32_t stsBuf_size = ((1 << (this->bufShift - this->sectShift))*(sizeof(struct nand_ecc_stats)));

#ifdef _DEBUG_NAND_
	mBuf_size += 512;
	sBuf_size += 512;
	stsBuf_size += 512;
#endif
#ifdef SPRDNAND_KERNEL
	virt_ptr = dma_alloc_coherent(NULL, mBuf_size, &phys_addr, GFP_KERNEL);
	if (!virt_ptr) {
		DPRINT(KERN_ERR "NAND - Failed to allocate memory for DMA main buffer\n");
		return -ENOMEM;
	}
	this->mBuf_p = (uint8_t *) phys_addr;
	this->mBuf_v = (uint8_t *) virt_ptr;

	virt_ptr = dma_alloc_coherent(NULL, sBuf_size, &phys_addr, GFP_KERNEL);
	if (!virt_ptr) {
		DPRINT(KERN_ERR "NAND - Failed to allocate memory for DMA main buffer\n");
		dma_free_coherent(NULL, mBuf_size, (void *)this->mBuf_v, (dma_addr_t) this->mBuf_p);
		return -ENOMEM;
	}
	this->sBuf_p = (uint8_t *) phys_addr;
	this->sBuf_v = (uint8_t *) virt_ptr;

	virt_ptr = dma_alloc_coherent(NULL, stsBuf_size, &phys_addr, GFP_KERNEL);
	if (!virt_ptr) {
		DPRINT(KERN_ERR "NAND - Failed to allocate memory for DMA main buffer\n");
		dma_free_coherent(NULL, mBuf_size, (void *)this->mBuf_v, (dma_addr_t) this->mBuf_p);
		dma_free_coherent(NULL, sBuf_size, (void *)this->sBuf_v, (dma_addr_t) this->sBuf_p);
		return -ENOMEM;
	}
	this->stsBuf_p = (uint8_t *) phys_addr;
	this->stsBuf_v = (uint8_t *) virt_ptr;

#endif

	this->mBuf_p = this->mBuf_v = malloc(mBuf_size);
	if(this->mBuf_p == NULL) {
		return -ENOMEM;
	}

	this->sBuf_p = this->sBuf_v = malloc(sBuf_size);
	if(this->sBuf_p == NULL) {
		return -ENOMEM;
	}

	this->stsBuf_p = this->stsBuf_v = malloc(stsBuf_size);
	if(this->stsBuf_p == NULL) {
		return -ENOMEM;
	}

#ifdef _DEBUG_NAND_
	*((uint32_t *) (&(this->mBuf_v[mBuf_size - 512]))) = _END_FLAG;
	*((uint32_t *) (&(this->sBuf_v[sBuf_size - 512]))) = _END_FLAG;
	*((uint32_t *) (&(this->stsBuf_v[stsBuf_size - 512]))) = _END_FLAG;
#endif
	return 0;
}

STATIC_FUNC int _param_init(NAND_CTL * this)
{
	int ret = 0;
	ret = __param_init_nandHWInfo(this);
	if (ret) {
		return ret;
	}
	__param_init_inst(this);
	return __param_init_buf(this);
}

STATIC_FUNC void _init_reg_state1(NAND_CTL * this)
{
	this->NFC_start |=  _START_DEF1_ECC_MODE(this->eccModeReg);
	this->NFC_cfg0 |= _CFG0_DEF1_SECT_NUM(this->param.nSectPerPage)
	    | _CFG0_DEF1_BUS_WIDTH(this->param.nBusWidth)
	    | _CFG0_DEF1_MAIN_SPAR_APT(this->param.nSectPerPage);
	this->NFC_cfg1 = _CFG1_DEF1_SPAR_INFO_SIZE(this->param.info_size)
	    | _CFG1_DEF1_SPAR_SIZE(this->param.nSpareSize)
	    | _CFG1_DEF1_MAIN_SIZE(this->param.nSecSize);
	this->NFC_cfg2 = _CFG2_DEF1_SPAR_SECTOR_NUM(this->param.nSectPerPage)
	    | _CFG2_DEF1_SPAR_INFO_POS(this->param.info_pos)
	    | _CFG2_DEF1_ECC_POSITION(this->param.ecc_pos);

	this->NFC_cfg0 |= _CFG0_SET_WPN;

	__32reg_write(NFC_CFG0_REG, this->NFC_cfg0);
	__32reg_write(NFC_CFG1_REG, this->NFC_cfg1);
	__32reg_write(NFC_CFG2_REG, this->NFC_cfg2);
	__32reg_write(NFC_STAT_ADDRH_REG, 0x0);
	__32reg_write(NFC_STAT_ADDRL_REG, _RAM_STAT_ADDR(this->stsBuf_p));
	__32reg_write(NFC_MAIN_ADDRH_REG, 0x0);
	__32reg_write(NFC_MAIN_ADDRL_REG, _RAM_MAIN_ADDR(this->mBuf_p));
	__32reg_write(NFC_SPAR_ADDRH_REG, 0x0);
	__32reg_write(NFC_SPAR_ADDRL_REG, _RAM_SPAR_ADDR(this->sBuf_p));

}

#ifdef SPRDNAND_KERNEL
STATIC_FUNC int callback_debugfs_show(NFC_BASE_T * nfcBase, struct seq_file *s, void *data)
{
	uint32_t i;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;

	seq_printf(s, "drv irq = %d\n", this->irq);
	seq_printf(s, "drv freq = %d\n", this->frequence);
	seq_printf(s, "drv ioaddr = 0x%x\n", (uint32_t) (this->ioaddr));
// resource1: nand param & mtd ecclayout & risk threshold & nessisary const value
	seq_printf(s, "drv eccModeReg = 0x%x\n", this->eccModeReg);
	seq_printf(s, "drv risk_threshold = %d\n", this->risk_threshold);
	seq_printf(s, "drv csNum = %d:", this->csNum);
	for (i = 0; i < this->csNum; i++) {
		seq_printf(s, "\t%d", this->cs[i]);
	}
	seq_printf(s, "\n");
	seq_printf(s, "drv csDis = %d\n", this->csDis);
	seq_printf(s, "drv sectPerPgShift = %d\n", this->sectPerPgShift);
	seq_printf(s, "drv sectShift = %d\n", this->sectShift);
	seq_printf(s, "drv sectMsk = 0x%x\n", this->sectMsk);
	seq_printf(s, "drv pageShift = %d\n", this->pageShift);
	seq_printf(s, "drv blkShift = %d\n", this->blkShift);
	seq_printf(s, "drv bufShift = %d\n", this->bufShift);
// resource3: local DMA buffer
	seq_printf(s, "drv mBuf_p = 0x%x\n", (uint32_t) this->mBuf_p);
	seq_printf(s, "drv mBuf_v = 0x%x\n", (uint32_t) this->mBuf_v);
	seq_printf(s, "drv sBuf_p = 0x%x\n", (uint32_t) this->sBuf_p);
	seq_printf(s, "drv sBuf_v = 0x%x\n", (uint32_t) this->sBuf_v);
	seq_printf(s, "drv stsBuf_p = 0x%x\n", (uint32_t) this->stsBuf_p);
	seq_printf(s, "drv stsBuf_v = 0x%x\n", (uint32_t) this->stsBuf_v);
// resource4: register base value. some value is const while operate on nand flash, we store it to local valuable.
// Time & cfg & status mach. It is different with operation R W E.
	seq_printf(s, "drv NFC_Time0_R = 0x%x\n", this->NFC_Time0_R);
	seq_printf(s, "drv NFC_Time0_W = 0x%x\n", this->NFC_Time0_W);
	seq_printf(s, "drv NFC_Time0_E = 0x%x\n", this->NFC_Time0_E);

	seq_printf(s, "drv NFC_cfg0 = 0x%x\n", this->NFC_cfg0);
	seq_printf(s, "drv NFC_cfg1 = 0x%x\n", this->NFC_cfg1);
	seq_printf(s, "drv NFC_cfg2 = 0x%x\n", this->NFC_cfg2);

//      seq_printf(s, "---Nand HW Param---\n");
	seq_printf(s, "drv param id:");
	for (i = 0; i < NFC_MAX_ID_LEN; i++) {
		seq_printf(s, "\t0x%x", this->param.id[i]);
	}
	seq_printf(s, "\n");
	seq_printf(s, "drv param nBlkCnt = %d\n", this->param.nBlkCnt);
	seq_printf(s, "drv param nPagePerBlk = %d\n", this->param.nPagePerBlk);
	seq_printf(s, "drv param nSectPerPage = %d\n", this->param.nSectPerPage);
	seq_printf(s, "drv param nSecSize = %d\n", this->param.nSecSize);
	seq_printf(s, "drv param nSpareSize = %d\n", this->param.nSpareSize);

	seq_printf(s, "drv param badFlag_pos = %d\n", this->param.badFlag_pos);
	seq_printf(s, "drv param badFlag_len = %d\n", this->param.badFlag_len);
	seq_printf(s, "drv param ecc_mode = %d\n", this->param.ecc_mode);
	seq_printf(s, "drv param ecc_pos = %d\n", this->param.ecc_pos);
	seq_printf(s, "drv param ecc_size = %d\n", this->param.ecc_size);
	seq_printf(s, "drv param info_pos = %d\n", this->param.info_pos);
	seq_printf(s, "drv param info_size = %d\n", this->param.info_size);

	seq_printf(s, "drv param nBusWidth = %d\n", this->param.nBusWidth);
	seq_printf(s, "drv param nCycle = %d\n", this->param.nCycle);
	// ACS
	seq_printf(s, "drv param T_als = %d\n", this->param.T_als);	// ale enable --> 1st we enable
	seq_printf(s, "drv param T_cls = %d\n", this->param.T_cls);	// cle enable --> 1st we enable
	// ACE
	seq_printf(s, "drv param T_clh = %d\n", this->param.T_clh);	// last we disable --> cle disable
	seq_printf(s, "drv param T_alh = %d\n", this->param.T_alh);	// last we disable --> ale disable
	// RWS
	seq_printf(s, "drv param T_rr = %d\n", this->param.T_rr);	// RB busy --> re enable when read
	seq_printf(s, "drv param T_adl = %d\n", this->param.T_adl);	// last addr we --> 1st data we enable when write
	// RWE
	//uint32_t              // 5ns when read
	//uint32_t;             // 0 when write
	// RWH & RWL
	seq_printf(s, "drv param T_wh = %d\n", this->param.T_wh);	// we high when write
	seq_printf(s, "drv param T_wp = %d\n", this->param.T_wp);	// we low       when wirte
	seq_printf(s, "drv param T_reh = %d\n", this->param.T_reh);	// re high when read
	seq_printf(s, "drv param T_rp = %d\n", this->param.T_rp);	// re low when read
	return 0;
}
#endif
#define __GETCS(page) this->cs[((page)>>(nfcBase->chipShift-nfcBase->pageShift))]

/*
0		: ecc pass
-EBADMSG: ecc fail
-EUCLEAN: ecc risk
*/
STATIC_FUNC int8_t __0bitNum8[256] = {
	8, 7, 7, 6, 7, 6, 6, 5, 7, 6, 6, 5, 6, 5, 5, 4,
	7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
	7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
	6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
	7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
	6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
	6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
	5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
	7, 6, 6, 5, 6, 5, 5, 4, 6, 5, 5, 4, 5, 4, 4, 3,
	6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
	6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
	5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
	6, 5, 5, 4, 5, 4, 4, 3, 5, 4, 4, 3, 4, 3, 3, 2,
	5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
	5, 4, 4, 3, 4, 3, 3, 2, 4, 3, 3, 2, 3, 2, 2, 1,
	4, 3, 3, 2, 3, 2, 2, 1, 3, 2, 2, 1, 2, 1, 1, 0
};

STATIC_FUNC int __chkAllFF(NAND_CTL * this, /*IN*/ uint32_t sects, /*IN*/ uint32_t mode)
{
	uint32_t i, sectSize, oobSize;
	uint8_t *mainBuf, *spareBuf;
	int32_t bit0Num, bit0Total;
	uint32_t mbit0Pos[60];
	uint32_t mbit0ArrIdx = 0;
	uint32_t sbit0Pos[60];
	uint32_t sbit0ArrIdx = 0;
	int32_t riskNum;

	riskNum = (int32_t) min((uint32_t) 4, this->risk_threshold);

	sectSize = (1 << this->sectShift);
	if (MTD_OPS_AUTO_OOB == mode) {
		oobSize = this->param.info_size;
	} else {
		oobSize = this->param.nSpareSize;
	}
	mainBuf = this->mBuf_v + (sects << this->sectShift);
	spareBuf = this->sBuf_v + (sects * oobSize);

	bit0Total = 0;
	mbit0ArrIdx = 0;
	for (i = 0; i < sectSize; i++) {
		bit0Num = (int32_t) __0bitNum8[mainBuf[i]];
		if (bit0Num) {
			bit0Total += bit0Num;
			if (bit0Total > riskNum) {
				return -EBADMSG;
			}
			mbit0Pos[mbit0ArrIdx] = i;
			mbit0ArrIdx++;
		}
	}
	sbit0ArrIdx = 0;
	for (i = 0; i < oobSize; i++) {
		bit0Num = (int32_t) __0bitNum8[spareBuf[i]];
		if (bit0Num) {
			bit0Total += bit0Num;
			if (bit0Total > riskNum) {
				return -EBADMSG;
			}
			sbit0Pos[sbit0ArrIdx] = i;
			sbit0ArrIdx++;
		}
	}
	for (i = 0; i < mbit0ArrIdx; i++) {
		mainBuf[mbit0Pos[i]] = 0xFF;
	}
	for (i = 0; i < sbit0ArrIdx; i++) {
		spareBuf[sbit0Pos[i]] = 0xFF;
	}
	return bit0Total;
}

STATIC_FUNC int _eccAnalyze(NAND_CTL * this, uint32_t num, struct mtd_ecc_stats *ecc_sts, uint32_t mode)
{
	uint32_t i;
	uint32_t n;
	struct nand_ecc_stats *nand_ecc_sts = this->stsBuf_v;
	uint32_t sector_num = this->param.nSectPerPage;
	uint32_t ecc_bank_num = num / sector_num;
	uint32_t sector = 0;
	int ret = 0;

#ifndef CONFIG_SPRD_NAND_R4p0
	for (i = 0; i <= ecc_bank_num; i++) {
		for (n = 0; n < min((num - sector_num*i), sector_num); n++) {
			sector = n + sector_num * i;
			switch (_ECC_STAT(nand_ecc_sts->ecc_stats[n])) {
			case 0x00:	// pass do nothing
				break;
			case 0x02:
			case 0x03:	// fail
				ret = __chkAllFF(this, sector, mode);
				if (-EBADMSG == ret) {
					ecc_sts->failed++;
				} else {
					ecc_sts->corrected += ret;
				}
				break;
			case 0x01:
				if (0x1FF == _ECC_NUM(nand_ecc_sts->ecc_stats[n])) {
					ret = __chkAllFF(this, sector, mode);
					if (-EBADMSG == ret) {
						ecc_sts->failed++;
					} else {
						ecc_sts->corrected += ret;
						//ret = -EUCLEAN;
					}
				} else if (this->param.ecc_mode <= _ECC_NUM(nand_ecc_sts->ecc_stats[n])) {	// fail
					ecc_sts->failed++;
					ret = -EBADMSG;
				} else {
					ecc_sts->corrected += _ECC_NUM(nand_ecc_sts->ecc_stats[n]);
					if (_ECC_NUM(nand_ecc_sts->ecc_stats[n]) >= this->risk_threshold) {	// pass but has bit flip >= risk number
						//ret = -EUCLEAN;
					}
				}
				break;
			}
				if (-EBADMSG == ret) {
					goto err;
				}
		}
		nand_ecc_sts++;
	}
#endif
	if(ret)
		printk(KERN_ERR "sprd nand read ecc sts %d\n", ret);
	return ret;
err:
	printk(KERN_ERR "sprd nand read ecc sts %d\n", ret);
	return ret;
}

/*
mtd->ecc_stats
	__u32 corrected:
	__u32 failed;
	__u32 badblocks;
	__u32 bbtblocks;

chip->ecc.correct:


*/
/*
	if(0!=mBuf) then read main area
	if(0!=sBuf) then read spare area or read spare info

	if(MTD_OPS_PLACE_OOB == mode) then just read main area with Ecc
	if(MTD_OPS_AUTO_OOB == mode) then read main area(if(0!=mBuf)),and spare info(if(0!=sbuf)), with Ecc
	if(MTD_OPS_RAW == mode) then read main area(if(0!=mBuf)),and spare info(if(0!=sbuf)), without Ecc

	return
		0			: ecc pass
		-EBADMSG	: ecc fail
		-EUCLEAN	: ecc risk
		-EIO		: read fail

	mtd->ecc_stats
*/
STATIC_FUNC int _readPageInBlk(NFC_BASE_T * nfcBase, uint32_t page,
			       uint32_t num, uint32_t * retNum, uint32_t ifHasMBuf, uint32_t ifHasSBuf, uint32_t mode, struct mtd_ecc_stats *ecc_sts)
{
	NAND_INST *inst;
	int ret = 0;
	uint32_t ifChangeBuf = 0;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;

#ifdef _DEBUG_NAND_
	_chkMem(this);
#endif
	_selectCS(this, __GETCS(page));
	this->NFC_sts_mach_val = _MACH_READ;
	this->NFC_time0_val = this->NFC_Time0_R;
	this->NFC_cfg0_val = (this->NFC_cfg0 | _CFG0_SET_NFC_MODE(0));
	__32reg_write(NFC_MAIN_ADDRH_REG, 0x0);
    __32reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)this->mBuf_p);
	__32reg_write(NFC_SPAR_ADDRH_REG, 0x0);
    __32reg_write(NFC_SPAR_ADDRL_REG, (uint32_t)this->sBuf_p);
	__32reg_write(NFC_STAT_ADDRH_REG, 0x0);
    __32reg_write(NFC_STAT_ADDRL_REG, (uint32_t)this->stsBuf_p);

#ifndef CONFIG_NAND_SPL

        uint32_t mBuf_size = (1 << this->bufShift);
        uint32_t sBuf_size = (1 << (this->bufShift - this->sectShift)) * this->param.nSpareSize;
        uint32_t stsBuf_size = (1 << (this->bufShift - this->sectShift));

        if (ifHasMBuf){
            flush_cache((unsigned int)this->mBuf_p,mBuf_size);
        //    invalidate_cache((unsigned int)this->mBuf_p,mBuf_size);
        }

        if (ifHasSBuf){
            flush_cache((unsigned int)this->sBuf_p, sBuf_size);
       //     invalidate_cache((unsigned int)this->sBuf_p, sBuf_size);
        }

        flush_cache((unsigned int)this->stsBuf_p,stsBuf_size);
     //   invalidate_cache((unsigned int)this->stsBuf_p,stsBuf_size);
#endif

	switch (mode) {
	case MTD_OPS_AUTO_OOB:
		this->NFC_cfg0_val |= _CFG0_SET_SPARE_ONLY_INFO_PROD_EN;
	case MTD_OPS_PLACE_OOB:	//pass
		this->NFC_cfg0_val |= (_CFG0_SET_ECC_EN | _CFG0_SET_MAIN_USE | _CFG0_SET_SPAR_USE);
		inst = &_inst_read_main_spare;
		break;
	case MTD_OPS_RAW:
		if (ifHasMBuf & ifHasSBuf) {
			this->NFC_cfg0_val |= (_CFG0_SET_MAIN_USE | _CFG0_SET_SPAR_USE);
			inst = &_inst_read_main_spare;
		} else if (ifHasMBuf) {
			this->NFC_cfg0_val |= (_CFG0_SET_MAIN_USE);
			inst = &_inst_read_main_raw;
		} else if (ifHasSBuf) {	//pass
			this->NFC_cfg0_val |= (_CFG0_SET_MAIN_USE);
			inst = &_inst_read_spare_raw;
			{
				// 0 nand controller use mainAddr to send spare data, So i have to change some globe config here
				ifChangeBuf = 1;
				// 1 change to main buf
				__32reg_write(NFC_MAIN_ADDRH_REG, 0x0);
				__32reg_write(NFC_MAIN_ADDRL_REG, _RAM_MAIN_ADDR(this->sBuf_p));
				// 2 change mainsize
				this->NFC_cfg1 &= (~_CFG1_temp_MIAN_SIZE_MSK);
				this->NFC_cfg1 |= _CFG1_DEF1_MAIN_SIZE(this->param.nSpareSize << this->sectPerPgShift);
				__32reg_write(NFC_CFG1_REG, this->NFC_cfg1);
				// 3 change sect number
				this->NFC_cfg0_val &= (~_CFG0_temp_SECT_NUM_MSK);
				this->NFC_cfg0_val |= _CFG0_DEF1_SECT_NUM(1);
			}
		} else {
			_deSelectCS(this, -EINVAL);
			return -EINVAL;
		}
		break;
	default:
		panic("sprd nand ops mode error!\n");
		break;
	}
	_cmd_change(inst, page);
	_cmd_exec(this, inst, num, 0);
	ret = _cmd_wait(this, inst, 0);
	
	if (ifChangeBuf) {
		// 1 change to main buf
		__32reg_write(NFC_MAIN_ADDRH_REG, 0x0);
		__32reg_write(NFC_MAIN_ADDRL_REG, _RAM_MAIN_ADDR(this->mBuf_p));
		// 2 change mainsize
		this->NFC_cfg1 &= (~_CFG1_temp_MIAN_SIZE_MSK);
		this->NFC_cfg1 |= _CFG1_DEF1_MAIN_SIZE(this->param.nSecSize);
		__32reg_write(NFC_CFG1_REG, this->NFC_cfg1);
		// 3 change sect number
		__32reg_write(NFC_CFG0_REG, this->NFC_cfg0);
	}
	if (ret) {
		*retNum = 0;
		_deSelectCS(this, -EIO);
		return -EIO;
	}
	*retNum = num;

	switch (mode) {
	case MTD_OPS_AUTO_OOB:
	case MTD_OPS_PLACE_OOB:
		ret = _eccAnalyze(this, num * this->param.nSectPerPage, ecc_sts, mode);
		break;
	case MTD_OPS_RAW:
		break;
	default:
		panic("sprd nand ops mode error!\n");
		break;
	}
	_deSelectCS(this, ret);
	return ret;
}

STATIC_FUNC int callback_readPageInBlk(NFC_BASE_T * nfcBase, uint32_t page,
				       uint32_t num, uint32_t * retNum, uint32_t ifHasMBuf, uint32_t ifHasSBuf, uint32_t mode, struct mtd_ecc_stats *ecc_sts)
{
	int ret, i;

	i = 0;
	do {
		ret = _readPageInBlk(nfcBase, page, num, retNum, ifHasMBuf, ifHasSBuf, mode, ecc_sts);
		if ((!ret) || (-EINVAL == ret) || (-EUCLEAN == ret)) {
			break;
		}
		i++;
		printk(KERN_ERR "sprd_nand:retry %d\n", i);
	} while (i < 3);
	return 0;
}

STATIC_FUNC uint32_t sprd_dolphin_reg_read(uint32_t addr)
{
	return readl(addr);
}
STATIC_FUNC void sprd_dolphin_reg_write(uint32_t addr, uint32_t val)
{
	writel(val, addr);
}
STATIC_FUNC void sprd_dolphin_nand_int_clr(NAND_CTL *this,uint32_t bit_clear)
{
	sprd_dolphin_reg_write(NFC_INT_REG, bit_clear);
}

STATIC_FUNC unsigned int ecc_mode_convert(uint32_t mode)
{
	uint32_t mode_m;
	switch(mode) {
	case 1:
		mode_m = 0;
		break;
	case 2:
		mode_m = 1;
		break;
	case 4:
		mode_m = 2;
		break;
	case 8:
		mode_m = 3;
		break;
	case 12:
		mode_m = 4;
		break;
	case 16:
		mode_m = 5;
		break;
	case 24:
		mode_m = 6;
		break;
	case 32:
		mode_m = 7;
		break;
	case 40:
		mode_m = 8;
		break;
	case 48:
		mode_m = 9;
		break;
	case 56:
		mode_m = 10;
		break;
	case 60:
		mode_m = 11;
		break;
	default:
		mode_m = 0;
		break;
	}
	return mode_m;
}


STATIC_FUNC int sprd_dolphin_nand_wait_finish(NAND_CTL *this)
{
	unsigned int value;
	unsigned int counter = 0;
	while((counter < NFC_TIMEOUT_VAL/*time out*/)) {
		value = sprd_dolphin_reg_read(NFC_INT_REG);
		if(value & BIT_24) {
			break;
		}
		counter ++;
	}
	sprd_dolphin_reg_write(NFC_INT_REG, 0xf00); //clear all interrupt status
	if(counter >= NFC_TIMEOUT_VAL){
        printf("~~~~~~~~~~~transfer done failed\n\n");
		return -1;
	}
	return 0;
}

STATIC_FUNC unsigned int sprd_dolphin_data_trans(sprd_dolphin_nand_data_param *param)
{
	uint32_t cfg0 = 0;
	uint32_t i = 0;
	uint32_t cfg1 = 0;
	uint32_t cfg2 = 0;
	uint32_t cfg4 = 0;
    NAND_CTL *this = &controller;
	//cfg0 = NFC_ONLY_MST_MODE | MAIN_SPAR_APT | NFC_WPN;

	cfg0 |= NFC_ONLY_NAND_MODE;
	cfg4 = sprd_dolphin_reg_read(NFC_CFG4_REG);
	cfg4 &=(~_CFG4_ONLY_SEL_MODE);

	NAND_INST *inst = &_inst_nop;
	for (i = 0; i < inst->cnt; i += 2) {
		__32reg_write(NFC_INST0_REG + (i << 1), (inst->inst[i] | (inst->inst[i + 1] << 16)));
	}

	if(param->m_sct != 0) {
		sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)param->m_buf);
	}
	if(param->s_sct != 0) {
		sprd_dolphin_reg_write(NFC_SPAR_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_SPAR_ADDRL_REG, (uint32_t)param->s_buf);
	}
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_CFG1_REG, cfg1);
	sprd_dolphin_reg_write(NFC_CFG2_REG, cfg2);
	sprd_dolphin_reg_write(NFC_CFG4_REG, cfg4);
	sprd_dolphin_nand_int_clr(this,INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);//clear all interrupt
	sprd_dolphin_reg_write(NFC_START_REG, NFC_START);
	printf("######the first cmd");
	sprd_dolphin_nand_wait_finish(this);


	cfg4 = sprd_dolphin_reg_read(NFC_CFG4_REG);
	cfg4 |= _CFG4_ONLY_SEL_MODE;

	cfg0 = NFC_ONLY_MST_MODE | MAIN_SPAR_APT | NFC_WPN;
	if(param->dir) {
		cfg0 |= NFC_RW;
	}
	if(param->m_sct != 0) {
		cfg0 |= (param->m_sct - 1) << SECTOR_NUM_OFFSET;
		cfg0 |= MAIN_USE;
		cfg1 |= (param->m_size - 1);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)param->m_buf);
	}
	if(param->s_sct != 0) {
		cfg0 |= SPAR_USE;
		cfg1 |= (param->s_size - 1) << SPAR_SIZE_OFFSET;
		cfg2 |= (param->s_sct - 1) << SPAR_SECTOR_NUM_OFFSET;
		sprd_dolphin_reg_write(NFC_SPAR_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_SPAR_ADDRL_REG, (uint32_t)param->s_buf);
	}
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_CFG1_REG, cfg1);
	sprd_dolphin_reg_write(NFC_CFG2_REG, cfg2);
	sprd_dolphin_reg_write(NFC_CFG4_REG, cfg4);
	sprd_dolphin_nand_int_clr(this,INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);//clear all interrupt
	sprd_dolphin_reg_write(NFC_START_REG, NFC_ONLY_START);
	sprd_dolphin_nand_wait_finish(this);
	printf("@@@@@@@@@@done data transfer\n\n");
	return 0;
}



void sprd_ecc_ctrl(struct sprd_ecc_param *param, uint32_t dir)
{
	uint32_t nfc_start = 0;
	uint32_t cfg0 = 0;
	uint32_t cfg1 = 0;
	uint32_t cfg2 = 0;
	uint32_t cfg4 = 0;
    NAND_CTL *this = &controller;

	nfc_start |= ecc_mode_convert(param->mode) << ECC_MODE_OFFSET;
	cfg0 = NFC_ONLY_ECC_MODE | MAIN_SPAR_APT;
	if(dir)
	{
		cfg0 |= NFC_RW;
	}
	cfg1 |=(param->sinfo_size - 1) << SPAR_INFO_SIZE_OFFSET;
	cfg1 |=(param->sp_size - 1) << SPAR_SIZE_OFFSET;
	cfg1 |= (param->m_size - 1);

	cfg2 |= (param->sinfo_pos)<< SPAR_INFO_POS_OFFSET;
	cfg2 |= param->ecc_pos;

	cfg4 = sprd_dolphin_reg_read(NFC_CFG4_REG);
	cfg4 |= _CFG4_ONLY_SEL_MODE;
	
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_CFG1_REG, cfg1);
	sprd_dolphin_reg_write(NFC_CFG2_REG, cfg2);
	sprd_dolphin_reg_write(NFC_CFG4_REG, cfg4);
	
	sprd_dolphin_nand_int_clr(this,INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);//clear all interrupt
	sprd_dolphin_reg_write(NFC_START_REG, nfc_start | NFC_ONLY_START);
	sprd_dolphin_nand_wait_finish(this);
	printf("@@@@@@@@@@done ecc ctrl\n\n");
}

unsigned int sprd_ecc_encode(struct sprd_ecc_param *param)
{
	sprd_dolphin_nand_data_param d_param;
	NAND_CTL *this = &controller;

	memset(&d_param, 0, sizeof(d_param));
	d_param.m_buf = param->p_mbuf;
	d_param.s_buf = param->p_sbuf;
	d_param.m_sct = param->ecc_num;
	d_param.s_sct = param->ecc_num;
	d_param.dir = 1;
	d_param.m_size = param->m_size;
	d_param.s_size = param->sp_size;

	this->NFC_time0_val = this->NFC_Time0_R;
	this->NFC_cfg0_val = (this->NFC_cfg0 | _CFG0_SET_NFC_MODE(0));
	__32reg_write(NFC_CFG0_REG, this->NFC_cfg0_val);
	__32reg_write(NFC_TIMING0_REG, this->NFC_time0_val);
	flush_cache((unsigned int)d_param.m_buf, d_param.m_sct*d_param.m_size);
	flush_cache((unsigned int)d_param.s_buf, d_param.s_sct*d_param.s_size);
	sprd_dolphin_data_trans(&d_param);
	sprd_ecc_ctrl(param, 1);
	d_param.dir = 0;
	d_param.m_sct = 0;
	//invalidate_cache((unsigned int)d_param.m_buf , d_param.m_sct*d_param.m_size);
	//invalidate_cache((unsigned int)d_param.s_buf , d_param.s_sct*d_param.s_size);
	sprd_dolphin_data_trans(&d_param); //read the ecc value from nfc buffer

    return 0;
}


void NFC_PHY_McInsAdd(uint16_t ins)
{
	uint32_t  offset32;
	uint32_t  high_flag;
	uint32_t regVal;
	offset32    = mMcInsNum >> 1;
	high_flag   = mMcInsNum & 0x1;
	regVal= sprd_dolphin_reg_read(0x21a00220 + (offset32 << 2));
	
	if (high_flag)
	{
		regVal &= 0x0000ffff;
		regVal |= (uint32_t)ins << 16;
	}
	else
	{
		regVal &= 0xffff0000;
		regVal |= (uint32_t)ins;
	}
	sprd_dolphin_reg_write(0x21a00220 + (offset32 << 2), regVal);
	mMcInsNum ++;
}

void NFMcInsAdd(uint32_t column,uint32_t row)
{
	NFC_PHY_McInsAdd(_INST_ADDR(column&0xff,0));
	column >>= 8;
	NFC_PHY_McInsAdd(_INST_ADDR(column,0));
	NFC_PHY_McInsAdd(_INST_ADDR(row & 0xff,0));
	row >>= 8;
	NFC_PHY_McInsAdd(_INST_ADDR(row & 0xff,0));
	row >>= 8;
	NFC_PHY_McInsAdd(_INST_ADDR(row & 0xff,0));
}

void NandReadSector(uint32_t pageID)
{
	uint32_t cfg0 = 0;
	uint32_t cfg1 = 0;
	uint32_t cfg4=0;
	uint32_t i=0;
	NAND_CTL *this = &controller;
	
	mMcInsNum =0;
	NFC_PHY_McInsAdd(_INST_CMD(0x00));
	NFMcInsAdd(0,pageID);
	NFC_PHY_McInsAdd(_INST_CMD(0x30));
	NFC_PHY_McInsAdd(_INST_WRB0());
	NFC_PHY_McInsAdd(_INST_MRDT());
	NFC_PHY_McInsAdd(_INST_DONE());
	/*Purpose: clear all raw interrupt status*/
	sprd_dolphin_nand_int_clr(this,INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);//clear all interrupt

	cfg0 = MAIN_USE | MAIN_SPAR_APT | NFC_AUTO_MODE;
	cfg1 = (0x200 - 1) | (0x0<< 12);

	cfg4 = sprd_dolphin_reg_read(NFC_CFG4_REG);
	cfg4 &=~_CFG4_ONLY_SEL_MODE;
	__32reg_write(NFC_CFG0_REG, cfg0);
	__32reg_write(NFC_CFG1_REG, cfg1);
	__32reg_write(NFC_CFG4_REG, cfg4);
	__32reg_write(NFC_MAIN_ADDRH_REG, 0);
	__32reg_write(NFC_MAIN_ADDRL_REG, 0x90000000);

	__32reg_write(NFC_START_REG, NFC_START);
	sprd_dolphin_nand_wait_finish(this);
}

/*
 * spare info data is don't used at the romcode, so the fdl only set the s_info size to 1, and the data value 0xff
 */
#define HEADER_RESV_OFFSET 40
void set_header_info(u8 *bl_data, struct mtd_info *nand, int ecc_pos)
{
	struct bootloader_header *header;
	NFC_BASE_T *nand_control = (NFC_BASE_T *) nand->priv ;
	NAND_CTL *chip = (NAND_CTL *)nand_control->priv;
	struct sprd_ecc_param param;
	u8 *ecc;
	uint32_t image_size_save;

	ecc = memalign(ARCH_DMA_MINALIGN, 108);
	header = (struct bootloader_header *)(bl_data);
	image_size_save = header->image_size;
	memset(((u8 *)header + HEADER_RESV_OFFSET), 0, (sizeof(struct bootloader_header) - HEADER_RESV_OFFSET));
	memset(ecc, 0xff, 108);
	header->image_size = image_size_save;
	//header->version = NAND_BOOT_HEADER_VER;
	header->sct_size = (1<<chip->sectShift);
	if (chip->param.nBusWidth == BW_16)	{
		header->bus_width = 1;
	}
	if(nand->writesize > 512) {
		if ((1<<(nand_control->chipShift)) > (128 << 20)) {
			header->acycle = 5;
		}
		else	 {
			header->acycle = 4;
		}
	}
	else{
		/* One more address cycle for devices > 32MiB */

		if ((1<<(nand_control->chipShift)) > (32 << 20)) {
			header->acycle = 4;
		}
		else	{
			header->acycle = 3;
		}
	}

	//header->magic_num = NAND_BOOT_MAGIC_DATA;
	header->spare_size = chip->param.nSpareSize; //(nand->oobsize);
	header->ecc_mode = ecc_mode_convert(nand_control->ecc_mode);
	header->ecc_pos = header->spare_size - chip->param.ecc_size;
	header->sct_per_page = 1<<chip->sectPerPgShift;
	header->info_pos = header->ecc_pos;
	header->info_size = 0;
	header->mBlkShift = chip->blkShift;
	header->mPageShift = chip->pageShift;

	param.mode = 60;
	param.ecc_pos = 0;
	param.sinfo_size = 1;
	param.ecc_num = 1;
	param.sp_size = 108;
	param.m_size = 1<<chip->sectShift;
	param.p_mbuf = (u8 *)bl_data;
	param.p_sbuf = ecc;
	param.sinfo_pos = 0;
	sprd_ecc_encode(&param);
	memcpy(header->ecc_value, ecc, 108);
#if 0
	__32reg_write(0x81000000,0x6d4);
	__32reg_write(0x81000004,0x1d7b);
	__32reg_write(0x81000008,0x3565d);
	__32reg_write(0x8100000c,0x5d137c);
	__32reg_write(0x81000010,0x7be);
	__32reg_write(0x81000014,0x6120);
	__32reg_write(0x81000018,0x8ff);
	__32reg_write(0x8100001c,0x30bcde);
	__32reg_write(0x81000020,0x1d1d);
	__32reg_write(0x81000024,0x16b0f);
	__32reg_write(0x81000028,0x736db);
	__32reg_write(0x8100002c,0x2bf5f);
	__32reg_write(0x81000030,0x94a);
	__32reg_write(0x81000034,0x4d56);
	__32reg_write(0x81000038,0x1aefb);
	__32reg_write(0x8100003c,0x5de20b);
	__32reg_write(0x81000040,0x1e7c);
	__32reg_write(0x81000044,0x1b9a7);
	__32reg_write(0x81000048,0x459f6);
	__32reg_write(0x8100004c,0x7c49d);
	__32reg_write(0x81000050,0xe4c);
	__32reg_write(0x81000054,0x1cbcd);
	__32reg_write(0x81000058,0x25c78);
	__32reg_write(0x8100005c,0xbeb05);
	__32reg_write(0x81000060,0x632);
	__32reg_write(0x81000064,0x557b);
	__32reg_write(0x81000068,0x7aa1a);
	__32reg_write(0x8100006c,0x76fd69);
	__32reg_write(0x81000070,0x1339);
	__32reg_write(0x81000074,0x12d1);
	__32reg_write(0x81000078,0x465c);
	__32reg_write(0x8100007c,0x6e53f2);
	__32reg_write(0x81000080,0xc49);
	__32reg_write(0x81000084,0x53c5);
	__32reg_write(0x81000088,0x79678);
	__32reg_write(0x8100008c,0x11ef16);
	__32reg_write(0x81000090,0x150);
	__32reg_write(0x81000094,0x1c3c0);
	__32reg_write(0x81000098,0x5167);
	__32reg_write(0x8100009c,0x7248de);
	__32reg_write(0x810000a0,0x11f1);
	__32reg_write(0x810000a4,0x16bbd);
	__32reg_write(0x810000a8,0x2abb1);
	__32reg_write(0x810000ac,0x57e015);
	__32reg_write(0x810000b0,0xc81);
	__32reg_write(0x810000b4,0x1ab9d);
	__32reg_write(0x810000b8,0x1634f);
	__32reg_write(0x810000bc,0x70cec0);
	__32reg_write(0x810000c0,0x1447);
	__32reg_write(0x810000c4,0x18da2);
	__32reg_write(0x810000c8,0x124a1);
	__32reg_write(0x810000cc,0x877e9);
	__32reg_write(0x810000d0,0xa90);
	__32reg_write(0x810000d4,0xb8b8);
	__32reg_write(0x810000d8,0x55d61);
	__32reg_write(0x810000dc,0x2aef2c);
	__32reg_write(0x810000e0,0x1242);
	__32reg_write(0x810000e4,0x1b3a7);
	__32reg_write(0x810000e8,0x560a);
	__32reg_write(0x810000ec,0x4860bc);
	__32reg_write(0x810000f0,0x657);
	__32reg_write(0x810000f4,0xedea);
	__32reg_write(0x810000f8,0x3c948);
	__32reg_write(0x810000fc,0x2e4c00);
	__32reg_write(0x81000100,0x6d4);
	__32reg_write(0x81000104,0x1dc7b);
	__32reg_write(0x81000108,0x3565d);
	__32reg_write(0x8100010c,0x5d137c);

	__32reg_write(0x21a000b0,0x100d);
	__32reg_write(0x21a000b4,0x10004);
	__32reg_write(0x21a000b8,0x40013);
	__32reg_write(0x21a000bc,0x400010);
	__32reg_write(0x21a00060,0x100d);
	__32reg_write(0x21a00064,0x10004);
	__32reg_write(0x21a00068,0x40013);
	__32reg_write(0x21a0006c,0x400010);

	__32reg_write(0x21a00218,0);
	__32reg_write(0x21a0021c,0x81000000);
	__32reg_write(0x21a00038,0x00003);//use 8 polynomial and enalbe randomizing


	NandReadSector(0x6);
	nfc_dump(0x21a00000);
	nfc_dump(0x90000000);
	while(1);
#endif
}

STATIC_FUNC int callback_writePageInBlk(NFC_BASE_T * nfcBase, uint32_t page,
					uint32_t num, uint32_t * retNum, uint32_t ifHasMBuf, uint32_t ifHasSBuf, uint32_t mode)
{
	NAND_INST *inst;
	int ret = 0;
	uint32_t ifChangeBuf = 0;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;
#ifdef _DEBUG_NAND_
	_chkMem(this);
#endif
	_selectCS(this, __GETCS(page));
	this->NFC_sts_mach_val = _MACH_WRITE;
	this->NFC_time0_val = this->NFC_Time0_W;
	this->NFC_cfg0_val = (this->NFC_cfg0 | _CFG0_SET_NFC_MODE(0) | _CFG0_SET_NFC_RW);

    __32reg_write(NFC_MAIN_ADDRH_REG, 0x0);
    __32reg_write(NFC_SPAR_ADDRH_REG, 0x0);
    __32reg_write(NFC_STAT_ADDRH_REG, 0x0);
    __32reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)this->mBuf_p);
    __32reg_write(NFC_SPAR_ADDRL_REG, (uint32_t)this->sBuf_p);
    __32reg_write(NFC_STAT_ADDRL_REG, (uint32_t)this->stsBuf_p);


#ifndef CONFIG_NAND_SPL

        uint32_t mBuf_size = (1 << this->bufShift);
        uint32_t sBuf_size = (1 << (this->bufShift - this->sectShift)) * this->param.nSpareSize;
        uint32_t stsBuf_size = (1 << (this->bufShift - this->sectShift));


        if (ifHasMBuf){
		flush_cache((unsigned int)this->mBuf_p,mBuf_size);
		//invalidate_cache((unsigned int)this->mBuf_p,mBuf_size);
        }

        if (ifHasSBuf){
		flush_cache((unsigned int)this->sBuf_p, sBuf_size);
		//invalidate_cache((unsigned int)this->sBuf_p, sBuf_size);
        }

	flush_cache((unsigned int)this->stsBuf_p,stsBuf_size);
	//invalidate_cache((unsigned int)this->stsBuf_p,stsBuf_size);
#endif

	switch (mode) {
	case MTD_OPS_AUTO_OOB:
		this->NFC_cfg0_val |= _CFG0_SET_SPARE_ONLY_INFO_PROD_EN;
	case MTD_OPS_PLACE_OOB:	//pass
		this->NFC_cfg0_val |= (_CFG0_SET_ECC_EN | _CFG0_SET_MAIN_USE | _CFG0_SET_SPAR_USE);
		inst = &_inst_write_main_spare;
		break;
	case MTD_OPS_RAW:
		if (ifHasMBuf & ifHasSBuf) {
			this->NFC_cfg0_val |= (_CFG0_SET_MAIN_USE | _CFG0_SET_SPAR_USE);
			inst = &_inst_write_main_spare;
		} else if (ifHasMBuf) {
			this->NFC_cfg0_val |= (_CFG0_SET_MAIN_USE);
			inst = &_inst_write_main_raw;
		} else if (ifHasSBuf) {
			this->NFC_cfg0_val |= (_CFG0_SET_MAIN_USE);	// use main to write spare area
			inst = &_inst_write_spare_raw;
			{
				// 0 nand controller use mainAddr to send spare data, So i have to change some globe config here
				ifChangeBuf = 1;
				// 1 change to main buf
				__32reg_write(NFC_MAIN_ADDRH_REG, 0x0);
				__32reg_write(NFC_MAIN_ADDRL_REG, _RAM_MAIN_ADDR(this->sBuf_p));
				// 2 change mainsize
				this->NFC_cfg1 &= (~_CFG1_temp_MIAN_SIZE_MSK);
				this->NFC_cfg1 |= _CFG1_DEF1_MAIN_SIZE(this->param.nSpareSize << this->sectPerPgShift);
				__32reg_write(NFC_CFG1_REG, this->NFC_cfg1);
				// 3 change sect number
				this->NFC_cfg0_val &= (~_CFG0_temp_SECT_NUM_MSK);
				this->NFC_cfg0_val |= _CFG0_DEF1_SECT_NUM(1);
			}
		} else {
			_deSelectCS(this, -EINVAL);
			return -EINVAL;
		}
		break;
	default:
		panic("sprd nand ops mode error!\n");
		break;
	}

	_cmd_change(inst, page);
	_cmd_exec(this, inst, num, 0);
	ret = _cmd_wait(this, inst, 0);
	if (ifChangeBuf) {
		// 1 change to main buf
		__32reg_write(NFC_MAIN_ADDRH_REG, 0x0);
		__32reg_write(NFC_MAIN_ADDRL_REG, _RAM_MAIN_ADDR(this->mBuf_p));
		// 2 change mainsize
		this->NFC_cfg1 &= (~_CFG1_temp_MIAN_SIZE_MSK);
		this->NFC_cfg1 |= _CFG1_DEF1_MAIN_SIZE(this->param.nSecSize);
		__32reg_write(NFC_CFG1_REG, this->NFC_cfg1);
		// 3 change sect number
		__32reg_write(NFC_CFG0_REG, this->NFC_cfg0);
	}
	if (ret) {
		if(retNum != NULL)
			*retNum = 0;
		_deSelectCS(this, -EIO);
		return -EIO;
	}
	if(retNum != NULL)
		*retNum = num;
	_deSelectCS(this, 0);
	return 0;
}

#define MAX_SPL_OFFSET    0x20000
int nand_write_spl_page(u8 *buf, struct mtd_info *mtd, u32 page, u32 ecc_pos)
{
	uint32_t ifHasMBuf = 1;
	uint32_t ifHasSBuf = 1;
	int ret = 0;
	uint32_t cfg4 = 0;
	NFC_BASE_T *nfcBase = (NFC_BASE_T * )mtd->priv ;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;

	cfg4 = sprd_dolphin_reg_read(NFC_CFG4_REG);
	cfg4 &=(~_CFG4_ONLY_SEL_MODE);
	memset(this->mBuf_p,0xff,(1 << this->pageShift));
	memcpy(this->mBuf_p,buf,(1 << this->pageShift));
	memset(this->sBuf_p,0xFF, (1 << (this->bufShift - this->sectShift)));
	__32reg_write(NFC_CFG1_REG, (uint32_t)this->NFC_cfg1);
	__32reg_write(NFC_CFG2_REG, (uint32_t)this->NFC_cfg2);
	__32reg_write(NFC_CFG4_REG, cfg4);

	GenPageSeed(page % (MAX_SPL_OFFSET/mtd->writesize));
	NandSetRandomizer(this,(uint32_t)(seedBuf+((page & 0xf)<<2)));
	flush_cache((unsigned int)seedBuf,sizeof(seedBuf));
	ret = callback_writePageInBlk(nfcBase, page,
					1, NULL,ifHasMBuf, ifHasSBuf,
					MTD_OPS_PLACE_OOB);
	__32reg_write(NFC_CFG3_REG,_CFG3_DETECT_ALL_FF);//disable random and enable detect_all_ff
	return ret;
}

int nand_read_spl_page(u8 *buf, struct mtd_info *mtd, u32 page, u32 ecc_pos)
{
	uint32_t ifHasMBuf = 1;
	uint32_t ifHasSBuf = 1;
	int ret = 0;
	NFC_BASE_T *nfcBase = (NFC_BASE_T * )mtd->priv ;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;

	GenPageSeed(page % (MAX_SPL_OFFSET/mtd->writesize));
	NandSetRandomizer(this,(uint32_t)(seedBuf+((page & 0xf)<<2)));
	flush_cache((unsigned int)seedBuf,sizeof(seedBuf));
	ret = callback_readPageInBlk(nfcBase, page,
					1, NULL,ifHasMBuf, ifHasSBuf,
					MTD_OPS_PLACE_OOB, &(mtd->ecc_stats));
	memcpy(buf, this->mBuf_p, (1 << this->pageShift));
	__32reg_write(NFC_CFG3_REG,_CFG3_DETECT_ALL_FF);//disable random and enable detect_all_ff
	return ret;
}

STATIC_FUNC int callback_eraseBlk(NFC_BASE_T * nfcBase, uint32_t page)
{
	NAND_INST *inst = &_inst_erase;
	int ret = 0;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;
#ifdef _DEBUG_NAND_
	_chkMem(this);
#endif
	_selectCS(this, __GETCS(page));
	this->NFC_sts_mach_val = _MACH_ERASE;
	this->NFC_time0_val = this->NFC_Time0_E;
	this->NFC_cfg0_val = (this->NFC_cfg0 | _CFG0_SET_NFC_MODE(2));

	_cmd_change(inst, page);
	_cmd_exec(this, inst, 1, 0);
	ret = _cmd_wait(this, inst, 0);
	_deSelectCS(this, ret);
	return ret;
}

STATIC_FUNC int _ifBadFlag(uint8_t * flag, uint32_t len)
{
	//caculate zero bit number;
	uint32_t i, k, num;

	num = 0;
	for (i = 0; i < len; i++) {
		for (k = 0; k < 8; k++) {
			if (flag[i] & (1 << k)) {
				num++;
			}
		}
	}
	return (num < (len << 2));
}

int callback_isBadBlk(NFC_BASE_T * nfcBase, uint32_t page)
{
	int ret;
	uint32_t retNum;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;

	ret = nfcBase->_readPageInBlk(nfcBase, page, 1, &retNum, 0, 1, MTD_OPS_RAW, 0);
	if (ret) {
		return ret;
	}
	return _ifBadFlag(this->sBuf_v + this->param.badFlag_pos, this->param.badFlag_len);
}

int callback_markBadBlk(NFC_BASE_T * nfcBase, uint32_t page)
{
	int ret;
	uint32_t retNum;
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;

	memset(this->sBuf_v, 0xFF, this->param.nSpareSize * this->param.nSectPerPage);
	memset(this->sBuf_v + this->param.badFlag_pos, 0, this->param.badFlag_len);
	ret = nfcBase->_writePageInBlk(nfcBase, page, 1, &retNum, 0, 1, MTD_OPS_RAW);

	return 0;
}

STATIC_FUNC int callback_ctrl_en(NFC_BASE_T * nfcBase, uint32_t en)
{
//#ifndef _DEBUG_NAND_
//	if (en) {
//		sci_glb_set(REG_AP_AHB_AHB_EB, BIT_NANDC_EB | BIT_NANDC_2X_EB | BIT_NANDC_ECC_EB);
//	} else {
//		sci_glb_clr(REG_AP_AHB_AHB_EB, BIT_NANDC_EB | BIT_NANDC_2X_EB | BIT_NANDC_ECC_EB);
//	}
//#endif
	return 0;
}

STATIC_FUNC int _getGlobeResource(NAND_CTL * this)
{
	uint32_t i;

#ifdef SPRDNAND_KERNEL
	this->irq = IRQ_NFC_INT;
#endif
	this->ioaddr = (void __iomem *)SPRD_NANDC_CTRL_PHYS;
	this->frequence = SPRD_NAND_CLOCK;

	printk(KERN_ERR "sprd nand ioaddr = 0x%x ,freq = %d\n", (uint32_t) this->ioaddr, this->frequence);
	return 0;
}


STATIC_FUNC void sprd_dolphin_reg_or(uint32_t addr, uint32_t val)
{
	sprd_dolphin_reg_write(addr, sprd_dolphin_reg_read(addr) | val);
}
STATIC_FUNC void sprd_dolphin_reg_and(uint32_t addr, uint32_t mask)
{
	sprd_dolphin_reg_write(addr, sprd_dolphin_reg_read(addr) & mask);
}

STATIC_FUNC int _initGlobeResource(NAND_CTL * this)
{
	sprd_dolphin_reg_or(REG_AP_AHB_AHB_EB, BIT_AP_AHB_NANDC_EB);
	sprd_dolphin_reg_or(REG_AP_AHB_AHB_EB, BIT_AP_AHB_NANDC_ECC_EB);
	sprd_dolphin_reg_or(REG_AP_AHB_AHB_EB, BIT_AP_AHB_NANDC_26M_EB);

	sprd_dolphin_reg_or(REG_AON_APB_CGM_CLK_TOP_REG1,
			    BIT_AON_APB_CGM_NANDC_2X_EN | BIT_AON_APB_CGM_NANDC_1X_EN);

	sprd_dolphin_reg_write(REG_AON_CLK_CORE_CGM_NANDC_2X_CFG,0x3);//195

	sprd_dolphin_reg_write(REG_AP_CLK_CORE_CGM_NANDC_ECC_CFG,0x1);//256
	sprd_dolphin_reg_or(REG_AP_AHB_AHB_RST,BIT_AP_AHB_NANDC_SOFT_RST );
	udelay(1000);
	sprd_dolphin_reg_and(REG_AP_AHB_AHB_RST, ~(BIT_AP_AHB_NANDC_SOFT_RST ));
	return 0;

}

STATIC_FUNC void callback_ctrl_suspend(struct NFC_BASE *this)
{
	return;
}

STATIC_FUNC int callback_ctrl_resume(struct NFC_BASE *nfcBase)
{
	NAND_CTL *this = (NAND_CTL *) nfcBase->priv;
	_init_reg_state1(this);
	return 0;
}

STATIC_FUNC void _init_nfc_base(NFC_BASE_T * base, NAND_CTL * this)
{
	uint32_t nSect, pos, i;

	memset(base, 0, sizeof(NFC_BASE_T));

	for (i = 0; i < NFC_MAX_ID_LEN; i++) {
		base->id[i] = this->param.id[i];
	}
	base->ecc_mode = this->param.ecc_mode;
	base->risk_threshold = this->risk_threshold;
	base->oobSize = this->param.nSpareSize << (this->pageShift - this->sectShift);
	base->layout.eccbytes = this->param.ecc_size << (this->pageShift - this->sectShift);
	base->layout.oobavail = this->param.info_size << (this->pageShift - this->sectShift);
	for (nSect = 0, i = 0; nSect < this->param.nSectPerPage; nSect++) {
		for (pos = this->param.ecc_pos; pos < this->param.ecc_pos + this->param.ecc_size; pos++) {
			base->layout.eccpos[i] = nSect * this->param.nSpareSize + pos;
			i++;
		}
		base->layout.oobfree[nSect].offset = nSect * this->param.nSpareSize + this->param.info_pos;
		base->layout.oobfree[nSect].length = this->param.info_size;
	}
	base->pageShift = this->pageShift;
	base->blkShift = this->blkShift;
	base->chipShift = ffs(this->param.nBlkCnt << this->blkShift) - 1;
	base->chipNum = this->csNum;
	base->bufShift = this->bufShift;

	base->_ctrl_en = callback_ctrl_en;
	base->_ctrl_suspend = callback_ctrl_suspend;
	base->_ctrl_resume = callback_ctrl_resume;
	base->_readPageInBlk = callback_readPageInBlk;
	base->_writePageInBlk = callback_writePageInBlk;
	base->_nand_eraseBlk = callback_eraseBlk;
	base->_nand_isBadBlk = callback_isBadBlk;
	base->_nand_markBadBlk = callback_markBadBlk;
	base->mBuf_v = this->mBuf_v;
	base->sBuf_v = this->sBuf_v;
#ifdef SPRDNAND_KERNEL
	base->_debugfs_drv_show = callback_debugfs_show;
#endif
	base->priv = this;
}

STATIC_FUNC int nand_drv_probe(NAND_CTL *dev)
{
	NAND_CTL *this = dev;
	uint32_t i;
	int ret;

	memset(this, 0, sizeof(NAND_CTL));

	printf("nand_drv_probe\n");

	ret = _getGlobeResource(this);
	if (ret) {
		return ret;
	}
	ret = _initGlobeResource(this);
	if (ret) {
		return ret;
	}

	_init_reg_state0(this);

	nand_set_timing_config(this, &default_timing, SPRD_NAND_CLOCK);

	this->csNum = 1;
	this->cs[0] = 0;
	_selectCS(this, 0);
	ret = __reset(this);
	if (ret) {
		printf("nand_drv_probe  flash0 reset fail\n");
		_deSelectCS(this, ret);
		return ret;
	}
	else{
		printf("nand_drv_probe  flash0 reset pass\n");
	}
	ret = __readId(this);
	if (ret) {
		printf("nand_drv_probe  flash0 readid fail\n");
		_deSelectCS(this, ret);
		return ret;
	}
	else{
		printf("flash0 readid success,id[] is %x %x %x %x %x\n",
			this->param.id[0],this->param.id[1],this->param.id[2],this->param.id[3],this->param.id[4]);
	}
	_deSelectCS(this, ret);

	for (i = 1; i < _CFG0_CS_MAX; i++) {
		printf("try to probe flash%d\n",i);
		_selectCS(this, i);
		ret = __reset(this);
		if (ret){
			_deSelectCS(this, ret);
			__32reg_write(NFC_START_REG, _CTRL_NFC_CMD_CLR);
			printf("flash%d reset fail\n",i);//flash  reset fail,jump the multi flash init
			break;
		}
		else{
			ret = __readId(this);
			if (ret) {
				printf("flash%d readid fail\n",i);//flash  readid fail,jump the multi flash init
				break;
			}
			else{
				printf("find flash%d,id[] is %x %x %x %x %x\n",
					i,this->param.id[0],this->param.id[1],this->param.id[2],this->param.id[3],this->param.id[4]);
				this->csNum = this->csNum + 1;
				this->cs[i] = i;
			}
		}
		_deSelectCS(this, ret);
	}

	ret = _param_init(this);
	if (ret) {
		return ret;
	}
	_init_reg_state1(this);

	_init_nfc_base(&nfc_base, this);
	nfc_base_register(&nfc_base);

	return 0;

}

#ifdef SPRDNAND_KERNEL

#ifdef CONFIG_OF

STATIC_FUNC const struct of_device_id sprd_nand_of_match[] = {
	{.compatible = "sprd,sprd-nand"},
	{}
};

MODULE_DEVICE_TABLE(of, sprd_nand_of_match);
#endif

STATIC_FUNC struct platform_driver sprd_nand_driver = {
	.probe = nand_drv_probe,
	.driver = {
		   .name = "sprd-nand",
		   .owner = THIS_MODULE,
		   .of_match_table = of_match_ptr(sprd_nand_of_match),
		   },
};

STATIC_FUNC int __init sprd_nand_init(void)
{
	return platform_driver_register(&sprd_nand_driver);
}

STATIC_FUNC void __exit sprd_nand_exit(void)
{
	platform_driver_unregister(&sprd_nand_driver);
}

module_init(sprd_nand_init);
module_exit(sprd_nand_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("jason.wu@spreadtrum.com");
MODULE_DESCRIPTION("SPRD MTD NAND driver");
MODULE_ALIAS("platform:sprd-nand");
#endif //end SPRDNAND_KERNEL

#ifdef SPRDNAND_UBOOT
int nand_curr_device = -1;
void nand_init(void)
{
    if(nand_curr_device == -1)
            nand_curr_device = 0;
    nand_drv_probe(&controller);

}
#endif
