/******************************************************************************
 ** File Name:    timer_reg_r4p0.h                                            *
 ** Author:       mingwei.zhang                                                 *
 ** DATE:         06/11/2010                                                  *
 ** Copyright:    2010 Spreatrum, Incoporated. All Rights Reserved.           *
 ** Description:                                                              *
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History                                         *
 **---------------------------------------------------------------------------*
 ** DATE          NAME            DESCRIPTION                                 *
 ** 06/11/2010    mingwei.zhang   Create.                                     *
 ******************************************************************************/
#ifndef _TIMER_REG_R4P0_H_
#define _TIMER_REG_R4P0_H_
/*----------------------------------------------------------------------------*
 **                         Dependencies                                      *
 **------------------------------------------------------------------------- */
 #include <asm/arch/sprd_reg.h>
/**---------------------------------------------------------------------------*
 **                             Compiler Flag                                 *
 **--------------------------------------------------------------------------*/
#ifdef   __cplusplus
extern   "C"
{
#endif
/**---------------------------------------------------------------------------*
**                               Micro Define                                **
**---------------------------------------------------------------------------*/

/*----------Timer Control Register----------*/
#define TIMER_CTL_BASE        		SPRD_AON_TIMER_BASE //0x40050000
#define TIMER0_BASE                     (TIMER_CTL_BASE + 0x0000)
#define TM0_LOAD_LO                        (TIMER0_BASE + 0x0000)
#define TM0_LOAD_HI                        (TIMER0_BASE + 0x0004)
#define TM0_VALUE_LO                       (TIMER0_BASE + 0x0008)
#define TM0_VALUE_HI                       (TIMER0_BASE + 0x000C)
#define TM0_CTL                         (TIMER0_BASE + 0x0010)
#define TM0_CLR                         (TIMER0_BASE + 0x0014)
#define TM0_SHDW_LO                       (TIMER0_BASE + 0x0018)
#define TM0_SHDW_HI                       (TIMER0_BASE + 0x001C)


#define TIMER1_BASE                     (TIMER_CTL_BASE + 0x0020)
#define TM1_LOAD_LO                        (TIMER1_BASE + 0x0000)
#define TM1_LOAD_HI                        (TIMER1_BASE + 0x0004)
#define TM1_VALUE_LO                       (TIMER1_BASE + 0x0008)
#define TM1_VALUE_HI                       (TIMER1_BASE + 0x000C)
#define TM1_CTL                         (TIMER1_BASE + 0x0010)
#define TM1_CLR                         (TIMER1_BASE + 0x0014)
#define TM1_SHDW_LO                       (TIMER1_BASE + 0x0018)
#define TM1_SHDW_HI                       (TIMER1_BASE + 0x001C)

#define TIMER2_BASE                     (TIMER_CTL_BASE + 0x0040)
#define TM2_LOAD_LO                        (TIMER2_BASE + 0x0000)
#define TM2_LOAD_HI                        (TIMER2_BASE + 0x0004)
#define TM2_VALUE_LO                       (TIMER2_BASE + 0x0008)
#define TM2_VALUE_HI                       (TIMER2_BASE + 0x000C)
#define TM2_CTL                         (TIMER2_BASE + 0x0010)
#define TM2_CLR                         (TIMER2_BASE + 0x0014)
#define TM2_SHDW_LO                       (TIMER2_BASE + 0x0018)
#define TM2_SHDW_HI                       (TIMER2_BASE + 0x001C)

/* this is depend on the SOC timer resource */
#define TIMER_PHY_NUMBER 3
#define BIT_TIMER_RUN    0x02
#define BIT_TIMER_MODE   0
#define BIT_TIMER_SEL    16


//the structure of Timer register group.
typedef struct timer_tag
{
	volatile uint32_t load_lo;
	volatile uint32_t load_hi;
	volatile uint32_t value_lo;
	volatile uint32_t value_hi;
	volatile uint32_t ctl;
	volatile uint32_t clr;
	volatile uint32_t shdw_lo;
	volatile uint32_t shdw_hi;
} timer_s;



/**----------------------------------------------------------------------------*
**                         Compiler Flag                                      **
**----------------------------------------------------------------------------*/

#ifdef   __cplusplus
}
#endif
/**---------------------------------------------------------------------------*/
#endif
