#include <common.h>
#include <command.h>
#include <linux/types.h>
#include <part.h>

#include <sprd_common_rw.h>
#include <linux/sizes.h>
#include <malloc.h>
#include <sprd_ufs.h>

extern int write_attribute(enum attr_id idn, uint8_t *value, uint8_t selector);
extern int read_attribute(enum attr_id idn, uint8_t *ret_value, uint8_t selector);

extern int read_flag(enum flags_id idn, uint8_t *flags_ret);
extern int set_flag(enum flags_id idn, uint8_t *flags_ret);


int test_ufs_repart(int argc, char * argv[])
{
	disk_partition_t *partition_info = NULL;
	int part_num = 0;
	int32_t blksz = 0;
	uint32_t lbas_per_m = 0;
	lbaint_t partition_start_lba = 0;
	int i = 0;
	uint32_t partition_size_m = 0;
	int arg_id = 0;
	int ret = 0;
	
	if (0 != argc % 2) {
		errorf("illegal arguement number\n");
		return CMD_RET_USAGE;
	}

	part_num = argc / 2;

	partition_info = malloc(sizeof(disk_partition_t) * part_num);
	if (NULL == partition_info) {
		errorf("No space to store partition_info!\n");
		return CMD_RET_FAILURE;
	}

	blksz = common_get_lba_size();
	if (-1 == blksz) {
		errorf("can not get lba size!\n");
		free(partition_info);
		return CMD_RET_FAILURE;
	}
	lbas_per_m = SZ_1M / blksz;

	partition_start_lba = SZ_1M / blksz;

	for (i = 0; i < part_num; i++) {
		arg_id = i * 2;
		partition_info[i].blksz = (ulong)blksz;
		strcpy(partition_info[i].type, "U-boot");	/*unuseful */
		
		partition_size_m = (uint32_t) simple_strtoul(argv[arg_id + 1], NULL, 10);
		partition_info[i].size = (lbaint_t) partition_size_m * lbas_per_m;
		strcpy(partition_info[i].name, argv[arg_id]);
		partition_info[i].start = partition_start_lba;
		partition_start_lba += partition_info[i].size;

		debugf("partition name:%s,partition_size:0x%lx,partiton_start:0x%lx,\n", partition_info[i].name, partition_info[i].size,
		       partition_info[i].start);
	}

	ret = common_repartition(partition_info, part_num);
	debugf("Common repartition for UFS result=%d\n", ret);
	free(partition_info);

	if (0 == ret)
		return 0;
	else
		return CMD_RET_FAILURE;
}


int test_ufs_setattr(int argc, char * argv[])
{
	int idn = 0;
	uint32_t val = 0;
	int ret =0;

	idn = (int) simple_strtoul(argv[0], NULL, 16);
	val = (uint32_t)simple_strtoul(argv[1], NULL, 16);
	val = cpu_to_be32(val);
	ret = write_attribute((enum attr_id)idn, (uint8_t *)&val, 0);
	if (UFS_SUCCESS != ret) {
		errorf("UFS write_attribute(0x%x) fail!ret=%d\n", idn, ret);
		return CMD_RET_FAILURE;
	}
	debugf("UFS write_attribute(0x%x) OK\n", idn);
	return 0;
}

int test_ufs_getattr(int argc, char * argv[])
{
	int idn = 0;
	uint32_t val = 0;
	int ret =0;

	idn = (int) simple_strtoul(argv[0], NULL, 16);

	ret = read_attribute((enum attr_id)idn, (uint8_t *)&val, 0);
	if (UFS_SUCCESS != ret) {
		errorf("UFS read_attribute(0x%x) fail!ret=%d\n", idn, ret);
		return CMD_RET_FAILURE;
	}

	val = cpu_to_be32(val);
	debugf("read attribute value=0x%x\n", val);
	return 0;
}

int test_ufs_setflag(int argc, char * argv[])
{
	int idn = 0;
	int ret =0;
	uint8_t flags_ret_val;

	idn = (int) simple_strtoul(argv[0], NULL, 16);

	ret = set_flag((enum flags_id)idn,  &flags_ret_val);
	if (UFS_SUCCESS != ret) {
		errorf("UFS set_flag(0x%x) fail!ret=%d\n", idn, ret);
		return CMD_RET_FAILURE;
	}
	debugf("UFS set_flag(0x%x) OK\n", idn);
	return 0;
}

