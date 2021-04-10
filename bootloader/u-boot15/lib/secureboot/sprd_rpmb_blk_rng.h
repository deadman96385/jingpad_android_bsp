/*
 * Copyright (C) 2017 spreadtrum.com
 *
 */
 #ifndef _SPRD_RPMB_BLK_RNG_H
 #define _SPRD_RPMB_BLK_RNG_H

#define MMC_BLOCK_SIZE 512
#define RPMB_DATA_SIZE 256

#define MAX_RPMB_BLOCK_CNT    2
//secure storage use 0 - 1021,see APP_STORAGE_RPMB_BLOCK_COUNT in .mk
#define RPMB_BLOCK_IND_START  (1022 * 2)
#define RPMB_BLOCK_IND_END    (1023 * 2)

#define SPRD_IMGVERSION_BLK   (1023 * 2)
#define SPRD_MODEM_IMGVERSION_BLK   (1022 * 2)


#endif // _SPRD_RPMB_BLK_RNG_H
