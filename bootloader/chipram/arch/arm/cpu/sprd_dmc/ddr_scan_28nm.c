/*****************************************************************************
 ** File Name:        emc.c
 ** Author:           Johnny Wang
 ** DATE:             2012/12/04
 ** Copyright:        2007 Spreatrum, Incoporated. All Rights Reserved.
 ** Description:
 ******************************************************************************/
/******************************************************************************
 **                   Edit    History
 **------------------------------------------------------------------------
 ** DATE          NAME            DESCRIPTION
 ** 2012/12/04                    Create.
 ******************************************************************************/
#include "dram_phy_28nm.h"
#include "umctl2_reg_28nm.h"
#include "ddr_scan_28nm.h"
#include <asm/arch/clk_para_config.h>
#include <common.h>
#include <adi.h>


#ifdef   __cplusplus
extern   "C"
{
#endif

#define UART1_TX_BUF_ADDR 0X70100000
#define UART1_TX_BUF_CNT ((REG32(0x70100000 + 0xc)>>8)&0xff)
#define LDO_DCDC_PD_SET 0x40038810
#define LDO_DCDC_PD_CLR 0x40038814

#define LDO_DCDC_PD 0x40038810

#define PWR_WR_PROT_VALUE     0x40038950
#define MCU_WR_PROT_VALUE     0x4003894c

#define PWR_PROT_KEY    0x6e7f
#define MCU_PROT_KEY    0x3c4d

//#define LOG_TYPE_OPEN

extern const MCU_CLK_PARA_T mcu_clk_para;
extern void sdram_init_short();



uint32 line_num=0;
uint8 TPRD;
uint32 aclcd_mid;

void ddr_power_control(uint32 mode)
{
    uint32 dcdc_pd;

#ifdef CONFIG_ADIE_SC2723

    ANA_REG_SET(PWR_WR_PROT_VALUE,PWR_PROT_KEY);
    while((ANA_REG_GET(PWR_WR_PROT_VALUE) & 0x8000) != 0x8000);

	if(mode==0)    //power on
    {
        dcdc_pd = ANA_REG_GET(LDO_DCDC_PD);
		dcdc_pd &= ~(1<<11);
		ANA_REG_SET(LDO_DCDC_PD,dcdc_pd);
	}
	else           //power down
	{
		dcdc_pd = ANA_REG_GET(LDO_DCDC_PD);
		dcdc_pd |= 1<<11;
		ANA_REG_SET(LDO_DCDC_PD,dcdc_pd);
	}

	ANA_REG_SET(PWR_WR_PROT_VALUE,0);
#else
	if(mode==0)    //power on
    {
        dcdc_pd = ANA_REG_GET(LDO_DCDC_PD_SET);
		dcdc_pd &= ~(1<<11);
		ANA_REG_SET(LDO_DCDC_PD_SET,dcdc_pd);

		dcdc_pd = ANA_REG_GET(LDO_DCDC_PD_CLR);
		dcdc_pd |= 1<<11;
		ANA_REG_SET(LDO_DCDC_PD_CLR,dcdc_pd);
	}
	else           //power down
	{
		dcdc_pd = ANA_REG_GET(LDO_DCDC_PD_CLR);
		dcdc_pd &= ~(1<<11);
		ANA_REG_SET(LDO_DCDC_PD_CLR,dcdc_pd);

		dcdc_pd = ANA_REG_GET(LDO_DCDC_PD_SET);
		dcdc_pd |= 1<<11;
		ANA_REG_SET(LDO_DCDC_PD_SET,dcdc_pd);
	}
#endif

	//ANA_REG_SET(PWR_WR_PROT_VALUE,0);
}

void ddr_print_28nm(char *string)
{
    unsigned char *s1 = NULL;

    s1 = string;

    while (*s1 != NULL)
    {
		//wait until uart1 tx fifo empty
		while(UART1_TX_BUF_CNT != 0);

		//put out char by uart1 tx fifo
		REG32(UART1_TX_BUF_ADDR) = *s1;
		s1++;
	}
}

void reg_bits_set(uint32 addr,uint32 start_bitpos,uint32 bit_num,unsigned int value)
{
	dmc_reg_bits_set(addr,start_bitpos,bit_num,value);
}



void wait_pclk_28nm(uint32 n_pclk)
{
    volatile uint32 i;
    volatile uint32 value;

    for(i = 0; i < n_pclk; i++)
    {
        value = REG32(PUBL_PGSR0);
    }
    value = value;
}

static pstruct_t PDATA;

char * uint8tochar(uint8 val)
{
	uint8 hbyte = 0;
	uint8 lbyte = 0;
	uint8 temp;

	#if 0
	if(((val&0xf)>9) ||((val>>4)>9))
	{
		while(1);// if not uint8 value, hold
	}
	else
	#endif
	    temp = val & 0xf;
        if(temp > 9)
		  lbyte=temp - 10+0x61;
		else
		  lbyte=temp+0x30;

		temp = (val &0xf0) >>4;
		if(temp >9)
			hbyte=temp-10+0x61;
		else
		    hbyte=temp+0x30;


	PDATA.pnull = ((void *)0);
	PDATA.puint16 = (uint16)((lbyte<<8)|(hbyte));

	return(&PDATA); //for little endian
}

BOOLEAN publ_bist_result()
{
	volatile uint32 bist_result;

	do{bist_result = REG32(PUBL_BISTGSR);}
	while((bist_result&0x1) == 0);

	if(bist_result == 1)
	{
	    return TRUE;
	}
	else
	{
	    return FALSE;
	}
}


void publ_dll_autocal_bypass()
{
	//disable dll auto calibration
	REG32(PUBL_PIR) |= BIT_29;
}

void publ_dll_reset()
{
	volatile uint32 temp;

	//do dll calibration
	//REG32(PUBL_PIR) |= 0X20000021;
    REG32(PUBL_PIR) |= 0X21;
    wait_pclk_28nm(100);
	//wait dll calibration done
	do{temp = REG32(PUBL_PGSR0);}
	while((temp&0x5) != 0x5);

	reg_bits_set(PUBL_PIR, 6,1,1);  //phy reset
	wait_pclk_28nm(100);
	reg_bits_set(PUBL_PIR, 6,1,0);

}



#define IS_HBYTE(x) ((((x>>2)&BIT_0)==BIT_0)? 1:0)

void publ_dll_cnt_set(DLL_TYPE_E dll_type,uint8 dll_num,uint8 dll_cnt)
{
	volatile uint32 byte_num = dll_num>>3;
	volatile uint32 bit_num = dll_num;

	switch(dll_type)
	{
		//DX LCDL
		case DLL_TYPE_DX_WDQDLCDL:
		{
			reg_bits_set(PUBL_DX0LCDLR1+dll_num*0x80,0,8,dll_cnt); return;
		}
		case DLL_TYPE_DX_RDQSLCDL:
		{
			reg_bits_set(PUBL_DX0LCDLR1+dll_num*0x80,8,8,dll_cnt); return;
		}
		case DLL_TYPE_DX_RDQSNLCDL:
		{
			reg_bits_set(PUBL_DX0LCDLR1+dll_num*0x80,16,8,dll_cnt); return;
		}
		//WRITE BDL
		case DLL_TYPE_DX_DQWBDLL:
		{
			//reg_bits_set(PUBL_DX0BDLCR0+byte_num*0x80+IS_HBYTE(bit_num)*4,
			//	         (bit_num%4)<<3,5,
			//	         dll_cnt);
			if((1<<bit_num) & 0x0f0f0f0f)
			{
				reg_bits_set(PUBL_DX0BDLCR0+byte_num*0x80, (bit_num%4)*8,5,dll_cnt);
			}
			else
			{
                reg_bits_set(PUBL_DX0BDLCR1+byte_num*0x80, (bit_num%4)*8,5,dll_cnt);
			}

			return;
		}
		#if 0
		case DLL_TYPE_DX_DMWBDLL:
		{
			return;
		}
		case DLL_TYPE_DX_DQSWBDLL:
		{
			return;
		}
		case DLL_TYPE_DX_OEBDLL:
		{
			return;
		}
		#endif
		//READ BDL
		case DLL_TYPE_DX_RBDLL:
		{
            if((1<<bit_num) & 0x0f0f0f0f)
			{
				reg_bits_set(PUBL_DX0BDLCR3+byte_num*0x80, (bit_num%4)*8,5,dll_cnt);
			}
			else
			{
                reg_bits_set(PUBL_DX0BDLCR4+byte_num*0x80, (bit_num%4)*8,5,dll_cnt);
			}
			return;
		}
		#if 0
		case DLL_TYPE_DX_DMRBDLL:
			{}
		case DLL_TYPE_DX_DQSRBDLL:
			{}
		case DLL_TYPE_DX_DQSNRBDLL:
			{}
		case DLL_TYPE_DX_PDDBDLL:
			{}
		case DLL_TYPE_DX_PDRBDLL:
			{}
		case DLL_TYPE_DX_TERBDLL:
			{}
		#endif
		delault:while(1);
	}
}


BOOLEAN publ_dram_bist(BIST_TYPE_E is_bist_ac,uint8 byte_bit_num,uint8 pattern)
{
	volatile uint32 bist_result;

	//bist stop
	reg_bits_set(PUBL_BISTRR, 0, 3, 2);
	wait_pclk_28nm(10);

	//bist reset
	reg_bits_set(PUBL_BISTRR, 0, 3, 3);
	wait_pclk_28nm(100);

    switch(pattern)
    {
    #if 1
        case 1: REG32(PUBL_BISTUDPR) = 0x11111111;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 2: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
			    REG32(PUBL_BISTUDPR) = 0xeeeeeeee;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 3: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0;    //start address
			    REG32(PUBL_BISTUDPR) = 0x22222222;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 4: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
			    REG32(PUBL_BISTUDPR) = 0xdddddddd;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 5: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0;    //start address
			    REG32(PUBL_BISTUDPR) = 0x33333333;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 6: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
			    REG32(PUBL_BISTUDPR) = 0xcccccccc;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 7: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0;    //start address
			    REG32(PUBL_BISTUDPR) = 0x44444444;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 8: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
			    REG32(PUBL_BISTUDPR) = 0xbbbbbbbb;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 9: //set bist address
	    //        REG32(PUBL_BISTAR0) = 0;    //start address
			    REG32(PUBL_BISTUDPR) = 0x55555555;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 10://set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
	    		REG32(PUBL_BISTUDPR) = 0xaaaaaaaa;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 11://set bist address
	    //        REG32(PUBL_BISTAR0) = 0;    //start address
			    REG32(PUBL_BISTUDPR) = 0x66666666;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 12://set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
			    REG32(PUBL_BISTUDPR) = 0x99999999;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 13://set bist address
	    //        REG32(PUBL_BISTAR0) = 0;    //start address
			    REG32(PUBL_BISTUDPR) = 0x77777777;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 14://set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
			    REG32(PUBL_BISTUDPR) = 0x88888888;
		        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		#endif

	//	case 15: REG32(PUBL_BISTUDPR) = 0xffff0000;
		//        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		  //      break;
	//	case 16: REG32(PUBL_BISTUDPR) = 0x0000ffff;
		//        reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		  //      break;
		case 15://set bist address
	    //        REG32(PUBL_BISTAR0) = 0;    //start address
		        reg_bits_set(PUBL_BISTRR, 17,  2, 0);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 16://set bist address
	    //        REG32(PUBL_BISTAR0) = 0x73ffc1fc;    //start address
		        reg_bits_set(PUBL_BISTRR, 17,  2, 1);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		case 17:
		        reg_bits_set(PUBL_BISTRR, 17,  2, 2);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
		        break;
		default:
		        break;
	}
	reg_bits_set(PUBL_BISTRR, 19,  4, ((is_bist_ac==BIST_TYPE_BYTE)?byte_bit_num:0) |
		                              ((is_bist_ac==BIST_TYPE_BIT)?(byte_bit_num>>3):0) );

   // wait_pclk_28nm(100);
	//trigger bist run
	reg_bits_set(PUBL_BISTRR, 0, 3, 1);

	wait_pclk_28nm(100);
	do{bist_result = REG32(PUBL_BISTGSR);}
	while((bist_result&0x1) == 0);

	if(bist_result == 1)
	{
	    return TRUE;
	}
	else
	{
	    return FALSE;
	}
}

void publ_clear_bits_settings()
{
    uint32 i;

	for(i=0;i<4;i++)
	{
        reg_bits_set(PUBL_DX0BDLCR0+i*0x80,0,32,0);
	    reg_bits_set(PUBL_DX0BDLCR1+i*0x80,0,32,0);
		reg_bits_set(PUBL_DX0BDLCR3+i*0x80,0,32,0);
	    reg_bits_set(PUBL_DX0BDLCR4+i*0x80,0,32,0);
	}
}

void publ_set_bits_settings(uint32 value)
{
    uint32 i;

	for(i=0;i<4;i++)
    {
        reg_bits_set(PUBL_DX0BDLCR0+i*0x80,0,32,value);
	    reg_bits_set(PUBL_DX0BDLCR1+i*0x80,0,32,value);
	}
}

void reset_ddr_scan_env(uint32 slew_rate, uint32 bist_ds, uint32 flag)
{
      if(flag==1)
      {
          ddr_power_control(1);
	      wait_pclk_28nm(100000);
	      ddr_power_control(0);
	      wait_pclk_28nm(100000);
      }

      REG32(PUBL_ACLCDLR) = aclcd_mid;
      //en auto selfrefresh
	  //REG32(0x30000060) &= ~(1<<0);

	  //wait_pclk_28nm(1000);

	sdram_init_short();

	  //reg_bits_set(PUBL_ACIOCR0,30,2,0);
	 //dis auto selfrefresh
	 REG32(0x30000060) |= 1;
	 REG32(0x300001a0) |= (1<<31);      //DFIUDP0 dis auto udp
	 REG32(PUBL_PGCR1) |= 1<<26;        //DIS VT

	 ddr_phy_bist_init(1);

     if(flag==1)
     {
         reg_bits_set(PUBL_ACIOCR0,30,2,slew_rate);
		 reg_bits_set(PUBL_DXCCR,13,2,slew_rate);

		 __mem_ds_set(bist_ds);
	     __publ_ds_set(bist_ds);

		 publ_dll_autocal_bypass();

        //clear all bits delay settings
         publ_clear_bits_settings();

        //DISABLE AC CAL
		reg_bits_set(PUBL_PGCR1,23,2,0);

     }

   //close ac vt
	//reg_bits_set(PUBL_PGCR1,23,2,0);
}

void publ_ddr_scan(BIST_DS_E bist_ds, uint32 sr)
{
	volatile uint32 i = 0;
	volatile uint32 dll_num = 0;
	volatile uint32 dll_cnt = 0;
	volatile uint32 DS;
	volatile uint8  pattern;
	volatile uint32 value;

	volatile uint32 byte_wp_left[4];
	volatile uint32 byte_wp_right[4];
	volatile uint32 byte_rp_left[4];
	volatile uint32 byte_rp_right[4];
	volatile uint32 first_fail=0;
	volatile uint32 first_pass=0;

	publ_dll_autocal_bypass();

    //clear all bits delay settings
    publ_clear_bits_settings();


#ifdef DDR_SCAN_RLCDL_SUPPROT
#ifdef LOG_TYPE_OPEN
	ddr_print_28nm("\r\n/***Read DQS DQSN LCDL SCAN***/\r\n");
#else
    ddr_print_28nm("\r\n0x434F4E54");
#endif
	for(dll_num = 0; dll_num< 4;dll_num++)
	{
		publ_dll_reset();

		for(dll_cnt = 0;dll_cnt <0x45;dll_cnt++)
		{
        #ifdef LOG_TYPE_OPEN
			DS = (((bist_ds)==BIST_DS_34OHM)?0x34:0) |
				(((bist_ds)==BIST_DS_40OHM)?0x40:0) |
				(((bist_ds)==BIST_DS_48OHM)?0x48:0) |
				(((bist_ds)==BIST_DS_60OHM)?0x60:0) |
				(((bist_ds)==BIST_DS_80OHM)?0x80:0);

			ddr_print_28nm("\r\nsr = ");
			ddr_print_28nm(uint8tochar(sr));
			ddr_print_28nm(";");

			ddr_print_28nm("	drv_str = ");
			ddr_print_28nm(uint8tochar(DS));
			ddr_print_28nm("ohm;");

			ddr_print_28nm("	byte = ");
			ddr_print_28nm(uint8tochar(dll_num));
			ddr_print_28nm(";");

			ddr_print_28nm("	rlcdl = 0x");
			ddr_print_28nm(uint8tochar(dll_cnt));
			ddr_print_28nm(",");
        #else

			DS = (((bist_ds)==BIST_DS_34OHM)?0x22:0) |
				(((bist_ds)==BIST_DS_40OHM)?0x28:0) |
				(((bist_ds)==BIST_DS_48OHM)?0x30:0) |
				(((bist_ds)==BIST_DS_60OHM)?0x3c:0) |
				(((bist_ds)==BIST_DS_80OHM)?0x50:0);

			//line_num++;
			ddr_print_28nm("\r\n0x0");
			//ddr_print_28nm(uint8tochar(line_num));

			ddr_print_28nm("\t0xc10000");
			ddr_print_28nm(uint8tochar(dll_num));

			ddr_print_28nm("\t0xc20004");
			ddr_print_28nm(uint8tochar(DS));

			ddr_print_28nm("\t0xc30003");
			ddr_print_28nm(uint8tochar(sr));

			ddr_print_28nm("\t0xb10007");
			ddr_print_28nm(uint8tochar(dll_cnt));
        #endif

			publ_dll_cnt_set(DLL_TYPE_DX_RDQSLCDL, dll_num, dll_cnt);
			publ_dll_cnt_set(DLL_TYPE_DX_RDQSNLCDL,dll_num, dll_cnt);

			REG32(0x3000030c) |= 1<<5;   // MANUAL UPDATE PHY PARAMETERS
            wait_pclk_28nm(10);
			// WAIT UPDATE STATUS
			while(REG32(0x30000310)&BIT_5);

			for(pattern=1;pattern<17;pattern++)
			{
				if(publ_dram_bist(BIST_TYPE_BYTE,dll_num,pattern)==FALSE)
				{
                    break;
				}
			}
            REG32(0x1f00) = pattern;
			if(pattern == 17)
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" PASS;");
            #else
                ddr_print_28nm("\t0x0");
            #endif
				first_fail = 1;
				if(first_pass == 1)
				{
				  //  if(dll_cnt>=0x8)
                    byte_rp_left[dll_num] = dll_cnt + 0x8;
				 //	else
				//	byte_rp_left[dll_num] = 0;
					REG32(0x1c00+dll_num*4) = byte_rp_left[dll_num];
					first_pass = 0;
				}
			}
			else
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" FAIL;");
            #else
                ddr_print_28nm("\t0xf");
            #endif
				first_pass = 1;
				if(first_fail == 1)
				{
                //    if(dll_cnt>=0x8)
					byte_rp_right[dll_num] = dll_cnt + 0x8;
				//	else
				//	byte_rp_right[dll_num] = 0;
					REG32(0x1c10+dll_num*4) = byte_rp_right[dll_num];
					first_fail = 0;
				}
			}
		}
	}
