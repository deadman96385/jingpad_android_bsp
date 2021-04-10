/*
 * Copyright (C) 2012 Spreadtrum Communications Inc.
 *
 */

#include <common.h>
//#include <malloc.h>
#include <asm/io.h>
//#include <asm/errno.h>
#include <config.h>

#include <sci_types.h>
#include <asm/arch/sprd_reg.h>
#include <bits.h>

#include <nand.h>
#include <linux/mtd/nand.h>

#include "sprd_nfc_reg_r6p0.h"
#include <gpio_drvapi.h>

#ifdef CONFIG_NAND_SPL
#define udelay(x) \
	do { \
		volatile int i; \
		int cnt = 200 * (x); \
		for (i=0; i<cnt; i++);\
	} while(0);
#endif

#define mdelay(_ms) udelay((_ms)*1000)

#define NAND_DBG

#if defined(CONFIG_NAND_SPL) || !defined(NAND_DBG)
#define DPRINT(arg...) do{}while(0)
#else
#define DPRINT printf
#endif
#define ASSERT(cond) { assert(cond); }


#define NFC_MC_ICMD_ID	(0xCD)
#define NFC_MC_ADDR_ID	(0x0A)
#define NFC_MC_WRB0_ID	(0xB0)
#define NFC_MC_WRB1_ID	(0xB1)
#define NFC_MC_MRDT_ID	(0xD0)
#define NFC_MC_MWDT_ID	(0xD1)
#define NFC_MC_SRDT_ID	(0xD2)
#define NFC_MC_SWDT_ID	(0xD3)
#define NFC_MC_IDST_ID	(0xDD)
#define NFC_MC_CSEN_ID	(0xCE)
#define NFC_MC_NOP_ID	(0xF0)
#define NFC_MC_DONE_ID	(0xFF)
#define NFC_MAX_CHIP	1
#define NFC_TIMEOUT_VAL		0x10000000

#define NAND_MC_CMD(x)  (uint16_t)(((x & 0xff) << 8) | NFC_MC_ICMD_ID)
#define NAND_MC_ADDR(x) (uint16_t)(((x & 0xff) << 8) | (NFC_MC_ADDR_ID << 4))
#define NAND_MC_WRB0(x) (uint16_t)(NFC_MC_WRB0_ID)
#define NAND_MC_MRDT	(uint16_t)(NFC_MC_MRDT_ID)
#define NAND_MC_MWDT	(uint16_t)(NFC_MC_MWDT_ID)
#define NAND_MC_SRDT	(uint16_t)(NFC_MC_SRDT_ID)
#define NAND_MC_SWDT	(uint16_t)(NFC_MC_SWDT_ID)
#define NAND_MC_IDST(x)	(uint16_t)((NFC_MC_IDST_ID) | ((x -1) << 8))
#define NAND_MC_NOP(x)	(uint16_t)(((x & 0xff) << 8) | NFC_MC_NOP_ID)


#define NAND_MC_BUFFER_SIZE (24)

static int mtderasesize = 0;
static int mtdwritesize = 0;
static int mtdoobsize = 0;


#define SPRD_ASSERT(cond) { if (!(cond)) while(1); }
#define STATIC_FUNC static

#include "sprd_nand_param.h"

/* 2 bit correct, sc8810 support 1, 2, 4, 8, 12,14, 24 */
#define CONFIG_SYS_NAND_ECC_MODE    (2)
//#define CONFIG_SYS_NAND_ECC_MODE	8
/* Number of ECC bytes per OOB - S3C6400 calculates 4 bytes ECC in 1-bit mode */
#define CONFIG_SYS_NAND_ECCBYTES    (4)
//#define CONFIG_SYS_NAND_ECCBYTES	14

#define NAND_MC_BUFFER_SIZE         (24)
#define CONFIG_SYS_NAND_ECCSIZE     (512)
#define CONFIG_SYS_NAND_5_ADDR_CYCLE	5

#define BIT_NAND_ENABLE		BIT_AP_AHB_NANDC_EB
#define BIT_NAND_RESET		(BIT_AP_AHB_NANDC_SOFT_RST)
#define SPRD_NAND_CLOCK (133)

static struct sprd_nand_timing default_timing = {10, 30, 30};


#define IRQ_TIMEOUT  100//unit:ms,IRQ timeout value
#define DRIVER_NAME "sp9820e_nand"


enum NAND_ERR_CORRECT_S {
    NAND_FATAL_ERROR=0,
    NAND_ERR_NEED_RETRY,
    NAND_ERR_FIXED,
    NAND_NO_ERROR
};

enum NAND_HANDLE_STATUS_S {
    NAND_HANDLE_DONE=0,
    NAND_HANDLE_TIMEOUT,
    NAND_HANDLE_ERR
};

static enum NAND_HANDLE_STATUS_S  handle_status = NAND_HANDLE_DONE;
static enum NAND_ERR_CORRECT_S ret_irq_en = NAND_NO_ERROR;

STATIC_FUNC void nfc_enable_interrupt(void);
STATIC_FUNC void nfc_disable_interrupt(void);
STATIC_FUNC void nfc_clear_interrupt(void);

struct sprd_dolphin_nand_info {
	struct mtd_info *mtd;
	struct nand_chip *nand;

	struct device *pdev;

	struct sprd_nand_param *param;
	uint32_t chip; //chip index
	uint32_t v_mbuf; //virtual main buffer address
	uint32_t p_mbuf; //phy main buffer address
	uint32_t v_oob; // virtual oob buffer address
	uint32_t p_oob; //phy oob buffer address
	uint32_t page; //page address
	uint16_t column; //column address
	uint16_t oob_size;
	uint16_t m_size; //main part size per sector
	uint16_t s_size; //oob size per sector
	uint8_t a_cycles;//address cycles, 3, 4, 5
	uint8_t sct_pg; //sector per page
	uint8_t info_pos;
	uint8_t info_size;
	uint8_t ecc_mode;//0-1bit, 1-2bit, 2-4bit, 3-8bit,4-12bit,5-16bit,6-24bit
	uint8_t ecc_pos; // ecc postion
	uint8_t wp_en; //write protect enable
	uint16_t write_size;
	uint16_t page_per_bl;//page per block
	uint16_t  buf_head;
	uint16_t _buf_tail;
	uint8_t ins_num;//instruction number
	uint32_t ins[NAND_MC_BUFFER_SIZE >> 1];
};


#define mtd_to_dolphin(m) (&g_dolphin)

