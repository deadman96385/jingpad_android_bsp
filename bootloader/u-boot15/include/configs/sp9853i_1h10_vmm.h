#ifndef __CONFIG_SP9853I_VMM_H
#define __CONFIG_SP9853I_VMM_H

#include <configs/sp9853i_1h10.h>

/**********vmm related***********/
#undef VMM_RESERVE_SIZE
#define VMM_RESERVE_SIZE 0x100000
#define CONFIG_USB_UTMI_WIDTH_8

#endif /* __CONFIG_H */
