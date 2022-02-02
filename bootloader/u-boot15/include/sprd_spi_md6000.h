/**
 * Lattice MD6000 FPGA
 * Single-mipi to Dual-mipi
 *
 */

#ifndef __SPRD_MD6000_H__
#define __SPRD_MD6000_H__

#define MD6000_LOGIC_RST	159
#define MD6000_VDD1V85		72  
#define MD6000_VDD1V2		73
#define MD6000_RST		137
#define MD6000_ID_LEN		4

#define MD6000_STAT_DONE	(1 << 8)
#define MD6000_STAT_BUSY	(1 << 12)
#define MD6000_STAT_FAIL	(1 << 13)

int sprd_spi_md6000_load_bitfile(unsigned int spi_id, unsigned char *bitfile, int len);

#endif /* __SPRD_MD6000_H__ */