#endif


#ifdef DDR_SCAN_WLCDL_SUPPROT
#ifdef LOG_TYPE_OPEN
    ddr_print_28nm("\r\n\r\n");
	ddr_print_28nm("/***Write DQ WLCDL SCAN***/");
#else
    ddr_print_28nm("\r\n0x434F4E54");
#endif
	//publ_clear_bits_settings();

	for(dll_num = 0; dll_num< 4;dll_num++)
	{

		publ_dll_reset();

		for(dll_cnt = 0;dll_cnt <0x45;dll_cnt++)
		{
		#ifdef LOG_TYPE_OPEN
			DS = (((bist_ds)==BIST_DS_34OHM)?0x34:0) |
				 (((bist_ds)==BIST_DS_40OHM)?0x40:0) |
				 (((bist_ds)==BIST_DS_48OHM)?0x48:0) |
				 (((bist_ds)==BIST_DS_60OHM)?0x60:0) |
				 (((bist_ds)==BIST_DS_80OHM)?0x80:0);

			ddr_print_28nm("\r\nsr = ");
		    ddr_print_28nm(uint8tochar(sr));
		    ddr_print_28nm(";");

			ddr_print_28nm("	drv_str = ");
		    ddr_print_28nm(uint8tochar(DS));
		    ddr_print_28nm("ohm;");

			ddr_print_28nm("	byte = ");
		    ddr_print_28nm(uint8tochar(dll_num));
			ddr_print_28nm(";");

			ddr_print_28nm("	wlcdl = 0x");
			ddr_print_28nm(uint8tochar(dll_cnt));
			ddr_print_28nm(",");
        #else

			DS = (((bist_ds)==BIST_DS_34OHM)?0x22:0) |
				(((bist_ds)==BIST_DS_40OHM)?0x28:0) |
				(((bist_ds)==BIST_DS_48OHM)?0x30:0) |
				(((bist_ds)==BIST_DS_60OHM)?0x3c:0) |
				(((bist_ds)==BIST_DS_80OHM)?0x50:0);

            //line_num++;
            ddr_print_28nm("\r\n0x0");
            //ddr_print_28nm(uint8tochar(line_num));

			ddr_print_28nm("\t0xc10000");
			ddr_print_28nm(uint8tochar(dll_num));

			ddr_print_28nm("\t0xc20004");
			ddr_print_28nm(uint8tochar(DS));

            ddr_print_28nm("\t0xc30003");
			ddr_print_28nm(uint8tochar(sr));



            ddr_print_28nm("\t0xb10008");
			ddr_print_28nm(uint8tochar(dll_cnt));
        #endif

			publ_dll_cnt_set(DLL_TYPE_DX_WDQDLCDL, dll_num, dll_cnt);

			REG32(0x3000030c) |= 1<<5;   // MANUAL UPDATE PHY PARAMETERS
            wait_pclk_28nm(10);
			// WAIT UPDATE STATUS
			while(REG32(0x30000310)&BIT_5);

			for(pattern=1;pattern<17;pattern++)
			{
				if(publ_dram_bist(BIST_TYPE_BYTE,dll_num,pattern)==FALSE)
				{
                    break;
				}
			}

            if(pattern == 17)
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" PASS;");
            #else
                ddr_print_28nm("\t0x0");
            #endif
				first_fail = 1;
				if(first_pass == 1)
				{
				       if(dll_cnt>=0x4)
							byte_wp_left[dll_num] = dll_cnt - 0x4;
					   else
					        byte_wp_left[dll_num] = 0;

					   REG32(0x1c20+dll_num*4) = byte_wp_left[dll_num];
					   first_pass = 0;

				}
			}
			else
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" FAIL;");
            #else
                ddr_print_28nm("\t0xf");
            #endif
				first_pass = 1;
				if(first_fail == 1)
				{
                    if(dll_cnt>=0x8)
					    byte_wp_right[dll_num] = dll_cnt - 0x8;
					else
					    byte_wp_right[dll_num] = 0;

					REG32(0x1c30+dll_num*4) = byte_wp_right[dll_num];
					first_fail = 0;
				}

			}
		}
	}