int test_ufs_getflag(int argc, char * argv[])
{
	int idn = 0;
	uint32_t val = 0;
	int ret =0;
	uint8_t flags_ret_val;

	idn = (int) simple_strtoul(argv[0], NULL, 16);

	ret = read_flag((enum flags_id)idn, &flags_ret_val);
	if (UFS_SUCCESS != ret) {
		errorf("UFS read_flag(0x%x) fail!ret=%d\n", idn, ret);
		return CMD_RET_FAILURE;
	}

	debugf("read flag value=0x%x\n", flags_ret_val);
	return 0;
}


int test_ufs_read(int argc, char * argv[])
{
	int ret = 0;
	uint64_t size = 0;
	uint64_t offset = 0;
	int i =0;
	char* buf = malloc(SZ_32K);
	if (NULL == buf) {
		errorf("Malloc for read buf fail\n");
		return CMD_RET_FAILURE;
	}
	memset(buf, 0, SZ_32K);

	size = (uint64_t) simple_strtoul(argv[1], NULL, 16);
	if (size > SZ_32K) {
		errorf("Read size cannot over 32KB!\n");
		goto fail;
	}
	offset = (uint64_t)simple_strtoul(argv[2], NULL, 16);

	debugf("read part(%s), size=0x%llx, offset=0x%llx\n", argv[0], size, offset);
	ret = common_raw_read(argv[0], size, offset, buf);
	if (-1 == ret) {
		errorf("common_raw_read fail!\n");
		goto fail;
	}

	debugf("Read result:");
	for (i = 0; i < size; i += 4) {
		if (0 == i % 16)
			printf("\n");
		printf("%08x ", *(uint32_t *)(buf + i));
	}
	printf("\n");

	free(buf);
	return 0;
fail:
	free(buf);
	return CMD_RET_FAILURE;
}

int test_ufs_write(int argc, char * argv[])
{
	int ret = 0;
	uint64_t size = 0;
	uint64_t offset = 0;
	int i =0;
	int value = 0;
	char* buf = malloc(SZ_32K);
	if (NULL == buf) {
		errorf("Malloc for write buf fail\n");
		return CMD_RET_FAILURE;
	}

	size = (uint64_t) simple_strtoul(argv[1], NULL, 16);
	if (size > SZ_32K) {
		errorf("Write size cannot over 32KB!\n");
		goto fail;
	}
	offset = (uint64_t)simple_strtoul(argv[2], NULL, 16);

	value = (int)simple_strtoul(argv[3], NULL, 16);
	memset(buf, value, size);

	debugf("write part(%s), size=0x%llx, offset=0x%llx, value=0x%x\n", argv[0], size, offset, value);
	ret = common_raw_write(argv[0], size, 0, offset, buf);
	if (-1 == ret) {
		errorf("common_raw_write fail!\n");
		goto fail;
	}
	debugf("Write OK\n");

	memset(buf, 0, SZ_32K);
	free(buf);
	return 0;
fail:
	free(buf);
	return CMD_RET_FAILURE;

}

int test_ufs_comp(int argc, char * argv[])
{
	int ret = 0;
	uint64_t size = 0;
	int value = 0;
	char* write_buf = (char *)0x6000000;
	char* read_buf = (char *)0x7000000;

	size = (uint64_t) simple_strtoul(argv[1], NULL, 16);

	value = (uint64_t)simple_strtoul(argv[2], NULL, 16);

	memset(write_buf, value, size);

	debugf("write compare part(%s), size=0x%llx, value=0x%x\n", argv[0], size, value);
	ret = common_raw_write(argv[0], size, 0, 0, write_buf);
	if (-1 == ret) {
		errorf("common_raw_write fail!\n");
		goto fail;
	}
	debugf("Comp write OK\n");

	ret = common_raw_read(argv[0], size, 0, read_buf);
	if (-1 == ret) {
		errorf("common_raw_read fail!\n");
		goto fail;
	}
	debugf("Comp read OK\n");

	ret = memcmp(write_buf, read_buf, size);
	if (0 == ret)
		debugf("Write and read compare same! \n");
	else
		debugf("Write and read compare diff! \n");

	return 0;
fail:
	return CMD_RET_FAILURE;

}