//gloable variable
static struct nand_ecclayout sprd_dolphin_nand_oob_default = {
	.eccbytes = 0,
	.eccpos = {0},
	.oobfree = {
		{.offset = 2,
		 .length = 46}}
};
struct sprd_dolphin_nand_info g_dolphin = {0};
//save the data read by read_byte and read_word api interface functon
static __attribute__((aligned(4))) uint8_t s_oob_data[NAND_MAX_OOBSIZE];
//static __attribute__((aligned(4))) uint8_t s_oob_data[8];
//static __attribute__((aligned(4))) uint8_t s_id_status[8];

STATIC_FUNC int sprd_dolphin_nand_read_id(struct sprd_dolphin_nand_info *dolphin, uint32_t *buf);
STATIC_FUNC int sprd_dolphin_nand_reset(struct sprd_dolphin_nand_info *dolphin);
STATIC_FUNC int sprd_dolphin_nand_wait_finish(struct sprd_dolphin_nand_info *dolphin);

STATIC_FUNC uint32_t sprd_dolphin_reg_read(uint32_t addr)
{
	return readl(addr);
}
STATIC_FUNC void sprd_dolphin_reg_write(uint32_t addr, uint32_t val)
{
	writel(val, addr);
}
STATIC_FUNC void sprd_dolphin_reg_or(uint32_t addr, uint32_t val)
{
	sprd_dolphin_reg_write(addr, sprd_dolphin_reg_read(addr) | val);
}
STATIC_FUNC void sprd_dolphin_reg_and(uint32_t addr, uint32_t mask)
{
	sprd_dolphin_reg_write(addr, sprd_dolphin_reg_read(addr) & mask);
}
STATIC_FUNC void sprd_dolphin_nand_int_clr(uint32_t bit_clear)
{
	sprd_dolphin_reg_write(NFC_INT_REG, bit_clear);
}

STATIC_FUNC void nfc_clear_interrupt(void)
{
	uint32_t value = 0;

	value = ( INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);
	sprd_dolphin_reg_or(NFC_INT_REG, value); /* clear all interrupt status */

	//value = NFC_CMD_CLR;
	//sprd_dolphin_reg_or(NFC_START_REG, value); /* clear all interrupt status */
}

STATIC_FUNC void nfc_enable_interrupt(void)
{
	uint32_t value = 0;

	value = (INT_TO_EN | INT_DONE_EN);
	sprd_dolphin_reg_or(NFC_INT_REG, value); /* clear all interrupt status */
}

STATIC_FUNC void nfc_disable_interrupt(void)
{
	uint32_t value = 0;

	value = ~(INT_TO_EN | INT_DONE_EN);
	sprd_dolphin_reg_and(NFC_INT_REG, value); /* clear all interrupt status */
}

unsigned int ecc_mode_convert(uint32_t mode)
{
	uint32_t mode_m;
	switch(mode)
	{
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
	case 40:
		mode_m = 7;
		break;
	case 60:
		mode_m = 8;
		break;
	default:
		mode_m = 0;
		break;
	}
	return mode_m;
}

STATIC_FUNC void dolphin_set_timing_config(struct sprd_nand_timing *timing ,
					   uint32_t nfc_clk_MHz)
{
	u32 reg_val, temp_val;

		reg_val = 0;

		/* get acs value : 0ns */
		reg_val |= ((2 & 0x1F) << NFC_ACS_OFFSET);

		/* get ace value + 6ns read delay time, and rwl added */
		temp_val = (timing->ace_ns + 6) * nfc_clk_MHz / 1000;
		if (((timing->ace_ns * nfc_clk_MHz) % 1000)  != 0) {
			temp_val++;
		}
		reg_val |= ((temp_val & 0x1F) << NFC_ACE_OFFSET);

		/* get rws value : 20 ns */
		temp_val = 20 * nfc_clk_MHz / 1000;
		if (((timing->ace_ns * nfc_clk_MHz) % 1000)  != 0) {
			temp_val++;
		}
		reg_val |= ((temp_val & 0x3F) << NFC_RWS_OFFSET);

		/* get rws value : 0 ns */
		reg_val |= ((2 & 0x1F) << NFC_RWE_OFFSET);

		/* get rwh value */
		temp_val = (timing->rwh_ns + 6) * nfc_clk_MHz / 1000;
		if (((timing->ace_ns * nfc_clk_MHz) % 1000)  != 0) {
			temp_val++;
		}
		reg_val |= ((temp_val & 0x1F) << NFC_RWH_OFFSET);

		/* get rwl value, 6 is read delay time*/
		temp_val = (timing->rwl_ns + 6) * nfc_clk_MHz / 1000;
		if (((timing->ace_ns * nfc_clk_MHz) % 1000)  != 0) {
			temp_val++;
		}
		reg_val |= (temp_val & 0x3F);

		DPRINT("%s nand timing val: 0x%x\n\r", __func__, reg_val);

		sprd_dolphin_reg_write(NFC_TIMING0_REG, reg_val);

}

#ifdef CONFIG_NAND_SPL
struct sprd_dolphin_boot_header_info {
	uint32_t check_sum;
	uint32_t sct_size; //
	uint32_t acycle; // 3, 4, 5
	uint32_t bus_width; //0 ,1
	uint32_t spare_size; //spare part sise for one sector
	uint32_t ecc_mode; //0--1bit, 1--2bit,2--4bit,3--8bit,4--12bit, 5--16bit, 6--24bit
	uint32_t ecc_pos; // ecc postion at spare part
	uint32_t sct_per_page; //sector per page
	uint32_t info_pos;
	uint32_t info_size;
	uint32_t magic_num; //0xaa55a5a5
	uint32_t ecc_value[27];
};
void boad_nand_param_init(struct sprd_dolphin_nand_info *dolphin, struct nand_chip *chip, uint8 *id)
{
	int extid;
	uint32_t writesize;
	uint32_t oobsize;
	uint32_t erasesize;
	uint32_t busw;

	/* The 4th id byte is the important one */
	extid = id[3];
	writesize = 1024 << (extid & 0x3);
	extid >>= 2;
	/* Calc oobsize */
	oobsize = (8 << (extid & 0x01)) * (writesize >> 9);
	extid >>= 2;
	/* Calc blocksize. Blocksize is multiples of 64KiB */
	erasesize = (64 * 1024) << (extid & 0x03);
	extid >>= 2;
	/* Get buswidth information */
	busw = (extid & 0x01) ? NAND_BUSWIDTH_16 : 0;
	dolphin->write_size = writesize;
	dolphin->m_size =CONFIG_SYS_NAND_ECCSIZE;
	dolphin->sct_pg = writesize / CONFIG_SYS_NAND_ECCSIZE;
	dolphin->s_size = oobsize / dolphin->sct_pg;
	dolphin->ecc_mode = ecc_mode_convert(CONFIG_SYS_NAND_ECC_MODE);
	dolphin->ecc_pos = dolphin->s_size - ((14 * CONFIG_SYS_NAND_ECC_MODE + 7) / 8);
	dolphin->info_pos = dolphin->ecc_pos - 1;
	dolphin->info_size = 1;
	dolphin->page_per_bl = erasesize / dolphin->write_size;
	dolphin->a_cycles = CONFIG_SYS_NAND_5_ADDR_CYCLE;
	if(NAND_BUSWIDTH_16 == busw)
	{
		chip->options |= NAND_BUSWIDTH_16;
	}
	else
	{
		chip->options &= ~NAND_BUSWIDTH_16;
	}
}