#endif




#ifdef DDR_SCAN_WBDLL_SUPPROT
#ifdef LOG_TYPE_OPEN
    ddr_print_28nm("\r\n\r\n");
	ddr_print_28nm("/***Write Bit Delay SCAN***/");
#else
    ddr_print_28nm("\r\n0x434F4E54");
#endif

	for(dll_num = 0; dll_num< 32;dll_num++)
	{

        publ_clear_bits_settings();
		publ_dll_reset();

	    reg_bits_set(PUBL_DX0BDLCR0+(dll_num>>3)*0x80,0,32,0);
	    reg_bits_set(PUBL_DX0BDLCR1+(dll_num>>3)*0x80,0,32,0);


	    //test byte shift down
	    reg_bits_set(PUBL_DX0LCDLR1+(dll_num>>3)*0x80,0,8,byte_wp_right[dll_num>>3]);

		for(dll_cnt = 0;dll_cnt <0x20;dll_cnt++)
		{


        #ifdef LOG_TYPE_OPEN
			DS =  (((bist_ds)==BIST_DS_34OHM)?0x34:0) |
				  (((bist_ds)==BIST_DS_40OHM)?0x40:0) |
				  (((bist_ds)==BIST_DS_48OHM)?0x48:0) |
				  (((bist_ds)==BIST_DS_60OHM)?0x60:0) |
				  (((bist_ds)==BIST_DS_80OHM)?0x80:0);

			ddr_print_28nm("\r\nsr = ");
		    ddr_print_28nm(uint8tochar(sr));
		    ddr_print_28nm(";");

			ddr_print_28nm("	drv_str = ");
		    ddr_print_28nm(uint8tochar(DS));
		    ddr_print_28nm("ohm;");

			ddr_print_28nm("	bit = 0x");
		    ddr_print_28nm(uint8tochar(dll_num));
			ddr_print_28nm(";");

			ddr_print_28nm("	wbdll_right = 0x");
			ddr_print_28nm(uint8tochar(dll_cnt));
			ddr_print_28nm(",");
        #else
		   DS = (((bist_ds)==BIST_DS_34OHM)?0x22:0) |
			   (((bist_ds)==BIST_DS_40OHM)?0x28:0) |
			   (((bist_ds)==BIST_DS_48OHM)?0x30:0) |
			   (((bist_ds)==BIST_DS_60OHM)?0x3c:0) |
			   (((bist_ds)==BIST_DS_80OHM)?0x50:0);

           //line_num++;
		   ddr_print_28nm("\r\n0x0");
		   //ddr_print_28nm(uint8tochar(line_num));

		   ddr_print_28nm("\t0xc10001");
		   ddr_print_28nm(uint8tochar(dll_num));

		   ddr_print_28nm("\t0xc20004");
		   ddr_print_28nm(uint8tochar(DS));

		   ddr_print_28nm("\t0xc30003");
		   ddr_print_28nm(uint8tochar(sr));

		   ddr_print_28nm("\t0xb1000a");
		   ddr_print_28nm(uint8tochar(dll_cnt));
        #endif

			publ_dll_cnt_set(DLL_TYPE_DX_DQWBDLL, dll_num, dll_cnt);

			REG32(0x3000030c) |= 1<<5;   // MANUAL UPDATE PHY PARAMETERS
            wait_pclk_28nm(10);
			// WAIT UPDATE STATUS
			while(REG32(0x30000310)&BIT_5);

			for(pattern=1;pattern<17;pattern++)
			{
				if(publ_dram_bist(BIST_TYPE_BIT,dll_num,pattern)==FALSE)
				{
                    break;
				}
			}

            if(pattern == 17)
			{
        #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" PASS;");
        #else
                ddr_print_28nm("\t0x0");
        #endif
			}
			else
			{
        #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" FAIL;");
        #else
                ddr_print_28nm("\t0xf");
        #endif
			}
		}
	}


	for(dll_num = 0; dll_num< 32;dll_num++)
	{

        publ_clear_bits_settings();
		publ_dll_reset();

	    reg_bits_set(PUBL_DX0BDLCR0+(dll_num>>3)*0x80,0,32,0x09090909);
	    reg_bits_set(PUBL_DX0BDLCR1+(dll_num>>3)*0x80,0,32,0x09090909);

	    //test byte shift down
	    reg_bits_set(PUBL_DX0LCDLR1+(dll_num>>3)*0x80,0,8,byte_wp_left[dll_num>>3]);

		for(dll_cnt = 0;dll_cnt <0x20;dll_cnt++)
		{
        #ifdef LOG_TYPE_OPEN
			DS =  (((bist_ds)==BIST_DS_34OHM)?0x34:0) |
				 (((bist_ds)==BIST_DS_40OHM)?0x40:0) |
				 (((bist_ds)==BIST_DS_48OHM)?0x48:0) |
				 (((bist_ds)==BIST_DS_60OHM)?0x60:0) |
				 (((bist_ds)==BIST_DS_80OHM)?0x80:0);

			ddr_print_28nm("\r\nsr = ");
		    ddr_print_28nm(uint8tochar(sr));
		    ddr_print_28nm(";");

			ddr_print_28nm("	drv_str = ");
		    ddr_print_28nm(uint8tochar(DS));
		    ddr_print_28nm("ohm;");

			ddr_print_28nm("	bit = 0x");
		    ddr_print_28nm(uint8tochar(dll_num));
			ddr_print_28nm(";");

			ddr_print_28nm("	wbdll_left = 0x");
			ddr_print_28nm(uint8tochar(dll_cnt));
			ddr_print_28nm(",");
        #else
		   DS = (((bist_ds)==BIST_DS_34OHM)?0x22:0) |
				(((bist_ds)==BIST_DS_40OHM)?0x28:0) |
				(((bist_ds)==BIST_DS_48OHM)?0x30:0) |
				(((bist_ds)==BIST_DS_60OHM)?0x3c:0) |
				(((bist_ds)==BIST_DS_80OHM)?0x50:0);

           //line_num++;
		   ddr_print_28nm("\r\n0x0");
		   //ddr_print_28nm(uint8tochar(line_num));

		   ddr_print_28nm("\t0xc10001");
		   ddr_print_28nm(uint8tochar(dll_num));

		   ddr_print_28nm("\t0xc20004");
		   ddr_print_28nm(uint8tochar(DS));

		   ddr_print_28nm("\t0xc30003");
		   ddr_print_28nm(uint8tochar(sr));



		   ddr_print_28nm("\t0xb1000a");
		   ddr_print_28nm(uint8tochar(dll_cnt));
        #endif

			publ_dll_cnt_set(DLL_TYPE_DX_DQWBDLL, dll_num, dll_cnt);

			REG32(0x3000030c) |= 1<<5;   // MANUAL UPDATE PHY PARAMETERS
            wait_pclk_28nm(10);
			// WAIT UPDATE STATUS
			while(REG32(0x30000310)&BIT_5);

			for(pattern=1;pattern<17;pattern++)
			{
				if(publ_dram_bist(BIST_TYPE_BIT,dll_num,pattern)==FALSE)
				{
                    break;
				}
			}

            if(pattern == 17)
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" PASS;");
            #else
                ddr_print_28nm("\t0x0");
            #endif
			}
			else
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" FAIL;");
            #else
                ddr_print_28nm("\t0xf");
            #endif
			}
		}
	}
