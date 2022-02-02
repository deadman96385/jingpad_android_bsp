#include <config.h>
#include <common.h>
#include <command.h>
#include <linux/types.h>
#include <malloc.h>
#include <sprd_rpmb.h>
#include <sprd_ufs.h>

#include "protocol_util.h"

struct lu_info_tbl rpmb_lu_info = {0};

static void u16_to_bytes(uint16_t u16, uint8_t *bytes)
{
	*bytes = (uint8_t) (u16 >> 8);
	*(bytes + 1) = (uint8_t) u16;
}

static void bytes_to_u16(uint8_t *bytes, uint16_t *u16)
{
	*u16 = (uint16_t) ((*bytes << 8) + *(bytes + 1));
}

static void bytes_to_u32(uint8_t *bytes, uint32_t *u32)
{
	*u32 = (uint32_t) ((*(bytes) << 24) +
			   (*(bytes + 1) << 16) +
			   (*(bytes + 2) << 8) + (*(bytes + 3)));
}

static void u32_to_bytes(uint32_t u32, uint8_t *bytes)
{
	*bytes = (uint8_t) (u32 >> 24);
	*(bytes + 1) = (uint8_t) (u32 >> 16);
	*(bytes + 2) = (uint8_t) (u32 >> 8);
	*(bytes + 3) = (uint8_t) u32;
}

int prepare_rpmb_lu(void)
{
	struct ufs_rpmb_unit_desc_tbl *rpmb_unit_desc;
	uint64_t block_count = 0;
	uint8_t ret = 0;

	ret = get_descriptor_data((void **)(&rpmb_unit_desc),
                                   RPMB_UNIT_DESC, 0xc4);
	if (ret != UFS_SUCCESS)
		return ret;
	block_count = be64_to_cpu(rpmb_unit_desc->qLogicalBlockCount);
	if (block_count) {
		rpmb_lu_info.lu_index = 0xc4;
		rpmb_lu_info.blkcnt = block_count;
		rpmb_lu_info.log2blksz = rpmb_unit_desc->bLogicalBlockSize;
		rpmb_lu_info.memory_type =rpmb_unit_desc->bMemoryType;
		rpmb_lu_info.bootable = rpmb_unit_desc->bBootLunID;
		rpmb_lu_info.write_protect = rpmb_unit_desc->bLUWriteProtect;
	}
	/*
	 * write key,read counter,write data,
	 * need this test_unit_ready operation.
	 */
	ret = test_unit_ready(&(rpmb_lu_info));

	return ret;
}