int test_ufs_erase(int argc, char * argv[])
{
	int ret = 0;
	uint64_t size = 0;
	uint64_t offset = 0;

	size = (uint64_t) simple_strtoul(argv[1], NULL, 16);
	offset = (uint64_t)simple_strtoul(argv[2], NULL, 16);

	debugf("erase part(%s), size=0x%llx, offset=0x%llx\n", argv[0], size, offset);
	ret = common_raw_erase(argv[0], size, offset);
	if (-1 == ret) {
		errorf("common_raw_erase fail!\n");
		return CMD_RET_FAILURE;
	}
	return 0;
}

int test_ufs_raw_read(int argc, char * argv[])
{
	int ret = 0;
	int id = 0;
	uint64_t size = 0;
	uint64_t offset = 0;
	int i =0;
	block_dev_desc_t *dev_desc;
	char* buf = malloc(SZ_32K);
	if (NULL == buf) {
		errorf("Malloc for raw read buf fail\n");
		return CMD_RET_FAILURE;
	}
	memset(buf, 1, SZ_32K);

	id = (uint64_t) simple_strtoul(argv[0], NULL, 16);

	dev_desc = get_dev("ufs", id);
	if (NULL == dev_desc)
		goto fail;

	size = (uint64_t) simple_strtoul(argv[1], NULL, 16);
	if (size > 8) {
		errorf("Raw read size cannot over 8!\n");
		goto fail;
	}

	offset = (uint64_t)simple_strtoul(argv[2], NULL, 16);

	ret = dev_desc->block_read(dev_desc->dev, offset, size, buf);
	if (size != ret) {
		errorf("ufs raw read fail, size=0x%x, offset=0x%x!\n", size, offset);
		goto fail;
	}

	debugf("Raw read result:");
	size = size << dev_desc->log2blksz;

	for (i = 0; i < size; i += 4) {
		if (0 == i % 16)
			printf("\n");
		printf("%08x ", *(uint32_t *)(buf + i));
	}
	printf("\n");

	free(buf);
	return 0;
fail:
	free(buf);
	return CMD_RET_FAILURE;

}

int test_ufs_raw_write(int argc, char * argv[])
{
	int ret = 0;
	int id = 0;
	uint64_t size = 0;
	uint64_t offset = 0;
	int value = 0;
	int i =0;
	block_dev_desc_t *dev_desc;
	char* buf = malloc(SZ_32K);
	if (NULL == buf) {
		errorf("Malloc for raw write buf fail\n");
		return CMD_RET_FAILURE;
	}

	id = (int) simple_strtoul(argv[0], NULL, 16);

	dev_desc = get_dev("ufs", id);
	if (NULL == dev_desc)
		goto fail;

	size = (uint64_t) simple_strtoul(argv[1], NULL, 16);
	if (size > 8) {
		errorf("Raw read size cannot over 8!\n");
		goto fail;
	}

	offset = (uint64_t)simple_strtoul(argv[2], NULL, 16);

	value = (int)simple_strtoul(argv[3], NULL, 16);
	memset(buf, value, size << dev_desc->log2blksz);

	debugf("raw write lun(%d), offset=0x%x, size=0x%x\n", dev_desc->dev, offset, size);
	ret = dev_desc->block_write(dev_desc->dev, offset, size, buf);
	if (size != ret) {
		errorf("ufs raw write fail, size=0x%x, offset=0x%x!\n", size, offset);
		return CMD_RET_FAILURE;
	}
	debugf("Raw write OK\n");

	memset(buf, 0, SZ_32K);
	free(buf);
	return 0;
fail:
	free(buf);
	return CMD_RET_FAILURE;

}

int test_ufs_raw_erase(int argc, char * argv[])
{
	int ret = 0;
	uint64_t size = 0;
	uint64_t offset = 0;
	int id = 0;
	block_dev_desc_t *dev_desc;

	id = (int) simple_strtoul(argv[0], NULL, 16);
	dev_desc = get_dev("ufs", id);
	if (NULL == dev_desc)
		return CMD_RET_FAILURE;

	size = (uint64_t) simple_strtoul(argv[1], NULL, 16);
	offset = (uint64_t)simple_strtoul(argv[2], NULL, 16);

	debugf("erase part(%s), size=0x%llx, offset=0x%llx\n", argv[0], size, offset);
	ret = dev_desc->block_erase(dev_desc->dev, offset, size);
	if (size != ret) {
		errorf("common_raw_erase fail!\n");
		return CMD_RET_FAILURE;
	}
	return 0;

}