#endif


#ifdef DDR_SCAN_RBDLL_SUPPROT
#ifdef LOG_TYPE_OPEN
    ddr_print_28nm("\r\n\r\n");
	ddr_print_28nm("/***Read Bit Delay SCAN***/");
#else
    ddr_print_28nm("\r\n0x434F4E54");
#endif

	for(dll_num = 0; dll_num< 32;dll_num++)
	{

        publ_clear_bits_settings();
		publ_dll_reset();

	    reg_bits_set(PUBL_DX0BDLCR3+(dll_num>>3)*0x80,0,32,0x11111111);
	    reg_bits_set(PUBL_DX0BDLCR4+(dll_num>>3)*0x80,0,32,0x11111111);


	    //test byte shift up
	    reg_bits_set(PUBL_DX0LCDLR1+(dll_num>>3)*0x80,8,8,byte_rp_right[dll_num>>3]);
		reg_bits_set(PUBL_DX0LCDLR1+(dll_num>>3)*0x80,16,8,byte_rp_right[dll_num>>3]);

		for(dll_cnt = 0;dll_cnt <0x20;dll_cnt++)
		{
        #ifdef LOG_TYPE_OPEN
			DS =  (((bist_ds)==BIST_DS_34OHM)?0x34:0) |
				 (((bist_ds)==BIST_DS_40OHM)?0x40:0) |
				 (((bist_ds)==BIST_DS_48OHM)?0x48:0) |
				 (((bist_ds)==BIST_DS_60OHM)?0x60:0) |
				 (((bist_ds)==BIST_DS_80OHM)?0x80:0);

			ddr_print_28nm("\r\nsr = ");
		    ddr_print_28nm(uint8tochar(sr));
		    ddr_print_28nm(";");

			ddr_print_28nm("	drv_str = ");
		    ddr_print_28nm(uint8tochar(DS));
		    ddr_print_28nm("ohm;");

			ddr_print_28nm("	bit = 0x");
		    ddr_print_28nm(uint8tochar(dll_num));
			ddr_print_28nm(";");

			ddr_print_28nm("	rbdll_right = 0x");
			ddr_print_28nm(uint8tochar(dll_cnt));
			ddr_print_28nm(",");
        #else

		  DS = (((bist_ds)==BIST_DS_34OHM)?0x22:0) |
			 (((bist_ds)==BIST_DS_40OHM)?0x28:0) |
			 (((bist_ds)==BIST_DS_48OHM)?0x30:0) |
			 (((bist_ds)==BIST_DS_60OHM)?0x3c:0) |
			 (((bist_ds)==BIST_DS_80OHM)?0x50:0);

          //line_num++;
		  ddr_print_28nm("\r\n0x0");
		  //ddr_print_28nm(uint8tochar(line_num));

		  ddr_print_28nm("\t0xc10001");
		  ddr_print_28nm(uint8tochar(dll_num));

		  ddr_print_28nm("\t0xc20004");
		  ddr_print_28nm(uint8tochar(DS));

		  ddr_print_28nm("\t0xc30003");
		  ddr_print_28nm(uint8tochar(sr));



		  ddr_print_28nm("\t0xb10009");
		  ddr_print_28nm(uint8tochar(dll_cnt));
        #endif

			publ_dll_cnt_set(DLL_TYPE_DX_RBDLL, dll_num, dll_cnt);

			REG32(0x3000030c) |= 1<<5;   // MANUAL UPDATE PHY PARAMETERS
            wait_pclk_28nm(10);
			// WAIT UPDATE STATUS
			while(REG32(0x30000310)&BIT_5);

			for(pattern=1;pattern<17;pattern++)
			{
				if(publ_dram_bist(BIST_TYPE_BIT,dll_num,pattern)==FALSE)
				{
                    break;
				}
			}

            if(pattern == 17)
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" PASS;");
            #else
                ddr_print_28nm("\t0x0");
            #endif
			}
			else
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" FAIL;");
            #else
                ddr_print_28nm("\t0xf");
            #endif
			}
		}
	}


	for(dll_num = 0; dll_num< 32;dll_num++)
	{

        publ_clear_bits_settings();
		publ_dll_reset();

	    reg_bits_set(PUBL_DX0BDLCR3+(dll_num>>3)*0x80,0,32,0);
	    reg_bits_set(PUBL_DX0BDLCR4+(dll_num>>3)*0x80,0,32,0);

	    //test byte shift up
	    reg_bits_set(PUBL_DX0LCDLR1+(dll_num>>3)*0x80,8,8,byte_rp_left[dll_num>>3]);
		reg_bits_set(PUBL_DX0LCDLR1+(dll_num>>3)*0x80,16,8,byte_rp_left[dll_num>>3]);

		for(dll_cnt = 0;dll_cnt <0x20;dll_cnt++)
		{

        #ifdef LOG_TYPE_OPEN
			DS =  (((bist_ds)==BIST_DS_34OHM)?0x34:0) |
				 (((bist_ds)==BIST_DS_40OHM)?0x40:0) |
				 (((bist_ds)==BIST_DS_48OHM)?0x48:0) |
				 (((bist_ds)==BIST_DS_60OHM)?0x60:0) |
				 (((bist_ds)==BIST_DS_80OHM)?0x80:0);

			ddr_print_28nm("\r\nsr = ");
		    ddr_print_28nm(uint8tochar(sr));
		    ddr_print_28nm(";");

			ddr_print_28nm("	drv_str = ");
		    ddr_print_28nm(uint8tochar(DS));
		    ddr_print_28nm("ohm;");

			ddr_print_28nm("	bit = 0x");
		    ddr_print_28nm(uint8tochar(dll_num));
			ddr_print_28nm(";");

			ddr_print_28nm("	rbdll_left = 0x");
			ddr_print_28nm(uint8tochar(dll_cnt));
			ddr_print_28nm(",");
        #else
		  DS = (((bist_ds)==BIST_DS_34OHM)?0x22:0) |
			 (((bist_ds)==BIST_DS_40OHM)?0x28:0) |
			 (((bist_ds)==BIST_DS_48OHM)?0x30:0) |
			 (((bist_ds)==BIST_DS_60OHM)?0x3c:0) |
			 (((bist_ds)==BIST_DS_80OHM)?0x50:0);

          //line_num++;
		  ddr_print_28nm("\r\n0x0");
		  //ddr_print_28nm(uint8tochar(line_num));

		  ddr_print_28nm("\t0xc10001");
		  ddr_print_28nm(uint8tochar(dll_num));

		  ddr_print_28nm("\t0xc20004");
		  ddr_print_28nm(uint8tochar(DS));

		  ddr_print_28nm("\t0xc30003");
		  ddr_print_28nm(uint8tochar(sr));



		  ddr_print_28nm("\t0xb10009");
		  ddr_print_28nm(uint8tochar(dll_cnt));

        #endif

			publ_dll_cnt_set(DLL_TYPE_DX_RBDLL, dll_num, dll_cnt);

			REG32(0x3000030c) |= 1<<5;   // MANUAL UPDATE PHY PARAMETERS
            wait_pclk_28nm(10);
			// WAIT UPDATE STATUS
			while(REG32(0x30000310)&BIT_5);

			for(pattern=1;pattern<17;pattern++)
			{
				if(publ_dram_bist(BIST_TYPE_BIT,dll_num,pattern)==FALSE)
				{
                    break;
				}
			}

            if(pattern == 17)
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" PASS;");
            #else
                ddr_print_28nm("\t0x0");
            #endif
			}
			else
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" FAIL;");
            #else
                ddr_print_28nm("\t0xf");
            #endif
			}
		}
	}
