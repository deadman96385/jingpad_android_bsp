/* Copyright (C) 2020 spreadtrum.com */
 #ifndef _SPRD_RPMB_H
 #define _SPRD_RPMB_H

#define RPMB_DATA_FRAME_SIZE        512
/* add rpmb in .h */
#define RPMB_MSG_TYPE_REQ_AUTH_KEY_PROGRAM          0x0001
#define RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ    0x0002
#define RPMB_MSG_TYPE_REQ_AUTH_DATA_WRITE           0x0003
#define RPMB_MSG_TYPE_REQ_AUTH_DATA_READ            0x0004
#define RPMB_MSG_TYPE_REQ_RESULT_READ               0x0005

#define RPMB_MSG_TYPE_RESP_AUTH_KEY_PROGRAM         0x0100
#define RPMB_MSG_TYPE_RESP_WRITE_COUNTER_VAL_READ   0x0200
#define RPMB_MSG_TYPE_RESP_AUTH_DATA_WRITE          0x0300
#define RPMB_MSG_TYPE_RESP_AUTH_DATA_READ           0x0400

#define RPMB_STUFF_DATA_SIZE                        196
#define RPMB_KEY_MAC_SIZE                           32
#define RPMB_DATA_SIZE                              256
#define RPMB_NONCE_SIZE                             16
#define RPMB_RESULT_OK                              0x00
#define RPMB_RES_NO_AUTH_KEY                        0x0007

#define RPMB_BLOCK_COUNT    1

struct rpmb_data_frame {
	uint8_t	stuff_bytes[RPMB_STUFF_DATA_SIZE];
	uint8_t	key_mac[RPMB_KEY_MAC_SIZE];
	uint8_t	data[RPMB_DATA_SIZE];
	uint8_t	nonce[RPMB_NONCE_SIZE];
	uint8_t	write_counter[4];
	uint8_t	address[2];
	uint8_t	block_count[2];
	uint8_t	op_result[2];
	uint8_t	msg_type[2];
};

/*
* blk_data: for save read data;
* blk_index: the block index for read;
* block_count: the read count;
* success return 0 ;
*/
#ifdef CONFIG_UFS
extern struct lu_info_tbl rpmb_lu_info;
uint8_t ufs_rpmb_blk_read(char *blk_data, uint16_t blk_index,
			  uint8_t block_count);
int check_ufs_rpmb_key(uint8_t *package, int package_size);
/* @retrun 0 rpmb key unwritten */
int is_wr_ufs_rpmb_key(void);
int prepare_rpmb_lu(void);
#endif

#ifdef CONFIG_MMC
uint8_t mmc_rpmb_blk_read(char *blk_data, uint16_t blk_index,
			  uint8_t block_count);
int check_mmc_rpmb_key(uint8_t *package, int package_size);
/* @retrun 0 rpmb key unwritten */
int is_wr_mmc_rpmb_key(void);
uint8_t mmc_rpmb_get_wr_cnt(void);
#endif
#endif // _SPRD_RPMB_H
