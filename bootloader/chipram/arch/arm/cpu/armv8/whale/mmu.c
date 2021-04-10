
#include <sci_types.h>
extern void MMU_EnableIDCM (void);
/**********************************************************************
  Section Descriptor:
  31                   20 19        12 11 10  9  8   5  4  3  2  1  0
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
  | section base address |   ZERO     |  AP | 0 | DAC | 1 | C/B | 1 0|
  ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

AP: Access Permission Bits, it action together with R/S Bits in C1 register[9:8],
    (R represents ROM protection, S represents System protection.) AP can be b_11,
    thus Access Control will be done by DA bits.
    AP  S   R   SVC     USER
    00  0   0   No Access   No Access
    00  1   0   Read-Only   No Access
    00  0   1   Read-Only   Read-Only
    00  1   1   Unpredictable   Unpredictable
    01  X   X   Read/Write  No Access
    10  X   X   Read/Write  Read-Only
    11  X   X   Read/Write  Read/Write

DA: Domain Access Bits, it indicate the position of DAC in register C3.
C/B:    Cacheable/Bufferable,
    C:1 Enable, 0 Disable
    B:1 Enable, 0 Disable
***********************************************************************/
#define MMU_SD_CONST    0x00000012
#define MMU_AP_B00      0x00000000
#define MMU_AP_B01      0x00000400
#define MMU_AP_B10      0x00000800
#define MMU_AP_B11      0x00000C00
#define MMU_C_BIT       0x00000008
#define MMU_B_BIT       0x00000004

//MMU table start address can be configed by specific project! it is in mem_cfg_xxx.c.
/*
modify from 0x1600000 to 0x3f0000, to avoid memory corruption in RW region 
when watchdog reset happen
in 8800x series, 0x3f0000--0x400000 is empty
in 6800 serirs, maybe has little problem, have risk to overlap the memory!!!!
Now, change to 0x008f0000, in reserved region.
*/

const uint32 const_MMUTableStartAddr       = 0x81600000 - 16*1024;

// MMU page table starting address to be referred in mmu_asm.s
unsigned int *g_mmu_page_table;

void MMU_Init (unsigned pageBaseAddr)
{
    int i;

    // 15Mb physical addr for page table
    g_mmu_page_table = const_MMUTableStartAddr;

    // Create page table 1mb entries
    for (i = 0; i < 0x1000; i++)
    {
		if (i>=0x800 && i<0xa00)
		{
			g_mmu_page_table[i] = (MMU_SD_CONST|MMU_AP_B11|MMU_C_BIT|MMU_B_BIT) + (i << 20);
		}
		else
		{
		    g_mmu_page_table[i] = (MMU_SD_CONST|MMU_AP_B11) + (i << 20);
		}
    }

   // MMU_InvalideICACHEALL();//steve.zhan add.
    MMU_EnableIDCM();
	
    //Delay some time
    for (i=0; i<1000; i++);
}

