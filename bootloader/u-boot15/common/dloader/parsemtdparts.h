#ifndef FDL_PARSRMTD_H
#define FDL_PARSRMTD_H

#define MTDPARTITION_MAX	(40)
#define PARTITION_NAME_LEN	(20)

struct real_mtd_partition {
	char name[PARTITION_NAME_LEN];			/* identifier string */
	unsigned long size;			/* partition size */
	unsigned long offset;		/* offset within the master MTD space */
	unsigned long mask_flags;		/* master MTD flags to mask out for this partition */
	unsigned long yaffs;	/* 1 is yaffs image, 0 is not raw image */
};

typedef struct _NAND_PAGE_OOB_STATUS
{
	unsigned long	erasesize;
	unsigned long	writesize;
	unsigned long	oobsize;
} NAND_PAGE_OOB_STATUS;
int parse_cmdline_partitions(unsigned long long mastersize);
int parse_mtd_part_info(char *name,struct mtd_partition *part);


#endif /* FDL_NAND_H */
