#include <part.h>
#include <part_efi.h>
#include <common.h>
#include <malloc.h>
#include <common.h>
#include <linux/types.h>
#include <sci_types.h>

gpt_entry *alloc_read_gpt_entries(block_dev_desc_t * dev_desc,
					 gpt_header * pgpt_head,int count, gpt_entry *pte)
{
	int i;

	if (!dev_desc || !pgpt_head) {
		return NULL;
	}
	if (dev_desc->block_read(dev_desc->dev,
		(lbaint_t)(pgpt_head->partition_entry_lba+count),
		1, pte)!= TRUE) {
		return NULL;
	}
	return pte;
}
 int is_gpt_valid(block_dev_desc_t * dev_desc, unsigned long long lba,
			gpt_header * pgpt_head, gpt_entry ** pgpt_pte)
{
	if (!dev_desc || !pgpt_head) {
		return 0;
	}
	/* Read GPT Header from device */
	if (dev_desc->block_read(dev_desc->dev,(lbaint_t)lba, 1, pgpt_head) != TRUE) {
		return 0;
	}
	/* Check the GPT header signature */
	if ((pgpt_head->signature) != GPT_HEADER_SIGNATURE) {
		return 0;
	}
	/* Check that the my_lba entry points to the LBA that contains the GPT */
	if ((pgpt_head->my_lba) != lba) {
		return 0;
	}

	/* Read and allocate Partition Table Entries */
	return 1;
}


int get_partition_info_by_name_efi(block_dev_desc_t * dev_desc, uchar * partition_name,
				disk_partition_t * info)
{
	gpt_entry *pgpt_pte = NULL;
	int ret = -1;
	unsigned int i,j,z;
	uchar disk_parition[PARTNAME_SZ];
	unsigned char gpt_h[dev_desc->blksz];
	unsigned char gpt_entry_data[dev_desc->blksz];
	gpt_header *gpt_head =gpt_h;

	if (!dev_desc || !info || !partition_name) {
		return -1;
	}

	/* This function validates AND fills in the GPT header and PTE */
	if (is_gpt_valid(dev_desc, GPT_PRIMARY_PARTITION_TABLE_LBA,
			gpt_head, &pgpt_pte) != 1) {
		if (is_gpt_valid(dev_desc, (dev_desc->lba - 1),
				gpt_head, &pgpt_pte) != 1) {
			return -1;
		}
	}

	for(i = 0; i<GPT_BLKSIZE; i++) {
		if(NULL == alloc_read_gpt_entries(dev_desc, gpt_head,i, gpt_entry_data))
			return -1;
		for(z = 0; z<(dev_desc->blksz/128); z++) {
			pgpt_pte=&gpt_entry_data[128*z];
			for(j = 0; j<PARTNAME_SZ; j++) {
				disk_parition[j] =(* pgpt_pte).partition_name[j] & 0xFF;
			}
			if(0 == sprd_strcmp(disk_parition, partition_name)) {
				/* The ulong casting limits the maximum disk size to 2 TB */
				info->start = (ulong) ((*pgpt_pte).starting_lba);
				/* The ending LBA is inclusive, to calculate size, add 1 to it */
				info->size = ((ulong)((*pgpt_pte).ending_lba) + 1) - info->start;
				info->blksz = dev_desc->blksz;
				ret = 0;
				break;
			}
		}
		if(ret==0)
			break;
	}

	return ret;
}

