
#include <common.h>
#include <command.h>
#include <config.h>
#include <fat.h>
#include <exfat.h>
#include <asm/byteorder.h>
#include <part.h>
#include <malloc.h>
#include <linux/ctype.h>

typedef struct fs_object
{
	__u32 (*get_alignment)(void);
	__u32 (*get_size)(void);
	int (*write)(exfat_boot_sector * bs, __u64 start);
};

static struct
{
	int sector_bits;
	int spc_bits;
	__u64  volume_size;
	__u16 volume_label[EXFAT_ENAME_MAX + 1];
	__u32 volume_serial;
	__u64 first_sector;
}
param;


struct fs_object vbr;
struct fs_object fat;
struct fs_object cbm;
struct fs_object uct;
struct fs_object  rootdir;


struct fs_object* objects[] =
{
	&vbr,
	&vbr,
	&fat,
	/* clusters heap */
	&cbm,
	&uct,
	&rootdir,
	NULL,
};



int get_sector_bits(void)
{
	return param.sector_bits;
}

int get_spc_bits(void)
{
	return param.spc_bits;
}

__u64 get_volume_size(void)
{
	return param.volume_size;
}

const __u16* get_volume_label(void)
{
	return param.volume_label;
}

__u32 get_volume_serial(void)
{
	return param.volume_serial;
}

__u64 get_first_sector(void)
{
	return param.first_sector;
}

int get_sector_size(void)
{
	return 1 << get_sector_bits();
}

int get_cluster_size(void)
{
	return get_sector_size() << get_spc_bits();
}

__u64 get_position(struct fs_object* object)
{
	struct fs_object** pp;
	__u64 position = 0;

	for (pp = objects; *pp; pp++)
	{
		position = ROUND_UP(position, (*pp)->get_alignment());
		if (*pp == object)
			return position;
		position += (*pp)->get_size();
	}
	debugf("unknown object\n");

	return  0;
}


static __u32 vbr_alignment(void)
{
	return get_sector_size();
}

static __u32 vbr_size(void)
{
	return 12 * get_sector_size();
}

static __u32 exfat_vbr_start_checksum(const void* sector, size_t size)
{
	size_t i;
	__u32 sum = 0;

	for (i = 0; i < size; i++)
		/* skip volume_state and allocated_percent fields */
		if (i != 0x6a && i != 0x6b && i != 0x70)
			sum = ((sum << 31) | (sum >> 1)) + ((const uint8_t*) sector)[i];
	return sum;
}


static  __u32 exfat_vbr_add_checksum(const void* sector, size_t size, __u32 sum)
{
	size_t i;

	for (i = 0; i < size; i++)
		sum = ((sum << 31) | (sum >> 1)) + ((const uint8_t*) sector)[i];
	return sum;
}

static void init_sb(struct exfat_super_block* sb)
{
	__u32 clusters_max;
	__u32 fat_sectors;

	clusters_max = get_volume_size() / get_cluster_size();
	fat_sectors = DIV_ROUND_UP((__u32) clusters_max * sizeof(__u32),
			get_sector_size());

	memset(sb, 0, sizeof(struct exfat_super_block));
	sb->jump[0] = 0xeb;
	sb->jump[1] = 0x76;
	sb->jump[2] = 0x90;
	memcpy(sb->oem_name, "EXFAT   ", sizeof(sb->oem_name));
	sb->sector_start = cpu_to_le64(get_first_sector());
	sb->sector_count = cpu_to_le64(get_volume_size() / get_sector_size());
	sb->fat_sector_start = cpu_to_le32(
			fat.get_alignment() / get_sector_size());
	sb->fat_sector_count = cpu_to_le32(ROUND_UP(
			EXFAT2CPU32(sb->fat_sector_start) + fat_sectors,
				1 << get_spc_bits()) -
			EXFAT2CPU32(sb->fat_sector_start));
	sb->cluster_sector_start = cpu_to_le32(
			get_position(&cbm) / get_sector_size());
	sb->cluster_count = cpu_to_le32(clusters_max -
			((EXFAT2CPU32(sb->fat_sector_start) +
			  EXFAT2CPU32(sb->fat_sector_count)) >> get_spc_bits()));
	sb->rootdir_cluster = cpu_to_le32(
			(get_position(&rootdir) - get_position(&cbm)) / get_cluster_size()
			+ EXFAT_FIRST_DATA_CLUSTER);
	sb->volume_serial = cpu_to_le32(get_volume_serial());
	sb->version.major = 1;
	sb->version.minor = 0;
	sb->volume_state = cpu_to_le16(0);
	sb->sector_bits = get_sector_bits();
	sb->spc_bits = get_spc_bits();
	sb->fat_count = 1;
	sb->drive_no = 0x80;
	sb->allocated_percent = 0;
	sb->boot_signature = cpu_to_le16(0xaa55);
	debugf("\ninit_sb, exfat boot sector: \n");
	debugf("   vol_size  %llu\n", get_volume_size());
	debugf("   start_sec %llu\n", get_first_sector());
	debugf("   sector count %llu\n", get_volume_size()/get_sector_size());
	debugf("   fat_start %u\n   fat_secs %u\n",
			EXFAT2CPU32(sb->fat_sector_start), EXFAT2CPU32(sb->fat_sector_count));
	debugf("   cl_size %d\n   cl_count %u\n   cl_heap_start %d\n   root_cl %d\n",
			get_cluster_size(), clusters_max,
			EXFAT2CPU32(sb->cluster_sector_start),
			EXFAT2CPU32(sb->rootdir_cluster));
	debugf("   sec_bits %d\n   spc_bits %d\n   fat_count %d\n\n",
			sb->sector_bits, sb->spc_bits, sb->fat_count);
}

