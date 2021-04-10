/*
 * Copyright (C) 2017 spreadtrum.com
 *
 */
 #ifndef _SPRD_RPMB_H
 #define _SPRD_RPMB_H


#define RPMB_DATA_FRAME_SIZE        512

/*
blk_data: for save read data;
blk_index: the block index for read;
block_count: the read count;
success return 0 ;
*/
uint8_t rpmb_blk_read(char *blk_data, uint16_t blk_index, uint8_t block_count);

int check_rpmb_key(uint8_t *package, int package_size);
 /**@retrun 0 rpmb key unwritten*/
int is_wr_rpmb_key(void);
uint8_t rpmb_get_wr_cnt(void);

#endif // _SPRD_RPMB_H
