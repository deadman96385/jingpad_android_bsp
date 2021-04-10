#include <common.h>
#include <command.h>
#include <config.h>
#include <fat.h>
#include <exfat.h>
#include <asm/byteorder.h>
#include <part.h>
#include <malloc.h>
#include <linux/ctype.h>

#define RD_BLOCK_SIZE  512

__u8  dir_block[RD_BLOCK_SIZE]
	__aligned(ARCH_DMA_MINALIGN);
__u8  dir_block1[RD_BLOCK_SIZE]
	__aligned(ARCH_DMA_MINALIGN);


static  int  find_bitmap_entry(exfsdata *mydata,  exfat_buf_array *bfs , __u32 startsect)
{
	__u32 curclust = (startsect - mydata->data_begin) / mydata->clust_size;
	__u32 rd_sec,  rd_sec_total = 0;
	int i;

	while (1) {
		exfat_dentry *dentptr;

		if (bfs->bf1.sectors > 0)
			bfs->bf0 = bfs->bf1;

		if (bfs->bf1.pbuf==dir_block)
			bfs->bf1.pbuf = dir_block1;
		else
			bfs->bf1.pbuf = dir_block;

		rd_sec = (mydata->clust_size - rd_sec_total) > mydata->rd_sectors ?
					mydata->rd_sectors : (mydata->clust_size - rd_sec_total);
		if (get_exfat_blocks(mydata, startsect, bfs->bf1.pbuf, rd_sec) != 0) {
			debugf("Error: reading root directory block......Return -1\n");
			return  -1;
		}
		bfs->bf1.sectors = rd_sec;
		bfs->bf1.cluster = curclust;
		bfs->bf1.start_sec = startsect;
		startsect += rd_sec;
		rd_sec_total += rd_sec;

		dentptr = (exfat_dentry *)bfs->bf1.pbuf;
		for (i = 0; i < (bfs->bf1.sectors * mydata->sect_size /sizeof(exfat_dentry));  i++, dentptr++) {

			if ((dentptr->entry_type&EXFAT_DTYPE_USED) &&
				((dentptr->entry_type & EXFAT_DTYPE_MASK)== EXFAT_DTYPE_BM) ) {
				exfat_bitmap_entry *bm_dentptr = (exfat_bitmap_entry *)dentptr;
				mydata->cur_bitmap_cluster = EXFAT2CPU32(bm_dentptr->start_clu);
				mydata->bitmap_sect = mydata->cur_bitmap_cluster * mydata->clust_size + mydata->data_begin;
				mydata->bitmaplen = (__u32) EXFAT2CPU64(bm_dentptr->data_len);
				return 0;
			}
			else if (dentptr->entry_type==0)  {
				debugf("Error: bitmap entry is not found till null dentry is found - index %d\n", i);
				return -1;
			}
			else {
				continue;
			}
		}

		if (rd_sec_total >= mydata->clust_size) {
			debugf("Error: bitmap entry is not found till first cluster of root dirctory.\n");
			return -1;
		}
	}

	return -1;
}


int exfat_checksys(size_t ram_size)
{
	exfat_boot_sector bs;
	exfsdata datablock;
	exfsdata *mydata = &datablock;
	exfat_buf_array  buf_array;
	__u32 startsect;
	__u32 cl_size;
	__u64  vol_size;
	int mod = 0;
	int ret;

	if (read_exfat_bootsec(&bs)) {
		debugf("Error: reading boot sector\n");
		return FSFATAL;
	}

	memset(mydata, 0, sizeof(exfsdata));
	mydata->sect_size = 1<<bs.sector_size_bits;
	mydata->clust_size= 1<< bs.sectors_per_clu_bits;
	cl_size  = mydata->sect_size * mydata->clust_size;

	mydata->fat_num  = bs.num_fats;
	mydata->fatlength = bs.fat_len;
	mydata->bitmaplen= (bs.cluster_cnt +7)/8;
	mydata->cluster_cnt = bs.cluster_cnt;
	mydata->fat_sect = bs.fat_off;
	mydata->rootdir_sect = bs.cluster_heap_off + (bs.root_cluster-2)*mydata->clust_size;
	mydata->data_begin = bs.cluster_heap_off - (mydata->clust_size * 2);
	mydata->rd_sectors = (cl_size > RD_BLOCK_SIZE) ? (RD_BLOCK_SIZE /mydata->sect_size) : mydata->clust_size;

	vol_size = (__u64)mydata->cluster_cnt * cl_size;
	if (vol_size < (__u64)ram_size) {
		debugf("Volume has no enough space for sysdump. Total size: %llu bytes. Ram size: %llu bytes\n", vol_size, ram_size);
		mod = FSSMSIZE;
		goto exit;
	}

	mydata->fatbuf_idx = 0;
	mydata->fatbuf = (__u8 *)exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
	if (mydata->fatbuf == NULL) {
		debugf("Error: allocating memory\n");
		mod = FSFATAL;
		goto exit;
	}

	mydata->bitmap_idx = 0;
	mydata->bitmap = (__u8 *)exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
	if (mydata->bitmap == NULL) {
		debugf("Error: allocating memory\n");
		mod = FSFATAL;
		goto exit;
	}

	memset(&buf_array, 0, sizeof(buf_array));
	startsect = mydata->rootdir_sect;
	ret = find_bitmap_entry(mydata, &buf_array,  startsect);
	if (ret < 0) {
		debugf("Error: exfat bitmap is not found\n");
		mod = FSFATAL;
		goto exit;
	}

	mydata->bitmap_fatbuf_size = EXFAT_FAT_ENTRY_SIZE * (mydata->bitmaplen + cl_size - 1)/cl_size;
	mydata->bitmap_fatbuf_size = (mydata->bitmap_fatbuf_size + mydata->sect_size -1) / mydata->sect_size;
	mydata->bitmap_fatbuf = (__u8 *)exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->bitmap_fatbuf_size * mydata->sect_size);
	if (mydata->bitmap_fatbuf == NULL) {
		debugf("Error: allocating memory\n");
		mod = FSFATAL;
		goto exit;
	}

	ret = check_bitmap_fatbuf(mydata);
	if (ret < 0) {
		debugf("Error: read and check fatbuf for bitmap failed.\n");
		mod = FSFATAL;
		goto exit;
	}

	/* Reserve 1MB for possible directory clusters allocation. */
	ret = check_available_size(mydata, (__u64)(ram_size+1024*1024));
	if (ret < 0) {
		mod = FSFATAL;
		debugf("FSFATAL and exit.\n");
		goto exit;
	}
	else if (ret > 0) {
		mod = FSNOSPACE;
		debugf("There is no enough space in SD card to dump %lld bytes.\n",ram_size+1024*1024);
		goto exit;
	}

	debugf("FSOK and return.\n");
	mod = FSOK;

exit:
	if (mydata->fatbuf)
		exfat_mfree(mydata->fatbuf);
	if (mydata->bitmap)
		exfat_mfree(mydata->bitmap);
	if(mydata->bitmap_fatbuf)
		exfat_mfree(mydata->bitmap_fatbuf);

	return mod;
}

