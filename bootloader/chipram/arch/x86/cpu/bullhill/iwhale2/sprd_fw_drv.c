#include <config.h>
#include <common.h>
#include <sci_types.h>
/* delete  chip_drv_common_io_h */
#include <asm/arch/sprd_reg.h>

#define DDR_CP_BASE_ADDR		(0x80000000)
#define DDR_END_ADDR			(0xFFFFFFFFF)
#define DDR_INFO_IN_MEM			(0xE602B000)

#define FW_MEM_MAX_REGION		32

typedef enum {
	FW_MEM_BIA = 0,
	FW_MEM_AP,
	FW_MEM_CAM,
	FW_MEM_VSP,
	FW_MEM_GPU,
	FW_MEM_PUBPC,
	FW_MEM_WTL_AG,
	FW_MEM_RAM,
	FW_MEM_MAX
} FW_MEM_ARCH;

typedef enum {
	ALL_FORBID = 0,
	SEC_ACCESS,
	NONSEC_ACCESS,
	ALL_ACCESS
} FW_MEM_PROT;

struct fw_mem_cfg {
	FW_MEM_ARCH		fw_mem_arch;
	uint64			fw_mem_addr[32][2];
	uint64			fw_mem_mstid[32][8];
	FW_MEM_PROT		fw_mem_rprot[32];
	FW_MEM_PROT		fw_mem_wprot[32];
};

/* memory firewall register definition */
struct sprd_fw_mem_reg {
	uint32 first_addr;
	uint32 last_addr;
	uint32 mst_id[8];
	uint32 rd_attr;
	uint32 wr_attr;
};
struct fw_mem_cfg fw_cfg = {};

/* DDR info, judge which board of ddr need set fw */
typedef struct section_info
{
	uint32 type;	//reserved
	uint32 start_addr_h;
	uint32 start_addr_l;
	uint32 end_addr_h;
	uint32 end_addr_l;
}section_info_t;

typedef struct ddr_info
{
	uint32 section_num;
	section_info_t sec_info[3];
}ddr_info_t;

static int sprd_fw_get_ddr_info(ddr_info_t *ddr_info)
{
	ddr_info_t * ddr_info_s;
	ddr_info_s = (ddr_info_t *)DDR_INFO_IN_MEM;

	/* ddr has 3 section memory regions, and it is 1.5G*2 board */
	if ((ddr_info_s->section_num == 3) &&
		(ddr_info_s->sec_info[0].end_addr_l == 0x5fffffff)) {
		ddr_info->section_num = 3;
		ddr_info->sec_info[0].start_addr_l = ddr_info_s->sec_info[0].start_addr_l;
		ddr_info->sec_info[0].start_addr_h = ddr_info_s->sec_info[0].start_addr_h;
		ddr_info->sec_info[0].end_addr_l = ddr_info_s->sec_info[0].end_addr_l;
		ddr_info->sec_info[0].end_addr_h = ddr_info_s->sec_info[0].end_addr_h;
		ddr_info->sec_info[1].start_addr_l = ddr_info_s->sec_info[1].start_addr_l;
		ddr_info->sec_info[1].start_addr_h = ddr_info_s->sec_info[1].start_addr_h;
		ddr_info->sec_info[1].end_addr_l = ddr_info_s->sec_info[1].end_addr_l;
		ddr_info->sec_info[1].end_addr_h = ddr_info_s->sec_info[1].end_addr_h;
		ddr_info->sec_info[2].start_addr_l = ddr_info_s->sec_info[2].start_addr_l;
		ddr_info->sec_info[2].start_addr_h = ddr_info_s->sec_info[2].start_addr_h;
		ddr_info->sec_info[2].end_addr_l = ddr_info_s->sec_info[2].end_addr_l;
		ddr_info->sec_info[2].end_addr_h = ddr_info_s->sec_info[2].end_addr_h;
		return 1;
	}
	return 0;
}

