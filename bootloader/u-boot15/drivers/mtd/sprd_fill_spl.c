
#include <linux/mtd/mtd.h>
#include <nand.h>
#include <linux/mtd/nand.h>
#include <common.h>

#define BOOTLOADER_HEADER_OFFSET    32
#define CONFIG_SYS_SPL_ECC_POS    8
#define MAX_SPL_SIZE    0x20000
#if 0
struct bootloader_header
{
	uint32_t version; //version
	uint32_t magic_num; //0xaa55a5a5
	uint32_t check_sum;
	uint32_t hash_len; //word length, only used when secure boot enable
	uint32_t sct_size; //
	uint32_t acycle; // 3, 4, 5
	uint32_t bus_width; //0 ,1
	uint32_t spare_size; //spare part sise for one sector
	uint32_t ecc_mode; //0--1bit, 1--2bit,2--4bit,3--8bit,4--12bit, 5--16bit, 6--24bit
	uint32_t ecc_pos; // ecc postion at spare part
	uint32_t sct_per_page; //sector per page
	uint32_t info_pos;
	uint32_t info_size;
	uint32_t ecc_value[27];
	uint32_t page_per_blk;
	uint32_t img_page[5];
};

/*
 * spare info data is don't used at the romcode, so the fdl only set the s_info size to 1, and the data value 0xff
 */
static void set_header_info(u8 *bl_data, struct mtd_info *nand, int ecc_pos)
{
	struct bootloader_header *header;
	struct nand_chip *chip = nand->priv;
	struct sprd_ecc_param param;
	uint32_t hash_len;
	u8 *ecc;
	ecc = memalign(ARCH_DMA_MINALIGN, 108);
	header = (struct bootloader_header *)(bl_data + BOOTLOADER_HEADER_OFFSET);
	hash_len = header->hash_len;
	memset(header, 0, sizeof(struct bootloader_header));
	memset(ecc, 0xff, 108);
	header->version = 1;
	header->sct_size = chip->ecc.size;
	header->hash_len = hash_len;
	if (chip->options & NAND_BUSWIDTH_16)	{
		header->bus_width = 1;
	}
	if(nand->writesize > 512) {
		if (chip->chipsize > (128 << 20))		{
			header->acycle = 5;
		}
		else	 {
			header->acycle = 4;
		}
	}
	else{
		/* One more address cycle for devices > 32MiB */

		if (chip->chipsize > (32 << 20)) {
			header->acycle = 4;
		}
		else	{
			header->acycle = 3;
		}
	}

	header->magic_num = 0xaa55a5a5;
	header->spare_size = (nand->oobsize/chip->ecc.steps);
	header->ecc_mode = ecc_mode_convert(chip->eccbitmode);
	/*ecc is at the last postion at spare part*/
	header->ecc_pos = header->spare_size - (chip->ecc.bytes);
	header->sct_per_page = chip->ecc.steps;

	header->info_pos = header->ecc_pos;
	header->info_size = 0;
	header->page_per_blk = nand->erasesize / nand->writesize;
	param.mode = 60;
	param.ecc_pos = 0;
	param.sinfo_size = 1;
	param.ecc_num = 1;
	param.sp_size = 108;
	param.m_size = chip->ecc.size;
	param.p_mbuf = (u8 *)bl_data;
	param.p_sbuf = ecc;
	param.sinfo_pos = 0;
	sprd_ecc_encode(&param);
	memcpy(header->ecc_value, ecc, 108);
}

static int nand_write_spl_page(u8 *buf, struct mtd_info *mtd, u32 pg, u32 ecc_pos)
{
	struct nand_chip *chip = mtd->priv;

	chip->cmdfunc(mtd, NAND_CMD_SEQIN, 0x00, pg);
	chip->ecc.write_page(mtd, chip, buf, 0);
	chip->ecc.write_page(mtd, chip, buf, 0);
	chip->cmdfunc(mtd, NAND_CMD_PAGEPROG, -1, -1);
	chip->waitfunc(mtd, chip);

	return 0;
}
#endif

#define MAX_SPL_OFFSET    0x20000

int sprd_nand_write_spl(u8 *buf, struct mtd_info *mtd)
{
	u32 i = 0;
	u32 pg_start;
	u32 pg_end;
	u32 pg;
	u8 * data;
	int ret = 0;
	printf("sprd_nand_write_spl\n");

	set_header_info(buf, mtd, CONFIG_SYS_SPL_ECC_POS);

	/* write spl to flash*/
	for (i = 0; i < 2; i++)
	{
		pg_start = i * MAX_SPL_OFFSET / mtd->writesize;
		pg_end = (i * MAX_SPL_OFFSET + MAX_SPL_SIZE) / mtd->writesize;
		data = buf + mtd->writesize;
		for(pg  = pg_start + 1; pg < pg_end; pg += 1) {
			ret = nand_write_spl_page(data, mtd, pg, CONFIG_SYS_SPL_ECC_POS);
			data += mtd->writesize;
			//mdelay(1000);
		}
	}

	data = buf;
	pg = 0;
	ret = nand_write_spl_page(data, mtd, pg, CONFIG_SYS_SPL_ECC_POS);
	pg = MAX_SPL_OFFSET / mtd->writesize;
	ret = nand_write_spl_page(data, mtd, pg, CONFIG_SYS_SPL_ECC_POS);
	return ret;
}

int sprd_nand_read_spl(u8 *buf, struct mtd_info *mtd, uint32_t size)
{
	u32 pg_start=0;
	u32 pg_end;
	u32 pg;
	u8 * data;
	int ret = 0;

	pg_end = size / mtd->writesize;
	if((size % mtd->writesize) != 0)
		pg_end++;
	data = buf;
	for(pg  = pg_start; pg < pg_end; pg += 1) {
		ret = nand_read_spl_page(data, mtd, pg, CONFIG_SYS_SPL_ECC_POS);
		data += mtd->writesize;
	}
	return ret;
}