static int vbr_write(exfat_boot_sector * bs, __u64 start)
{
	struct exfat_super_block sb;
	unsigned long sec_size = 1 << get_sector_bits();
	__u32 checksum;
	__u32* sector = exfat_malloc_aligned(ARCH_DMA_MINALIGN, sec_size);
	size_t i;

	if (sector == NULL)
	{
		debugf("failed to allocate sector-sized block of memory\n");
		return 1;
	}

	init_sb(&sb);
	__u32 s = (__u32)(start/sec_size);
	if (exfat_disk_write(s, 1, &sb)  < 0) {
		exfat_mfree(sector);
		debugf("failed to write super block sector\n");
		return 1;
	}
	checksum = exfat_vbr_start_checksum(&sb, sizeof(struct exfat_super_block));

	s++;
	memset(sector, 0, sec_size);
	sector[sec_size / sizeof(sector[0]) - 1] = cpu_to_le32(0xaa550000);
	for (i = 0; i < 8; i++, s++)
	{
		if (exfat_disk_write(s, 1, sector) < 0) {
			exfat_mfree(sector);
			debugf("failed to write a sector with boot signature\n");
			return 1;
		}
		checksum = exfat_vbr_add_checksum(sector, sec_size, checksum);
	}

	memset(sector, 0, sec_size);
	for (i = 0; i < 2; i++, s++)
	{
		if (exfat_disk_write(s, 1, sector) < 0) {
			exfat_mfree(sector);
			debugf("failed to write an empty sector\n");
			return 1;
		}
		checksum = exfat_vbr_add_checksum(sector, sec_size, checksum);
	}

	for (i = 0; i < sec_size / sizeof(sector[0]); i++)
		sector[i] = cpu_to_le32(checksum);

	if (exfat_disk_write(s, 1, sector) < 0) {
		exfat_mfree(sector);
		debugf("failed to write checksum sector\n");
		return 1;
	}

	exfat_mfree(sector);
	return 0;
}


static __u32 fat_table_alignment(void)
{
	return (__u32) 128 * get_sector_size();
}

static __u32 fat_table_size(void)
{
	return get_volume_size() / get_cluster_size() * sizeof(__u32);
}