/* @retrun 0 get rpmb package successful */
int check_ufs_rpmb_key(uint8_t *package, int package_size)
{
	/* Must match in tos */
	uint8_t nonce[RPMB_NONCE_SIZE] = {
		0xa5, 0x5a, 0xff, 0x00, 0xbe, 0xef, 0xbe, 0xef,
		0xbe, 0xef, 0xbe, 0xef, 0x00, 0xff, 0x5a, 0xa5
	};
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint32_t writecount;
	lbaint_t transfer_blkcnt = 0;
	int ret = 0;

	if (rpmb_lu_info.log2blksz == 0) {
		ret = prepare_rpmb_lu();
		if(ret != UFS_SUCCESS)
			return ret;
	}

	/* rpmb_lu_info.log2blksz=0x08,256B */
	transfer_blkcnt = RPMB_DATA_FRAME_SIZE >> (rpmb_lu_info.log2blksz);
	if (!package && package_size < sizeof(struct rpmb_data_frame)) {
		printf("%s parameter package is invalid\n", __func__);
		return -1;
	}

	data_frame = package;
	msg_type = RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ;
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	memcpy(data_frame->nonce, nonce, RPMB_NONCE_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_IN, DMA_FROM_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	return 0;
}

/* @retrun 0 rpmb key unwritten */
int is_wr_ufs_rpmb_key(void)
{
	uint8_t result=0;
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint32_t writecount;
	uint8_t nonce[RPMB_NONCE_SIZE] = {
		0xa5, 0x5a, 0xff, 0x00, 0xbe, 0xef, 0xbe, 0xef,
		0xbe, 0xef, 0xbe, 0xef, 0x00, 0xff, 0x5a, 0xa5
	};
	lbaint_t transfer_blkcnt = 0;

	if (rpmb_lu_info.log2blksz == 0) {
		result = prepare_rpmb_lu();
		if(UFS_SUCCESS != result)
			return result;
	}
	/* rpmb_lu_info.log2blksz=0x08,256B */
	transfer_blkcnt = RPMB_DATA_FRAME_SIZE >> (rpmb_lu_info.log2blksz);

	msg_type = RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	if (!data_frame) {
		printf("%s malloc error\n", __func__);
		return -1;
	}

	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	memcpy(data_frame->nonce, nonce, RPMB_NONCE_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_IN, DMA_FROM_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	/* result check */
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if (op_result == RPMB_RES_NO_AUTH_KEY) {
		printf("%s rpmb key not write\n", __func__);
		result = 0;
	} else {
		printf("%s rpmb key has been written\n", __func__);
		result = -1;
	}
	free(data_frame);

	return result;
}

uint32_t ufs_rpmb_read_writecount(void)
{
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint32_t writecount;
	uint8_t nonce[RPMB_NONCE_SIZE] = {
		0xa5, 0x5a, 0xff, 0x00, 0xbe, 0xef, 0xbe, 0xef,
		0xbe, 0xef, 0xbe, 0xef, 0x00, 0xff, 0x5a,0xa5
	};
	lbaint_t transfer_blkcnt = 0;
	uint8_t ret = 0;

	if (rpmb_lu_info.log2blksz == 0) {
		ret = prepare_rpmb_lu();
		if (ret != UFS_SUCCESS) {
			debugf("prepare rpmb unit failed!\n");
			return ret;
		}
	}
	/* rpmb_lu_info.log2blksz =0x08 */
	transfer_blkcnt = RPMB_DATA_FRAME_SIZE >> (rpmb_lu_info.log2blksz);

	msg_type = RPMB_MSG_TYPE_REQ_WRITE_COUNTER_VAL_READ;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	memcpy(data_frame->nonce, nonce, RPMB_NONCE_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_IN, DMA_FROM_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	/* result check */
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK) &&
	    (msg_type == RPMB_MSG_TYPE_RESP_WRITE_COUNTER_VAL_READ)) {
		bytes_to_u32(data_frame->write_counter, &writecount);
		debugf("read write count successed\n");
		free(data_frame);
		return writecount;
	}
	else
		debugf(" read write count:0x%x ,msg_type:0x%x\n",
		       op_result,msg_type);
	free(data_frame);

	return 1;
}

/*
 * blk_data: for save read data;
 * blk_index: the block index for read;
 * block_count: the read count;
 * success return 0;
 */
uint8_t ufs_rpmb_blk_read(char *blk_data, uint16_t blk_index,
			  uint8_t block_count)
{
	struct rpmb_data_frame *data_frame;
	struct rpmb_data_frame *resp_buf;
	uint16_t msg_type;
	uint16_t op_result;
	uint8_t nonce[RPMB_NONCE_SIZE] = {
		0xa5, 0x5a, 0xff, 0x00, 0xbe, 0xef, 0xbe, 0xef,
		0xbe, 0xef, 0xbe, 0xef, 0x00, 0xef, 0x5a,0xa5
	};
	lbaint_t transfer_blkcnt = 0;
	uint8_t ret = 0;

	if (rpmb_lu_info.log2blksz == 0) {
		ret = prepare_rpmb_lu();
		if (ret != UFS_SUCCESS)
		return ret;
	}
	/* rpmb_lu_info.log2blksz=0x08,256B */
	transfer_blkcnt = RPMB_DATA_FRAME_SIZE >> (rpmb_lu_info.log2blksz);

	if (!blk_data) {
		printf("rpmb_blk_read null \n");
		return 1;
	}
	msg_type = RPMB_MSG_TYPE_REQ_AUTH_DATA_READ;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	u16_to_bytes(blk_index, data_frame->address);
	u16_to_bytes(block_count, data_frame->block_count);
	memcpy(data_frame->nonce, nonce, RPMB_NONCE_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	resp_buf = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE * block_count);
	memset(resp_buf, 0, RPMB_DATA_FRAME_SIZE * block_count);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_IN, DMA_FROM_DEVICE,
		      &rpmb_lu_info, (void*)resp_buf, 0,
		      transfer_blkcnt*block_count, 0);

	/* result check */
	bytes_to_u16((resp_buf + block_count - 1)->op_result, &op_result);
	bytes_to_u16((resp_buf + block_count - 1)->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK) &&
            (msg_type == RPMB_MSG_TYPE_RESP_AUTH_DATA_READ)) {
		uint8_t i = 0;
		for (i = 0; i < block_count; i++)
			memcpy((blk_data + i * RPMB_DATA_SIZE),
			       ((uint8_t *) (resp_buf + i) +
				RPMB_STUFF_DATA_SIZE + RPMB_KEY_MAC_SIZE),
			       RPMB_DATA_SIZE);
		printf("read  successed\n");
		free(resp_buf);
		free(data_frame);
		return 0;
	}
	else
		debugf("read write count:0x%x ,msg_type:0x%x\n",
		       op_result, msg_type);
	free(resp_buf);
	free(data_frame);

	return 1;
}

