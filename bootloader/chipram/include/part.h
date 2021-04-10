#ifndef _PART_H
#define _PART_H
#include <linux/types.h>
#include <common.h>
#define IF_TYPE_UNKNOWN		0
#define IF_TYPE_MMC		6
#define PART_TYPE_EFI		0x05

#define PAD_TO_BLOCKSIZE(size, block_dev_desc) \
	(PAD_SIZE(size, block_dev_desc->blksz))
typedef struct block_dev_desc {
	int		if_type;	/* type of the interface */
	int		dev;		/* device number */
	unsigned char	part_type;	/* partition type */
	unsigned char	target;		/* target SCSI ID */
	unsigned char	lun;		/* target LUN */
	unsigned char	type;		/* device type */
	unsigned char	removable;	/* removable device */
#ifdef CONFIG_LBA48
	unsigned char	lba48;		/* device can use 48bit addr (ATA/ATAPI v7) */
#endif
	ulong	lba;		/* number of blocks */
	unsigned long	blksz;		/* block size */
	int		log2blksz;	/* for convenience: log2(blksz) */
	char		vendor [40+1];	/* IDE model, SCSI Vendor */
	char		product[20+1];	/* IDE Serial no, SCSI product */
	char		revision[8+1];	/* firmware revision */
	unsigned long	(*block_read)(int dev,
				      ulong start,
				      ulong blkcnt,
				      void *buffer);
	unsigned long	(*block_write)(int dev,
				       ulong start,
				       ulong blkcnt,
				       const void *buffer);
	unsigned long   (*block_erase)(int dev,
				       ulong start,
				       ulong blkcnt);
	void		*priv;		/* driver private struct pointer */
}block_dev_desc_t;
typedef struct disk_partition {
	ulong	start;	/* # of first block in partition	*/
	ulong	size;	/* number of blocks in partition	*/
	ulong	blksz;		/* block size in bytes			*/
	uint8_t	name[32];	/* partition name			*/
	uint8_t	type[32];	/* string type description		*/
	int	bootable;	/* Active/Bootable flag is set		*/
#ifdef CONFIG_PARTITION_UUIDS
	char	uuid[37];	/* filesystem UUID as string, if exists	*/
#endif
} disk_partition_t;
#endif /* _PART_H */
extern block_dev_desc_t *get_dev();
extern int get_partition_info_by_name (block_dev_desc_t *dev_desc, uchar * partition_name,
						disk_partition_t *info);
extern block_dev_desc_t *mmc_get_dev();