/*
 * because the dolphin firmware use the nand identify process
 * and the data at the header of nand_spl is the nand param used at nand read and write,
 * so in nand_spl, don't need read the id or use the onfi spec to calculate the nand param,
 * just use the param at the nand_spl header instead of
 */
void nand_hardware_config(struct mtd_info *mtd, struct nand_chip *chip)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	struct sprd_nand_param* param;
	struct sprd_nand_oob* oob;
	struct sprd_nand_timing* timing;
	uint8 *id;

	sprd_dolphin_nand_reset(dolphin);
	mdelay(1);
	sprd_dolphin_nand_read_id(dolphin, (uint32_t *)s_oob_data);
	boad_nand_param_init(dolphin, dolphin->nand, s_oob_data);
	id = s_oob_data;

	param = SprdGetNandParam(id);

	if (param != NULL) {
		dolphin->param = param;
		oob = &param->sOOB;
		timing = &param->sTiming;

		dolphin_set_timing_config(timing, SPRD_NAND_CLOCK);

		//save the param config
		dolphin->write_size = param->nPageSize;
		dolphin->page_per_bl = param->nBlkSize / param->nPageSize;
		dolphin->m_size = param->nSecSize;
		dolphin->sct_pg = (param->nPageSize / param->nSecSize);
		dolphin->oob_size = param->nSpareSize;
		dolphin->a_cycles = param->nCycles;

		dolphin->s_size = oob->nOOBSize;
		dolphin->info_pos = oob->nInfoPos;
		dolphin->info_size = oob->nInfoSize;
		dolphin->ecc_pos = oob->nEccPos;
		dolphin->ecc_mode = ecc_mode_convert(oob->nEccBits);
		dolphin->nand=chip;
		dolphin->mtd = mtd;

		chip->ecc.bytes  = (oob->nEccBits * 14 + 7) / 8;
		chip->eccbitmode = oob->nEccBits;

		if(param->nBusWidth)
		{
			chip->options |= NAND_BUSWIDTH_16;
		}
		else
		{
			chip->options &= ~NAND_BUSWIDTH_16;
		}
	}
	mtd->writesize = dolphin->write_size;
	mtd->oobsize = dolphin->s_size * dolphin->sct_pg;
	mtd->erasesize = dolphin->page_per_bl * dolphin->write_size;
}

#else

STATIC_FUNC void sprd_dolphin_nand_ecc_layout_gen(struct sprd_nand_oob *oob,
						  uint8_t sector_num, struct nand_ecclayout *layout)
{
	uint8_t sct = 0;
	uint32_t i = 0;
	uint32_t offset;
	uint32_t used_len ; //one sector ecc data size(byte)
	uint32_t eccbytes = 0; //one page ecc data size(byte)
	uint32_t oobfree_len = 0;

	used_len = (14 * oob->nEccBits + 7) / 8 + oob->nInfoSize;
	if(sector_num > ARRAY_SIZE(layout->oobfree))
	{
		while(1);
	}
	for(sct = 0; sct < sector_num; sct++)
	{
		//offset = (oob_size * sct) + ecc_pos;
		//for(i = 0; i < ecc_len; i++)
		offset = (oob->nOOBSize * sct) + oob->nEccPos;
		for(i = 0; i < used_len; i++)
		{
			layout->eccpos[eccbytes++] = offset + i;
		}
		layout->oobfree[sct].offset = oob->nOOBSize * sct;
		layout->oobfree[sct].length = oob->nOOBSize - used_len ;
		oobfree_len += oob->nOOBSize - used_len;
	}
	//for bad mark postion
	layout->oobfree[0].offset = 2;
	layout->oobfree[0].length = oob->nOOBSize - used_len - 2;
	oobfree_len -= 2;
	layout->eccbytes = used_len * sector_num;
}

void nand_hardware_config(struct mtd_info *mtd, struct nand_chip *chip, uint8_t id[5])
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	struct sprd_nand_param* param;
	struct sprd_nand_oob* oob;
	struct sprd_nand_timing* timing;

	param = SprdGetNandParam(id);

	if (param != NULL) {
		dolphin->param = param;
		oob = &param->sOOB;
		timing = &param->sTiming;

		dolphin_set_timing_config(timing, SPRD_NAND_CLOCK);

		//save the param config
		dolphin->write_size = param->nPageSize;
		dolphin->page_per_bl = param->nBlkSize / param->nPageSize;
		dolphin->m_size = param->nSecSize;
		dolphin->sct_pg = (param->nPageSize / param->nSecSize);
		dolphin->oob_size = param->nSpareSize;
		dolphin->a_cycles = param->nCycles;

		dolphin->s_size = oob->nOOBSize;
		dolphin->info_pos = oob->nInfoPos;
		dolphin->info_size = oob->nInfoSize;
		dolphin->ecc_pos = oob->nEccPos;
		dolphin->ecc_mode = ecc_mode_convert(oob->nEccBits);
		dolphin->nand=chip;
		dolphin->mtd = mtd;

		chip->ecc.bytes  = (oob->nEccBits * 14 + 7) / 8;
		chip->eccbitmode = oob->nEccBits;

		if(param->nBusWidth)
		{
			chip->options |= NAND_BUSWIDTH_16;
		}
		else
		{
			chip->options &= ~NAND_BUSWIDTH_16;
		}

		/* Calculate the address shift from the page size */
		chip->page_shift = ffs(mtd->writesize) - 1;
		/* Convert chipsize to number of pages per chip -1. */
		chip->pagemask = (chip->chipsize >> chip->page_shift) - 1;
		sprd_dolphin_nand_ecc_layout_gen(oob, dolphin->sct_pg, &sprd_dolphin_nand_oob_default);
		chip->ecc.layout = &sprd_dolphin_nand_oob_default;

		mtd->writesize = dolphin->write_size;
		mtd->oobsize = dolphin->oob_size;
		mtd->erasesize = dolphin->page_per_bl * dolphin->write_size;
	}
	else {
		int steps;
		struct sprd_nand_oob oob_tmp;

		//save the param config
		steps = mtd->writesize / CONFIG_SYS_NAND_ECCSIZE;
		dolphin->ecc_mode = ecc_mode_convert(CONFIG_SYS_NAND_ECC_MODE);
		dolphin->m_size = CONFIG_SYS_NAND_ECCSIZE;
		dolphin->s_size = mtd->oobsize / steps;
		dolphin->a_cycles = mtd->writesize / CONFIG_SYS_NAND_ECCSIZE;
		dolphin->sct_pg = steps;
		dolphin->info_pos = dolphin->s_size - CONFIG_SYS_NAND_ECCBYTES - 1;
		dolphin->info_size = 1;
		dolphin->write_size = mtd->writesize;
		dolphin->page_per_bl = mtd->erasesize / mtd->writesize;
		dolphin->oob_size = mtd->oobsize;
		dolphin->ecc_pos = dolphin->s_size - CONFIG_SYS_NAND_ECCBYTES;
		dolphin->mtd = mtd;

		oob_tmp.nOOBSize = dolphin->s_size;
		oob_tmp.nInfoPos = dolphin->info_pos;
		oob_tmp.nInfoSize = dolphin->info_size;
		oob_tmp.nEccPos = dolphin->ecc_pos;
		oob_tmp.nEccBits = CONFIG_SYS_NAND_ECC_MODE;
		sprd_dolphin_nand_ecc_layout_gen(&oob_tmp, dolphin->sct_pg, &sprd_dolphin_nand_oob_default);

		chip->ecc.layout = &sprd_dolphin_nand_oob_default;
		chip->eccbitmode = CONFIG_SYS_NAND_ECC_MODE;

		if(chip->chipsize > (128 << 20)) {
			dolphin->a_cycles = 5;
		}
		else {
			dolphin->a_cycles = 4;
		}
	}
}