static int fat_table_write(exfat_boot_sector * bs, __u64 start)
{
	__u32 c = 0;
	__u32  s, end, idx;
	__u32 sec_size = 1 << get_sector_bits();
	__u32* sector = exfat_malloc_aligned(ARCH_DMA_MINALIGN, sec_size);

	if (sector == NULL)
	{
		debugf("failed to allocate sector-sized block of memory\n");
		return 1;
	}
	memset(sector, 0, sec_size);
	sector[0] = cpu_to_le32(0xfffffff8);   /* media type */
	sector[1] = cpu_to_le32(0xffffffff);   /* some weird constant */

	c = idx = 2;
	s = (__u32)(start/sec_size);
	end = c + DIV_ROUND_UP(cbm.get_size(), get_cluster_size());
	while (c < end) {
		if (idx >= (sec_size/EXFAT_FAT_ENTRY_SIZE)) {
			if (exfat_disk_write(s, 1, sector) < 0) {
				exfat_mfree(sector);
				debugf("failed to write fat entry sector: %u\n", s);
				return 1;
			}
			s++;
			memset(sector, 0, sec_size);
			idx = 0;
		}
		c++;
		if (c==end)
			sector[idx++] = cpu_to_le32(EXFAT_CLUSTER_END);
		else
			sector[idx++] = c;
	}

	end = c + DIV_ROUND_UP(uct.get_size(),  get_cluster_size());
	while (c < end) {
		if (idx >= (sec_size/EXFAT_FAT_ENTRY_SIZE)) {
			if (exfat_disk_write(s, 1, sector) < 0) {
				exfat_mfree(sector);
				debugf("failed to write fat entry sector: %u\n", s);
				return 1;
			}
			s++;
			memset(sector, 0, sec_size);
			idx = 0;
		}
		c++;
		if (c==end)
			sector[idx++] = cpu_to_le32(EXFAT_CLUSTER_END);
		else
			sector[idx++] = c;
	}

	end = c + DIV_ROUND_UP(rootdir.get_size(), get_cluster_size());
	while (c < end) {
		if (idx >= (sec_size/EXFAT_FAT_ENTRY_SIZE)) {
			if (exfat_disk_write(s, 1, sector) < 0) {
				exfat_mfree(sector);
				debugf("failed to write fat entry sector: %u\n", s);
				return 1;
			}
			s++;
			memset(sector, 0, sec_size);
			idx = 0;
		}
		c++;
		if (c==end)
			sector[idx++] = cpu_to_le32(EXFAT_CLUSTER_END);
		else
			sector[idx++] = c;
	}

	if (exfat_disk_write(s, 1, sector) < 0) {
		exfat_mfree(sector);
		debugf("failed to write fat entry sector: %u\n", s);
		return 1;
	}
	exfat_mfree(sector);

	return 0;
}


static __u32 cbm_alignment(void)
{
	return get_cluster_size();
}

static __u32 cbm_size(void)
{
	return DIV_ROUND_UP(
			(get_volume_size() - get_position(&cbm)) / get_cluster_size(),
			CHAR_BIT);
}

static int cbm_write(exfat_boot_sector * bs, __u64 start)
{
	__u32 allocated_clusters =
			DIV_ROUND_UP(cbm.get_size(), get_cluster_size()) +
			DIV_ROUND_UP(uct.get_size(), get_cluster_size()) +
			DIV_ROUND_UP(rootdir.get_size(), get_cluster_size());
	__u32 rem_bytes, bytes, bits;
	__u32 i = 0;
	__u32 s, sec_size = 1 << get_sector_bits();
	__u8 * sector = exfat_malloc_aligned(ARCH_DMA_MINALIGN, sec_size);

	if (sector == NULL)
	{
		debugf("failed to allocate sector-sized block of memory\n");
		return 1;
	}

	memset(sector, 0xff, sec_size);
	bits = 0;
	s = (__u32)(start/sec_size);
	while ( i < allocated_clusters) {
		rem_bytes =  (allocated_clusters - i)/CHAR_BIT;
		bytes = (rem_bytes > sec_size) ? sec_size : rem_bytes;
		if (bytes < sec_size) {
			bits = allocated_clusters%CHAR_BIT;
			memset(sector+bytes, 0, sec_size-bytes);
			if (bits > 0) {
				sector[bytes] |= (1<<bits)-1;
			}
		}
		if (exfat_disk_write(s, 1, sector) < 0) {
			exfat_mfree(sector);
			debugf("failed to write bitmap  sector: %u\n", s);
			return 1;
		}
		s++;
		i += bytes*CHAR_BIT + bits;
	}
	exfat_mfree(sector);
	return 0;
}


static __u32 uct_alignment(void)
{
	return get_cluster_size();
}

static __u32 uct_size(void)
{
	return sizeof(upcase_table);
}

static int uct_write(exfat_boot_sector * bs, __u64 start)
{
	__u32  i = 0, size = sizeof(upcase_table);
	__u32 s, n, sec_size = 1 << get_sector_bits();
	__u8 * sector = exfat_malloc_aligned(ARCH_DMA_MINALIGN, sec_size);
	__u8 * ptr = upcase_table;

	if (sector == NULL)
	{
		debugf("failed to allocate sector-sized block of memory.\n");
		return 1;
	}
	memset(sector, 0, sec_size);

	s = (__u32)(start/sec_size);
	n = size/sec_size;
	if (exfat_disk_write(s, n, ptr) < 0) {
		exfat_mfree(sector);
		debugf("failed to write upcase table sector: %u\n", s);
		return 1;
	}
	i += n*sec_size;
	if ((size-i) > 0) {
		s += n;
		ptr += n*sec_size;
		memcpy(sector, ptr, size-i);
		if (exfat_disk_write(s, 1, sector) < 0) {
			exfat_mfree(sector);
			debugf("failed to write upcase table sector: %u\n", s);
			return 1;
		}
	}
	exfat_mfree(sector);
	return 0;
}


