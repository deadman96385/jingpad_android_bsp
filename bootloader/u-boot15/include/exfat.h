
#ifndef _EXFAT_H_
#define _EXFAT_H_

#include <asm/byteorder.h>

#define _uswap_64(x, sfx) \
	((((x) & 0xff00000000000000##sfx) >> 56) | \
	 (((x) & 0x00ff000000000000##sfx) >> 40) | \
	 (((x) & 0x0000ff0000000000##sfx) >> 24) | \
	 (((x) & 0x000000ff00000000##sfx) >>  8) | \
	 (((x) & 0x00000000ff000000##sfx) <<  8) | \
	 (((x) & 0x0000000000ff0000##sfx) << 24) | \
	 (((x) & 0x000000000000ff00##sfx) << 40) | \
	 (((x) & 0x00000000000000ff##sfx) << 56))

#if defined(__GNUC__)
# define uswap_64(x) _uswap_64(x, ull)
#else
# define uswap_64(x) _uswap_64(x, )
#endif

#if defined(__linux__) && defined(__KERNEL__)
#define EXFAT2CPU16	le16_to_cpu
#define EXFAT2CPU32	le32_to_cpu
#define EXFAT2CPU64	le64_to_cpu
#else
#if __LITTLE_ENDIAN
#define EXFAT2CPU16(x)	(x)
#define EXFAT2CPU32(x)	(x)
#define EXFAT2CPU64(x)	(x)
#else
#define EXFAT2CPU16(x)	((((x) & 0x00ff) << 8) | (((x) & 0xff00) >> 8))
#define EXFAT2CPU32(x)	((((x) & 0x000000ff) << 24)  |	\
			 (((x) & 0x0000ff00) << 8)  |	\
			 (((x) & 0x00ff0000) >> 8)  |	\
			 (((x) & 0xff000000) >> 24))
#define EXFAT2CPU64(x)	 uswap_64(x)
#endif
#endif

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define DIV_ROUND_UP(x, d) (((x) + (d) - 1) / (d))
#define ROUND_UP(x, d) (DIV_ROUND_UP(x, d) * (d))


#define FNAME_MAXLEN_BYTES	256   /* Maximum LFN buffer in bytes */
#define MAX_RD_BLK_SIZE	65536
#define EXFAT_FAT_ENTRY_SIZE  4

#define EXFAT_ATTR_RDONLY  0x01
#define EXFAT_ATTR_HIDDEN  0x02
#define EXFAT_ATTR_SYSTEM   0x04
#define EXFAT_ATTR_DIR          0x10
#define EXFAT_ATTR_FILE         0x20

#define EXFAT_ENAME_MAX 15
#define EXFAT_FIRST_DATA_CLUSTER 2
#define EXFAT_LAST_DATA_CLUSTER 0xfffffff6

#define EXFAT_CLUSTER_FREE         0 /* free cluster */
#define EXFAT_CLUSTER_BAD 0xfffffff7 /* cluster contains bad sector */
#define EXFAT_CLUSTER_END 0xffffffff /* final cluster of file or directory */
#define	CHAR_BIT	8		/* number of bits in a char */

enum {
	EXFAT_DTYPE_BM = 0x01,  // bitmap entry
	EXFAT_DTYPE_UC = 0x02,  // up-case table entry
	EXFAT_DTYPE_LABLE = 0x03,  // label
	EXFAT_DTYPE_FILE = 0x05,    // regular file or directory
	EXFAT_DTYPE_STREXT = 0x40,  // stream extension entry
	EXFAT_DTYPE_FNEXT = 0x41,    // file name extension entry
	EXFAT_DTYPE_MASK = 0x7f,    // entry type mask
	EXFAT_DTYPE_USED = 0x80,   // flag bit of whether entry is in used or not
};


struct exfat_super_block
{
	__u8 jump[3];				/* 0x00 jmp and nop instructions */
	__u8 oem_name[8];			/* 0x03 "EXFAT   " */
	__u8	__unused1[53];			/* 0x0B always 0 */
	__u64 sector_start;			/* 0x40 partition first sector */
	__u64 sector_count;			/* 0x48 partition sectors count */
	__u32 fat_sector_start;		/* 0x50 FAT first sector */
	__u32 fat_sector_count;		/* 0x54 FAT sectors count */
	__u32 cluster_sector_start;	/* 0x58 first cluster sector */
	__u32 cluster_count;			/* 0x5C total clusters count */
	__u32 rootdir_cluster;			/* 0x60 first cluster of the root dir */
	__u32 volume_serial;			/* 0x64 volume serial number */
	struct							/* 0x68 FS version */
	{
		__u8 minor;
		__u8 major;
	}
	version;
	__u16 volume_state;			/* 0x6A volume state flags */
	__u8 sector_bits;			/* 0x6C sector size as (1 << n) */
	__u8 spc_bits;				/* 0x6D sectors per cluster as (1 << n) */
	__u8 fat_count;				/* 0x6E always 1 */
	__u8 drive_no;				/* 0x6F always 0x80 */
	__u8 allocated_percent;		/* 0x70 percentage of allocated space */
	__u8 __unused2[397];			/* 0x71 always 0 */
	__u16 boot_signature;			/* the value of 0xAA55 */
};

typedef struct exfat_boot_sector {
	__u8	ignored[3];	/* Bootstrap code */
	char	       fs_name[8];	/* Name of fs, should be "EXFAT   "  */
	__u8	zero_bytes[53];	/* Must be zero bytes */
	__u64	part_off;    	/* Partition offset (in sector) */
	__u64	vol_len;	       /* Volume length (in sector) */
	__u32	fat_off;		/* FATs start sector */
	__u32	fat_len;		/* FATs length */
	__u32      cluster_heap_off;  /* Cluster heap */
	__u32      cluster_cnt;            /* Cluster  count */
	__u32      root_cluster;             /* first cluster of root dir */
	__u32      vol_serial;
	__u16      fs_version;
	__u16      vol_flags;
	__u8       sector_size_bits;
	__u8       sectors_per_clu_bits;
	__u8       num_fats;
	__u8       phy_drv_no;
	__u8       perc_in_use;
	__u8       reserved[7];
	__u8       boot_code[390];
	__u8       boot_signature[2];
} exfat_boot_sector;

typedef struct {
	__u16      sec;
	__u16      min;
	__u16      hour;
	__u16      day;
	__u16      mon;
	__u16      year;
}timestamp_t;

/*
 * Private filesystem parameters
 *
 * Note: exFAT buffer has to be 32 bit aligned
 * (see exFAT accesses)
 */
typedef struct {
	__u8	*fatbuf;	/* Current FAT buffer */
	__u8       *bitmap; /* Current bitmap buffer */
	__u8       *bitmap_fatbuf;   /* FAT buffer for bitmap file */
	__u16     *uptab_buf;     /* upcase-table buffer */
	__u32     fat_num;
	__u32	fatlength;	/* Length of FAT in sectors */
	__u32     bitmaplen;   /* Length of bitmap in bytes */
	__u32     cluster_cnt;   /* Total cluster count */
	__u32	fat_sect;	/* Starting sector of the FAT */
	__u32	bitmap_sect;	/* Starting sector of the FAT */
	__u32     bitmap_fatbuf_size;       /* size in sector of FAT buffer for bitmap file */
	__u32     cur_bitmap_cluster;  /* current read in bitmap file cluster */
	__u32	rootdir_sect;	/* Start sector of root directory */
	__u16	sect_size;	/* Size of sectors in bytes */
	__u16	clust_size;	/* Size of clusters in sectors */
	__u32     rd_sectors;   /* read sectors once */
	__u32	fatbuf_idx;	/* got fat table buffer index */
	__u32     bitmap_idx;  /* got bitmap buffer index */
	__u32     avail_clusters;  /* free clusters can be used */
	__s32     data_begin;	/* The sector of the first cluster, can be negative */
} exfsdata;

typedef struct exfat_entry_label			/* volume label */
{
	__u8  entry_type;					/* EXFAT_ENTRY_LABEL */
	__u8  length;					/* number of characters */
	__u16 name[EXFAT_ENAME_MAX];	/* in UTF-16LE */
}exfat_entry_label;

typedef struct exfat_bitmap_entry {
	__u8	entry_type;		/*entry type */
	__u8	bitmap_flags;
	__u8	reserved[18];
	__u32     start_clu;
	__u64   data_len;
}exfat_bitmap_entry;

typedef struct exfat_entry_upcase			/* upper case translation table */
{
	__u8   entry_type;					/* EXFAT_ENTRY_UPCASE */
	__u8   __unknown1[3];
	__u32 checksum;
	__u8   __unknown2[12];
	__u32  start_cluster;
	__u64  size;					/* in bytes */
}exfat_entry_upcase;

typedef struct exfat_strext_entry {
	__u8   entry_type;
	__u8   secondary_flags;
	__u8    reserved0;
	__u8    name_len;
	__u16  name_hash;
	__u8    reserved1[2];
	__u64    val_data_len;
	__u8    reserved2[4];
	__u32  first_cluster;
	__u64  data_len;
}exfat_strext_entry;

typedef struct exfat_file_entry {
	__u8   entry_type;
	__u8   secondary_cnt;
	__u16   checksum;
	__u16   attr;
	__u8    reserved0[2];
	__u32  creat_time;
	__u32  mod_time;
	__u32  access_time;
	__u8    creat_ms_inc;
	__u8    mod_ms_inc;
	__u8    creat_utc_off;
	__u8    mod_utc_off;
	union  {
		struct  {
			__u8    access_utc_off;
			__u8    reserved1[8];
		}a;
		exfat_strext_entry  *str_dent;
	}
}exfat_file_entry;

typedef struct exfat_fnext_entry {
	__u8   entry_type;
	__u8   secondary_flags;
	__u16   uniname[15];
}exfat_fnext_entry;


typedef struct exfat_dentry {
	__u8   entry_type;
	__u8   secondary_flags;
	__u8   bytes[30];
}exfat_dentry;


typedef struct exfat_buf_info {
	__u8   *pbuf;
	__u32   cluster;
	__u32   start_sec;
	__u32   sectors;
}exfat_buf_info;

typedef struct exfat_whole_dentry {
	exfat_buf_info bf0;
	exfat_buf_info bf1;
	exfat_file_entry *empty;
	exfat_file_entry *prim;
	exfat_strext_entry  *strext;
	exfat_fnext_entry *fname_dent[17];
	void *parent;
}exfat_whole_dentry;

typedef struct exfat_buf_array {
	exfat_buf_info bf0;
	exfat_buf_info bf1;
}exfat_buf_array;



extern __u8 bitmap_mask[9];
extern __u8 bitmap_clr_mask[8];
extern __u8  bits_num_table[256] ;
extern __u8  bitmap_avail[256];
extern __u8 upcase_table[5836];

int exfat_disk_read(__u32 block, __u32 nr_blocks, void *buf);
int exfat_disk_write(__u32 block, __u32 nr_blocks, void *buf);
int exfat_set_blk_dev(block_dev_desc_t *dev_desc, disk_partition_t *info);
int read_exfat_bootsec(exfat_boot_sector *bs);
void  *exfat_malloc_aligned(size_t align,  size_t bytes);
int   exfat_mfree(void *ptr);


int exfat_register_device(block_dev_desc_t *dev_desc, int part_no);
int file_exfat_detectfs(void);
int  get_exfat_blocks(exfsdata *mydata, __u32 start_sec, __u8 *buffer,  __u32 rd_sec);

int file_exfat_write(const char *filename, void *buffer, unsigned long maxsize);
int exfat_checksys(size_t ram_size);
int exfat_format();
#endif /* _EXFAT_H_ */