#endif  //end CONFIG_NAND_SPL

#ifndef CONFIG_NAND_SPL
typedef struct {
	uint8_t *m_buf;
	uint8_t *s_buf;
	uint8_t m_sct;
	uint8_t s_sct;
	uint8_t dir; //if dir is 0, read dadta from NFC buffer, if 1, write data to NFC buffer
	uint16_t m_size;
	uint16_t s_size;
} sprd_dolphin_nand_data_param;

STATIC_FUNC unsigned int sprd_dolphin_data_trans(sprd_dolphin_nand_data_param *param)
{
	uint32_t cfg0 = 0;
	uint32_t cfg1 = 0;
	uint32_t cfg2 = 0;
	cfg0 = NFC_ONLY_MST_MODE | MAIN_SPAR_APT | NFC_WPN;
	if(param->dir)
	{
		cfg0 |= NFC_RW;
	}
	if(param->m_sct != 0)
	{
		cfg0 |= (param->m_sct - 1) << SECTOR_NUM_OFFSET;
		cfg0 |= MAIN_USE;
		cfg1 |= (param->m_size - 1);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)param->m_buf);
	}
	if(param->s_sct != 0)
	{
		cfg0 |= SPAR_USE;
		cfg1 |= (param->s_size - 1) << SPAR_SIZE_OFFSET;
		cfg2 |= (param->s_sct - 1) << SPAR_SECTOR_NUM_OFFSET;
		sprd_dolphin_reg_write(NFC_SPAR_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_SPAR_ADDRL_REG, (uint32_t)param->s_buf);
	}
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_CFG1_REG, cfg1);
	sprd_dolphin_reg_write(NFC_CFG2_REG, cfg2);
	sprd_dolphin_nand_int_clr(INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);//clear all interrupt
	sprd_dolphin_reg_write(NFC_START_REG, NFC_START);
	sprd_dolphin_nand_wait_finish(&g_dolphin);
	return 0;
}
void sprd_ecc_ctrl(struct sprd_ecc_param *param, uint32_t dir)
{
	uint32_t nfc_start = 0;
	uint32_t cfg0 = 0;
	uint32_t cfg1 = 0;
	uint32_t cfg2 = 0;

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
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_CFG1_REG, cfg1);
	sprd_dolphin_reg_write(NFC_CFG2_REG, cfg2);
	sprd_dolphin_nand_int_clr(INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);//clear all interrupt
	sprd_dolphin_reg_write(NFC_START_REG, nfc_start | NFC_START);
	sprd_dolphin_nand_wait_finish(&g_dolphin);
}

unsigned int sprd_ecc_encode(struct sprd_ecc_param *param)
{
	struct sprd_dolphin_nand_info *dolphin;
	sprd_dolphin_nand_data_param d_param;

	dolphin = &g_dolphin;
	sprd_memset(&d_param, 0, sizeof(d_param));

	d_param.m_buf = param->p_mbuf;
	d_param.s_buf = param->p_sbuf;
	d_param.m_sct = param->ecc_num;
	d_param.s_sct = param->ecc_num;
	d_param.dir = 1;
	d_param.m_size = param->m_size;
	d_param.s_size = param->sp_size;

	Dcache_CleanRegion((unsigned int)d_param.m_buf, d_param.m_sct*d_param.m_size);
	Dcache_CleanRegion((unsigned int)d_param.s_buf, d_param.s_sct*d_param.s_size);

	sprd_dolphin_data_trans(&d_param);
	sprd_ecc_ctrl(param, 1);
	d_param.dir = 0;
	d_param.m_sct = 0;

	Dcache_InvalRegion((unsigned int)d_param.m_buf , d_param.m_sct*d_param.m_size);
	Dcache_InvalRegion((unsigned int)d_param.s_buf , d_param.s_sct*d_param.s_size);

	sprd_dolphin_data_trans(&d_param); //read the ecc value from nfc buffer
	return 0;
}
#endif  //CONFIG_NAND_SPL end



//add one macro instruction to nand controller
STATIC_FUNC void sprd_dolphin_nand_ins_init(struct sprd_dolphin_nand_info *dolphin)
{
	dolphin->ins_num = 0;
}
STATIC_FUNC void sprd_dolphin_nand_ins_add(uint16_t ins, struct sprd_dolphin_nand_info *dolphin)
{
	uint16_t *buf = (uint16_t *)dolphin->ins;
	if(dolphin->ins_num >= NAND_MC_BUFFER_SIZE)
	{
		while(1);
	}
	*(buf + dolphin->ins_num) = ins;
	dolphin->ins_num++;
}

