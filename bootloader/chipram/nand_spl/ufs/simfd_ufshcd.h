/*
 * UFS host controller driver structure definitions.
 *
 * Copyright (C) 2016 Spreadtrum Communications, Inc.
 *
 * Authors: 
 *	Wang Ding <justin.wang@spreadtrum.com>
 *	
 */
 
#ifndef __SIMFD_UFSHCD_H__
#define __SIMFD_UFSHCD_H__

#include <asm/types.h>
//#include <linux/compiler.h>
#include "simfd_ufs.h"

struct ufs_upiu_hd {
	__be32 dw0;
	__be32 dw1;
	__be32 dw2;
} __attribute__((packed));

struct ufs_cmd_req_upiu {
	struct ufs_upiu_hd header;
	__be32 exp_data_transfer_len;
	u8 cdb[MAX_CDB_SIZE];
} __attribute__((packed));

struct ufs_cmd_rsp_upiu {
	struct ufs_upiu_hd header;
	__be32 residual_transfer_count;
	__be32 reserved[4];
	__be16 sense_data_len;
	u8 sense_data[18];
} __attribute__((packed));

struct ufs_query_readflag_req_osf {
	u8 opcode;
	u8 idn;
	u8 index;
	u8 selector;
	__be32 resv[3];
} __attribute__((packed));

struct ufs_query_readflag_rsp_osf {
	u8 opcode;
	u8 idn;
	u8 index;
	u8 selector;
	__be32 resv1;
	u8 resv2[3];
	u8 value;
	__be32 resv3;
} __attribute__((packed));

struct ufs_query_req_rsp_upiu {
	struct ufs_upiu_hd header;
	union {
		__be32 general_osf[4];
		struct ufs_query_readflag_req_osf req_rdflag;
		struct ufs_query_readflag_rsp_osf rsp_rdflag;
	};
} __attribute__((packed));

struct ufshci_uic_cmd {
	u32 cmd;
	u32 arg1;
	u32 arg2;
	u32 arg3;
} __attribute__((packed));

struct ufshci_prdt {
	__le32    base;
	__le32    upper;
	__le32    resv;
	__le32    size;
} __attribute__((packed));

struct ufshci_ucd {
	uint8_t	cmd_upiu[ALIGNED_UPIU_SIZE];
	uint8_t	rsp_upiu[ALIGNED_UPIU_SIZE];
	struct ufshci_prdt	sglist[MAX_PRDT_ENTRY];
} __attribute__((packed));

struct ufshci_utrd_hd {
	__le32 dw0;
	__le32 dw1;
	__le32 dw2;
	__le32 dw3;
} __attribute__((packed));

struct ufshci_utmd {
	struct ufshci_utrd_hd header;

	__le32 req_upiu[TM_UPIU_SIZE_DW];
	__le32 rsp_upiu[TM_UPIU_SIZE_DW];
} __attribute__((packed));

struct ufshci_utrd {
	struct ufshci_utrd_hd header;

	__le32  ucd_ba;
	__le32  ucd_bau;

	__le16  rsp_upiu_len;
	__le16  rep_upiu_off;

	__le16  prdt_len;
	__le16  prdt_off;
} __attribute__((packed));

struct ufs_hinfo {
	void  *mmio_base;

	struct ufshci_ucd *ucdl;
	struct ufshci_utrd *utrdl;
	struct ufshci_utmd *utmrdl;

	u32 ufs_version;
	u32 capabilities;

	u32 logical_blk_size;
};

#endif