/**
 * sprd_fw_mem_cfg: config memory firewall.
 *
 * configure memory firewall to protect ddr memory.
 */
static void sprd_fw_mem_cfg(struct fw_mem_cfg *fw_cfg)
{
	FW_MEM_ARCH fw_mem_arch = fw_cfg->fw_mem_arch;
	struct sprd_fw_mem_reg *fw_base;
	int i, j;

	for (i = 0; i < FW_MEM_MAX_REGION; i++) {
		/* segurment(i) is zero means this seg memory fw is closed */
		if (!fw_cfg->fw_mem_addr[i][0] && !fw_cfg->fw_mem_addr[i][1])
			continue;
		/* get FW base and offset */
		fw_base = (struct sprd_fw_mem_reg *)(SPRD_SEC_TZPC_BASE + 0x2000
				+ fw_mem_arch * 0x1000 + i * sizeof (struct sprd_fw_mem_reg));
		fw_base->first_addr = fw_cfg->fw_mem_addr[i][0] >> 4;
		fw_base->last_addr = fw_cfg->fw_mem_addr[i][1] >> 4;
		/* there are eight master id need to be set */
		for (j=0; j< 8; j++)
			fw_base->mst_id[j] = fw_cfg->fw_mem_mstid[i][j];
		fw_base->rd_attr = fw_cfg->fw_mem_rprot[i];
		fw_base->wr_attr = fw_cfg->fw_mem_wprot[i];
	}
}

/**
 * sprd_fw_ddr_hollow_cfg: configure memory fw for DDR HOLLOW bug.
 *
 * There some ddr hollow segurments need to avoid.
 * It needs to use memory firewall to protect these regions.
 * e.g. 0x60000000 - 0x7fffffff/0x120000000 - 0xfffffffff
 */
void sprd_fw_ddr_hollow_cfg(void)
{
	ddr_info_t ddr_info_s;

	/* whether this DDR need to handle hollow memory */
	if (!sprd_fw_get_ddr_info(&ddr_info_s))
		return;

	/* AP and BIA memory firewall protect */
	fw_cfg.fw_mem_addr[0][0] = ddr_info_s.sec_info[0].end_addr_l + 1;
	fw_cfg.fw_mem_addr[0][1] = ddr_info_s.sec_info[1].start_addr_l - 1;
	fw_cfg.fw_mem_rprot[0] = ALL_FORBID;
	fw_cfg.fw_mem_wprot[0] = ALL_FORBID;
	fw_cfg.fw_mem_addr[1][0] = ((uint64)ddr_info_s.sec_info[2].end_addr_h << 32)
							+ ddr_info_s.sec_info[2].end_addr_l + 1;
	fw_cfg.fw_mem_addr[1][1] = DDR_END_ADDR;
	fw_cfg.fw_mem_rprot[1] = ALL_FORBID;
	fw_cfg.fw_mem_wprot[1] = ALL_FORBID;
	fw_cfg.fw_mem_arch = FW_MEM_AP;
	sprd_fw_mem_cfg(&fw_cfg);

	/* CP memory firewall protect, NOTE: CP base addr is 0x80000000 */
	fw_cfg.fw_mem_addr[0][0] = ddr_info_s.sec_info[0].end_addr_l + 1
							+ DDR_CP_BASE_ADDR;
	fw_cfg.fw_mem_addr[0][1] = ddr_info_s.sec_info[1].start_addr_l - 1
							+ DDR_CP_BASE_ADDR;
	fw_cfg.fw_mem_addr[1][0] = 0;
	fw_cfg.fw_mem_addr[1][1] = 0;
	fw_cfg.fw_mem_arch = FW_MEM_PUBPC;
	sprd_fw_mem_cfg(&fw_cfg);
	fw_cfg.fw_mem_arch = FW_MEM_WTL_AG;
	sprd_fw_mem_cfg(&fw_cfg);
}