STATIC_FUNC void sprd_dolphin_nand_ins_exec(struct sprd_dolphin_nand_info *dolphin)
{
	uint32_t i;
	uint32_t nfc_start;
	uint32_t cfg0;

	for(i = 0; i < ((dolphin->ins_num + 1) >> 1); i++)
	{
		sprd_dolphin_reg_write(NFC_INST0_REG + (i << 2), dolphin->ins[i]);
	}
	cfg0 = sprd_dolphin_reg_read(NFC_CFG0_REG);
	if(dolphin->wp_en)
	{
		cfg0 &= ~NFC_WPN;
	}
	else
	{
		cfg0 |= NFC_WPN;
	}
	if(dolphin->chip)
	{
		cfg0 |= CS_SEL;
	}
	else
	{
		cfg0 &= ~CS_SEL;
	}

	nfc_start = sprd_dolphin_reg_read(NFC_START_REG);

	sprd_dolphin_nand_int_clr(INT_STSMCH_CLR | INT_WP_CLR | INT_TO_CLR | INT_DONE_CLR);//clear all interrupt
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_START_REG, nfc_start | NFC_START);
}

STATIC_FUNC int sprd_dolphin_nand_wait_finish(struct sprd_dolphin_nand_info *dolphin)
{
	unsigned int value;
	unsigned int counter = 0;
	while((counter < NFC_TIMEOUT_VAL/*time out*/))
	{
		value = sprd_dolphin_reg_read(NFC_INT_REG);
		if(value & INT_DONE_RAW)
		{
			break;
		}
		counter ++;
	}
	sprd_dolphin_reg_write(NFC_INT_REG, 0xf00); //clear all interrupt status
	if(counter >= NFC_TIMEOUT_VAL)
	{
        //while (1);
		return -1;
	}
	return 0;
}

STATIC_FUNC void sprd_dolphin_nand_wp_en(struct sprd_dolphin_nand_info *dolphin, int en)
{
	if(en)
	{
		dolphin->wp_en = 1;
	}
	else
	{
		dolphin->wp_en = 0;
	}
}
STATIC_FUNC void sprd_dolphin_select_chip(struct mtd_info *mtd, int chip)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	if(chip < 0) {
		return;
	}
	dolphin->chip = chip;
#ifdef CONFIG_NAND_SPL
	nand_hardware_config(mtd,dolphin->nand);
#endif
}

STATIC_FUNC void sprd_dolphin_nand_read_status(struct sprd_dolphin_nand_info *dolphin)
{
	uint32_t *buf;

	sprd_dolphin_nand_ins_init(dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_STATUS), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_NOP(10), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_IDST(1), dolphin);
	sprd_dolphin_nand_ins_add(NFC_MC_DONE_ID, dolphin);
	sprd_dolphin_reg_write(NFC_CFG0_REG, NFC_ONLY_NAND_MODE);
	sprd_dolphin_nand_ins_exec(dolphin);
	sprd_dolphin_nand_wait_finish(dolphin);
	buf = (uint32_t *)s_oob_data;
	*buf = sprd_dolphin_reg_read(NFC_STATUS0_REG);
	dolphin->buf_head = 0;
	dolphin->_buf_tail = 1;

    //DPRINT("%s leave\n", __func__);
}
STATIC_FUNC int sprd_dolphin_nand_read_id(struct sprd_dolphin_nand_info *dolphin, uint32_t *buf)
{
	sprd_dolphin_nand_ins_init(dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_READID), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(0), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_NOP(10), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_IDST(8), dolphin);
	sprd_dolphin_nand_ins_add(NFC_MC_DONE_ID, dolphin);

	sprd_dolphin_reg_write(NFC_CFG0_REG, NFC_ONLY_NAND_MODE);
	sprd_dolphin_nand_ins_exec(dolphin);
	if (sprd_dolphin_nand_wait_finish(dolphin) != 0)
    {
        return -1;
    }
	*buf = sprd_dolphin_reg_read(NFC_STATUS0_REG);
	*(buf + 1) = sprd_dolphin_reg_read(NFC_STATUS1_REG);
	dolphin->buf_head = 0;
	dolphin->_buf_tail = 8;

    return 0;
}

STATIC_FUNC int sprd_dolphin_nand_reset(struct sprd_dolphin_nand_info *dolphin)
{
    //DPRINT("%s enter\n", __func__);

	sprd_dolphin_nand_ins_init(dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_RESET), dolphin);
	sprd_dolphin_nand_ins_add(NFC_MC_WRB0_ID, dolphin); //wait rb
	sprd_dolphin_nand_ins_add(NFC_MC_DONE_ID, dolphin);
	//config register
	sprd_dolphin_reg_write(NFC_CFG0_REG, NFC_ONLY_NAND_MODE);
	sprd_dolphin_nand_ins_exec(dolphin);
	if (sprd_dolphin_nand_wait_finish(dolphin) != 0)
    {
        return 0;
    }

    return 0;
}
STATIC_FUNC u32 sprd_dolphin_get_decode_sts(u32 index)
{
	uint32_t err;
	uint32_t shift;
	uint32_t reg_addr;
	reg_addr = NFC_STATUS0_REG + 2*(index & 0xfffffffc);
	shift = (index & 0x3) << 4;
	err = sprd_dolphin_reg_read(reg_addr);
	err >>= shift;
	err &= ERR_ERR_NUM0_MASK;

	if (err == ERR_ERR_NUM0_MASK)
		return err;
	else
		return 0;
}

STATIC_FUNC int sprd_dolphin_nand_read_lp(struct mtd_info *mtd,
					  uint8_t *mbuf, uint8_t *sbuf,uint32_t raw)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	struct nand_chip *chip = dolphin->nand;
	uint32_t column;
	uint32_t page_addr;
	uint32_t nfc_start;
	uint32_t cfg0;
	uint32_t cfg1;
	uint32_t cfg2;
	uint32_t i;
	uint32_t err;
	page_addr = dolphin->page;

	if(sbuf) {
		column = mtd->writesize;
	}
	else
	{
		column = 0;
	}
	if(chip->options & NAND_BUSWIDTH_16)
	{
		column >>= 1;
	}

	sprd_dolphin_nand_ins_init(dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_READ0), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(column & 0xff), dolphin);
	column >>= 8;
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(column & 0xff), dolphin);

	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);
	page_addr >>= 8;
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);

	if (5 == dolphin->a_cycles)// five address cycles
	{
		page_addr >>= 8;
		sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);
	}
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_READSTART), dolphin);

	sprd_dolphin_nand_ins_add(NFC_MC_WRB0_ID, dolphin); //wait rb
	if(mbuf && sbuf)
	{
		sprd_dolphin_nand_ins_add(NAND_MC_SRDT, dolphin);
		//switch to main part
		sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_RNDOUT), dolphin);
		sprd_dolphin_nand_ins_add(NAND_MC_ADDR(0), dolphin);
		sprd_dolphin_nand_ins_add(NAND_MC_ADDR(0), dolphin);
		sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_RNDOUTSTART), dolphin);
		sprd_dolphin_nand_ins_add(NAND_MC_MRDT, dolphin);
	}
	else
	{
		sprd_dolphin_nand_ins_add(NAND_MC_MRDT, dolphin);
	}
	sprd_dolphin_nand_ins_add(NFC_MC_DONE_ID, dolphin);

	nfc_start = ((dolphin->ecc_mode) << 11);
	cfg0 = NFC_AUTO_MODE | MAIN_SPAR_APT | ((dolphin->sct_pg - 1)<< SECTOR_NUM_OFFSET);
	if((!raw) && mbuf && sbuf)
	{
		cfg0 |= ECC_EN | DETECT_ALL_FF;
	}
	if(chip->options & NAND_BUSWIDTH_16)
	{
		cfg0 |= BUS_WIDTH;
	}
	cfg1 = (dolphin->info_size) << SPAR_INFO_SIZE_OFFSET;
	cfg2 = (dolphin->info_pos << SPAR_INFO_POS_OFFSET) | ((dolphin->sct_pg - 1) << SPAR_SECTOR_NUM_OFFSET) | dolphin->ecc_pos;

