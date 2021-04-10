#ifndef _OTP_HELP_H_
#define _OTP_HELP_H_

extern u32 sprd_ap_efuse_read(int blk_index);
extern int sprd_ap_efuse_prog(int blk_index, u32 val);
extern int sprd_efuse_double_prog(u32 blk, bool backup, bool lock, u32 val);
extern u32 sprd_efuse_double_read(int blk, bool backup);
extern u32 sprd_pmic_efuse_read(int blk_index);
extern u32 sprd_pmic_efuse_read_bits(int bit_index, int length);
extern void pmic_efuse_block_dump(void);
extern void ap_efuse_block_dump(void);
extern void sprd_uid_bin_info(void);
extern int sprd_get_chip_uid(char *buf);
extern int sprd_get_chip_hex_uid(char *buf);
extern int sprd_secure_efuse_read(u32 start_id, u32 end_id, u32 *pReadData,u32 Isdouble);
extern void ap_sansa_efuse_prog_power_on(void);
extern void ap_sansa_efuse_power_off(void);
extern void sansa_enable_efuse_EB(void);
#endif
