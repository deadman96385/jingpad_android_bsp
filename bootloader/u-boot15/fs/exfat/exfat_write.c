/*
 * exfat_write.c
 *
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <rtc.h>
#include <common.h>
#include <command.h>
#include <config.h>
#include <fat.h>
#include <exfat.h>
#include <asm/byteorder.h>
#include <part.h>
#include <malloc.h>
#include <linux/ctype.h>
#include "exfat.c"

extern struct rtc_time get_time_by_sec(void);

__u8  dir_content_block[MAX_RD_BLK_SIZE]
	__aligned(ARCH_DMA_MINALIGN);
__u8  dir_content_block1[MAX_RD_BLK_SIZE]
	__aligned(ARCH_DMA_MINALIGN);


/*
 * Write bitmap buffer into block device
 */
int  flush_bitmap(exfsdata *mydata)
{
	if(mydata->bitmap_idx < mydata->bitmap_sect)
		return 0;

	if(exfat_disk_write(mydata->bitmap_idx, 1, mydata->bitmap) < 0) {
		debugf("Error: writting bitmap file\n");
		return -1;
	}
	return 0;
}


/*
 * Write fat buffer into block device
 */
int  flush_exfatent(exfsdata *mydata)
{
	if (mydata->fatbuf_idx < mydata->fat_sect)
		return 0;

	if(exfat_disk_write(mydata->fatbuf_idx, 1, mydata->fatbuf) < 0) {
		debugf("Error: writting fat table\n");
		return -1;
	}
	if (mydata->fat_num >1) {
		if(exfat_disk_write(mydata->fatbuf_idx + mydata->fatlength, 1, mydata->fatbuf) < 0) {
		 	debugf("Error: writting backup fat table\n");
			return -1;
		}
	}
	return 0;
}

int  check_available_size(exfsdata *mydata,  __u64  size)
{
	__u32  cl_size  = mydata->sect_size * mydata->clust_size;
	__u32  cl_needed = (__u32)((size + cl_size -1 )/cl_size);
	__u32  cl_avail = 0;
	__u32  checked = 0;
	__u32  idx, ival, start_sec;
	int ret;

	if (flush_bitmap(mydata) < 0) {
		debugf("Error: flush bitmap buffer\n");
		return  -1;
	}

	start_sec = mydata->bitmap_sect;
	while (checked < mydata->bitmaplen) {
		if (get_exfat_blocks(mydata, start_sec, mydata->bitmap, 1) != 0) {
			debugf("Error: reading bitmap\n");
			return  -1;
		}
		mydata->bitmap_idx = start_sec++;
		for (idx=0; idx<mydata->sect_size; idx++) {
			ival = mydata->bitmap[idx];
			cl_avail += 8 - (__u32)bits_num_table[ival];
			checked++;
			if(cl_avail > cl_needed || checked >= mydata->bitmaplen)
				goto exit0;
		}
	}
exit0:
	ret = (cl_avail > cl_needed) ? 0 : 1;
	return ret;
}


__u32 clear_bitmap(exfsdata *mydata, __u32  curclust)
{
	__u32  start_sec, bits_off, bytes_off, sec_off;

	curclust -= 2;	// bitmap starts from cluster 2
	sec_off    = (curclust /8) / mydata->sect_size;
	bits_off    = curclust & 0x7;
	bytes_off = curclust /8 - sec_off * mydata->sect_size;
	start_sec = mydata->bitmap_sect+ sec_off;

	if (mydata->bitmap_idx != start_sec) {
		if (mydata->bitmap_idx >= mydata->bitmap_sect) {
			if (flush_bitmap(mydata) < 0) {
				return 0;
			}
		}
		if (get_exfat_blocks(mydata, start_sec, mydata->bitmap, 1) != 0) {
			debugf("Error: reading bitmap\n");
			return  0;
		}
		mydata->bitmap_idx = start_sec;
	}
	mydata->bitmap[bytes_off] &= bitmap_clr_mask[bits_off];

	return curclust+2;
}


static __u32 clear_exfatent_value(exfsdata *mydata, __u32  curclust)
{
	__u32  nextclust, start_sec, bytes_off, sec_off;

	nextclust = 0;
	sec_off    = (curclust *EXFAT_FAT_ENTRY_SIZE) / mydata->sect_size;
	bytes_off = curclust * EXFAT_FAT_ENTRY_SIZE - sec_off * mydata->sect_size;
	start_sec = mydata->fat_sect + sec_off;

	if (mydata->fatbuf_idx != start_sec) {
		if (mydata->fatbuf_idx >= mydata->fat_sect) {
			if (flush_exfatent(mydata) < 0) {
				return 0;
			}
		}

		if (get_exfat_blocks(mydata, start_sec, mydata->fatbuf, 1) != 0) {
			debugf("Error: reading fat table\n");
			return  0;
		}
		mydata->fatbuf_idx = start_sec;
	}

	nextclust = *(__u32 *)(mydata->fatbuf+bytes_off);
	nextclust = EXFAT2CPU32(nextclust);
	if (nextclust==0) {
		debugf("Error: next_cl shoud not be all 00\n");
		nextclust = curclust + 1;
	}

	*(__u32 *)(mydata->fatbuf + bytes_off) = 0;
	return nextclust;
}

/*
 * Clear original file's bitmap & fat table entry
 */
static int clear_exfatent_bitmap(exfsdata *mydata, __u32 start_clust, __u32 cl_num, int clr_fatent)
{

	__u32 next_cluster, cur_cluster, i=0;
	cur_cluster = start_clust;

	while (i++ < cl_num) {
		if (clr_fatent)
			next_cluster = clear_exfatent_value(mydata, cur_cluster);
		else
			next_cluster = cur_cluster+1;
		cur_cluster  = clear_bitmap(mydata, cur_cluster);
		if (next_cluster < 2 || next_cluster > mydata->cluster_cnt ||
			cur_cluster < 2 || cur_cluster > mydata->cluster_cnt ) {
			debugf("exFAT broken next cluster or file end: %08x or clear bitmap %08x\n", next_cluster,cur_cluster);
			break;
		}
		cur_cluster = next_cluster;
	}

	if (flush_exfatent(mydata) < 0) {
		return -1;
	}
	if (flush_bitmap(mydata) < 0) {
		return -1;
	}

	return 0;
}