#ifndef CONFIG_NAND_SPL
	if (mbuf)
	{
		Dcache_CleanRegion((unsigned int)mbuf, dolphin->m_size*dolphin->sct_pg);
		Dcache_InvalRegion((unsigned int)mbuf, dolphin->m_size*dolphin->sct_pg);
	}

	if (sbuf)
	{
		Dcache_CleanRegion((unsigned int)sbuf, dolphin->s_size*dolphin->sct_pg);
		Dcache_InvalRegion((unsigned int)sbuf, dolphin->s_size*dolphin->sct_pg);
	}
#endif

	if(mbuf && sbuf)
	{
		cfg1 |= (dolphin->m_size - 1) | ((dolphin->s_size  - 1)<< SPAR_SIZE_OFFSET);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)mbuf);
		sprd_dolphin_reg_write(NFC_SPAR_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_SPAR_ADDRL_REG, (uint32_t)sbuf);
		cfg0 |= MAIN_USE | SPAR_USE;
	}
	else
	{
		if(mbuf)
		{
			cfg1 |= (dolphin->m_size - 1);
			sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
			sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)mbuf);
		}
		if(sbuf)
		{
			cfg1 |= (dolphin->s_size - 1);
			sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
			sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)sbuf);
		}
		cfg0 |= MAIN_USE;
	}
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_CFG1_REG, cfg1);
	sprd_dolphin_reg_write(NFC_CFG2_REG, cfg2);
	sprd_dolphin_reg_write(NFC_START_REG, nfc_start);

	sprd_dolphin_nand_ins_exec(dolphin);
	sprd_dolphin_nand_wait_finish(dolphin);
	if(!raw) {
		for(i = 0; i < dolphin->sct_pg; i++) {
			err = sprd_dolphin_get_decode_sts(i);
			if(err == ERR_ERR_NUM0_MASK) {
				mtd->ecc_stats.failed++;
				dolphin_set_timing_config(&default_timing, SPRD_NAND_CLOCK);
				return err;
			}
			else {
				mtd->ecc_stats.corrected += err;
				return 0;
			}
		}
	}

	return 0;
}


STATIC_FUNC int sprd_dolphin_nand_write_lp(struct mtd_info *mtd,
					   const uint8_t *mbuf, uint8_t *sbuf,uint32_t raw)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	struct nand_chip *chip = dolphin->nand;
	uint32_t column;
	uint32_t page_addr;
	uint32_t nfc_start;
	uint32_t cfg0;
	uint32_t cfg1;
	uint32_t cfg2;
	page_addr = dolphin->page;
	if(mbuf) {
		column = 0;
	}
	else {
		column = mtd->writesize;
	}
	if(chip->options & NAND_BUSWIDTH_16)
	{
		column >>= 1;
	}

	sprd_dolphin_nand_ins_init(dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_SEQIN), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(column & 0xff), dolphin);
	column >>= 8;
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(column & 0xff), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);
	page_addr >>= 8;
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);

	if (5 == dolphin->a_cycles)// five address cycles
	{
		page_addr >>= 8;
		sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);
	}

	sprd_dolphin_nand_ins_add(NAND_MC_MWDT, dolphin);
	if(mbuf && sbuf)
	{
		sprd_dolphin_nand_ins_add(NAND_MC_SWDT, dolphin);
	}
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_PAGEPROG), dolphin);
	sprd_dolphin_nand_ins_add(NFC_MC_WRB0_ID, dolphin); //wait rb

	sprd_dolphin_nand_ins_add(NFC_MC_DONE_ID, dolphin);
	//config registers
	nfc_start = (dolphin->ecc_mode << 11);
	cfg0 = NFC_AUTO_MODE | NFC_RW |  NFC_WPN | MAIN_SPAR_APT | ((dolphin->sct_pg - 1)<< SECTOR_NUM_OFFSET);
	if((!raw) && mbuf && sbuf)
	{
		cfg0 |= ECC_EN;
	}
	if(chip->options & NAND_BUSWIDTH_16)
	{
		cfg0 |= BUS_WIDTH;
	}
	cfg1 = ((dolphin->info_size) << SPAR_INFO_SIZE_OFFSET);
	cfg2 = (dolphin->info_pos << SPAR_INFO_POS_OFFSET) | ((dolphin->sct_pg - 1) << SPAR_SECTOR_NUM_OFFSET) | dolphin->ecc_pos;

#ifndef CONFIG_NAND_SPL
	if (mbuf)
	{
		Dcache_CleanRegion((unsigned int)mbuf, dolphin->m_size*dolphin->sct_pg);
		Dcache_InvalRegion((unsigned int)mbuf, dolphin->m_size*dolphin->sct_pg);
	}

	if (sbuf)
	{
		Dcache_CleanRegion((unsigned int)sbuf, dolphin->s_size*dolphin->sct_pg);
		Dcache_InvalRegion((unsigned int)sbuf, dolphin->s_size*dolphin->sct_pg);
	}
