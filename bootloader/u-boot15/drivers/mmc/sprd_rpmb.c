/******************************************************************************
 ** File Name:    sprd_rpmb.c                                     *
 ** Author:       zhongqiang.xiao                                           *
 ** DATE:         24/11/2014                                        *
 ** Copyright:    2014 Spreatrum, Incoporated. All Rights Reserved. *
 ** Description:  emmc rpmb partition access interface                                               *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                               *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                       *

 ******************************************************************************/

#include <config.h>
#include <common.h>
#include <command.h>
#include <linux/types.h>
#include <mmc.h>
#include <malloc.h>
#include <sprd_rpmb.h>

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

#define BLOCK_SIZE 512
#define EMMC  0
#define RPMB_PARTITION 3
#define USER_PARTITION 0
#define MMC_SET_BLOCK_COUNT   23

extern int mmc_send_cmd(struct mmc *mmc, struct mmc_cmd *cmd,
			struct mmc_data *data);

struct rpmb_data_frame {
	uint8_t stuff_bytes[RPMB_STUFF_DATA_SIZE];
	uint8_t key_mac[RPMB_KEY_MAC_SIZE];
	uint8_t data[RPMB_DATA_SIZE];
	uint8_t nonce[RPMB_NONCE_SIZE];
	uint8_t write_counter[4];
	uint8_t address[2];
	uint8_t block_count[2];
	uint8_t op_result[2];
	uint8_t msg_type[2];
};

static void u16_to_bytes(uint16_t u16, uint8_t * bytes)
{
	*bytes = (uint8_t) (u16 >> 8);
	*(bytes + 1) = (uint8_t) u16;
}

static void bytes_to_u16(uint8_t * bytes, uint16_t * u16)
{
	*u16 = (uint16_t) ((*bytes << 8) + *(bytes + 1));
}

static void bytes_to_u32(uint8_t * bytes, uint32_t * u32)
{
	*u32 = (uint32_t) ((*(bytes) << 24) +
			   (*(bytes + 1) << 16) +
			   (*(bytes + 2) << 8) + (*(bytes + 3)));
}

static void u32_to_bytes(uint32_t u32, uint8_t * bytes)
{
	*bytes = (uint8_t) (u32 >> 24);
	*(bytes + 1) = (uint8_t) (u32 >> 16);
	*(bytes + 2) = (uint8_t) (u32 >> 8);
	*(bytes + 3) = (uint8_t) u32;
}

void rpmb_write_cmd(struct mmc *mmc, lbaint_t blkcnt, uint blocksize,
		    const void *src)
{
	struct mmc_cmd cmd;
	struct mmc_data data;
	int timeout = 1000;
	cmd.cmdidx = MMC_CMD_WRITE_MULTIPLE_BLOCK;
	cmd.resp_type = MMC_RSP_R1;

	data.src = src;
	data.blocks = blkcnt;
	data.blocksize = blocksize;
	data.flags = MMC_DATA_WRITE;

	if (mmc_send_cmd(mmc, &cmd, &data)) {
		printf("rpmb_write_cmd failed\n");
	}
}

void rpmb_read_cmd(struct mmc *mmc, void *dst, lbaint_t blkcnt)
{
	struct mmc_cmd cmd;
	struct mmc_data data;

	cmd.cmdidx = MMC_CMD_READ_MULTIPLE_BLOCK;
	cmd.resp_type = MMC_RSP_R1;

	data.dest = dst;
	data.blocks = blkcnt;
	data.blocksize = mmc->read_bl_len;
	data.flags = MMC_DATA_READ;

	if (mmc_send_cmd(mmc, &cmd, &data))
		printf("rpmb_read_cmd error \n");
}

int mmc_set_blockcount(struct mmc *mmc, unsigned int blockcount,
		       bool is_rel_write)
{
	struct mmc_cmd cmd = { 0 };

	cmd.cmdidx = MMC_SET_BLOCK_COUNT;
	cmd.cmdarg = blockcount & 0x0000FFFF;
	if (is_rel_write)
		cmd.cmdarg |= 1 << 31;
	cmd.resp_type = MMC_RSP_R1;
	return mmc_send_cmd(mmc, &cmd, NULL);
}