static __u32 set_exfatent_value(exfsdata *mydata, __u32  curclust,  __u32 val)
{
	__u32   start_sec, bytes_off, sec_off;

	sec_off    = (curclust *EXFAT_FAT_ENTRY_SIZE) / mydata->sect_size;
	bytes_off = curclust * EXFAT_FAT_ENTRY_SIZE - sec_off * mydata->sect_size;
	start_sec = mydata->fat_sect + sec_off;

	if (mydata->fatbuf_idx != start_sec) {
		if (mydata->fatbuf_idx >= mydata->fat_sect) {
			if (flush_exfatent(mydata) < 0) {
				return 0;
			}
		}
		if (get_exfat_blocks(mydata, start_sec, mydata->fatbuf, 1) != 0) {
			debugf("Error: reading fat table\n");
			return  0;
		}
		mydata->fatbuf_idx = start_sec;
	}

	*(__u32 *)(mydata->fatbuf + bytes_off) = cpu_to_le32(val);
	return 0;
}


/* Find first available cluster from *start, return consecutive number, and set bitmap*/
static __u32  get_available_clusters(exfsdata *mydata, __u32  *start, __u32 max_cl, int search_first)
{
	__u32  start_sec, bits_off, rem_bits, bytes_off, sec_off, avail, ret, curclust, i;
	__u8  value;

	if (*start < 2)
		curclust = 0;
	else
		curclust = *start - 2;

	/* find first bit-0 from current cluster  */
	while (search_first) {
		sec_off    = (curclust /8) / mydata->sect_size;
		bits_off    = curclust & 0x7;
		bytes_off = curclust /8 - sec_off * mydata->sect_size;
		start_sec = mydata->bitmap_sect+ sec_off;

		if (mydata->bitmap_idx != start_sec) {
			if (mydata->bitmap_idx >= mydata->bitmap_sect) {
				if (flush_bitmap(mydata) < 0) {
					return 0;
				}
			}
			if (get_exfat_blocks(mydata, start_sec, mydata->bitmap, 1) != 0) {
				debugf("Error: reading bitmap\n");
				return  0;
			}
			mydata->bitmap_idx = start_sec;
		}
		value = mydata->bitmap[bytes_off] >> bits_off;
		if (max_cl > 1) {
			if (value==0) {
				*start = (curclust+2);
				break;
			}
			curclust += 8 -  bits_off;
		} else {
			for (i = bits_off; i < 8; i++) {
				if ((value&1)==0) {
					break;
				}
				value >>= 1;
			}
			if (i<8) {
				curclust += i - bits_off;
				*start = (curclust+2);
				break;
			}
			curclust += 8 -  bits_off;
		}
	}

	/* Find consecutive number of bits 0 */
	ret = 0;
	while (curclust < mydata->cluster_cnt) {
		sec_off    = (curclust /8) / mydata->sect_size;
		bits_off    = curclust & 0x7;
		rem_bits  = 8 - bits_off;
		bytes_off = curclust /8 - sec_off * mydata->sect_size;
		start_sec = mydata->bitmap_sect+ sec_off;

		if (mydata->bitmap_idx != start_sec) {
			if (mydata->bitmap_idx >= mydata->bitmap_sect) {
				if (flush_bitmap(mydata) < 0) {
					return 0;
				}
			}
			if (get_exfat_blocks(mydata, start_sec, mydata->bitmap, 1) != 0) {
				debugf("Error: reading bitmap\n");
				return  0;
			}
			mydata->bitmap_idx = start_sec;
		}
		value = mydata->bitmap[bytes_off] >> bits_off;
		avail  = (__u32)bitmap_avail[value];
		ret += avail;

		if (avail > rem_bits) {
			avail = rem_bits;
			ret -= bits_off;
		}
		if (ret > max_cl) {
			avail -= (ret - max_cl);
			ret = max_cl;
		}
		value = bitmap_mask[avail] << bits_off;
		mydata->bitmap[bytes_off] |= value;
		if (avail < rem_bits || ret >= max_cl) {
			break;
		}
		curclust += rem_bits;
	}

	return  ret;
}


int  check_bitmap_fatbuf(exfsdata *mydata)
{
	__u32 curclust, nextclust, start_sec, bytes_off, sec_off;
	__u32 idx, cl_num, cl_size, *pentry;

	curclust = mydata->cur_bitmap_cluster;

	sec_off    = (curclust *EXFAT_FAT_ENTRY_SIZE) / mydata->sect_size;
	bytes_off = curclust * EXFAT_FAT_ENTRY_SIZE - sec_off * mydata->sect_size;
	start_sec = mydata->fat_sect + sec_off;

	if (get_exfat_blocks(mydata, start_sec, mydata->bitmap_fatbuf, mydata->bitmap_fatbuf_size) != 0) {
		debugf("Error: reading bitmap fat entries\n");
		return  -1;
	}

	cl_size    = mydata->sect_size*mydata->clust_size;
	cl_num = (mydata->bitmaplen + cl_size - 1)/cl_size;
	pentry = (__u32 *)(mydata->bitmap_fatbuf + bytes_off);
	for (idx=0; idx < cl_num; idx++) {
		nextclust = EXFAT2CPU32(*pentry);
		if (nextclust < mydata->cluster_cnt && (nextclust != (curclust+1))) {
			debugf("Error: non-continuously bitmap, cluster %d to %d.\n", curclust, nextclust);
			return -1;
		}
		curclust = nextclust;
		pentry++;
	}

	return 0;
}

static int get_upcase_table(exfsdata *mydata, __u32 start_cl, __u32 length)
{
	__u32  start_sec, rd_sec;
	start_sec = mydata->data_begin +  start_cl * mydata->clust_size;
	rd_sec  = (length + mydata->sect_size - 1) / mydata->sect_size;
	mydata->uptab_buf = (__u16 *)exfat_malloc_aligned(ARCH_DMA_MINALIGN,   rd_sec*mydata->sect_size);

	if (get_exfat_blocks(mydata, start_sec, mydata->uptab_buf, rd_sec) != 0) {
		debugf("Error: reading upcase table\n");
		return  -1;
	}
	return 0;
}