#endif

	if(mbuf && sbuf)
	{
		cfg0 |= MAIN_USE | SPAR_USE;
		cfg1 |= (dolphin->m_size - 1) | ((dolphin->s_size - 1) << SPAR_SIZE_OFFSET);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)mbuf);
		sprd_dolphin_reg_write(NFC_SPAR_ADDRH_REG, 0x0);
		sprd_dolphin_reg_write(NFC_SPAR_ADDRL_REG, (uint32_t)sbuf);
	}
	else
	{
		cfg0 |= MAIN_USE;
		if(mbuf)
		{
			cfg1 |= dolphin->m_size - 1;
			sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
			sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)mbuf);
		}
		else
		{
			cfg1 |= dolphin->s_size - 1;
			sprd_dolphin_reg_write(NFC_MAIN_ADDRH_REG, 0x0);
			sprd_dolphin_reg_write(NFC_MAIN_ADDRL_REG, (uint32_t)sbuf);
		}
	}
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);
	sprd_dolphin_reg_write(NFC_CFG1_REG, cfg1);
	sprd_dolphin_reg_write(NFC_CFG2_REG, cfg2);
	sprd_dolphin_reg_write(NFC_START_REG, nfc_start);
	sprd_dolphin_nand_ins_exec(dolphin);
	sprd_dolphin_nand_wait_finish(dolphin);
	return 0;
}

STATIC_FUNC int sprd_dolphin_nand_read_sp(struct mtd_info *mtd,uint8_t *mbuf,
					  uint8_t *sbuf,uint32_t raw)
{
	return 0;
}
STATIC_FUNC int sprd_dolphin_nand_write_sp(struct mtd_info *mtd,
					   const uint8_t *mbuf, uint8_t *sbuf,uint32_t raw)
{
	return 0;
}
STATIC_FUNC void sprd_dolphin_erase(struct mtd_info *mtd, int page_addr)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	uint32_t cfg0 = 0;

	//DPRINT("%s, page addr is %x\r\n", __func__ , page_addr);

	sprd_dolphin_nand_ins_init(dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_ERASE1), dolphin);
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);
	page_addr >>= 8;
	sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);
	if((5 == dolphin->a_cycles) || ((4 == dolphin->a_cycles) && (512 == dolphin->write_size)))
	{
		page_addr >>= 8;
		sprd_dolphin_nand_ins_add(NAND_MC_ADDR(page_addr & 0xff), dolphin);
	}
	sprd_dolphin_nand_ins_add(NAND_MC_CMD(NAND_CMD_ERASE2), dolphin);
	sprd_dolphin_nand_ins_add(NFC_MC_WRB0_ID, dolphin); //wait rb

	sprd_dolphin_nand_ins_add(NFC_MC_DONE_ID, dolphin);
	cfg0 = NFC_WPN | NFC_ONLY_NAND_MODE;
	sprd_dolphin_reg_write(NFC_CFG0_REG, cfg0);


	#ifdef NAND_IRQ_EN
	sprd_dolphin_nand_ins_exec_irq(dolphin);
	sprd_dolphin_nand_wait_finish_irq(dolphin);
	#else
	sprd_dolphin_nand_ins_exec(dolphin);
	sprd_dolphin_nand_wait_finish(dolphin);
	#endif

    //DPRINT("%s leave\n", __func__);
}
STATIC_FUNC uint8_t sprd_dolphin_read_byte(struct mtd_info *mtd)
{
	uint8_t ch = 0xff;
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	if(dolphin->buf_head < dolphin->_buf_tail)
	{
		ch = s_oob_data[dolphin->buf_head ++];
	}
	return ch;
}
STATIC_FUNC uint16_t sprd_dolphin_read_word(struct mtd_info *mtd)
{
	uint16_t data = 0xffff;
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	if(dolphin->buf_head < (dolphin->_buf_tail - 1))
	{
		data = s_oob_data[dolphin->buf_head ++];
		data |= ((uint16_t)s_oob_data[dolphin->buf_head ++]) << 8;
	}
	return data;
}

STATIC_FUNC int sprd_dolphin_waitfunc(struct mtd_info *mtd, struct nand_chip *chip)
{
	return 0;
}

STATIC_FUNC int sprd_dolphin_ecc_calculate(struct mtd_info *mtd, const uint8_t *data,
				uint8_t *ecc_code)
{
	return 0;
}

STATIC_FUNC int sprd_dolphin_ecc_correct(struct mtd_info *mtd, uint8_t *data,
				uint8_t *read_ecc, uint8_t *calc_ecc)
{
	return 0;
}

static int sprd_dolphin_read_page(struct mtd_info *mtd, struct nand_chip *chip,
			uint8_t *buf, int page)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	dolphin->page = page;
	if(512 == mtd->writesize)
	{
		sprd_dolphin_nand_read_sp(mtd, buf, chip->oob_poi, 0);
	}
	else
	{
		sprd_dolphin_nand_read_lp(mtd, buf, chip->oob_poi, 0);
	}
	return 0;
}
static int sprd_dolphin_read_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
				uint8_t *buf, int page)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	dolphin->page = page;
	if(512 == mtd->writesize)
	{
		sprd_dolphin_nand_read_sp(mtd, buf, chip->oob_poi, 1);
	}
	else
	{
		sprd_dolphin_nand_read_lp(mtd, buf, chip->oob_poi, 1);
	}
	return 0;
}
STATIC_FUNC int sprd_dolphin_read_oob(struct mtd_info *mtd, struct nand_chip *chip,
			   int page, int sndcmd)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	dolphin->page = page;
	if(512 == mtd->writesize)
	{
		sprd_dolphin_nand_read_sp(mtd, 0, chip->oob_poi, 1);
	}
	else
	{
		sprd_dolphin_nand_read_lp(mtd, 0, chip->oob_poi, 1);
	}
	return 0;
}
STATIC_FUNC void sprd_dolphin_write_page(struct mtd_info *mtd, struct nand_chip *chip,
				const uint8_t *buf)
{
	if(512 == mtd->writesize)
	{
		sprd_dolphin_nand_write_sp(mtd, buf, chip->oob_poi, 0);
	}
	else
	{
		sprd_dolphin_nand_write_lp(mtd, buf, chip->oob_poi, 0);
	}

}
STATIC_FUNC void sprd_dolphin_write_page_raw(struct mtd_info *mtd, struct nand_chip *chip,
					const uint8_t *buf)
{
	if(512 == mtd->writesize)
	{
		sprd_dolphin_nand_write_sp(mtd, buf, chip->oob_poi, 1);
	}
	else
	{
		sprd_dolphin_nand_write_lp(mtd, buf, chip->oob_poi, 1);
	}
}
STATIC_FUNC int sprd_dolphin_write_oob(struct mtd_info *mtd, struct nand_chip *chip,
				int page)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	dolphin->page = page;
	if(512 == mtd->writesize)
	{
		sprd_dolphin_nand_write_sp(mtd, 0, chip->oob_poi, 1);
	}
	else
	{
		sprd_dolphin_nand_write_lp(mtd, 0, chip->oob_poi, 1);
	}
	return 0;
}