#endif

/**************************************here we scan ac*******************************************/

#ifdef DDR_SCAN_ACDDL_SUPPORT
#ifdef LOG_TYPE_OPEN
		ddr_print_28nm("\r\n\r\n");
		ddr_print_28nm("/***Read Bit Delay SCAN***/");
#else
        ddr_print_28nm("\r\n0x434F4E54");
#endif

        publ_clear_bits_settings();
		publ_dll_reset();
        //DISABLE AC CAL
		reg_bits_set(PUBL_PGCR1,23,2,0);

		for(dll_cnt=0;dll_cnt<0x40;dll_cnt++)
		{
        #ifdef LOG_TYPE_OPEN
			DS =  (((bist_ds)==BIST_DS_34OHM)?0x34:0) |
				 (((bist_ds)==BIST_DS_40OHM)?0x40:0) |
				 (((bist_ds)==BIST_DS_48OHM)?0x48:0) |
				 (((bist_ds)==BIST_DS_60OHM)?0x60:0) |
				 (((bist_ds)==BIST_DS_80OHM)?0x80:0);
				ddr_print_28nm("\r\nsr = ");
				ddr_print_28nm(uint8tochar(sr));
				ddr_print_28nm(";");

				ddr_print_28nm("	drv_str = ");
				ddr_print_28nm(uint8tochar(DS));
				ddr_print_28nm("ohm;");

			//	ddr_print_28nm("	byte = ");
			//    ddr_print_28nm(uint8tochar(dll_num));
			//	ddr_print_28nm(";");

				ddr_print_28nm("	acd = 0x");
				ddr_print_28nm(uint8tochar(dll_cnt));
				ddr_print_28nm(",");
        #else
		  DS = (((bist_ds)==BIST_DS_34OHM)?0x22:0) |
			  (((bist_ds)==BIST_DS_40OHM)?0x28:0) |
			  (((bist_ds)==BIST_DS_48OHM)?0x30:0) |
			  (((bist_ds)==BIST_DS_60OHM)?0x3c:0) |
			  (((bist_ds)==BIST_DS_80OHM)?0x50:0);

              //line_num++;
			ddr_print_28nm("\r\n0x0");
			//ddr_print_28nm(uint8tochar(line_num));

			ddr_print_28nm("\t0xc10004");
			ddr_print_28nm(uint8tochar(DS));
			ddr_print_28nm("\t0xc20003");
			ddr_print_28nm(uint8tochar(sr));

			//ddr_print_28nm("	0xc30000");
			//ddr_print_28nm(uint8tochar(dll_num));

			ddr_print_28nm("\t0xb1000b");
			ddr_print_28nm(uint8tochar(dll_cnt));

        #endif

			REG32(PUBL_ACLCDLR) = dll_cnt;

			REG32(0x3000030c) |= 1<<5;   // MANUAL UPDATE PHY PARAMETERS
            wait_pclk_28nm(10);
			// WAIT UPDATE STATUS
			while(REG32(0x30000310)&BIT_5);

			for(pattern=1;pattern<17;pattern++)
			{
			    for(dll_num = 0; dll_num< 4;dll_num++)
			    	{
						if(publ_dram_bist(BIST_TYPE_BYTE,dll_num,pattern)==FALSE)
						{
		                    //break;
		                    goto out_ac;
						}
			    	}
			}

out_ac:
            if(pattern == 17)
			{
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" PASS;");
            #else
                ddr_print_28nm("\t0x0");
            #endif
			}
			else
			{
                reset_ddr_scan_env(sr,bist_ds,1);	
				
            #ifdef LOG_TYPE_OPEN
                ddr_print_28nm(" FAIL;");
            #else
                ddr_print_28nm("\t0xf");
            #endif
			}
		}

