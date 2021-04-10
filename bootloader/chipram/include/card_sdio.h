#include <sci_types.h>

#ifndef __SD_SDIO_20_H__
#define __SD_SDIO_20_H__

typedef enum CARD_EMMC_PARTITION_TPYE_TAG {
	PARTITION_USER,
	PARTITION_BOOT1,
	PARTITION_BOOT2,
	PARTITION_RPMB,
	PARTITION_GENERAL_P1,
	PARTITION_GENERAL_P2,
	PARTITION_GENERAL_P3,
	PARTITION_GENERAL_P4,
	PARTITION_MAX
} CARD_EMMC_PARTITION_TPYE;


PUBLIC BOOLEAN Emmc_Init(void);

PUBLIC BOOLEAN Emmc_Read(CARD_EMMC_PARTITION_TPYE cardPartiton, uint32 startBlock, uint32 num, uint8 * buf);

PUBLIC void Emmc_DisSdClk();

//-------------------------------for SD card--------------------------//
PUBLIC BOOLEAN SD_Init(void);

PUBLIC BOOLEAN SD_CARD_Read( uint32 startBlk, uint32 num, uint8 * buf);

#endif
