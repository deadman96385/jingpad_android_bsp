#include <common.h>
#include <stdio_dev.h>
#include <libfdt.h>
#include <fdtdec.h>
#include <inttypes.h>
#include <malloc.h>
static const char MEM_REGION_STR[] = {"memory-region"};
static const char MEM_REGION_AUTO_STR[] = {"sprd,memory-region-auto"};
#if (defined CONFIG_ARM64) || (defined CONFIG_X86)
typedef uint64_t mem_addr_t;
typedef uint64_t mem_size_t;
#define fdt_to_cpu(reg) fdt64_to_cpu(reg)
#define cpu_to_fdt(reg) cpu_to_fdt64(reg)
#else
typedef uint32_t mem_addr_t;
typedef uint32_t mem_size_t;
#define fdt_to_cpu(reg) fdt32_to_cpu(reg)
#define cpu_to_fdt(reg) cpu_to_fdt32(reg)
#endif
#define MAX_MEM_REGION_NUM 32
static char *auto_mem_region_list[MAX_MEM_REGION_NUM];

 int fdt_get_addr_size(const void *fdt, int node, const char *propname,
			mem_addr_t *addrp, mem_size_t *sizep)
{
	const mem_addr_t *addr;
	const mem_size_t *size;

	addr = fdt_getprop(fdt, node, propname, NULL);
	if (addr) {
		if (addrp)
			*addrp = fdt_to_cpu(*addr);
		if (sizep) {
			size = (mem_size_t *)((char *)addr + sizeof(mem_addr_t));
			*sizep = fdt_to_cpu(*size);
		}
		return 0;
	}
	return -1;
}

static int fdt_set_addr_size(const void *fdt, int node, const char *propname,
			mem_addr_t addr, mem_size_t size)
{
	int err;

	addr = cpu_to_fdt(addr);
	err =  fdt_setprop(fdt, node, propname, &addr, sizeof(addr));
	if (err < 0) {
		errorf("cannot set node's reg property(addr)!\n");
		return err;
	}

	size = cpu_to_fdt(size);
	err = fdt_appendprop(fdt, node, propname, &size, sizeof(size));
	if (err < 0) {
		errorf("cannot set node's reg property(size)!\n");
		return err;
	}
	return 0;
}

static int fdt_node_offset_by_name(const void *fdt,  const char *nodename)
{
	int offset;
	char *name;

	for (offset = fdt_next_node(fdt, -1, NULL); offset >= 0;
		offset = fdt_next_node(fdt, offset, NULL)) {
		name = fdt_get_name(fdt, offset, NULL);
		if(0 == strcmp(nodename, name))
			return offset;
	}
	return offset;
}

int check_mem_region_auto(void *fdt, char *name)
{
	int i = 0;

	while((i <= (MAX_MEM_REGION_NUM - 1)) && auto_mem_region_list[i]) {
		if(0 == strcmp(name, auto_mem_region_list[i]))
			return 0;
		i++;
	}
	return -1;
}

int fixup_memory_addr(void *fdt, int offset,
				mem_addr_t addr, mem_size_t *size)
{
	mem_addr_t prev_ddr;
	if(fdt_get_addr_size(fdt, offset, "reg", &prev_ddr, size) < 0) {
		errorf("cannot find reg addr and size.\n" );
		return -1;
	}

	if(fdt_set_addr_size(fdt, offset, "reg", addr, *size) < 0)
		return -1;

	return 0;
}

int move_prev_memory(void *fdt, mem_addr_t offset, char *name)
{
	mem_addr_t addr;
	mem_size_t size;
	int nodeoffset;
	nodeoffset = fdt_node_offset_by_name(fdt, name);
	if(fdt_get_addr_size(fdt, nodeoffset, "reg", &addr, &size) < 0) {
		errorf("cannot find reg addr and size.\n" );
		return -1;
	}
	addr +=  offset;
	if(fdt_set_addr_size(fdt, nodeoffset, "reg", addr, size) <0)
		return -1;
	return 0;
}

