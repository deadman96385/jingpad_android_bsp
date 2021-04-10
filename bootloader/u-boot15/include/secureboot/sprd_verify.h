

#ifndef __SPRD_VERIFY_H
#define __SPRD_VERIFY_H

#include "sprdsec_header.h"
#include<crypto/sprdrsa.h>

void dumpHex(const char *title, uint8_t * data, int len);
void cal_sha256(uint8_t * input, uint32_t bytes_num, uint8_t * output);
bool sprd_verify_cert(uint8_t * hash_key_precert, uint8_t * hash_data, uint8_t * certptr);
uint8_t * sprd_get_sechdr_addr(uint8_t * buf);
uint8_t * sprd_get_code_addr(uint8_t * buf);
uint8_t * sprd_get_cert_addr(uint8_t * buf);
void sprd_get_pubk(uint8_t *load_buf,uint8_t *pubk);
bool sprd_verify_img(uint8_t * hash_key_precert, uint8_t * imgbuf);
void sprd_secure_check(uint8_t * current_img_addr,uint8_t * data_header);
void sprd_dl_check(uint8_t * hash,uint8_t * data_header);
void sprd_dl_verify(uint8_t *name,uint8_t * header,uint8_t *code);
void sprd_calc_hbk(void);
#endif	/* !HEADER_AES_H */
