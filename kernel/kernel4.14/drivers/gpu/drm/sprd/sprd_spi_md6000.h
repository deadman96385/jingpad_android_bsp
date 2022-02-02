/**
 * Lattice MD6000 FPGA
 * Single-mipi to Dual-mipi
 *
 */

#ifndef __SPRD_MD6000_H__
#define __SPRD_MD6000_H__

//#define MD6000_LOGIC_RST	138
//#define MD6000_VDD1V85	72  
//#define MD6000_VDD1V2		73
//#define MD6000_RST		137
//#define MD6000_VDD3V3		62
#define MD6000_ID_LEN		4
#define spi_freq 96000000
#define spi_mode 0
#define MD6000_STAT_DONE        (1 << 8)
#define MD6000_STAT_BUSY        (1 << 12)
#define MD6000_STAT_FAIL        (1 << 13)

int sprd_spi_md6000_load_bitfile(unsigned char *bitfile, int len);
void spi_md6000_suspend(void);
void spi_md6000_resume(void);

#endif /* __SPRD_MD6000_H__ */