static  __u32  get_next_cluster(exfsdata *mydata, __u32 curclust)
{
	__u32  nextclust, start_sec, bytes_off, sec_off;

	nextclust = 0;

	sec_off    = (curclust *EXFAT_FAT_ENTRY_SIZE) / mydata->sect_size;
	bytes_off = curclust * EXFAT_FAT_ENTRY_SIZE - sec_off * mydata->sect_size;
	start_sec = mydata->fat_sect + sec_off;

	if (mydata->fatbuf_idx != start_sec) {
		if (get_exfat_blocks(mydata, start_sec, mydata->fatbuf, 1) != 0) {
			debugf("Error: reading fat table\n");
			return  0;
		}
		mydata->fatbuf_idx = start_sec;
	}
	nextclust = *(__u32 *)(mydata->fatbuf+bytes_off);
	nextclust = EXFAT2CPU32(nextclust);
	if (nextclust==0) {
		debugf("Error nextclust %d \n", nextclust);
		nextclust = curclust + 1;
	}

	return nextclust;
}

static int write_back_entry(exfat_whole_dentry *p_ent)
{
	/* Write directory table to device */
	if (p_ent->bf0.sectors > 0) {
		if (exfat_disk_write(p_ent->bf0.start_sec,  p_ent->bf0.sectors, p_ent->bf0.pbuf) < 0) {
			debugf("Error writing data sector: %u, cnt: %u\n", p_ent->bf0.start_sec, p_ent->bf0.sectors);
			return -1;
		}
	}
	if (p_ent->bf1.sectors > 0) {
		if (exfat_disk_write(p_ent->bf1.start_sec,  p_ent->bf1.sectors, p_ent->bf1.pbuf) < 0) {
			debugf("Error writing data sector: %u, cnt: %u\n", p_ent->bf1.start_sec, p_ent->bf1.sectors);
			return -1;
		}
	}
	return 0;
}


/*
 * Write at most 'size' bytes from 'buffer' into the specified cluster.
 * Return 0 if success, -1 otherwise.
 */
static int
 write_clusters(exfsdata *mydata, __u32 start_clust, __u8 *buffer, unsigned long size)
{
	int idx = 0;
	__u32 startsect,  sect_n;

	startsect  = mydata->data_begin + start_clust * mydata->clust_size;
	sect_n = size / mydata->sect_size;

	if ( sect_n > 0) {
		if (exfat_disk_write(startsect, sect_n, buffer) < 0) {
			debugf("Error writing data\n");
			return -1;
		}
	}

	if (size % mydata->sect_size) {
		__u8 tmpbuf[mydata->sect_size];

		idx = size / mydata->sect_size;
		buffer += idx * mydata->sect_size;
		memcpy(tmpbuf, buffer, size % mydata->sect_size);

		if (exfat_disk_write(startsect + idx, 1, tmpbuf) < 0) {
			debugf("Error writing data\n");
			return -1;
		}
	}

	return 0;
}


/*
 * Clear cluster to all zero. Size should be multiplier of cluster size
 * Return 0 if success, -1 otherwise.
 */
static int
clear_clusters(exfsdata *mydata, __u32 start_clust, __u8 *buffer, unsigned long size)
{
	__u32 startsect,  sect_n;
	__u8 *tmp_buf = NULL;

	tmp_buf = exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
	if (tmp_buf == NULL) {
		debugf("Error: allocate memory failed.\n");
		return -1;
	}
	memset(tmp_buf, 0, mydata->sect_size);

	startsect  = mydata->data_begin + start_clust * mydata->clust_size;
	sect_n = size / mydata->sect_size;

	while (sect_n-- > 0) {
		if (exfat_disk_write(startsect, 1, tmp_buf) < 0) {
			exfat_mfree(tmp_buf);
			debugf("Error writing data\n");
			return -1;
		}
		startsect++;
	}

	return 0;
}

unsigned long  write_file_contents(exfsdata *mydata, __u32 *start_cluster,  __u8 *buffer, unsigned long filesize, int *cont, int clear)
{
	unsigned long  gotsize = 0;
	unsigned long  actsize;
	unsigned long  bytesperclust = mydata->clust_size * mydata->sect_size;
	__u32 curclust  = *start_cluster;
	__u32 last_startclust = 0, last_endclust = 0, gotclust = 0, needed_cluster = 0;
	int search_first = 0;
	*cont=0;

	while (filesize > 0) {
		gotclust = 0;
		actsize = 0;
		needed_cluster = (filesize + bytesperclust-1) / bytesperclust;
		/* search for consecutive clusters */
		if (needed_cluster > 0)	{
			/* For existing file over-writting, *start_cluster is always available. */
			search_first = ((*start_cluster==0) ||(curclust != *start_cluster)) ? 1 : 0;
			gotclust = get_available_clusters(mydata, &curclust, needed_cluster, search_first);
			if (gotclust == 0) {
				debugf("No free cluster for use. Left size = %ld, written size = %ld\n", filesize, gotsize);
				goto out;
			}
			if (*start_cluster == 0) {
				*start_cluster = curclust;
			}
			actsize = gotclust * bytesperclust;
		}
		if (actsize > filesize) {  /* Process tail data of file */
			actsize = filesize;
		}

		if (actsize > 0) {
			if (clear) {
				if (clear_clusters(mydata, curclust, buffer, actsize) != 0) {
					debugf("error: writing cluster\n");
					goto out;
				}
			}
			else if (write_clusters(mydata, curclust, buffer, actsize) != 0) {
				debugf("error: writing cluster\n");
				goto out;
			}

			/*  update clusters chain */
			if (*cont > 0) {
				for ( ; last_startclust < last_endclust; last_startclust++) {
					set_exfatent_value(mydata, last_startclust,  last_startclust+1);
				}
				set_exfatent_value(mydata, last_endclust,  curclust);
			}

			last_startclust = curclust;
			last_endclust = curclust + gotclust - 1;
			curclust  = last_endclust + 2;
			gotsize  +=actsize;
			filesize -= actsize;
			buffer += actsize;
			*cont = *cont +1;
		}
	}
out:
	if (*cont > 1 || gotsize <= bytesperclust) {
		for ( ; last_startclust < last_endclust; last_startclust++) {
			set_exfatent_value(mydata, last_startclust,  last_startclust+1);
		}
		/* set file end */
		curclust =  0xffffffff;
		set_exfatent_value(mydata, last_endclust,  curclust);
	}

	return gotsize;
}

