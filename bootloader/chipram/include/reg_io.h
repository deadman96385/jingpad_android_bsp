
#ifndef REG_IO_H
#define REG_IO_H

#define REG32(x)	(*((volatile uint32 *)(x)))
#define CHIP_REG_OR(reg_addr, value)    (*(volatile uint32 *)(reg_addr) |= (uint32)(value))
#define CHIP_REG_AND(reg_addr, value)   (*(volatile uint32 *)(reg_addr) &= (uint32)(value))
#define CHIP_REG_GET(reg_addr)          (*(volatile uint32 *)(reg_addr))
#define CHIP_REG_SET(reg_addr, value)   (*(volatile uint32 *)(reg_addr)  = (uint32)(value))

#endif

