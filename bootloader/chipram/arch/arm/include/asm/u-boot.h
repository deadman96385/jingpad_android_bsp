

#ifndef _U_BOOT_H_
#define _U_BOOT_H_	1

typedef struct bd_info {
    int			bi_baudrate;	/* serial console baudrate */
    unsigned long	bi_ip_addr;	/* IP Address */
    ulong	        bi_arch_number;	/* unique id for this board */
    ulong	        bi_boot_params;	/* where this board expects params */
    struct				/* RAM configuration */
    {
	ulong start;
	ulong size;
    }			bi_dram[CONFIG_NR_DRAM_BANKS];
} bd_t;

#endif	/* _U_BOOT_H_ */