int test_ufs_bufread(int argc, char * argv[])
{
	int ret = 0;
	uint64_t size = 0;
	uint64_t offset = 0;
	char* buf = NULL;

	offset = (uint64_t) simple_strtoul(argv[1], NULL, 16);

	buf = (char *)simple_strtoul(argv[2], NULL, 16);

	size = (uint64_t)simple_strtoul(argv[3], NULL, 16);

	debugf("read part(%s), size=0x%llx, offset=0x%llx, to buffer 0x%lx\n", argv[0], size, offset, buf);
	ret = common_raw_read(argv[0], size, offset, buf);
	if (-1 == ret) {
		errorf("common_raw_read fail!\n");
		return CMD_RET_FAILURE;
	}
	debugf("Buffer read OK\n");
	return 0;
}

int test_ufs_bufwrite(int argc, char * argv[])
{
	int ret = 0;
	uint64_t size = 0;
	uint64_t offset = 0;
	int i =0;
	char* buf = NULL;

	offset = (uint64_t) simple_strtoul(argv[1], NULL, 16);

	buf = (char *)simple_strtoul(argv[2], NULL, 16);

	size = (uint64_t)simple_strtoul(argv[3], NULL, 16);

	debugf("write part(%s), size=0x%llx, offset=0x%llx, from buffer 0x%lx\n", argv[0], size, offset, buf);
	ret = common_raw_write(argv[0], size, 0, offset, buf);
	if (-1 == ret) {
		errorf("common_raw_write fail!\n");
		return CMD_RET_FAILURE;
	}

	debugf("Buffer write OK\n");
	return 0;
}

int test_ufs_backwrite(int argc, char * argv[])
{
	int ret = 0;
	uint32_t size = 0;
	uint32_t offset = 0;
	int i =0;
	char * buf = NULL;
	int wait = 0;

	offset = (uint32_t) simple_strtoul(argv[1], NULL, 16);
	buf = (char *)simple_strtoul(argv[2], NULL, 16);
	size = (uint32_t)simple_strtoul(argv[3], NULL, 16);
	wait = (int)simple_strtoul(argv[4], NULL, 16);

	debugf("backstage write part(%s), size=0x%x, offset=0x%x, from buffer 0x%lx\n", argv[0], size, offset, buf);
	ret = common_write_backstage(argv[0], size, offset, buf);
	if (-1 == ret) {
		errorf("common_write_backstage fail!\n");
		return CMD_RET_FAILURE;
	}

	if (0 != wait)
		mdelay(wait);

	ret = common_query_backstage(argv[0], size, buf);
	if (-1 == ret) {
		errorf("common_query_backstage fail!\n");
		return CMD_RET_FAILURE;
	}

	debugf("Backstage write OK\n");
	return 0;
}

extern uint32_t fatal_err;

int test_ufs_stress(int argc, char * argv[])
{
	int ret = 0;
	uint32_t num = 0;
	int id = 0;
	block_dev_desc_t *dev_desc;
	lbaint_t blk_todo = 0;
	lbaint_t blk = 0;
	lbaint_t buf_in_blk = 0;
	lbaint_t offset = 0;
	char * buf = NULL;
	uint64_t count = 0;

	num = (uint32_t) simple_strtoul(argv[1], NULL, 16);

	buf = malloc(SZ_512K);
	if (NULL == buf) {
		errorf("Malloc for raw read buf fail\n");
		return CMD_RET_FAILURE;
	}
	memset(buf, 0x23, SZ_512K);

	if (0 == strcmp(argv[0], "seq")) {
		while (1) {
			dev_desc = get_dev("ufs", id);
			if (NULL == dev_desc)
				goto fail;
			blk_todo = dev_desc->lba;
			buf_in_blk = SZ_512K >> dev_desc->log2blksz;
			offset = 0;
			while (0 != blk_todo) {
				blk = (buf_in_blk < blk_todo) ? buf_in_blk : blk_todo;

				ret = dev_desc->block_write(dev_desc->dev, offset, blk, buf);
				if (blk != ret) {
					errorf("ufs stress write fail, blk=0x%x, offset=0x%x!\n", blk, offset);
					goto fail;
				}

				ret = dev_desc->block_read(dev_desc->dev, offset, blk, buf);
				if (blk != ret) {
					errorf("ufs stress read fail, blk=0x%x, offset=0x%x!\n", blk, offset);
					goto fail;
				}
				blk_todo -= blk;
				offset += blk;

				count++;
				debugf("c:%llx,e:%x\n", count, fatal_err);

				if (1 == num)
					break;
				else if (num > 0)
					num--;
			}

			if (1 == num)
				break;
			id++;
			id = id % 3;
		}
	}

	/*TODO*/
	if (0 == strcmp(argv[0], "random")) {
	}

	debugf("UFS stress over!!\n");
	free(buf);
	return 0;
fail:
	free(buf);
	return CMD_RET_FAILURE;
}