int cal_checksum(exfat_whole_dentry * p_ent)
{
	/* calculate primary checksum  */
	__u8 *ptr = (__u8 *)(p_ent->prim);
	__u16  val, checksum = 0;
	int i, j, n;
	n = 32;
	for (i=0; i<n; i++) {
		if (i==2 || i==3)
			continue;
		val = (__u16)ptr[i];
		checksum = ((checksum&1) ? 0x8000 : 0) + (checksum >>1) + val;
	}

	ptr = (__u8 *)(p_ent->strext);
	for (i=0; i<n; i++) {
		val = (__u16)ptr[i];
		checksum = ((checksum&1) ? 0x8000 : 0) + (checksum >>1) + val;
	}

	for (j=0; j<(p_ent->prim->secondary_cnt-1); j++) {
		ptr = (__u8 *)(p_ent->fname_dent[j]);
		for (i=0; i<n; i++) {
			val = (__u16)ptr[i];
			checksum = ((checksum&1) ? 0x8000 : 0) + (checksum >>1) + val;
		}
	}
	p_ent->prim->checksum = cpu_to_le16(checksum);

	return 0;
}


static exfat_file_entry *
update_dir_entry(exfsdata *mydata, exfat_whole_dentry *p_ent, __u32 start_cluster,  __u64  written_size, int cont)
{
	exfat_file_entry *prim_entry = p_ent->prim;
	exfat_strext_entry * strext_entry = p_ent->strext;
	struct rtc_time tm;
	__u32  mod_time;

	tm = get_time_by_sec();
	mod_time = ((tm.tm_year - 1980) << 9) | (tm.tm_mon << 5) | tm.tm_mday;
	mod_time <<= 16;
	mod_time |= (tm.tm_hour << 11) | (tm.tm_min << 5) |  (tm.tm_sec / 2);

	prim_entry->str_dent = NULL;
	prim_entry->mod_time  = cpu_to_le32(mod_time);
	prim_entry->access_time = cpu_to_le32(mod_time);
	strext_entry->secondary_flags = (cont > 1) ? 0x01 : 0x03;
	strext_entry->first_cluster = cpu_to_le32(start_cluster);
	strext_entry->data_len = strext_entry->val_data_len = cpu_to_le64(written_size);

	cal_checksum(p_ent);
	return prim_entry;
}