/**@retrun 0 get rpmb package successful*/
int check_rpmb_key(uint8_t *package, int package_size)
{
	//Must match in tos
	uint8_t nonce[RPMB_NONCE_SIZE] = {0xA5,0x5A,0xFF,0x00,0xBE,0xEF,0xBE,0xEF,0xBE,0xEF,0xBE,0xEF,0x00,0xFF,0x5A,0xA5};
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint32_t writecount;
	struct mmc *mmc = find_mmc_device(0);	//0 is emmc

	if (NULL == mmc) {
		printf("%s mmc is null\n", __func__);
		return -1;
	}

	if (NULL == package && package_size < sizeof(struct rpmb_data_frame)) {
		printf("%s parameter package is invalid\n", __func__);
		return -1;
	}

	data_frame = package;
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	msg_type = RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ;
	u16_to_bytes(msg_type, data_frame->msg_type);
	//Must match in tos
	memcpy(data_frame->nonce, nonce, RPMB_NONCE_SIZE);
	mmc_switch_part(EMMC, RPMB_PARTITION);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_read_cmd(mmc, data_frame, RPMB_BLOCK_COUNT);


	mmc_switch_part(EMMC, USER_PARTITION);
	return 0;
}


/**@retrun 0 rpmb key unwritten*/
int is_wr_rpmb_key(void)
{
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint32_t writecount;
	int result = -1;
	struct mmc *mmc = find_mmc_device(0);	//0 is emmc

	if (NULL == mmc) {
		printf("%s mmc is null\n", __func__);
		return -1;
	}

	msg_type = RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	if (NULL == data_frame) {
		printf("%s malloc error\n", __func__);
		return -1;
	}
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	mmc_switch_part(EMMC, RPMB_PARTITION);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_read_cmd(mmc, data_frame, RPMB_BLOCK_COUNT);

/*result check*/
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if (RPMB_RES_NO_AUTH_KEY == op_result) {
		printf("%s rpmb key not write\n", __func__);
		result = 0;
	} else {
		printf("%s rpmb key has been written\n", __func__);
		result = -1;

	}


	free(data_frame);
	mmc_switch_part(EMMC, USER_PARTITION);
	return result;
}


uint32_t rpmb_read_writecount(void)
{
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint32_t writecount;
	struct mmc *mmc = find_mmc_device(0);	//0 is emmc
	if (NULL == mmc)
		return 1;

	msg_type = RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	mmc_switch_part(EMMC, RPMB_PARTITION);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_read_cmd(mmc, data_frame, RPMB_BLOCK_COUNT);

/*result check*/
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK)
	    && (msg_type == RPMB_MSG_TYPE_RESP_WRITE_COUNTER_VAL_READ)) {
		bytes_to_u32(data_frame->write_counter, &writecount);
		printf("read write count successed\n");
		free(data_frame);
		mmc_switch_part(EMMC, USER_PARTITION);
		return writecount;
	}

	else
		printf(" read write count:0x%x ,msg_type:0x%x\n", op_result,
		       msg_type);
	free(data_frame);
	mmc_switch_part(EMMC, USER_PARTITION);
	return 1;		//should not run here;
}

/*
blk_data: for save read data;
blk_index: the block index for read;
block_count: the read count;
success return 0 ;
*/
uint8_t rpmb_blk_read(char *blk_data, uint16_t blk_index, uint8_t block_count)
{
	struct rpmb_data_frame *data_frame;
	struct rpmb_data_frame *resp_buf;
	uint16_t msg_type;
	uint16_t op_result;
	struct mmc *mmc = find_mmc_device(0);	//0 is emmc
	if (NULL == mmc)
		return 1;

	if (blk_data == NULL) {
		printf("rpmb_blk_read null \n");
		return 1;
	}
	msg_type = RPMB_MSG_TYPE_REQ_AUTH_DATA_READ;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	u16_to_bytes(blk_index, data_frame->address);
	mmc_switch_part(EMMC, RPMB_PARTITION);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);
	resp_buf = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE * block_count);
	memset(resp_buf, 0, RPMB_DATA_FRAME_SIZE * block_count);
	mmc_set_blockcount(mmc, block_count, 0);
	rpmb_read_cmd(mmc, resp_buf, block_count);

/*result check*/
	bytes_to_u16((resp_buf + block_count - 1)->op_result, &op_result);
	bytes_to_u16((resp_buf + block_count - 1)->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK)
	    && (msg_type == RPMB_MSG_TYPE_RESP_AUTH_DATA_READ)) {
		uint8_t i = 0;
		for (i = 0; i < block_count; i++)
			memcpy((blk_data + i * RPMB_DATA_SIZE),
			       ((uint8_t *) (resp_buf + i) +
				RPMB_STUFF_DATA_SIZE + RPMB_KEY_MAC_SIZE),
			       RPMB_DATA_SIZE);
		printf("read  successed\n");
		free(resp_buf);
		free(data_frame);
		mmc_switch_part(EMMC, USER_PARTITION);
		return 0;
	}

	else
		printf(" read write count:0x%x ,msg_type:0x%x\n", op_result,
		       msg_type);
	free(resp_buf);
	free(data_frame);
	mmc_switch_part(EMMC, USER_PARTITION);
	return 1;		//should not run here;
}