static __u32 rootdir_alignment(void)
{
	return get_cluster_size();
}

static __u32 rootdir_size(void)
{
	return get_cluster_size();
}

static void init_label_entry(exfat_entry_label* label_entry)
{
	memset(label_entry, 0, sizeof(exfat_entry_label));
	label_entry->entry_type = EXFAT_DTYPE_LABLE | EXFAT_DTYPE_USED;

	return;
}

static void init_bitmap_entry(exfat_bitmap_entry* bitmap_entry)
{
	memset(bitmap_entry, 0, sizeof(exfat_bitmap_entry));
	bitmap_entry->entry_type =  EXFAT_DTYPE_BM | EXFAT_DTYPE_USED;
	bitmap_entry->start_clu  = cpu_to_le32(EXFAT_FIRST_DATA_CLUSTER);
	bitmap_entry->data_len  = cpu_to_le64(cbm.get_size());
}

static void init_upcase_entry(exfat_entry_upcase* upcase_entry)
{
	size_t i;
	__u32 sum = 0;

	for (i = 0; i < sizeof(upcase_table); i++)
		sum = ((sum << 31) | (sum >> 1)) + upcase_table[i];

	memset(upcase_entry, 0, sizeof(struct exfat_entry_upcase));
	upcase_entry->entry_type = EXFAT_DTYPE_UC | EXFAT_DTYPE_USED;
	upcase_entry->checksum = cpu_to_le32(sum);
	upcase_entry->start_cluster = cpu_to_le32(
			(get_position(&uct) - get_position(&cbm)) / get_cluster_size() +
			EXFAT_FIRST_DATA_CLUSTER);
	upcase_entry->size = cpu_to_le64(sizeof(upcase_table));
}

static int rootdir_write(exfat_boot_sector * bs, __u64 start)
{
	exfat_entry_label *label_entry;
	exfat_bitmap_entry *bitmap_entry;
	exfat_entry_upcase *upcase_entry;
	__u32 s, sec_size = 1 << get_sector_bits();
	__u8 * sector = exfat_malloc_aligned(ARCH_DMA_MINALIGN, sec_size);

	if (sector == NULL)
	{
		debugf("failed to allocate sector-sized block of memory.\n");
		return 1;
	}
	memset(sector, 0, sec_size);

	label_entry = (exfat_entry_label *)sector;
	bitmap_entry = (exfat_bitmap_entry *)(sector+sizeof(exfat_entry_label));
	upcase_entry = (exfat_entry_upcase *)(bitmap_entry+1);

	init_label_entry(label_entry);
	init_bitmap_entry(bitmap_entry);
	init_upcase_entry(upcase_entry);

	s = (__u32)(start/sec_size);
	if (exfat_disk_write(s, 1, sector) < 0) {
		exfat_mfree(sector);
		debugf("failed to write root directory sector: %u\n", s);
		return 1;
	}
	exfat_mfree(sector);

	return 0;
}


static int init_objects()
{
	vbr.get_alignment = vbr_alignment;
	vbr.get_size = vbr_size;
	vbr.write = vbr_write;

	fat.get_alignment = fat_table_alignment;
	fat.get_size = fat_table_size;
	fat.write = fat_table_write;

	cbm.get_alignment = cbm_alignment;
	cbm.get_size = cbm_size;
	cbm.write = cbm_write;

	uct.get_alignment = uct_alignment;
	uct.get_size = uct_size;
	uct.write = uct_write;

	rootdir.get_alignment = rootdir_alignment;
	rootdir.get_size = rootdir_size;
	rootdir.write = rootdir_write;
}


static int check_size(__u64 volume_size)
{
	const struct fs_object** pp;
	__u64 position = 0;

	for (pp = objects; *pp; pp++)
	{
		position = ROUND_UP(position, (*pp)->get_alignment());
		position += (*pp)->get_size();
	}

	if (position > volume_size)
	{
		debugf("Volume size (%llu) if too small for minimum size (%llu) of exFAT file system.\n", volume_size,  position);
		return 1;
	}

	return 0;

}