static exfat_file_entry *
new_dir_entry(exfsdata *mydata, exfat_whole_dentry * p_ent, const char * filename,
				__u32 start_cluster,   __u64  written_size, int cont, int is_dir)
{
	exfat_dentry  *dentptr;
	exfat_file_entry *prim_entry = p_ent->empty;
	exfat_strext_entry *strext_entry = NULL;
	exfat_fnext_entry *fname_entry;
	char fname[FNAME_MAXLEN_BYTES];
	__u32 needed_clust, entry_num;
	__u32 newclust=0, start_sec;
	__u32 clust_start_sec;
	__u32 cl_size, rem_bytes;
	size_t  fname_len, cur_len;
	int  i, j, idx;
	struct rtc_time tm;
	__u32  mod_time;
	__u16   name_hash, val;
	__u16   attr;


	fname_len = strlen(filename);
	memcpy(fname, filename, fname_len);
	fname[fname_len] = '\0';

	needed_clust = 0;
	cl_size = mydata->sect_size * mydata->clust_size;
	entry_num = 2 + ((fname_len+14)/15);

	if (p_ent->empty==NULL) {
		needed_clust = (entry_num * 32 + cl_size - 1)/cl_size;
	} else {
		clust_start_sec = mydata->data_begin +  p_ent->bf1.cluster * mydata->clust_size;
		rem_bytes = cl_size - (p_ent->bf1.start_sec-clust_start_sec)*mydata->sect_size;
		rem_bytes -= ((__u8 *)p_ent->empty - p_ent->bf1.pbuf);
		if ((entry_num*32) > rem_bytes) {
			needed_clust = (entry_num * 32 - rem_bytes + cl_size - 1)/cl_size;
		}
	}

	if (needed_clust) {
		exfat_whole_dentry * parent = (exfat_whole_dentry *)p_ent->parent;
		unsigned long wr_size = (unsigned long)cl_size;
		int temp;
		newclust = 0;
		wr_size = write_file_contents(mydata, &newclust, NULL, wr_size, &temp, 1);
		if (wr_size == 0) {
			debugf("Error: get new cluster for parent.\n");
			return NULL;
		}

		if (parent->prim==NULL) { // parent is root dir
			set_exfatent_value(mydata, p_ent->bf1.cluster,  newclust);
			set_exfatent_value(mydata, newclust,  0xffffffff);
		} else {
			// update parent dir.
			__u64 data_len = EXFAT2CPU64(parent->strext->data_len);
			__u32 cl_num;
			cl_num = data_len/cl_size;
			data_len += cl_size;
			parent->strext->data_len = parent->strext->val_data_len = cpu_to_le64(data_len);

			if (parent->strext->secondary_flags==0x03 && newclust != (p_ent->bf1.cluster+1) ) {
				__u32  prev;
				parent->strext->secondary_flags=0x01;
				prev = EXFAT2CPU32(parent->strext->first_cluster);

				while(--cl_num > 0){
					set_exfatent_value(mydata, prev,  prev+1);
					prev++;
				}
			}
			set_exfatent_value(mydata, p_ent->bf1.cluster,  newclust);
			set_exfatent_value(mydata, newclust,  0xffffffff);

			parent->prim->str_dent = NULL;
			cal_checksum(parent);

			if (write_back_entry(parent) < 0) {
				debugf("Error writing parent data.\n");
				return NULL;
			}
		}

		if (prim_entry==NULL) {
			__u8 *tmp = p_ent->bf0.pbuf;
			p_ent->bf0 = p_ent->bf1;
			p_ent->bf1.pbuf = tmp;
			if (p_ent->bf1.pbuf==NULL) {
				p_ent->bf1.pbuf = exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
				if (p_ent->bf1.pbuf == NULL) {
					debugf("Error: allocate memory failed.\n");
					return NULL;
				}
			}
			p_ent->bf1.cluster = newclust;
			p_ent->bf1.sectors = 1;
			p_ent->bf1.start_sec = mydata->data_begin + newclust * mydata->clust_size;
			memset(p_ent->bf1.pbuf, 0, mydata->sect_size);
			prim_entry = (exfat_file_entry *)p_ent->bf1.pbuf;
		}
	}

	if (prim_entry==NULL) {
		debugf("Error:  prim_entry is NULL, this should never happen.\n");
		return NULL;
	}

	memset(prim_entry, 0, sizeof(exfat_file_entry));

	tm = get_time_by_sec();
	mod_time = ((tm.tm_year - 1980) << 9) | (tm.tm_mon << 5) | tm.tm_mday;
	mod_time <<= 16;
	mod_time |= (tm.tm_hour << 11) | (tm.tm_min << 5) |  (tm.tm_sec / 2);

	attr = is_dir ? EXFAT_ATTR_DIR : EXFAT_ATTR_FILE;
	prim_entry->entry_type = EXFAT_DTYPE_USED | EXFAT_DTYPE_FILE;
	prim_entry->secondary_cnt = (__u8)((entry_num-1)&0xff);
	prim_entry->attr = cpu_to_le16(attr);
	prim_entry->creat_time = cpu_to_le32(mod_time);
	prim_entry->mod_time  = cpu_to_le32(mod_time);
	prim_entry->access_time = cpu_to_le32(mod_time);

	entry_num--;
	dentptr = (exfat_dentry *)prim_entry;
	j = idx = 0;
	name_hash = 0;
	while (entry_num-- >0) {
		__u8 *bufend = NULL;
		dentptr++;
		bufend = p_ent->bf1.pbuf + p_ent->bf1.sectors * mydata->sect_size;
		if  ((__u8 *)dentptr >=bufend) {
			__u8 *tmp = p_ent->bf0.pbuf;
			p_ent->bf0 = p_ent->bf1;
			p_ent->bf1.pbuf = tmp;
			if (p_ent->bf1.pbuf == NULL) {
				p_ent->bf1.pbuf = exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
				if (p_ent->bf1.pbuf == NULL) {
					debugf("Error: allocate memory failed.\n");
					return NULL;
				}
			}

			if (needed_clust) {
				p_ent->bf1.cluster = newclust;
				p_ent->bf1.start_sec = mydata->data_begin + newclust * mydata->clust_size;
			} else {
				p_ent->bf1.cluster = p_ent->bf0.cluster;
				p_ent->bf1.start_sec = p_ent->bf0.start_sec + p_ent->bf0.sectors;
			}
			p_ent->bf1.sectors = 1;
			memset(p_ent->bf1.pbuf, 0, mydata->sect_size);
			dentptr = (exfat_dentry *)p_ent->bf1.pbuf;
		}

		if (strext_entry==NULL) {
			strext_entry = (exfat_strext_entry *)dentptr;
			strext_entry->entry_type = EXFAT_DTYPE_USED | EXFAT_DTYPE_STREXT;
			strext_entry->secondary_flags = (cont > 1) ? 0x01 : 0x03;
			strext_entry->name_len = (__u8)(fname_len&0xff);
			strext_entry->name_hash = cpu_to_le16(0x2345);
			strext_entry->first_cluster = cpu_to_le32(start_cluster);
			strext_entry->data_len = strext_entry->val_data_len = cpu_to_le64(written_size);
		} else {
			p_ent->fname_dent[j++] =  fname_entry = (exfat_fnext_entry *)dentptr;
			memset(fname_entry, 0, sizeof(exfat_fnext_entry));
			cur_len = (fname_len) > 15 ? 15 :  fname_len;
			fname_len -= cur_len;
			fname_entry->entry_type = EXFAT_DTYPE_USED | EXFAT_DTYPE_FNEXT;
			fname_entry->secondary_flags = 0x00;
			for (i=0; i < cur_len; i++) {
				if (fname[idx] > 0x80 || fname[idx] <0x20)
					debugf("Error: unsupported non-ascii code: %02x", fname[idx]);
				fname_entry->uniname[i] = (__u16)fname[idx++];
			}
			__u16   upcase_name[15];
			for (i=0; i < cur_len; i++) {
				upcase_name[i] = mydata->uptab_buf[fname_entry->uniname[i]];
			}

			__u8 *ptr;
			ptr = (__u8 *)upcase_name;
			cur_len <<= 1;
			for (i=0; i<cur_len; i++) {
				val = (__u16)ptr[i];
				name_hash = ((name_hash&1) ? 0x8000 : 0) + (name_hash >>1) + (val&0xff);
			}
		}
	}
	strext_entry->name_hash = cpu_to_le16(name_hash);
	p_ent->prim = prim_entry;
	p_ent->strext = strext_entry;
	cal_checksum(p_ent);

	if (write_back_entry(p_ent) < 0) {
		debugf("Error to write_back_entry.\n");
		return NULL;
	}
	prim_entry->str_dent = strext_entry;
	return prim_entry;
}