#endif


}

void __mem_ds_set(BIST_DS_E bist_ds)
{
	uint8 mr3 = 0;

	mr3 = ((bist_ds==BIST_DS_34OHM)?0X1:0X0)	|
		  ((bist_ds==BIST_DS_40OHM)?0X2:0X0)	|
		  ((bist_ds==BIST_DS_48OHM)?0X3:0X0)	|
		  ((bist_ds==BIST_DS_60OHM)?0X4:0X0)	|
		  ((bist_ds==BIST_DS_80OHM)?0X6:0X0);

	wait_pclk_28nm(10);

	//wait mode register idle
	while(REG32(UMCTL_MRSTAT));

	//send mode register command
	REG32(UMCTL_MRCTRL1) = (3<<8)|mr3;
	REG32(UMCTL_MRCTRL0) = (1<<31)|(3<<12)|(1<<4);

	//wait mode register idle
	while(REG32(UMCTL_MRSTAT));
	wait_pclk_28nm(100);
}

void __publ_ds_set(BIST_DS_E bist_ds)
{
	uint8 publ_ds = 0;
	uint32 i;

	publ_ds = ((bist_ds==BIST_DS_34OHM)?0XD:0) |
		      ((bist_ds==BIST_DS_40OHM)?0XB:0) |
		      ((bist_ds==BIST_DS_48OHM)?0X9:0) |
		      ((bist_ds==BIST_DS_60OHM)?0X7:0) |
		      ((bist_ds==BIST_DS_80OHM)?0X5:0);

	//disable auto publ zqcal
	//reg_bits_set(PUBL_ZQCR,1,1,0);
	//wait_pclk_28nm(50);

	//set publ zq
	reg_bits_set(PUBL_ZQ0PR,0,4,publ_ds);
	reg_bits_set(PUBL_ZQ1PR,0,4,publ_ds);
	reg_bits_set(PUBL_ZQ2PR,0,4,publ_ds);

	//zq power down
	reg_bits_set(PUBL_ZQCR,2,1,1);
	for(i = 0; i < 100; i++);
	reg_bits_set(PUBL_ZQCR,2,1,0);
	for(i = 0; i < 100; i++);
	//reg_bits_set(PUBL_ZQCR,2,1,1);

	//wait zq calibration done
	while((REG32(PUBL_ZQ0SR)&0x200) != 0x200);
	while((REG32(PUBL_ZQ1SR)&0x200) != 0x200);
	while((REG32(PUBL_ZQ2SR)&0x200) != 0x200);

	//tigger publ zqcal
	//reg_bits_set(PUBL_ZQCR,1,1,1);
	//wait_pclk_28nm(200);

	//wait publ zqcl done
	//while((REG32(PUBL_ZQ0SR)&BIT_9) != BIT_9);

	//if zqcl err, hold
	//while((REG32(PUBL_ZQ0SR)&BIT_8));

	//wait_pclk_28nm(50);
}