int scan_memory_region(void *fdt, int *auto_mem_num)
{
	const uint32_t *phandle = NULL;
	mem_addr_t addr;
	mem_size_t size;
	int nodeoffset;
	int offset;
	int i = -1;
	const char *find_name;
	char *auto_mem_name;
	int find_namelen;

	memset(auto_mem_region_list, '\0', sizeof(auto_mem_region_list));
	for (offset = fdt_next_node(fdt, -1, NULL);
	     offset >= 0;
	     offset = fdt_next_node(fdt, offset, NULL)) {
		if (fdt_get_property(fdt, offset, MEM_REGION_AUTO_STR, NULL)) {
			phandle = fdt_getprop(fdt, offset, MEM_REGION_STR, NULL);
			if (!phandle) {
				errorf("device tree doesn't have %s prop.\n", MEM_REGION_STR);
			} else {
				nodeoffset = fdt_node_offset_by_phandle(fdt, fdt32_to_cpu(*phandle));
				if (nodeoffset < 0) {
					errorf("get nodeoffset error\n");
					goto next;
				}
				if(fdt_get_addr_size(fdt, nodeoffset, "reg", &addr, &size) < 0) {
					errorf("cannot find reg addr and size.\n" );
					goto next;
				}
				/*  record memory region name with MEM_REGION_AUTO_STR property */
				find_name = fdt_get_name(fdt, nodeoffset, &find_namelen);
				auto_mem_name = malloc(find_namelen+1);
				strcpy(auto_mem_name, find_name);
				i++;
				if(i > (MAX_MEM_REGION_NUM - 1)) {
					errorf("auto_mem_region_list out of bounds \n" );
					return -1;
				}
				auto_mem_region_list[i]= auto_mem_name;
			}
		}
next:;
	}
	*auto_mem_num = i+1;
	return 0;
}

int get_dt_end_addr(void *fdt, uchar **addr)
{
	int parentoffset;
	int offset;

	parentoffset =  fdt_path_offset(fdt, "/reserved-memory");
	offset = fdt_first_subnode(fdt, parentoffset);
	if(fdt_get_addr_size(fdt, offset, "reg",  addr, NULL) < 0) {
		errorf("cannot find reg addr and size.\n" );
		return -1;
	}
	return 0;
}

int fdt_fixup_memory_region(void *fdt, int *auto_mem_num_p)
{
	int offset;
	mem_addr_t addr;
	mem_size_t size;
	int str_len;
	int parentoffset;
	char nodename[32];
	mem_addr_t rsvmem_p;
	char *auto_mem_name;
	char *tmp_auto_mem_region_list[MAX_MEM_REGION_NUM];
	int num = -1;
	int auto_mem_num = 0;
	int ret = 0;

	rsvmem_p = DT_ADR;
	memset(tmp_auto_mem_region_list, '\0', sizeof(tmp_auto_mem_region_list));
	ret = scan_memory_region(fdt, &auto_mem_num);
	if (ret < 0)
		goto end;
	if (0 == auto_mem_num) {
		debugf("no auto memory region, no need fixup memory region\n");
		goto end;
	}
	if (NULL != auto_mem_num_p)
		*auto_mem_num_p = auto_mem_num;
	parentoffset =  fdt_path_offset(fdt, "/reserved-memory");
	for (offset = fdt_first_subnode(fdt, parentoffset);
	      offset >= 0; offset = fdt_next_subnode(fdt, offset)) {
		sprintf(nodename, "%s", fdt_get_name(fdt, offset, NULL));
		str_len = strlen(nodename);
		nodename[str_len] = '\0';
		if(fdt_get_addr_size(fdt, offset, "reg", &addr, &size) < 0)
		{
			//debugf("cannot find reg prop, go to next node.\n" );
			goto next;
		}
		if(check_mem_region_auto(fdt, nodename) < 0) {
			//debugf("%s: stable node \n", fdt_get_name(fdt, offset, NULL));
			while (num>= 0) {
				if(addr < rsvmem_p) {
					errorf("prev end addr exceed the current start addr\n");
					ret = -1;
					goto end;
				}
				ret = move_prev_memory(fdt, (addr - rsvmem_p), tmp_auto_mem_region_list[num]);
				if(ret < 0)
					goto end;
				num--;
			}
			rsvmem_p = addr + size;
			memset(tmp_auto_mem_region_list, 0, sizeof(tmp_auto_mem_region_list));
		} else {
			/* the current node is auto */
			addr = rsvmem_p;
			//debugf("%s: auto node \n", fdt_get_name(fdt, offset, NULL));
			if (0 == fixup_memory_addr(fdt, offset, addr, &size) ) {
				rsvmem_p += size;
				auto_mem_name = malloc(str_len+1);
				strcpy(auto_mem_name, nodename);
				num++;
				if (num > MAX_MEM_REGION_NUM) {
					errorf("tmp_auto_mem_region_list out of bounds\n");
					ret = -1;
					goto end;
				}
				tmp_auto_mem_region_list[num]= auto_mem_name;
			}
		}
next:
		offset = fdt_node_offset_by_name(fdt, nodename);
	}
end:
	num = 0;
	while(num <= (MAX_MEM_REGION_NUM -1))
	{
		if(auto_mem_region_list[num] != NULL)
			free(auto_mem_region_list[num]);
		num++;
	}

	num = 0;
	while(num <= (MAX_MEM_REGION_NUM -1))
	{
		if (tmp_auto_mem_region_list[num] != NULL)
			free(tmp_auto_mem_region_list[num]);
		num++;
	}
	return ret;
}

