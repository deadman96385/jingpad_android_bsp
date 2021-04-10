#ifndef _SPRD_COMMON_RW_H_
#define _SPRD_COMMON_RW_H_
#include <common.h>
#define SPRD_DISK_GUID_STR "11111111-2222-3333-4444-000000000000"

int common_raw_read(char *part_name, uint64_t size, uint64_t offset, char *buf);
int common_raw_write(char *part_name, uint64_t size, uint64_t updsize, uint64_t offset, char *buf);
int common_raw_erase(char *part_name, uint64_t size, uint64_t offset);
int common_repartition(disk_partition_t *partitions, int parts_count);
int32_t common_get_lba_size(void);
int do_fs_file_read(char *mpart, char *filenm, void *buf, int len);
int do_fs_file_write(char *mpart, char *filenm, void *buf, int len);
int fdt_fixup_iq_reserved_mem(void *fdt);
void fdt_fixup_pmic_wa(void *fdt);
 int common_query_backstage(char *part_name, uint32_t size, char *buf);
 int common_write_backstage(char *part_name, uint32_t size, uint64_t offset, char *buf);
 int write_sparse_img(uchar * partname, u8* buf, unsigned long length);
 int get_partition_info_by_name(block_dev_desc_t *dev_desc,uchar* partition_name,disk_partition_t *info);
 int fdt_fixup_adc_calibration_data(void *fdt);
 int fdt_fixup_ddr_size(void *fdt);
 int fdt_fixup_sysdump_magic(void *fdt);
 int _fixup_sysdump_uboot(void *fdt);
 int fdt_fixup_cp_boot(void *fdt);
 int fdt_fixup_memleakon(void *fdt);
 int fdt_fixup_verified_boot(void *fdt);
 int fdt_fixup_flash_lock_state(void *fdt);
 int fdt_fixup_serialno(void *fdt);
 int fdt_fixup_chosen_bootargs_board_private(void *fdt);
 void fdt_fixup_all(u8 *fdt_blob);
 int fdt_initrd_norsvmem(void *fdt, ulong initrd_start, ulong initrd_end, int force);
 int boot_sprdisk(int offset, char *ramdisk_addr);

#ifdef CONFIG_NAND_BOOT
int do_raw_data_write(char *part, u32 updsz, u32 size, u32 off, char *buf);
#endif
int get_img_partition_size(char *part_name, uint64_t *size);

#endif /* _LOADER_COMMON_H_ */