void ddr_phy_bist_init(uint32 cs_num)
{
	//set bist address
	REG32(PUBL_BISTAR0) = 0x71e8;    //start address

#if defined(DDR_LPDDR2)
    REG32(PUBL_BISTAR1) = 0x40 | ((cs_num-1)<<2); //start address
	REG32(PUBL_BISTAR2) = 0x73ffc1fc;  //end address

	//set bist data length
	//REG32(PUBL_BISTWCR) = 0X1000;
	REG32(PUBL_BISTWCR) = 0Xfffe;
#endif

#if defined(DDR_LPDDR3)
    REG32(PUBL_BISTAR1) = 0x80 | ((cs_num-1)<<2); //start address
	REG32(PUBL_BISTAR2) = 0x73ffc1f8;  //end address

	//set bist data length
	//REG32(PUBL_BISTWCR) = 0X1000;
	REG32(PUBL_BISTWCR) = 0Xfffc;
#endif




	//set bist mode register
	reg_bits_set(PUBL_BISTRR,  3,  1, 1);//0:loopback mode  1:dram mode
	reg_bits_set(PUBL_BISTRR,  5,  8, 0);//bist stop on n+1 fail
	reg_bits_set(PUBL_BISTRR, 13,  1, 1);//sotp if fail
	reg_bits_set(PUBL_BISTRR, 14,  2, 1); //1:bist data  2:bist ac
	reg_bits_set(PUBL_BISTRR, 17,  2, 3);//bist pattern mode, 0:walking0 1:walking1  2:lfsr  3:user
}