int do_ufs(cmd_tbl_t *cmdtp, int flag, int argc, char *const argv[])
{

	argc -= 2;

	if (0 == strcmp(argv[1], "repart")) {
		debugf("enter repart command\n");
		return test_ufs_repart(argc, &argv[2]);
	}

	if (0 == strcmp(argv[1], "read"))
		return test_ufs_read(argc, &argv[2]);

	if (0 == strcmp(argv[1], "write"))
		return test_ufs_write(argc, &argv[2]);

	if (0 == strcmp(argv[1], "erase"))
		return test_ufs_erase(argc, &argv[2]);

	if (0 == strcmp(argv[1], "rawread"))
		return test_ufs_raw_read(argc, &argv[2]);

	if (0 == strcmp(argv[1], "rawwrite"))
		return test_ufs_raw_write(argc, &argv[2]);

	if (0 == strcmp(argv[1], "rawerase"))
		return test_ufs_raw_erase(argc, &argv[2]);

	if (0 == strcmp(argv[1], "bufread"))
		return test_ufs_bufread(argc, &argv[2]);

	if (0 == strcmp(argv[1], "bufwrite"))
		return test_ufs_bufwrite(argc, &argv[2]);

	if (0 == strcmp(argv[1], "backwrite"))
		return test_ufs_backwrite(argc, &argv[2]);

	if (0 == strcmp(argv[1], "setattr"))
		return test_ufs_setattr(argc, &argv[2]);

	if (0 == strcmp(argv[1], "getattr"))
		return test_ufs_getattr(argc, &argv[2]);

	if (0 == strcmp(argv[1], "setflag"))
		return test_ufs_setflag(argc, &argv[2]);

	if (0 == strcmp(argv[1], "getflag"))
		return test_ufs_getflag(argc, &argv[2]);

	if (0 == strcmp(argv[1], "stress"))
		return test_ufs_stress(argc, &argv[2]);

	if (0 == strcmp(argv[1], "comp"))
		return test_ufs_comp(argc, &argv[2]);

	return CMD_RET_USAGE;
}


U_BOOT_CMD(
	ufs, CONFIG_SYS_MAXARGS, 1, do_ufs,
	"ufs test commands\n",
	"ufs repart [part] [size(in mega)]..."
		" - Repartition UFS device, support no more than 7 partitions\n"
	"ufs read [part] [size(byte)] [offset(byte)]"
		" - Read content in a specific partition\n"
	"ufs write  [part] [size(byte)] [offset(byte)] [value]"
		" - Fill a specific part in a partition with same value\n"
	"ufs erase [part] [size(byte)] [offset(byte)]"
		" - erase a part of a partition, size=0 means erase whole partition,\
		part=erase_all means erase the whole flash\n"
	"ufs rawread [lun] [size(block)] [offset(block)]"
		" - Directly read a few blocks in a specific LU\n"
	"ufs rawwrite [lun] [size(block)] [offset(block)] [value]"
		" - Directly fill a few blocks with same value in a specific LU\n"
	"ufs rawerase [lun] [size(block)] [offset(block)]"
		" - Directly erase a few blocks in a specific LU\n"
	"ufs bufread [part] [offset] [buf_addr] [buf_size]"
		" - Read part of a partition to the specific buffer\n"
	"ufs bufwrite [part] [offset] [buf_addr] [buf_size]"
		" - Write to a partition with data in the specific buffer\n"
	"ufs backwrite [part] [offset] [buf_addr] [buf_size] [mdelay]"
		" - Write to a partition with data in the specific buffer in backstage way\n"
	"ufs setattr [attr_idn] [value]"
		" - Set a specific UFS attribute\n"
		" - Attention! it's a dangerous action, be careful !\n"
	"ufs getattr [attr_idn]"
		" - Get a specific UFS attribute value\n"
	"ufs stress [seq/random] [number of times]"
		" - ufs device stress test, read and write many times, each time for 512KB\n"
		" - set 0 times means read and write forever, never stop\n"
	"ufs comp [part] [size] [value]"
);

