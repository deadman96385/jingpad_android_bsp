#ifndef __CONFIG_SP9861E_VMM_H
#define __CONFIG_SP9861E_VMM_H

#include <configs/sp9861e_3h10.h>

#undef CONFIG_BOOTCOMMAND
#define CONFIG_BOOTCOMMAND	"zboot 0x35100000 0x800000 0x3b800000 0x800000"

/**********vmm related***********/
#define VMM_RESERVE_SIZE 0x100000

#endif /* __CONFIG_H */