void ddr_phy_reset()
{
#if 0
    REG32(PUBL_PIR) |= BIT_6;
	wait_pclk_28nm(1000);
	REG32(PUBL_PIR) &= ~BIT_6;

	REG32(PUBL_PGCR0) |= BIT_26;
	wait_pclk_28nm(1000);
	REG32(PUBL_PGCR0) &= ~BIT_26;
#endif
    //reset ac and datx8 without rest RTL logic
    REG32(PUBL_PGCR0) &= ~BIT_25;
    wait_pclk_28nm(1000);
    REG32(PUBL_PGCR1) |= BIT_25;
}

#define DS_SCAN_MIN       BIST_DS_34OHM
#ifdef DDR_LPDDR2
#define DS_SCAN_MAX       BIST_DS_60OHM
#endif

#ifdef DDR_LPDDR3
#define DS_SCAN_MAX       BIST_DS_48OHM
#endif

void ddr_scan_28nm(uint32 cs_num)
{
	BIST_DS_E bist_ds = 0;
	uint32 slew_rate =0;
	uint32 clk_rate;
	uint32 high,mid,low;

    clk_rate = mcu_clk_para.ddr_freq/1000000;
    high = clk_rate/100 + 0x30;
    mid = (clk_rate/10)%10 + 0x30;
    low = clk_rate%10 + 0x30;

    TPRD = REG32(PUBL_ACMDLR)>>8;
	TPRD = 1000000/(clk_rate*2*TPRD);

#ifdef LOG_TYPE_OPEN
	ddr_print_28nm("\r\nVersion: 0.2");
	#ifdef CONFIG_SC9630
	ddr_print_28nm("\r\n//----PROJECT = SHARKL");
	#else
    ddr_print_28nm("\r\n//----PROJECT = TSHARK");
#endif
	ddr_print_28nm("\r\n//----FREQ = ");
	PDATA.pnull = ((void *)0);
	PDATA.puint16 = (uint16)((0<<8)|(high));
	ddr_print_28nm(&PDATA);
	PDATA.pnull = ((void *)0);
	PDATA.puint16 = (uint16)((0<<8)|(mid));
	ddr_print_28nm(&PDATA);
	PDATA.pnull = ((void *)0);
	PDATA.puint16 = (uint16)((0<<8)|(low));
	ddr_print_28nm(&PDATA);
	ddr_print_28nm("M");

	ddr_print_28nm("\r\n//-----target period = ");
	ddr_print_28nm(uint8tochar(TPRD));
#else
    ddr_print_28nm("\r\n********************");
	//#ifdef CONFIG_SC9630
    ddr_print_28nm("\r\n***0x28410000***");
	//#else
	//ddr_print_28nm("\r\n***0x28400000***");
	//#endif
	#ifdef DDR_LPDDR2
	ddr_print_28nm("\r\n***0x22222222***");
	#endif

	#ifdef DDR_LPDDR3
	ddr_print_28nm("\r\n***0x33333333***");
	#endif

	ddr_print_28nm("\r\n***0x");
	ddr_print_28nm(uint8tochar(clk_rate>>8));
	ddr_print_28nm(uint8tochar(clk_rate));
//	PDATA.pnull = ((void *)0);
//	PDATA.puint16 = (uint16)((0<<8)|(high));
//	ddr_print_28nm(&PDATA);
//	PDATA.pnull = ((void *)0);
//	PDATA.puint16 = (uint16)((0<<8)|(mid));
//	ddr_print_28nm(&PDATA);
//	PDATA.pnull = ((void *)0);
//	PDATA.puint16 = (uint16)((0<<8)|(low));
//	ddr_print_28nm(&PDATA);
	ddr_print_28nm("***");

	ddr_print_28nm("\r\n***0x55aa55aa");
	ddr_print_28nm(uint8tochar(TPRD));
	ddr_print_28nm("***");

	ddr_print_28nm("\r\n0x73747172");
#endif

    aclcd_mid = REG32(PUBL_ACLCDLR);
    REG32(0x1f80) = aclcd_mid;
	//reg_bits_set(PUBL_ACIOCR0,30,2,0);
	//dis auto selfrefresh
	REG32(0x30000060) |= 1;
	REG32(0x300001a0) |= (1<<31);      //DFIUDP0 dis auto udp
	REG32(PUBL_PGCR1) |= 1<<26;        //DIS VT

	//close zq cal
    //reg_bits_set(PUBL_ZQCR, 2, 1, 1);
	ddr_phy_bist_init(cs_num);

for(slew_rate=0;slew_rate<4;slew_rate++)
{
    reg_bits_set(PUBL_ACIOCR0,30,2,slew_rate);
	reg_bits_set(PUBL_DXCCR,13,2,slew_rate);
	for(bist_ds = DS_SCAN_MIN;bist_ds <= DS_SCAN_MAX; bist_ds++)
	{

		__mem_ds_set(bist_ds);
		__publ_ds_set(bist_ds);
		publ_ddr_scan(bist_ds,slew_rate);

		reset_ddr_scan_env(slew_rate,bist_ds,0);

	}

}

#ifdef LOG_TYPE_OPEN
    ddr_print_28nm("\r\n//-----DDR SCAN END!------");
#else
    ddr_print_28nm("\r\n0x656e6464");
#endif
}

#ifdef   __cplusplus
}
#endif