/*
 * write_data: data for write
 * blk_index: the block will be write to;
 * success return 0
 */

/* for single data */
uint8_t ufs_rpmb_blk_write(char *write_data, uint8_t *key, uint16_t blk_index)
{
	struct rpmb_data_frame *data_frame;
	uint16_t msg_type;
	uint16_t op_result;
	uint16_t block_count = 1;
	uint32_t writecount;
        lbaint_t transfer_blkcnt = 0;
	uint8_t ret = 0;

	if(rpmb_lu_info.log2blksz == 0) {
		ret = prepare_rpmb_lu();
		if (ret != UFS_SUCCESS)
			return ret;
	}
	/* rpmb_lu_info.log2blksz=0x08,256B */
	transfer_blkcnt = RPMB_DATA_FRAME_SIZE >>(rpmb_lu_info.log2blksz);

	if (!write_data)//|| (RPMB_DATA_SIZE != strlen(write_data)))
		return 1;

	/* TODO: The following codes is multiple block write
	 * for(int i=0;i<(strlen(write_data)/RPMB_DATA_SIZE),i++){
	 */

	msg_type = RPMB_MSG_TYPE_REQ_AUTH_DATA_WRITE;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	writecount = ufs_rpmb_read_writecount();
	u16_to_bytes(msg_type, data_frame->msg_type);
	u16_to_bytes(blk_index, data_frame->address);
	u16_to_bytes(block_count, data_frame->block_count);
	u32_to_bytes(writecount, data_frame->write_counter);
	memcpy(data_frame->data, write_data, RPMB_DATA_SIZE);

	/* TODO: The following codes is key mac caculate.
	 * int key_len = 32;
	 * int mac_data_len = 284;
	 * data_frame->key_mac = HMAC_SHA256(key, data_frame->data, key_len,
	 *                                   mac_data_len);
	 */

	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	/* for read result req */
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	msg_type = RPMB_MSG_TYPE_REQ_RESULT_READ;
	u16_to_bytes(msg_type, data_frame->msg_type);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_IN, DMA_FROM_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	/* result check */
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK) &&
	    (msg_type == RPMB_MSG_TYPE_RESP_AUTH_DATA_WRITE)) {
		printf(" data  write successed\n");
		free(data_frame);
		return 0;
	}
	else
		printf(" data write fail op_result:0x%x ,msg_type:0x%x\n",
		       op_result, msg_type);
	free(data_frame);

	return 1;
}

/*
 * key: the key will write must 32 len;
 * len :must be 32;
 * reutrn 0 success
 */
uint8_t ufs_rpmb_write_key(uint8_t * key, uint8_t len)
{
	struct rpmb_data_frame *data_frame = NULL;
	uint16_t msg_type;
	uint16_t op_result;
	uint8_t ret = 0;
	lbaint_t transfer_blkcnt = 0;

	if (rpmb_lu_info.log2blksz == 0) {
		ret = prepare_rpmb_lu();
		if (ret != UFS_SUCCESS)
			return ret;
	}

	/* rpmb_lu_info.log2blksz=0x08,256B */
	transfer_blkcnt = RPMB_DATA_FRAME_SIZE >> (rpmb_lu_info.log2blksz);

	if (!key || len != RPMB_KEY_MAC_SIZE)
		return 1;

	/* for write rpmb key req */
	msg_type = RPMB_MSG_TYPE_REQ_AUTH_KEY_PROGRAM;
	data_frame = (uint8_t *) malloc(RPMB_DATA_FRAME_SIZE);
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	u16_to_bytes(msg_type, data_frame->msg_type);
	memcpy(data_frame->key_mac, key, RPMB_KEY_MAC_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	/* for read result req */
	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	msg_type = RPMB_MSG_TYPE_REQ_RESULT_READ;
	u16_to_bytes(msg_type, data_frame->msg_type);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_OUT, DMA_TO_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	memset(data_frame, 0, RPMB_DATA_FRAME_SIZE);
	send_scsi_cmd(UFS_OP_SECURITY_PROTOCOL_IN, DMA_FROM_DEVICE,
		      &rpmb_lu_info, (void*)data_frame, 0, transfer_blkcnt, 0);

	/* result check */
	bytes_to_u16(data_frame->op_result, &op_result);
	bytes_to_u16(data_frame->msg_type, &msg_type);
	if ((op_result == RPMB_RESULT_OK) &&
	    (msg_type == RPMB_MSG_TYPE_RESP_AUTH_KEY_PROGRAM)) {
		printf(" key write successed\n");
		free(data_frame);
		return 0;
	}
	else
		printf(" key write fail op_result:0x%x ,msg_type:0x%x\n",
		       op_result, msg_type);
	free(data_frame);

	return 1;
}
