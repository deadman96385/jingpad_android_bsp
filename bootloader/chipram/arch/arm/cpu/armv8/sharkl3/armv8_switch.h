#include <sci_types.h>

typedef enum {
    TYPE_EL0 = 0x0,
    TYPE_FIQ = 0x1,
    TYPE_IRQ = 0x2,
    TYPE_SVC = 0x3,
    TYPE_EL1t = 0x4,
    TYPE_EL1h = 0x5,
    TYPE_MONITOR = 0x6,
    TYPE_EL2t = 0x8,
    TYPE_EL2h = 0x9,
    TYPE_Hyp = 0xa,
    TYPE_EL3t = 0xc,
    TYPE_EL3h = 0xd,
    TYPE_INVALID = 0xFF
} src_el_e;

#define TO_AARCH_32		0x2
#define TO_AARCH_64		0x3

#define EXCEPTION_LEVEL0	(0)
#define EXCEPTION_LEVEL1	(1)
#define EXCEPTION_LEVEL2	(2)
#define EXCEPTION_LEVEL3	(3)
#define SECURE_STATE		(0)
#define NON_SECURE_STATE	(1)
#define EXECUTE_STATE_AARCH32	(0x10)
#define EXECUTE_STATE_AARCH64	(0x0)

uint32 arm_spsr_read(void);
uint32 arm_scr_el3_read(void);
void arm_scr_el3_write(uint32 val);
uint32 arm_current_el_read(void);
void arm_secure_state_switch(BOOLEAN ns);
void arm_spsr_set(src_el_e el);
void arm_elr_set(uint64 addr);
void arm_eret(void);
void arm_eret_1(void);
void arm_set_sp(uint32 sp);
uint32 arm_get_sp(void);