static  exfat_file_entry  *
find_dir_entry(exfsdata *mydata,  exfat_whole_dentry *p_ent,  exfat_whole_dentry *p_parent,
					char *filename, int is_dir)
{
	__u32 curclust, startsect, sec_all;
	__u32 rd_sec, rd_sec_cl = 0, rd_sec_all = 0;
	int pending_strext = 0;
	int pending_fnext = 0;
	exfat_file_entry  *ret_dent = NULL;
	exfat_file_entry  *prim_entry;
	exfat_strext_entry  *strext_entry;
	char l_name[FNAME_MAXLEN_BYTES];
	int  i, j,  fn_len, idx, fname_dent_idx, strend, cont;

	if (p_parent->strext == NULL) {// root dir
		sec_all = 0xffffffff;
		startsect = mydata->rootdir_sect;
		curclust = (startsect - mydata->data_begin) / mydata->clust_size;
		cont = 0;
	} else {
		sec_all = 0xffffffff;
		curclust = EXFAT2CPU32(p_parent->strext->first_cluster);
		startsect = mydata->data_begin + curclust * mydata->clust_size;
		cont = (p_parent->strext->secondary_flags==0x03) ? 1 : 0;
	}

	fn_len = strlen(filename);

	if (p_ent->bf0.pbuf)
		exfat_mfree(p_ent->bf0.pbuf);
	if (p_ent->bf1.pbuf)
		exfat_mfree(p_ent->bf1.pbuf);

	memset(p_ent, 0, sizeof(exfat_whole_dentry));

	while (1) {
		exfat_dentry *dentptr;
		__u8 *temp = p_ent->bf0.pbuf;
		p_ent->bf0 = p_ent->bf1;
		p_ent->bf1.pbuf=temp;

		if (p_ent->bf1.pbuf==NULL) {
			p_ent->bf1.pbuf = exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
			if (p_ent->bf1.pbuf==NULL) {
				debugf("Error alloc buffer.\n");
				return  (exfat_file_entry  *)-1;
			}
		}

		rd_sec = (mydata->clust_size - rd_sec_cl) > mydata->rd_sectors ?
					mydata->rd_sectors : (mydata->clust_size - rd_sec_cl);

		rd_sec = 1;
		if (get_exfat_blocks(mydata, startsect, p_ent->bf1.pbuf, rd_sec) != 0) {
			debugf("Error: reading directory block......Return -1\n");
			return  (exfat_file_entry  *)-1;
		}
		p_ent->bf1.sectors = rd_sec;
		p_ent->bf1.cluster = curclust;
		p_ent->bf1.start_sec = startsect;
		startsect += rd_sec;
		rd_sec_cl += rd_sec;
		rd_sec_all += rd_sec;

		dentptr = (exfat_dentry *)p_ent->bf1.pbuf;
		for (i = 0; i < (p_ent->bf1.sectors * mydata->sect_size /sizeof(exfat_dentry));  i++, dentptr++) {

			if (pending_strext) {
				if ((dentptr->entry_type&EXFAT_DTYPE_USED) &&
					((dentptr->entry_type & EXFAT_DTYPE_MASK)== EXFAT_DTYPE_STREXT) ) {
					strext_entry = (exfat_strext_entry *)dentptr;
					pending_strext = 0;
					if (fn_len != (int)strext_entry->name_len) {
						pending_strext = 0;
						pending_fnext = 0;
						continue;
					}
					memset(l_name, '\0', sizeof(l_name));
					idx = strend = 0;
					fname_dent_idx = 0;
					continue;
				}
				else {
					pending_strext = 0;
					pending_fnext = 0;
				}
			}
			else if (pending_fnext) {
				if ((dentptr->entry_type&EXFAT_DTYPE_USED) &&
					((dentptr->entry_type & EXFAT_DTYPE_MASK)== EXFAT_DTYPE_FNEXT) ) {
					pending_fnext--;
					p_ent->fname_dent[fname_dent_idx++] = dentptr;
					for (j=0; j < 30; j+=2) {
						if((dentptr->bytes[j] != 0 || dentptr->bytes[j+1] !=0) && idx <(int)strext_entry->name_len)
							l_name[idx++] = dentptr->bytes[j];
						else {
							l_name[idx] = '\0';
							strend = 1;
						}
					}
					if (pending_fnext==0 || strend==1) {
						downcase(l_name);
						if (!strcmp(filename, l_name)) {
							debugf("Existing file %s is found. It may be overwritten.\n",  filename);
							ret_dent = prim_entry;
							ret_dent->str_dent = strext_entry;
							p_ent->prim = prim_entry;
							p_ent->strext = strext_entry;
							return ret_dent;
						}
						else {
							pending_fnext = 0;
						}
					}
					continue;
				}
				else {
					debugf("Warning: exFAT stream extension entry should be here.");
					pending_strext = 0;
					pending_fnext = 0;
				}
			}

			if ((dentptr->entry_type&EXFAT_DTYPE_USED) &&
					((dentptr->entry_type & EXFAT_DTYPE_MASK)== EXFAT_DTYPE_FILE) ) {
				prim_entry = (exfat_file_entry *)dentptr;
				__u16 attr = EXFAT2CPU16(prim_entry->attr);
				if (is_dir==0 && attr != EXFAT_ATTR_FILE) {
					continue;
				}
				if (is_dir==1 && attr != EXFAT_ATTR_DIR) {
					continue;
				}
				if (prim_entry->secondary_cnt  > 18 || prim_entry->secondary_cnt < 2) {
					debugf("exFAT secondary entries %d out of range (2,18)\n", prim_entry->secondary_cnt);
					continue;
				}
				pending_strext = 1;
				pending_fnext = prim_entry->secondary_cnt - 1;
			}
			else if (dentptr->entry_type==0)  {
				p_ent->empty = dentptr;
				return NULL;
			}
			else {
				// unknown entry, skip it.
			}
		}

		if (rd_sec_all >= sec_all) {
			debugf("Parse to end of current directory. Read: %u,  parent size: %u (sectors).\n", rd_sec_all, sec_all);
			break;
		}

		if (rd_sec_cl >= mydata->clust_size) {
			rd_sec_cl = 0;
			if (cont)
				curclust++;
			else
				curclust = get_next_cluster(mydata,  curclust);
			if (curclust < 2 || curclust > mydata->cluster_cnt) {
				debugf("Get end or error for current directory, next cluster %08x\n", curclust);
				return  NULL;
			}
			startsect = mydata->data_begin + curclust * mydata->clust_size;
		}
	}

	return NULL;
}

