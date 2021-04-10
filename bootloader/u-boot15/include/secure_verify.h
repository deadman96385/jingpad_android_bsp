#ifndef SECURE_VERIFY_H
#define SECURE_VERIFY_H

#include <config.h>
#include <common.h>
#include "secure_boot.h"

#define SEC_HEADER_MAX_SIZE 4096
#define BOOTLOADER_HEADER_OFFSET 0x20
typedef struct {
	unsigned int mVersion;	// 1
	unsigned int mMagicNum;	// 0xaa55a5a5
	unsigned int mCheckSum;	//check sum value for bootloader header
	unsigned int mHashLen;	//word length
	unsigned int mSectorSize;	// sector size 1-1024
	unsigned int mAcyCle;	// 0, 1, 2
	unsigned int mBusWidth;	// 0--8 bit, 1--16bit
	unsigned int mSpareSize;	// spare part size for one sector
	unsigned int mEccMode;	// 0--1bit, 1-- 2bit, 2--4bit, 3--8bit, 4--12bit, 5--16bit, 6--24bit
	unsigned int mEccPostion;	// ECC postion at spare part
	unsigned int mSectPerPage;	// sector per page
	unsigned int mSinfoPos;
	unsigned int mSinfoSize;
	unsigned int mECCValue[27];
	unsigned int mPgPerBlk;
	unsigned int mImgPage[5];
} NBLHeader;
#define TRUE   1		/* Boolean true value. */
#define FALSE  0		/* Boolean false value. */
#define NBLHEADER_LEN  sizeof(NBLHeader)
typedef enum SEC_FLAG {
	UNABLE_SECURE = 0,
	ENABLE_SECURE,
	SPL_CHECK,
	SYSTEM_CHECK
} SEC_FCHECK;

int secure_header_parser(uint8_t * header_addr);
uint32_t get_code_offset(uint8_t * header_addr);
void *get_code_addr(uchar * name, uint8_t * header_addr);
int secure_verify(uchar * name, uint8_t * header, uint8_t * code);
unsigned char secure_verify_system_start(uchar * name, uint8_t * data, uint32_t data_len);
int secure_verify_system_end(uchar * name, uint8_t * header, uint8_t * code);

#endif