/**
 * nand_block_bad - [DEFAULT] Read bad block marker from the chip
 * @mtd:	MTD device structure
 * @ofs:	offset from device start
 * @getchip:	0, if the chip is already selected
 *
 * Check, if the block is bad.
 */
STATIC_FUNC int sprd_dolphin_block_bad(struct mtd_info *mtd, loff_t ofs, int getchip)
{
	int page, chipnr, res = 0;
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	struct nand_chip *chip = mtd->priv;
	uint16_t bad;
	uint16_t *buf;

	page = (int)((long)ofs >> chip->page_shift) & chip->pagemask;

	if (getchip) {
		chipnr = (int)((long)ofs >> chip->chip_shift);
		/* Select the NAND device */
		chip->select_chip(mtd, chipnr);
	}

	chip->cmdfunc(mtd, NAND_CMD_READOOB, 0, page);
	if(512 == dolphin->write_size) {
		sprd_dolphin_nand_read_sp(mtd, 0, s_oob_data, 1);
	}
	else  {
		sprd_dolphin_nand_read_lp(mtd, 0, s_oob_data, 1);
	}
	dolphin->buf_head = 0;
	dolphin->_buf_tail = mtd->oobsize;
	buf = (uint16_t *)(s_oob_data + chip->badblockpos);

	if (chip->options & NAND_BUSWIDTH_16) {
		bad = *(buf);
		if ((bad & 0xFF) != 0xff) {
			res = 1;
		}
	} else {
		bad = *(buf) & 0xff;
		if (bad != 0xff){
			res = 1;
		}
	}
	return res;
}

STATIC_FUNC void sprd_dolphin_nand_cmdfunc(struct mtd_info *mtd, unsigned int command,
			    int column, int page_addr)
{
	struct sprd_dolphin_nand_info *dolphin = mtd_to_dolphin(mtd);
	/* Emulate NAND_CMD_READOOB */
	if (command == NAND_CMD_READOOB) {
		column += mtd->writesize;
		command = NAND_CMD_READ0;
	}
	/*
	 * program and erase have their own busy handlers
	 * status, sequential in, and deplete1 need no delay
	 */
	switch (command) {
	case NAND_CMD_STATUS:
		sprd_dolphin_nand_read_status(dolphin);
		break;
	case NAND_CMD_READID:
		sprd_dolphin_nand_read_id(dolphin, (uint32_t *)s_oob_data);
		break;
	case NAND_CMD_RESET:
		sprd_dolphin_nand_reset(dolphin);
		break;
	case NAND_CMD_ERASE1:
		sprd_dolphin_erase(mtd, page_addr);
		break;
	case NAND_CMD_READ0:
	case NAND_CMD_SEQIN:
		dolphin->column = column;
		dolphin->page = page_addr;
	default:
		break;
	}
}
STATIC_FUNC void sprd_dolphin_nand_hwecc_ctl(struct mtd_info *mtd, int mode)
{
	return; //do nothing
}

STATIC_FUNC void sprd_dolphin_nand_hw_init(struct sprd_dolphin_nand_info *dolphin)
{
	uint32_t val;

	sprd_dolphin_reg_or(REG_AP_AHB_AHB_EB, BIT_NAND_ENABLE);
	sprd_dolphin_reg_or(REG_AP_AHB_AHB_EB, BIT_AP_AHB_NANDC_ECC_EB);
	sprd_dolphin_reg_or(REG_AP_AHB_AHB_EB, BIT_AP_AHB_NANDC_26M_EB);

	sprd_dolphin_reg_or(REG_AON_APB_CGM_CLK_TOP_REG1,
			    BIT_AON_APB_CGM_NANDC_2X_EN | BIT_AON_APB_CGM_NANDC_1X_EN);

	sprd_dolphin_reg_write(REG_AON_CLK_CORE_CGM_NANDC_2X_CFG,0x3);

	sprd_dolphin_reg_write(REG_AP_CLK_CORE_CGM_NANDC_ECC_CFG ,0x1);
	sprd_dolphin_reg_or(REG_AP_AHB_AHB_RST,BIT_AP_AHB_NANDC_SOFT_RST );
	mdelay(1);
	sprd_dolphin_reg_and(REG_AP_AHB_AHB_RST, ~(BIT_AP_AHB_NANDC_SOFT_RST ));

	sprd_dolphin_reg_write(NFC_CFG4_REG, 0x1017e);
	//close write protect
	sprd_dolphin_nand_wp_en(dolphin, 0);
}


int board_nand_init(struct nand_chip *chip)
{
	DPRINT("board_nand_init\r\n");

	sprd_dolphin_nand_hw_init(&g_dolphin);

	chip->select_chip = sprd_dolphin_select_chip;
	chip->cmdfunc = sprd_dolphin_nand_cmdfunc;
	chip->read_byte = sprd_dolphin_read_byte;
	chip->read_word	= sprd_dolphin_read_word;
	chip->waitfunc = sprd_dolphin_waitfunc;
	chip->ecc.mode = NAND_ECC_HW;
	chip->ecc.calculate = sprd_dolphin_ecc_calculate;
	chip->ecc.hwctl = sprd_dolphin_nand_hwecc_ctl;
	chip->ecc.correct = sprd_dolphin_ecc_correct;
	chip->ecc.read_page = sprd_dolphin_read_page;
	chip->ecc.read_page_raw = sprd_dolphin_read_page_raw;
	chip->ecc.write_page = sprd_dolphin_write_page;
	chip->ecc.write_page_raw = sprd_dolphin_write_page_raw;
	chip->ecc.read_oob = sprd_dolphin_read_oob;
	chip->ecc.write_oob = sprd_dolphin_write_oob;
	chip->erase_cmd = sprd_dolphin_erase;

	chip->ecc.bytes = CONFIG_SYS_NAND_ECCBYTES;
	g_dolphin.ecc_mode = ecc_mode_convert(CONFIG_SYS_NAND_ECC_MODE);
	g_dolphin.nand = chip;

	chip->eccbitmode = CONFIG_SYS_NAND_ECC_MODE;

	//dolphin_set_timing_config(&g_dolphin, SPRD_NAND_CLOCK);	/* 153 is current clock 153MHz */

	chip->ecc.size = CONFIG_SYS_NAND_ECCSIZE;

	chip->chip_delay = 20;
	chip->priv = &g_dolphin;

	chip->options = NAND_BUSWIDTH_16;

	return 0;
}

static unsigned long nfc_read_status(void)
{
	unsigned long status = 0;

	sprd_dolphin_nand_read_status(&g_dolphin);
	status = s_oob_data[0];

	return status;
}