static  exfat_file_entry  *
exfat_path_walk(exfsdata *mydata, const char *complete_filename, exfat_whole_dentry *file_ent)
{
	int  name_len, is_dir, cont;
	__u32 start_sec, start_cl;
	__u32 cl_size = mydata->sect_size * mydata->clust_size;
	__u64  size64;
	const char *dn_start, *dn_end, *cur;
	char l_filename[FNAME_MAXLEN_BYTES];
	exfat_file_entry  * retdent;
	__u32 parent_sec, parent_off;
	exfat_whole_dentry parent, current;

	name_len = strlen(complete_filename);

	memset(&parent, 0, sizeof(exfat_whole_dentry));
	memset(&current, 0, sizeof(exfat_whole_dentry));

	//split filename to path and file.
	start_sec = mydata->rootdir_sect;
	cur = dn_start = complete_filename;
	while (*cur != 0) {
		while (*cur=='/') {
			cur++;
		}
		dn_start = cur;

		while (*cur != '/' && *cur != 0) {
			cur ++;
		}
		is_dir = 1;
		dn_end = cur;
		name_len = dn_end - dn_start;
		if (*cur==0) {
			is_dir = 0;
		}

		if (name_len >= FNAME_MAXLEN_BYTES)
			name_len = FNAME_MAXLEN_BYTES - 1;

		/* Too long name length may cause one dir entry cross 3 sector, which we can't process. */
		if(name_len > 210) {
			debugf("Warning: too long sysdump file name(len=%d) may cause buffer overflow, truncate it to 210.\n", name_len);
			name_len=210;
		}

		memcpy(l_filename, dn_start, name_len);
		l_filename[name_len] = 0;
		downcase(l_filename);

		// start_sec = start sector of parent directory.
		if (start_sec == mydata->rootdir_sect)
			cont = 0;
		else
			cont = (parent.strext->secondary_flags==0x03) ? 1 : 0;
		retdent = find_dir_entry(mydata, &current,  &parent,  l_filename, is_dir);

		if (retdent==(exfat_file_entry *)(-1)) {
			debugf("Get error when find file entry\n");
			retdent = NULL;
			goto exit;
		}

		current.parent = (void *)&parent;
		if (is_dir) {
			if (retdent == NULL) {
				__u32 start_cluster = 0;
				unsigned long written_size = (unsigned long)cl_size;
				written_size = write_file_contents(mydata, &start_cluster, NULL, written_size, &cont, 1);
				if (written_size == 0) {
					debugf("Error: writing contents\n");
					goto exit;
				}
				size64  = written_size;
				retdent = new_dir_entry(mydata, &current, l_filename, start_cluster, size64, cont, is_dir);
				if (retdent==NULL) {
					debugf("Error to create a new file entry.\n");
					goto exit;
				}
				start_cl = start_cluster;
			} else {
				start_cl = EXFAT2CPU32(retdent->str_dent->first_cluster);
			}
			start_sec  = mydata->data_begin + start_cl * mydata->clust_size;

			if(parent.bf0.pbuf)
				exfat_mfree(parent.bf0.pbuf);
			if(parent.bf1.pbuf)
				exfat_mfree(parent.bf1.pbuf);
			memcpy(&parent, &current, sizeof(exfat_whole_dentry));
			memset(&current, 0, sizeof(exfat_whole_dentry));
		} else if (retdent == NULL){
			// Create new file
			__u32 start_cluster = 0;
			unsigned long written_size = (unsigned long)cl_size;
			written_size = write_file_contents(mydata, &start_cluster, NULL, written_size, &cont, 1);
			if (written_size == 0) {
				debugf("Error: writing contents\n");
				goto exit;
			}
			size64  = written_size;

			retdent = new_dir_entry(mydata, &current, l_filename, start_cluster, size64, cont, 0);
			if (retdent==NULL) {
				debugf("Error to create a new file entry.\n");
				goto exit;
			}

			memcpy(file_ent, &current, sizeof(exfat_whole_dentry));
			memset(&current, 0, sizeof(exfat_whole_dentry));
			goto exit;
		} else {
			memcpy(file_ent, &current, sizeof(exfat_whole_dentry));
			memset(&current, 0, sizeof(exfat_whole_dentry));
			goto exit;
		}
	}

exit:

	if(parent.bf0.pbuf)
		exfat_mfree(parent.bf0.pbuf);
	if(parent.bf1.pbuf)
		exfat_mfree(parent.bf1.pbuf);
	if(current.bf0.pbuf)
		exfat_mfree(current.bf0.pbuf);
	if(current.bf1.pbuf)
		exfat_mfree(current.bf1.pbuf);

	return retdent;
}

static  int exfat_path_init(exfsdata *mydata,  exfat_buf_array *bfs , __u32 startsect)
{
	__u32 curclust = (startsect - mydata->data_begin) / mydata->clust_size;
	__u32 rd_sec,  rd_sec_total = 0;
	int i, get_bitmap, get_uc;
	get_bitmap = get_uc = 0;

	while (1) {
		exfat_dentry *dentptr;

		if (bfs->bf1.sectors > 0)
			bfs->bf0 = bfs->bf1;

		if (bfs->bf1.pbuf==dir_content_block)
			bfs->bf1.pbuf = dir_content_block1;
		else
			bfs->bf1.pbuf = dir_content_block;

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
				exfat_bitmap_entry *bm_dentptr = dentptr;
				mydata->cur_bitmap_cluster = EXFAT2CPU32(bm_dentptr->start_clu);
				mydata->bitmap_sect = mydata->cur_bitmap_cluster * mydata->clust_size + mydata->data_begin;
				mydata->bitmaplen = (__u32) EXFAT2CPU64(bm_dentptr->data_len);
				get_bitmap = 1;
				debugf("exFAT bitmap entry got. \n");
			}
			else if ((dentptr->entry_type&EXFAT_DTYPE_USED) &&
					((dentptr->entry_type & EXFAT_DTYPE_MASK)== EXFAT_DTYPE_UC) ) {
				__u32 start_cl = EXFAT2CPU32(*(__u32 *)((__u8 *)dentptr + 20));
				__u32  length = (__u32)EXFAT2CPU64(*(__u64 *)((__u8 *)dentptr + 24));
				debugf("exFAT up-case table entry. \n");
				if(get_upcase_table(mydata, start_cl, length) < 0)
					return  (exfat_file_entry  *)-1;
				get_uc = 1;
			}
			else {
				// not bitmap or up-case table entry, skip it.
			}

			if (get_bitmap && get_uc)
				return 0;
		}

		if (rd_sec_total >= mydata->clust_size) {
			rd_sec_total = 0;
			curclust = get_next_cluster(mydata,  curclust);
			if (curclust < 2 || curclust > mydata->cluster_cnt) {
				debugf("Error: exfat get end, or invalid next cluster %08x\n", curclust);
				return -1;
			}
			startsect = mydata->data_begin + curclust * mydata->clust_size;
		}
	}

	return -1;
}