static int erase(exfat_boot_sector * bs)
{
	const struct fs_object** pp;
	__u32 s, n, total, sec_size = 1 << get_sector_bits();
	__u64 position = 0;
	unsigned long  block_size = 1024 * sec_size;
	void* block = exfat_malloc_aligned(ARCH_DMA_MINALIGN, block_size);

	if (block == NULL)
	{
		debugf("failed to allocate erase block of %u bytes\n", block_size);
		return 1;
	}
	memset(block, 0, block_size);

	for (pp = objects; *pp; pp++)
	{
		position = ROUND_UP(position, (*pp)->get_alignment());
		position += (*pp)->get_size();
	}

	position = ROUND_UP(position, sec_size);
	n =  (__u32)(block_size/sec_size);
	total = (__u32)(position/sec_size);
	for (s = 0; s < total; s+=n) {
		n = (total-s) > n ? n : (total-s);
		if (exfat_disk_write(s, n, block) < 0)
		{
			debugf("failed to write sectors. start=%u, n=%u\n", s, n);
			exfat_mfree(block);
			return 1;
		}
	}
	debugf("done......\n");
	exfat_mfree(block);
	return 0;
}

static int create(exfat_boot_sector * bs)
{
	const struct fs_object** pp;
	__u64 position = 0;
	for (pp = objects; *pp; pp++)
	{
		position = ROUND_UP(position, (*pp)->get_alignment());
		if ((*pp)->write(bs, position) != 0){
			debugf("failed to write obj: %p, position: %llu\n", *pp, position);
			return 1;
		}
		position += (*pp)->get_size();
	}
	return 0;
}

int mkfs(exfat_boot_sector * bs, __u64 volume_size)
{
	if (check_size(volume_size) != 0)
		return 1;

	debugf("Creating... \n");
	if (erase(bs)!= 0)
		return 1;
	if (create(bs)!= 0)
		return 1;
	debugf("Done... \n");

	return 0;
}


static int setup_spc_bits(int sector_bits, int user_defined, __u64 volume_size)
{
	int i;

	if (user_defined != -1)
	{
		__u32 cluster_size = 1 << sector_bits << user_defined;
		if (volume_size / cluster_size > EXFAT_LAST_DATA_CLUSTER)
		{
			debugf("cluster size %u is too small for volume size: %llu\n", cluster_size, volume_size);
		}
		else {
			return user_defined;
		}
	}

	if (volume_size < 256ull * 1024 * 1024)
		return MAX(0, 12 - sector_bits);	/* 4 KB */
	if (volume_size < 32ull * 1024 * 1024 * 1024)
		return MAX(0, 15 - sector_bits);	/* 32 KB */

	for (i = 17; ; i++)						/* 128 KB or more */
		if (DIV_ROUND_UP(volume_size, 1 << i) <= EXFAT_LAST_DATA_CLUSTER)
			return MAX(0, i - sector_bits);
}


static int setup(exfat_boot_sector * bs, int sector_bits, int spc_bits,
		const char* volume_label, __u32 volume_serial,
		__u64 first_sector)
{
	param.sector_bits = sector_bits;
	param.first_sector = first_sector;
	param.volume_size = bs->vol_len * (1<<sector_bits);

	param.spc_bits = setup_spc_bits(sector_bits, spc_bits, param.volume_size);
	if (param.spc_bits == -1) {
		param.spc_bits = 6;
	}
	if ((param.spc_bits + sector_bits) > 25) {
		debugf("Cluster size is too large: %d. It should not be larger than 32MB.\n", 1<<(param.spc_bits + sector_bits));
		param.spc_bits = 6;
	}
	memset(param.volume_label, 0, (EXFAT_ENAME_MAX + 1) * sizeof(__u16));
	param.volume_serial = bs->vol_serial;
	debugf("sec_bits:%d, spc_bits:%d, first_sec: %llu, vol_size: %llu\n", sector_bits, param.spc_bits, first_sector, param.volume_size);
	return mkfs(bs,  param.volume_size);
}


int exfat_format()
{
	exfat_boot_sector bs;
	int opt;
	int sec_bits = -1;
	int spc_bits = -1;
	const char* volume_label = NULL;
	__u32  volume_serial = 0;
	__u64  first_sector = 0;

	if (read_exfat_bootsec(&bs)) {
		debugf("Error: reading boot sector\n");
		return FSFATAL;
	}

	debugf("Start format .... .\n");

	init_objects();

	sec_bits = bs.sector_size_bits;
	first_sector = bs.part_off;
	spc_bits = -1;
	if (setup(&bs, sec_bits, spc_bits, volume_label, volume_serial,
				first_sector) != 0){
		debugf("Error: setup exfat failed.\n");
		return FSFATAL;
	}

	printf("File system created successfully.\n");
	return 0;
}