/**
write_data: data for write
blk_index: the block will be write to;
success return 0 
*/
uint8_t rpmb_blk_write(char *write_data, uint16_t blk_index)
{
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint16_t block_count = 1;
	uint32_t writecount;
	struct mmc *mmc = find_mmc_device(0);	//0 is emmc
	if (NULL == mmc)
		return 1;

	if (write_data == NULL)	//|| (RPMB_DATA_SIZE != strlen(write_data)))
		return 1;

	/*for write rpmb key req */
	msg_type = RPMB_MSG_TYPE_REQ_AUTH_DATA_WRITE;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	writecount = rpmb_read_writecount();
	u16_to_bytes(msg_type, data_frame->msg_type);
	u16_to_bytes(blk_index, data_frame->address);
	u16_to_bytes(block_count, data_frame->block_count);
	u32_to_bytes(writecount, data_frame->write_counter);
	memcpy(data_frame->data, write_data, RPMB_DATA_SIZE);
	 /**/
#if 0				//for key_mac calc;
	    key_len = 32;
	mac_data_len = 284;
	data_frame->key_mac =
	    HMAC_SHA256(key, data_frame->data, key_len, mac_data_len)
#endif /*  */
	     /**/ mmc_switch_part(EMMC, RPMB_PARTITION);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 1);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);

	/*for read result req */
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	msg_type = RPMB_MSG_TYPE_REQ_RESULT_READ;
	u16_to_bytes(msg_type, data_frame->msg_type);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_read_cmd(mmc, data_frame, RPMB_BLOCK_COUNT);

/*result check*/
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK)
	    && (msg_type == RPMB_MSG_TYPE_RESP_AUTH_DATA_WRITE)) {
		printf(" data  write successed\n");
		free(data_frame);
		mmc_switch_part(EMMC, USER_PARTITION);
		return 0;
	}

	else
		printf(" data write fail op_result:0x%x ,msg_type:0x%x\n",
		       op_result, msg_type);
	free(data_frame);
	mmc_switch_part(EMMC, USER_PARTITION);
	return 1;		//should not run here;
}

/*
  key: the key will write must 32 len;
  len :must be 32;
  reutrn 0 success
*/
uint8_t rpmb_write_key(uint8_t * key, uint8_t len)
{
	struct rpmb_data_frame *data_frame = NULL;
	uint16_t msg_type;
	uint16_t op_result;
	struct mmc *mmc = find_mmc_device(0);	//0 is emmc
	if (NULL == mmc)
		return 1;

	if (key == NULL || RPMB_KEY_MAC_SIZE != len)
		return 1;

/*for write rpmb key req */
	msg_type = RPMB_MSG_TYPE_REQ_AUTH_KEY_PROGRAM;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	memcpy(data_frame->key_mac, key, RPMB_KEY_MAC_SIZE);
	mmc_switch_part(EMMC, RPMB_PARTITION);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 1);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);

/*for read result req*/
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	msg_type = RPMB_MSG_TYPE_REQ_RESULT_READ;
	u16_to_bytes(msg_type, data_frame->msg_type);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_write_cmd(mmc, RPMB_BLOCK_COUNT, BLOCK_SIZE, data_frame);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	mmc_set_blockcount(mmc, RPMB_BLOCK_COUNT, 0);
	rpmb_read_cmd(mmc, data_frame, RPMB_BLOCK_COUNT);

/*result check*/
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK)
	    && (msg_type == RPMB_MSG_TYPE_RESP_AUTH_KEY_PROGRAM)) {
		printf(" key write successed\n");
		free(data_frame);
		mmc_switch_part(EMMC, USER_PARTITION);
		return 0;
	}

	else
		printf(" key write fail op_result:0x%x ,msg_type:0x%x\n",
		       op_result, msg_type);
	free(data_frame);
	mmc_switch_part(EMMC, USER_PARTITION);
	return 1;		//should not run here;
};

uint8_t rpmb_get_wr_cnt(void){
	struct mmc *mmc = find_mmc_device(0);	//0 is emmc
	printf(" rpmb_get_wr_cnt:0x%x\n",mmc->rel_wr_sec_c);
	return mmc->rel_wr_sec_c;
}