static int do_exfat_write(const char *filename, void *buffer,
	unsigned long size)
{
	exfat_file_entry  * retdent;
	__u32 startsect;
	__u32 start_cluster;
	__u32 cl_size;
	exfat_boot_sector bs;
	exfsdata datablock;
	exfsdata *mydata = &datablock;
	exfat_buf_array  buf_array;
	int ret = -1, name_len, path_len;
	unsigned long written_size;
	__u64  size64;
	char l_filename[FNAME_MAXLEN_BYTES];
	exfat_fnext_entry *fname_dent[17];

	exfat_whole_dentry  file_ent;
	memset(&file_ent, 0, sizeof(file_ent));

	if (read_exfat_bootsec(&bs)) {
		debugf("Error: reading boot sector\n");
		return -1;
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
	mydata->rd_sectors = (cl_size > MAX_RD_BLK_SIZE) ? (MAX_RD_BLK_SIZE /mydata->sect_size) : mydata->clust_size;

	mydata->fatbuf_idx = 0;
	mydata->fatbuf = exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
	if (mydata->fatbuf == NULL) {
		debugf("Error: allocating memory\n");
		goto exit;
	}

	mydata->bitmap_idx = 0;
	mydata->bitmap = exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->sect_size);
	if (mydata->bitmap == NULL) {
		debugf("Error: allocating memory\n");
		goto exit;
	}

	memset(&buf_array, 0, sizeof(buf_array));
	startsect = mydata->rootdir_sect;
	ret = exfat_path_init(mydata, &buf_array,  startsect);

	if (ret < 0) {
		debugf("Error: exfat_path_init failed.\n");
		goto exit;
	}

	if (mydata->bitmap_sect==0) {
		debugf("Error: exfat bitmap is not found\n");
		goto exit;
	}

	if(mydata->uptab_buf==NULL) {
		debugf("Error: exfat upcase table is not found\n");
		goto exit;
	}

	mydata->bitmap_fatbuf_size = EXFAT_FAT_ENTRY_SIZE * (mydata->bitmaplen + cl_size - 1)/cl_size;
	mydata->bitmap_fatbuf_size = (mydata->bitmap_fatbuf_size + mydata->sect_size -1) / mydata->sect_size;
	mydata->bitmap_fatbuf = exfat_malloc_aligned(ARCH_DMA_MINALIGN, mydata->bitmap_fatbuf_size * mydata->sect_size);
	if (mydata->bitmap_fatbuf == NULL) {
		debugf("Error: allocating memory\n");
		goto exit;
	}

	ret = check_bitmap_fatbuf(mydata);
	if (ret < 0) {
		debugf("Error: read and check fatbuf for bitmap failed.\n");
		goto exit;
	}

	retdent = exfat_path_walk(mydata, filename, &file_ent);
	if (retdent==NULL) {
		debugf("Got error when finding/creating file entry\n");
		goto exit;
	}

	start_cluster = 0;
	if (retdent->str_dent->first_cluster) {
		// Clear previous content of existing file (fat table & bitmap). Overwrite.
		__u32 cl_num = (EXFAT2CPU64(retdent->str_dent->data_len) + cl_size -1) / cl_size;
		start_cluster = EXFAT2CPU32(retdent->str_dent->first_cluster);
		ret = clear_exfatent_bitmap(mydata, start_cluster, cl_num, (retdent->str_dent->secondary_flags&0x02) ? 0 : 1);
		if (ret < 0) {
			debugf("Error: clear_exfatent_bitmap\n");
			goto exit;
		}
	}

	ret = check_available_size(mydata, (__u64)size);
	if (ret < 0) {
		debugf("Error: there is not enough free space for file size: %ld\n", size);
		goto exit;
	}

	int cont = 0;
	written_size = write_file_contents(mydata, &start_cluster, buffer, size, &cont, 0);
	if (written_size == 0) {
		debugf("Error: writing contents\n");
		goto exit;
	}

	size64  = (__u64)written_size;
	update_dir_entry(mydata, &file_ent, start_cluster, size64, cont);

	if (write_back_entry(&file_ent) < 0) {
		debugf("Error to write_back_entry.\n");
		goto exit;
	}

	ret = 0;

	flush_exfatent(mydata);
	flush_bitmap(mydata);

exit:
	if (mydata->fatbuf)
		exfat_mfree(mydata->fatbuf);
	if (mydata->bitmap)
		exfat_mfree(mydata->bitmap);
	if (mydata->uptab_buf)
		exfat_mfree(mydata->uptab_buf);
	if(mydata->bitmap_fatbuf)
		exfat_mfree(mydata->bitmap_fatbuf);

	if(file_ent.bf0.pbuf)
		exfat_mfree(file_ent.bf0.pbuf);
	if(file_ent.bf1.pbuf)
		exfat_mfree(file_ent.bf1.pbuf);

	return ret < 0 ? ret : (int)written_size;
}


int file_exfat_write(const char *filename, void *buffer, unsigned long maxsize)
{
	int ret = 0;
	debugf("writing %s\n", filename);
	ret = do_exfat_write(filename, buffer, maxsize);
	if (ret < 0)
		debugf("T-card write ERROR!!! T-card maybe is bad!!!: ret = %d\n", ret);
	return ret;
}
