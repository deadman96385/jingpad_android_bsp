/*********************************************************************************************************************
*
**Copyright:
**File Name:
**Description:

**Date:
**Version:
**
**
*
************************************************************************************************************************/

#include "ddr_common.h"
#include "ddr_scan_slice.h"
#include "ddr_init.h"

#ifdef SCAN_SLICE
#define PHY_SLICE  4
#define PHY_SLICE_DQ_NUM  8
#define LP3_PHY_CA_NUM   10
#define LP4_PHY_CA_NUM   12


uint32 freq_index=0;
uint32 bypass_mode=0;

//driver strength
#ifdef DRAM_LPDDR3
DDR_DS_E LPDDR3_PHY_DS[] = {PAD_DRV_34, PAD_DRV_40, PAD_DRV_48};
DDR_DS_E LPDDR3_DEVICE_DS[]={PAD_DRV_34, PAD_DRV_40, PAD_DRV_48};
DS_SLEW_E LP3_SLEW_RATE_ARRAY[] ={SLEW_RATE0};
#endif
#ifdef DRAM_LPDDR4
DDR_DS_E LPDDR4_DS[] = { PAD_DRV_48_LP4};
DDR_DS_E LPDDR4_DEVICE_DS[] = { PAD_DRV_60_LP4};
DDR_DS_E LPDDR4_ODT[] ={ PAD_DRV_60_LP4};
DS_SLEW_E LP4_SLEW_RATE_ARRAY[] ={SLEW_RATE0};
#endif

#define PASS __ddr_print("\t0x0")
#define FAIL  __ddr_print("\t0xf")

#define PASS_SYMBOL   __ddr_print("X")
#define FAIL_SYMBOL	  __ddr_print("_")


uint32 reg_bit_readl(uint32 addr,uint32 start_bit,uint32 bits_num)
{
   uint32 value;
   uint32 bit_mask = ((1<<bits_num)-1);
   value = (((__raw_readl(addr)>>start_bit) & bit_mask));
    return value;
}


/********************************************************************************************************************
*
**Name: uint8tochar
**Function: 
**
**
**
**
**
*
*********************************************************************************************************************/
typedef struct
{
	uint16 puint16;
	char   *pnull;
}pstruct_t;

static pstruct_t PDATA;

char p_data[5] = {0};
char *uint8tochar(uint8 val)
{
	uint8 high_byte = 0;
	uint8 low_byte = 0;
	uint8 temp;
	temp = val&0xf;
	if(temp > 9)
	{
		low_byte=temp-10+0x61;
	}else
	{
		low_byte=temp+0x30;
	}

	temp = (val&0xf0) >> 4;
	if(temp > 9)
	{
		high_byte=temp-10+0x61;
	}else
	{
		high_byte=temp+0x30;
	}

	p_data[0]= high_byte;
	p_data[1]= low_byte;
	p_data[2] = 0;
	return p_data;
}

uint32 pow(uint32 base,uint32 num)
{
	uint32 i =0;
	uint32 result =1;
	if(num==0)
	{
		return 1;
	}
	for(i=1;i<=num;i++)
	{
		result *=base;
	}
	return result;
}

void number_print(uint8 num)
{
	switch(num)
	{
		case 0:__ddr_print("0");break;
		case 1:__ddr_print("1");break;
		case 2:__ddr_print("2");break;
		case 3:__ddr_print("3");break;
		case 4:__ddr_print("4");break;
		case 5:__ddr_print("5");break;
		case 6:__ddr_print("6");break;
		case 7:__ddr_print("7");break;
		case 8:__ddr_print("8");break;
		case 9:__ddr_print("9");break;
		default:__ddr_print("print number error");break;
	}

}

void HextoDec(uint32 val)
{
	uint8 num[10];
	uint8 i=0;
	uint8 flag=0;
	for(i=10;i>0;i--)
	{
		num[i-1]=val/pow(10,i-1);
		val -=num[i-1]*pow(10,i-1);
	}
	for(i=10;i>0;i--)
	{
		if(num[i-1]!=0)
		{
			flag=i;
			break;
		}
	}
	for(i=flag;i>0;i--)
	{
	    number_print(num[i-1]);
	}

}


uint32 is_bypass_mode(uint32 chn_offset)
{
	uint32 force_bypass_mode=0;
	uint32 auto_bypass_mode=0;
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,0,1,0);
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,8,3,freq_index);
	force_bypass_mode =( REG32(CANDS_PHY0_(84)+chn_offset)>>8)&0xf;
	//reg_bit_set(CANDS_PHY0_(19)+chn_offset,16,3,0x7);
	//auto_bypass_mode =(REG32(CANDS_PHY0_(36)+chn_offset)>>8)&0x3;
	if(force_bypass_mode==0xc)
	{
		return 1;
	}else
	{
		return 0;
	}
}


#if PARAM_INFO_LOG
uint32 first_pass=0;
uint32 last_pass=0;
uint32 center_pass=0;

void param_to_pass_boundary_print()
{
	uint32 first_pass_percent=0;
	 uint32 last_pass_percent=0;
	first_pass_percent=((first_pass*1000)/512)-((first_pass/512)*1000);
	__ddr_print("\tfirst_pass:0x");
	__ddr_print(uint8tochar(first_pass>>8));
	__ddr_print(uint8tochar(first_pass));
	if(bypass_mode!=1)
	{
		if(first_pass_percent<100)
		{
			__ddr_print("(0.0");
		}else
		{
			__ddr_print("(0.");
		}
		HextoDec(first_pass_percent);
		__ddr_print(")");
	}
	last_pass_percent=((last_pass*1000)/512)-((last_pass/512)*1000);
	__ddr_print("\tlast_pass:0x");
	__ddr_print(uint8tochar(last_pass>>8));
	__ddr_print(uint8tochar(last_pass));
	if(bypass_mode!=1)
	{
		if(last_pass_percent<first_pass_percent)
		{
			__ddr_print("(1.");
		}else
		{
			__ddr_print("(0.");
		}
		HextoDec(last_pass_percent);
		__ddr_print(")");
	}
	center_pass=(first_pass+last_pass)/2;
	__ddr_print("\tcenter:0x");
	__ddr_print(uint8tochar(center_pass>>8));
	__ddr_print(uint8tochar(center_pass));

}

void param_to_start_boundary_print(uint32 dll_min,uint32 dll_max,uint32 step)
{
	__ddr_print("start:0x");
	__ddr_print(uint8tochar(dll_min>>8));
	__ddr_print(uint8tochar(dll_min));
	__ddr_print("\tend:0x");
	__ddr_print(uint8tochar(dll_max>>8));
	__ddr_print(uint8tochar(dll_max));
	__ddr_print("\tdll step:0x");
	__ddr_print(uint8tochar(step));
}

void param_to_slice_info_print(uint32 channel, uint32 vref, uint32 slew_rate, uint32 ds, uint32 slice_num)
{
  __ddr_print("\tchannel: ");
  __ddr_print(uint8tochar(channel));
  //__ddr_print("\tvref: ");
  //__ddr_print(uint8tochar(vref));
  __ddr_print("\tslew_rate: ");
  __ddr_print(uint8tochar(slew_rate));
  __ddr_print("\tds: ");
  __ddr_print(uint8tochar(ds));
  __ddr_print("\tslice_num: ");
  __ddr_print(uint8tochar(slice_num));
   __ddr_print("\n");
}

void param_to_dq_info_print(uint32 channel, uint32 vref, uint32 slew_rate, uint32 ds, uint32 slice_num, uint32 slice_dq_num)
{
  __ddr_print("\tchannel: ");
  __ddr_print(uint8tochar(channel));
  __ddr_print("\tvref: ");
  __ddr_print(uint8tochar(vref));
  __ddr_print("\tslew_rate: ");
  __ddr_print(uint8tochar(slew_rate));
  __ddr_print("\tds: ");
  __ddr_print(uint8tochar(ds));
  __ddr_print("\tslice_num: ");
  __ddr_print(uint8tochar(slice_num));
  __ddr_print("\tslice_dq_num: ");
  __ddr_print(uint8tochar(slice_dq_num));
  __ddr_print("\n"); 
}
#if CA_EN
void param_to_ca_info_print(uint32 channel, uint32 vref, uint32 slew_rate, uint32 ds, uint32 ca_num)
{
  __ddr_print("\tchannel: ");
  __ddr_print(uint8tochar(channel));
  __ddr_print("\tvref: ");
  __ddr_print(uint8tochar(vref));
  __ddr_print("\tslew_rate: ");
  __ddr_print(uint8tochar(slew_rate));
  __ddr_print("\tds: ");
  __ddr_print(uint8tochar(ds));
  __ddr_print("\tca_num: ");
  __ddr_print(uint8tochar(ca_num));
  __ddr_print("\n"); 
}
#endif
#endif
void line_num_print()
{
  __ddr_print("\r\n0x0");
}


void slew_rate_print(uint32 x)
{
 __ddr_print("\t0xc2");
  __ddr_print(uint8tochar(SLEW_RATE));
  __ddr_print("00");
  __ddr_print(uint8tochar(x));

}

void ds_print(uint32 x)
{
   __ddr_print("\t0xc1");
  __ddr_print(uint8tochar(DRIVE_STRENGTH));
  __ddr_print("00");
  uint32 ds =0;
  #ifdef DRAM_LPDDR3
  switch(x)
  {
	case PAD_DRV_34: ds = 34;break;
	case PAD_DRV_40: ds = 40;break;
	case PAD_DRV_48: ds = 48;break;
  }
 #endif
 #ifdef DRAM_LPDDR4
   switch(x)
  {
	case PAD_DRV_34: ds = 34;break;
	case PAD_DRV_40: ds = 40;break;
	case PAD_DRV_48_LP4: ds = 48;break;
	case PAD_DRV_60_LP4: ds = 60;break;
  }
 #endif
  __ddr_print(uint8tochar(ds));
}


void slice_num_print(uint32 x)
{
  __ddr_print("\t0xc3");
 __ddr_print(uint8tochar(SLICEX));
  __ddr_print("00");
  __ddr_print(uint8tochar(x));
}

#if CA_EN
void ca_num_print(uint32 x)
{
  __ddr_print("\t0xc3");
  __ddr_print(uint8tochar(SLICEX));
  __ddr_print("00");
  __ddr_print(uint8tochar(x));
}
#endif
void dq_vref_print(uint32 x,uint8 dll_type)
{
 #ifdef DRAM_LPDDR4
  __ddr_print("\t0xc4");
 #endif 
 if(bypass_mode=1)
 {
	if(dll_type==1)
	{
		__ddr_print(uint8tochar(DQ_VREF_DEVICE));
	}else
	{
		__ddr_print(uint8tochar(DQ_VREF_PHY));
	}
	return;
 }
 if((dll_type==3)||(dll_type==4))
 {
	__ddr_print(uint8tochar(DQ_VREF_PHY));
 }else
 {
	__ddr_print(uint8tochar(DQ_VREF_DEVICE));
 }
  __ddr_print("00");\
  __ddr_print(uint8tochar(x));

}

#define PARAM_SCAN_END   __ddr_print("\r\n0x434F4E54\r\n")
#define SCAN_LOG_START     __ddr_print("\r\n0x73747172")
#define SCAN_LOG_END	 __ddr_print("\r\n0x656E6464")

/**********************************************************************************************************************
*
**Name:  slave_delay_triggle
**Function:It enables the value of slave delay when you set a different value. 
**Calls:
**Called by:
**Input:
**Return:
*
***********************************************************************************************************************/
void slave_delay_triggle(uint32 chn_offset)
{
  reg_bit_set(CANDS_PHY0_(1027)+chn_offset,0,1,1);
}

/**********************************************************************************************************************
*
**Name:  ddr_scan_fixed_print
**Function:
**Calls:
**Called by:
**Input:
**Return:
*
***********************************************************************************************************************/
void ddr_scan_fixed_print(uint32 vref,uint32 slew_rate,uint32 ds,uint32 slice_num,uint8 mode)
{
	line_num_print();
	ds_print(ds);
	slew_rate_print(slew_rate);
	slice_num_print(slice_num);
	#ifdef DRAM_LPDDR4
	dq_vref_print(vref,mode);
	#endif	
}
#if CA_EN
void ddr_scan_ca_print(uint32 vref,uint32 slew_rate,uint32 ds,uint32 ca_num,uint32 ca_dll_cnt)
{
	line_num_print();
	dq_vref_print(vref);
	slew_rate_print(slew_rate);
	ds_print(ds);
	slice_num_print(ca_num);
	__ddr_print("\t0xb1");
	__ddr_print(uint8tochar(CA_DLL));
	__ddr_print(uint8tochar(ca_dll_cnt>>8));
	__ddr_print(uint8tochar(ca_dll_cnt));
}
#endif

void ddr_scan_dll_print(uint32 vref,uint32 slew_rate,uint32 ds,uint32 slice_num,uint32 dll_cnt,uint8 dll_type)
{
	ddr_scan_fixed_print(vref,slew_rate,ds,slice_num,dll_type);
	__ddr_print("\t0xb1");
	if(bypass_mode==1)
	{
		switch(dll_type)
		{
			case 1:
				__ddr_print(uint8tochar(WR_BYPASS_DLL));
				break;
			case 2:
				__ddr_print(uint8tochar(RDDQS_BYPASS_DLL));
				break;
			
		}
		__ddr_print(uint8tochar(dll_cnt>>8));
		__ddr_print(uint8tochar(dll_cnt));
		return;
	}
	switch(dll_type)
	{
		case 1:
			__ddr_print(uint8tochar(WRDQS_DLL));
			break;
		case 2:
			__ddr_print(uint8tochar(WRDQ_DLL));
			break;
		case 3:
			__ddr_print(uint8tochar(RDDQS_RISE_DLL));
			break;
		case 4:
			__ddr_print(uint8tochar(RDDQS_FALL_DLL));
			break;
	}
	__ddr_print(uint8tochar(dll_cnt>>8));
	__ddr_print(uint8tochar(dll_cnt));

}

/********************************************************************************************************************
*
**Name: mrw_issue
**Function: write mr register
**Calls:
**Called by:
**Return:
**
**
*
*********************************************************************************************************************/
void ds_mrw_issue(uint32 chn_offset, MRW_TYPE_E mrw_type, MRW_CS_E mrw_cs, uint32 mrw_num, uint32 cs0_data, uint32 cs1_data)
{
	if(mrw_cs == MRW_ALL_CS)
	{
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 24, 1,1);
        }else
        {
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 24, 1, 0);
	 }
	reg_bit_set(CANDS_CTL0_(164)+chn_offset, 8, 8, mrw_cs);


	if(mrw_type == MRW_SINGLE)
	{
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 23, 1, 1);
	}else
	{
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 23, 1, 0);
	}
	
	if(mrw_type == MRW_M16_M17)
	{
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 18, 1, 1);
	}else
	{
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 18, 1, 0);
	}

	if(mrw_type == MRW_M0_M1_M2_M3_M11)
	{
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 17, 1, 1);

	}else
	{
		reg_bit_set(CANDS_CTL0_(164)+chn_offset, 17, 1, 0);
	}
	
	reg_bit_set(CANDS_CTL0_(164)+chn_offset, 0, 8, mrw_num);
	//mrsingle_data
	reg_bit_set(CANDS_CTL0_(171)+chn_offset, 0, 8, cs0_data);
	reg_bit_set(CANDS_CTL0_(172)+chn_offset, 0, 8, cs1_data);
    //trigger the mrw sequence
	reg_bit_set(CANDS_CTL0_(164)+chn_offset, 25, 1, 1);
	//wait fot int_status--bit[26] mode register has completed and another mode register write may be issued
	while((__raw_readl(CANDS_CTL0_(319)+chn_offset)&0x04000000) != 0x04000000);

}

/********************************************************************************************************************
*
**Name: cands_phy_ds_set
**Function:set driver strength configration in phy registers
**Calls:
**Called by:
**Return:
**
**
*
*********************************************************************************************************************/

#ifdef DRAM_LPDDR4
public void vref_mrw_issue(uint32 chn_offset,uint32 range,uint32 mr_value)
{
    	reg_bit_set(CANDS_CTL0_(171)+chn_offset, 6,1,range);
	reg_bit_set(CANDS_CTL0_(171)+chn_offset, 0,6,mr_value);
	
	reg_bit_set(CANDS_CTL0_(164)+chn_offset, 0,8,0xe);//mr_num
	reg_bit_set(CANDS_CTL0_(164)+chn_offset, 8,8,0);//cs
	reg_bit_set(CANDS_CTL0_(164)+chn_offset,23,1,1);
	reg_bit_set(CANDS_CTL0_(164)+chn_offset,24,1,0);
	reg_bit_set(CANDS_CTL0_(164)+chn_offset,25,1,1);
	reg_bit_set(CANDS_CTL0_(164)+chn_offset,26,1,0);
	while((__raw_readl(CANDS_CTL0_(319)+chn_offset)&0x04000000) != 0x04000000);
}


public void cands_phy_dq_vref_set(uint32 chn_offset,uint32 mode_lv,uint32 en_lv,uint32 vrefsel_lv)
{
	//slice0
	reg_bit_set(CANDS_PHY0_(1041)+chn_offset,8,6,vrefsel_lv);
	reg_bit_set(CANDS_PHY0_(1041)+chn_offset,16,1,en_lv);
	reg_bit_set(CANDS_PHY0_(1041)+chn_offset,17,4,mode_lv);
	//slice1
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,0,6,vrefsel_lv);
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,8,1,en_lv);
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,9,4,mode_lv);
	//slice2
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,16,6,vrefsel_lv);
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,24,1,en_lv);
	reg_bit_set(CANDS_PHY0_(1042)+chn_offset,25,4,mode_lv);
	//slice3
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,0,6,vrefsel_lv);
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,8,1,en_lv);
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,9,4,mode_lv);
}

#if CA_EN
public void cands_phy_ca_vref_set(uint32 chn_offset,uint32 mode_lv,uint32 en_lv,uint32 vrefsel_lv)
{
	
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,16,6,vrefsel_lv);
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,24,1,en_lv);
	reg_bit_set(CANDS_PHY0_(1043)+chn_offset,25,4,mode_lv);

}
#endif
#endif


/********************************************************************************************************************
*
**Name: cands_phy_ds_set
**Function:set driver strength configration in phy registers
**Calls:
**Called by:
**Return:
**
**
*
*********************************************************************************************************************/
static void cands_phy_ds_set(uint32 chn_offset, DDR_DS_E ddr_ds)
{
	uint8 slice_num=0;
	for(slice_num=0;slice_num<4;slice_num++)
	{
		//phy_dqs_tsel_enable
  		reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_num*0x200, 25, 1, 1);
		//phy_dqs_tsel_select
  		reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_num*0x200, 8, 4, ddr_ds);
  		reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_num*0x200,12, 4, ddr_ds);
		//phy_dq_tsel_enable
  		reg_bit_set(CANDS_PHY0_(4)+chn_offset+slice_num*0x200, 17, 1, 1);
		//phy_dq_tsel_select
  		reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_num*0x200, 8, 4, ddr_ds);
  		reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_num*0x200,12, 4, ddr_ds);
	}
}

void cands_phy_odt_set(uint32 chn_offset, uint32 enable,DDR_DS_E ddr_odt)
{
	uint8 slice_num=0;
	for(slice_num=0;slice_num<4;slice_num++)
	{
		//phy_dqs_tsel_enable
  		reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_num*0x200, 24, 1, enable);
		//phy_dqs_tsel_select
  		reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_num*0x200, 0, 4, ddr_odt);
		reg_bit_set(CANDS_PHY0_(6)+chn_offset+slice_num*0x200, 4, 4, 0x0);
		//phy_dq_tsel_enable
  		reg_bit_set(CANDS_PHY0_(4)+chn_offset+slice_num*0x200, 16, 1, enable);
		//phy_dq_tsel_select
  		reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_num*0x200, 0, 4, ddr_odt);
		reg_bit_set(CANDS_PHY0_(5)+chn_offset+slice_num*0x200, 4, 4, 0x0);
		
	}
}


/********************************************************************************************************************
*
**Name: cands_ctrl_ds_set
**
**
**
**
**
*
*********************************************************************************************************************/
static void cands_ctrl_ds_set(uint32 chn_offset,DDR_DS_E ddr_ds)
{
	uint32 ddr_phy_ds_reg_val = 0;
	#ifdef DRAM_LPDDR3
	switch(ddr_ds)
	{
         case PAD_DRV_34:
		 ddr_phy_ds_reg_val = 1;
		 break;
	     case PAD_DRV_40:
		 ddr_phy_ds_reg_val = 2;
		 break;
	     case PAD_DRV_48:
		 ddr_phy_ds_reg_val =3;	
		 break;
	    case PAD_DRV_60:
		 ddr_phy_ds_reg_val =4;	
		 break;
         default:
		 ddr_phy_ds_reg_val =1;	
	}
	#endif
	#ifdef DRAM_LPDDR4
	switch(ddr_ds)
	{
		case PAD_DRV_34:
			ddr_phy_ds_reg_val = 0x31;
			break;
		case PAD_DRV_40:
			ddr_phy_ds_reg_val = 0x31;
			break;
		case PAD_DRV_48_LP4:
			ddr_phy_ds_reg_val = 0x29;
			break;
		case PAD_DRV_60_LP4:
			ddr_phy_ds_reg_val = 0x21;
			break;
	}
	#endif
	ds_mrw_issue(chn_offset, MRW_SINGLE, MRW_ALL_CS, 3, ddr_phy_ds_reg_val, ddr_phy_ds_reg_val);

}



public void cands_phy_slew_rate_set(uint32 chn_offset, DS_SLEW_E ds_slew)
{
	//phy_pad_data_drive
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,0,3,ds_slew); //slewn
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,3,3,ds_slew);//slewp
	//phy_pad_dqs_driver
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,16,3,ds_slew); //slewn
	reg_bit_set(CANDS_PHY0_(1057)+chn_offset,19,3,ds_slew);//slewp
}



#ifdef DRAM_LPDDR3
//DQS  for write 
uint32 wrdqs_dll_addr[4] =
{
	318,190,446,62
};
uint32 slice_wrdqs_dll[4];

//DQ  for write
uint32 wrdq_dll_addr[4][9] = 
{
	//slice2
	{314,314,315,315,316,316,317,317,318},
	//slice1
	{186,186,187,187,188,188,189,189,190},
	//slice3
	{442,442,443,443,444,444,445,445,446},
	//slice0
	{58,58,59,59,60,60,61,61,62},
};
uint32 slice_wrdq_dll[4][9];
uint32 wrdq_start_bit[9]=
{0,16,0,16,0,16,0,16,0};

//DQS for read
uint32 rddqs_fall_dll_addr[4][9] =
{
	//slice2
	{324,325,326,327,328,329,330,331,332},
	//slice1
	{196,197,198,199,200,201,202,203,204},
	//slice3
	{452,453,454,455,456,457,458,459,460},
	//slice0
	{68,69,70,71,72,73,74,75,76},
	
};
uint32 rddqs_rise_dll_addr[4][9] =
{
	//slice2
	{323,324,325,326,327,328,329,330,331},
	//slice1
	{195,196,197,198,199,200,201,202,203},
	//slice3
	{451,452,453,454,455,456,457,458,459},
	//slice0
	{67,68,69,70,71,72,73,74,75},
	
};

uint32 slice_rddqs_fall_dll[4][9];
uint32 slice_rddqs_rise_dll[4][9];

uint32 wrdq_bypass_dll_addr[4]=
{
	257,129,385,1
};
uint32 slice_wrdq_bypass_dll[4];
uint32 rddqs_bypass_dll_addr[4]=
{
	266,138,394,10
};
uint32 slice_rddqs_bypass_dll[4];
uint32 lp3_ddr_ds=0;
#else
//DQS  for write 
uint32 wrdqs_dll_addr[4] =
{
	62,190,318,446
};
uint32 slice_wrdqs_dll[4];

//DQ  for write
uint32 wrdq_dll_addr[4][9] = 
{
	//slice0
	{58,58,59,59,60,60,61,61,62},
	//slice1
	{186,186,187,187,188,188,189,189,190},
	//slice2
	{314,314,315,315,316,316,317,317,318},
	//slice3
	{442,442,443,443,444,444,445,445,446},
};
uint32 slice_wrdq_dll[4][9];
uint32 wrdq_start_bit[9]=
{0,16,0,16,0,16,0,16,0};

//DQS for read
uint32 rddqs_fall_dll_addr[4][9] =
{
	//slice0
	{68,69,70,71,72,73,74,75,76},
	//slice1
	{196,197,198,199,200,201,202,203,204},
	//slice2
	{324,325,326,327,328,329,330,331,332},
	//slice3
	{452,453,454,455,456,457,458,459,460},
};
uint32 rddqs_rise_dll_addr[4][9] =
{
	//slice0
	{67,68,69,70,71,72,73,74,75},
	//slice1
	{195,196,197,198,199,200,201,202,203},
	//slice2
	{323,324,325,326,327,328,329,330,331},
	//slice3
	{451,452,453,454,455,456,457,458,459},
};

uint32 slice_rddqs_fall_dll[4][9];
uint32 slice_rddqs_rise_dll[4][9];

uint32 wrdq_bypass_dll_addr[4]=
{
	1,129,257,385
};
uint32 slice_wrdq_bypass_dll[4];
uint32 rddqs_bypass_dll_addr[4]=
{
	10,138,266,394
};
uint32 slice_rddqs_bypass_dll[4];
uint32 odt_enable=0;
uint32 lp4_ddr_odt=0;
uint32 phy_dq_vref=0;
#endif

#if CA_EN
//CA
uint32 slice_ca_dll[4][6];
#endif

/*********************************************************************************************************************
*
**@Name:phy_dqs_dll_get
**@Function:
**@Calls:
**@Called by:
**@return
**
*
**********************************************************************************************************************/
void phy_dll_training_get(uint32 chn_offset)
{
	uint32 slice_num=0;
	uint32 slice_dq_num=0;
	if(bypass_mode==1)
	{
		for(slice_num=0;slice_num<4;slice_num++)
		{
			slice_wrdq_bypass_dll[slice_num] = reg_bit_readl(CANDS_PHY0_(wrdq_bypass_dll_addr[slice_num])+chn_offset,10, 8);
			slice_rddqs_bypass_dll[slice_num] = reg_bit_readl(CANDS_PHY0_(rddqs_bypass_dll_addr[slice_num])+chn_offset, 2, 8);
		}
		return;
	}
	
	for(slice_num=0;slice_num<4;slice_num++)
	{
		slice_wrdqs_dll[slice_num] = reg_bit_readl(CANDS_PHY0_(wrdqs_dll_addr[slice_num])+chn_offset, 16, 10);
		for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
		{
			slice_wrdq_dll[slice_num][slice_dq_num] = reg_bit_readl(CANDS_PHY0_(wrdq_dll_addr[slice_num][slice_dq_num])+chn_offset, wrdq_start_bit[slice_dq_num], 11);
			slice_rddqs_rise_dll[slice_num][slice_dq_num] = reg_bit_readl(CANDS_PHY0_(rddqs_rise_dll_addr[slice_num][slice_dq_num])+chn_offset,16, 10);
			slice_rddqs_fall_dll[slice_num][slice_dq_num] = reg_bit_readl(CANDS_PHY0_(rddqs_fall_dll_addr[slice_num][slice_dq_num])+chn_offset, 0, 10);
		}
	}
}




/*********************************************************************************************************************
*
**@Name:phy_dqs_dll_get
**@Function:
**@Calls:
**@Called by:
**@return
**
*
**********************************************************************************************************************/
#if CA_EN
public void phy_ca_dll_get(uint32 chn_offset)
{
	//SLICE 0
	slice_ca_dll[0][0] = reg_bit_readl(CANDS_PHY0_(543)+chn_offset, 8, 11);
	slice_ca_dll[0][1] = reg_bit_readl(CANDS_PHY0_(544)+chn_offset, 0, 11);
	slice_ca_dll[0][2] = reg_bit_readl(CANDS_PHY0_(544)+chn_offset,16, 11);
	slice_ca_dll[0][3] = reg_bit_readl(CANDS_PHY0_(545)+chn_offset, 0, 11);
	slice_ca_dll[0][4] = reg_bit_readl(CANDS_PHY0_(545)+chn_offset,16, 11);
	slice_ca_dll[0][5] = reg_bit_readl(CANDS_PHY0_(546)+chn_offset, 0, 11);
	//SLICE 1
	slice_ca_dll[1][0] = reg_bit_readl(CANDS_PHY0_(671)+chn_offset, 8, 11);
	slice_ca_dll[1][1] = reg_bit_readl(CANDS_PHY0_(672)+chn_offset, 0, 11);
	slice_ca_dll[1][2] = reg_bit_readl(CANDS_PHY0_(672)+chn_offset,16, 11);
	slice_ca_dll[1][3] = reg_bit_readl(CANDS_PHY0_(673)+chn_offset, 0, 11);
	slice_ca_dll[1][4] = reg_bit_readl(CANDS_PHY0_(673)+chn_offset,16, 11);
	slice_ca_dll[1][5] = reg_bit_readl(CANDS_PHY0_(674)+chn_offset, 0, 11);
	//SLICE 2
	slice_ca_dll[2][0] = reg_bit_readl(CANDS_PHY0_(799)+chn_offset, 8, 11);
	slice_ca_dll[2][1] = reg_bit_readl(CANDS_PHY0_(800)+chn_offset, 0, 11);
	slice_ca_dll[2][2] = reg_bit_readl(CANDS_PHY0_(800)+chn_offset,16, 11);
	slice_ca_dll[2][3] = reg_bit_readl(CANDS_PHY0_(801)+chn_offset, 0, 11);
	slice_ca_dll[2][4] = reg_bit_readl(CANDS_PHY0_(801)+chn_offset,16, 11);
	slice_ca_dll[2][5] = reg_bit_readl(CANDS_PHY0_(802)+chn_offset, 0, 11);
	//SLICE 3
	slice_ca_dll[3][0] = reg_bit_readl(CANDS_PHY0_(927)+chn_offset, 8, 11);
	slice_ca_dll[3][1] = reg_bit_readl(CANDS_PHY0_(928)+chn_offset, 0, 11);
	slice_ca_dll[3][2] = reg_bit_readl(CANDS_PHY0_(928)+chn_offset,16, 11);
	slice_ca_dll[3][3] = reg_bit_readl(CANDS_PHY0_(929)+chn_offset, 0, 11);
	slice_ca_dll[3][4] = reg_bit_readl(CANDS_PHY0_(929)+chn_offset,16, 11);
	slice_ca_dll[3][5] = reg_bit_readl(CANDS_PHY0_(930)+chn_offset, 0, 11);

}
#endif

/*********************************************************************************************************************
*
**@Name:phy_dqs_dll_get
**@Function:
**@Calls:
**@Called by:
**@return
**
**dll_type: 1-wrdqs 2-wrdq 3-rddqs_rise 4-rddqs_fall  normal mode
**             1-wr      2-rd     bypass mode
**
**
*
**********************************************************************************************************************/
void phy_dll_set(uint32 chn_offset,uint32 slice_num,uint8 dll_type,uint32 value,uint8 set_mode)
{
	uint32 dll_value=0;
	uint32 slice_dq_num=0;
	if(bypass_mode==1)
	{
		switch(dll_type)
		{
			case 1:
				(set_mode==1)?(dll_value=slice_wrdq_bypass_dll[slice_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(wrdq_bypass_dll_addr[slice_num])+chn_offset,10,8,dll_value);
				break;
			case 2:
				(set_mode==1)?(dll_value=value=slice_rddqs_bypass_dll[slice_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(rddqs_bypass_dll_addr[slice_num])+chn_offset,2,8,dll_value);
				break;
			default:while(1);
		}
	      return;
	}

	switch(dll_type)
	{
		case 1:
			(set_mode==1)?(dll_value=slice_wrdqs_dll[slice_num]):(dll_value=value);
			reg_bit_set(CANDS_PHY0_(wrdqs_dll_addr[slice_num])+chn_offset,16,10,dll_value);
			break;
		case 2:
			for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
			{
				(set_mode==1)?dll_value=(slice_wrdq_dll[slice_num][slice_dq_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(wrdq_dll_addr[slice_num][slice_dq_num])+chn_offset,wrdq_start_bit[slice_dq_num],11,dll_value);
			}
			break;
		case 3:
			for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
			{
				(set_mode==1)?(dll_value=slice_rddqs_rise_dll[slice_num][slice_dq_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(rddqs_rise_dll_addr[slice_num][slice_dq_num])+chn_offset,16,10,dll_value);
			}
			break;
		case 4:
			for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
			{
				(set_mode==1)?(dll_value=slice_rddqs_fall_dll[slice_num][slice_dq_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(rddqs_fall_dll_addr[slice_num][slice_dq_num])+chn_offset, 0,10,dll_value);
			}
			break;
		default:while(1);
	}
      slave_delay_triggle(chn_offset);

}

/*********************************************************************************************************************
*
**@Name:phy_dqs_dll_get
**@Function:
**@Calls:
**@Called by:
**@return
**
*
**********************************************************************************************************************/
#if CA_EN
public void phy_ca_dll_set(uint32 chn_offset,uint32 ca_num,uint32 value)
{
  #ifdef DRAM_LPDDR3
  switch(ca_num)
  {
		case 0:
			reg_bit_set(CANDS_PHY0_(927)+chn_offset, 8,11,value);
			break;
		case 1:
			reg_bit_set(CANDS_PHY0_(800)+chn_offset, 0,11,value);
			break;
		case 2:
			reg_bit_set(CANDS_PHY0_(799)+chn_offset, 8,11,value);
			break;
		case 3:
			reg_bit_set(CANDS_PHY0_(928)+chn_offset, 0,11,value);
			break;
		case 4:
			reg_bit_set(CANDS_PHY0_(673)+chn_offset, 0,11,value);
			break;
		case 5:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset,16,11,value);
			break;
		case 6:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset, 0,11,value);
			break;
		case 7:
			reg_bit_set(CANDS_PHY0_(671)+chn_offset, 8,11,value);
			break;
		case 8:
			reg_bit_set(CANDS_PHY0_(544)+chn_offset, 0,11,value);
			break;
		case 9:
			reg_bit_set(CANDS_PHY0_(543)+chn_offset, 8,11,value);
			break;
    }
  #endif
  #ifdef DRAM_LPDDR4
  	switch(ca_num)
	{
		case 0:
			reg_bit_set(CANDS_PHY0_(671)+chn_offset, 8,11,value);
			break;
		case 1:
			reg_bit_set(CANDS_PHY0_(644)+chn_offset, 8,11,value);
			break;
		case 2:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset,16,11,value);
			break;
		case 3:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset, 0,11,value);
			break;
		case 4:
			reg_bit_set(CANDS_PHY0_(543)+chn_offset, 8,11,value);
			break;
		case 5:
			reg_bit_set(CANDS_PHY0_(673)+chn_offset, 0,11,value);
			break;
		case 6:
			reg_bit_set(CANDS_PHY0_(799)+chn_offset, 8,11,value);
			break;
		case 7:
			reg_bit_set(CANDS_PHY0_(800)+chn_offset, 0,11,value);
			break;
		case 8:
			reg_bit_set(CANDS_PHY0_(927)+chn_offset, 8,11,value);
			break;
		case 9:
			reg_bit_set(CANDS_PHY0_(929)+chn_offset, 0,11,value);
			break;
		case 10:
			reg_bit_set(CANDS_PHY0_(928)+chn_offset, 0,11,value);
			break;
		case 11:
			reg_bit_set(CANDS_PHY0_(928)+chn_offset,16,11,value);
			break;
  		}	
  #endif
  slave_delay_triggle(chn_offset);

}

public void phy_ca_dll_reset(uint32 chn_offset,uint32 ca_num)
{
	#ifdef DRAM_LPDDR3
	switch(ca_num)
	{
		case 0:
			reg_bit_set(CANDS_PHY0_(927)+chn_offset, 8,11,slice_ca_dll[3][0]);
			break;
		case 1:
			reg_bit_set(CANDS_PHY0_(800)+chn_offset, 0,11,slice_ca_dll[2][1]);
			break;
		case 2:
			reg_bit_set(CANDS_PHY0_(799)+chn_offset, 8,11,slice_ca_dll[2][0]);
			break;
		case 3:
			reg_bit_set(CANDS_PHY0_(928)+chn_offset, 0,11,slice_ca_dll[3][2]);
			break;
		case 4:
			reg_bit_set(CANDS_PHY0_(673)+chn_offset, 0,11,slice_ca_dll[1][3]);
			break;
		case 5:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset, 16,11,slice_ca_dll[1][2]);
			break;
		case 6:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset, 0,11,slice_ca_dll[1][1]);
			break;
		case 7:
			reg_bit_set(CANDS_PHY0_(671)+chn_offset, 8,11,slice_ca_dll[1][0]);
			break;
		case 8:
			reg_bit_set(CANDS_PHY0_(544)+chn_offset, 0,11,slice_ca_dll[0][1]);
			break;
		case 9:
			reg_bit_set(CANDS_PHY0_(543)+chn_offset, 8,11,slice_ca_dll[0][0]);
			break;
	}
	#endif
	#ifdef DRAM_LPDDR4
	switch(ca_num)
	{
		case 0:
			reg_bit_set(CANDS_PHY0_(671)+chn_offset, 8,11,slice_ca_dll[1][0]);
			break;
		case 1:
			reg_bit_set(CANDS_PHY0_(644)+chn_offset, 8,11,slice_ca_dll[0][1]);
			break;
		case 2:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset,16,11,slice_ca_dll[1][2]);
			break;
		case 3:
			reg_bit_set(CANDS_PHY0_(672)+chn_offset, 0,11,slice_ca_dll[1][1]);
			break;
		case 4:
			reg_bit_set(CANDS_PHY0_(543)+chn_offset, 8,11,slice_ca_dll[1][0]);
			break;
		case 5:
			reg_bit_set(CANDS_PHY0_(673)+chn_offset, 0,11,slice_ca_dll[1][3]);
			break;
		case 6:
			reg_bit_set(CANDS_PHY0_(799)+chn_offset, 8,11,slice_ca_dll[2][0]);
			break;
		case 7:
			reg_bit_set(CANDS_PHY0_(800)+chn_offset, 0,11,slice_ca_dll[2][1]);
			break;
		case 8:
			reg_bit_set(CANDS_PHY0_(927)+chn_offset, 8,11,slice_ca_dll[3][0]);
			break;
		case 9:
			reg_bit_set(CANDS_PHY0_(929)+chn_offset, 0,11,slice_ca_dll[3][3]);
			break;
		case 10:
			reg_bit_set(CANDS_PHY0_(928)+chn_offset, 0,11,slice_ca_dll[3][1]);
			break;
		case 11:
			reg_bit_set(CANDS_PHY0_(928)+chn_offset,16,11,slice_ca_dll[3][2]);
			break;
			
	}
	#endif
   slave_delay_triggle(chn_offset);
}
#endif

/**********************************************************************************************************************
*
**Name:  ddr_scan_training_dll_print
**Function:
**Calls:
**Called by:
**Input:
**Return:
*
***********************************************************************************************************************/
#if DEBUG_SCAN
void ddr_scan_master_dll_print(uint32 chn_offset)
{
	uint32 dll_value=0;
	__ddr_print("\r\n");
	__ddr_print("*********Master Delay Line*************");
	__ddr_print("\nphy_master_dly_obs_0\n");
	reg_bit_set(CANDS_PHY0_(10)+chn_offset, 24, 1, 1);
	dll_value=reg_bit_readl(CANDS_PHY0_(35)+chn_offset,0,10);
	__ddr_print("0x");
	__ddr_print(uint8tochar(dll_value>>8));
	__ddr_print(uint8tochar(dll_value));
	__ddr_print("\t");
	__ddr_print("\n");
}

void ddr_scan_obs_print(uint32 chn_offset)
{
	uint32 dq_num=0;
	uint32 slice_num=0;
	uint32 obs_val=0;
	__ddr_print("\r\n");
	__ddr_print("*********Obs Value*************");
	for(dq_num=0;dq_num<8;dq_num++)
	{
		__ddr_print("\nphy_wdqlvl_dqdm_te_dly_obs\n");
		for(slice_num=0;slice_num<4;slice_num++)
		{
			reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_num*0x200,8,4,dq_num);
			obs_val=reg_bit_readl(CANDS_PHY0_(46)+chn_offset+slice_num*0x200,16,11);
			__ddr_print("0x");
			__ddr_print(uint8tochar(obs_val>>8));
			__ddr_print(uint8tochar(obs_val));
			__ddr_print("\t");
		}
		__ddr_print("\nphy_wdqlvl_dqdm_le_dly_obs\n");
		for(slice_num=0;slice_num<4;slice_num++)
		{
			reg_bit_set(CANDS_PHY0_(26)+chn_offset+slice_num*0x200,8,4,dq_num);
			obs_val=reg_bit_readl(CANDS_PHY0_(46)+chn_offset+slice_num*0x200,0,11);
			__ddr_print("0x");
			__ddr_print(uint8tochar(obs_val>>8));
			__ddr_print(uint8tochar(obs_val));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
}


void ddr_scan_training_dll_print(uint32 chn_offset)
{
	__ddr_print("\r\n");
	__ddr_print("*********Training Delay Line*************");
	uint32 slice_num = 0;
	uint32 slice_dq_num = 0;
if(1==bypass_mode)
{
	__ddr_print("\nphy_clk_wr_bypass_slave_delay_addr\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		HextoDec(wrdq_bypass_dll_addr[slice_num]);
		__ddr_print("\t");
	}
	__ddr_print("\nphy_clk_wr_bypass_slave_delay\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		__ddr_print("0x");
		__ddr_print(uint8tochar(slice_wrdq_bypass_dll[slice_num]>>8));
		__ddr_print(uint8tochar(slice_wrdq_bypass_dll[slice_num]));
		__ddr_print("\t");
	}
	__ddr_print("\nphy_rddqs_dq_bypass_slave_delay_addr\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		HextoDec(rddqs_bypass_dll_addr[slice_num]);
		__ddr_print("\t");
	}
	__ddr_print("\nphy_rddqs_dq_bypass_slave_delay\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		__ddr_print("0x");
		__ddr_print(uint8tochar(slice_rddqs_bypass_dll[slice_num]>>8));
		__ddr_print(uint8tochar(slice_rddqs_bypass_dll[slice_num]));
		__ddr_print("\t");
	}
	}
else{
	__ddr_print("\nphy_clk_wrdqs_slave_delay_addr\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		HextoDec(wrdqs_dll_addr[slice_num]);
		__ddr_print("\t");
	}
	__ddr_print("\nphy_clk_wrdqs_slave_delay\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		__ddr_print("0x");
		__ddr_print(uint8tochar(slice_wrdqs_dll[slice_num]>>8));
		__ddr_print(uint8tochar(slice_wrdqs_dll[slice_num]));
		__ddr_print("\t");
	}
	__ddr_print("\n");
	uint32 rddqs_gate_addr=0;
	uint32 rddqs_gate_value=0;
	__ddr_print("\nphy_rddqs_gate_slave_delay_addr\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		rddqs_gate_addr=76+slice_num*128;
		HextoDec(rddqs_gate_addr);
		__ddr_print("\t");
	}
	__ddr_print("\nphy_rddqs_gate_slave_delay\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		rddqs_gate_addr=76+slice_num*128;
		rddqs_gate_value=reg_bit_readl(CANDS_PHY0_(rddqs_gate_addr)+chn_offset, 16,10);
		__ddr_print("0x");
		__ddr_print(uint8tochar(rddqs_gate_value>>8));
		__ddr_print(uint8tochar(rddqs_gate_value));
		__ddr_print("\t");
	}
	__ddr_print("\n");
	__ddr_print("\nphy_clk_wrdqz_slave_delay_addr\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 9; slice_dq_num++)
		{
			HextoDec(wrdq_dll_addr[slice_num][slice_dq_num]);
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_clk_wrdqz_slave_delay\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 9; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(slice_wrdq_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(slice_wrdq_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_fall_slave_delay_addr\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 9; slice_dq_num++)
		{
			HextoDec(rddqs_fall_dll_addr[slice_num][slice_dq_num]);
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_fall_slave_delay\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 9; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(slice_rddqs_fall_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(slice_rddqs_fall_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_rise_slave_delay_addr\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 9; slice_dq_num++)
		{
			HextoDec(rddqs_rise_dll_addr[slice_num][slice_dq_num]);
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_rise_slave_delay\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 9; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(slice_rddqs_rise_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(slice_rddqs_rise_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	#if 0
	__ddr_print("\nphy_adr_clk_wr_slave_delay\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 6; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(slice_ca_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(slice_ca_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	#endif
  }
	
}
#if DRAM_LPDDR4
void ddr_scan_vref_print(uint32 chn_offset)
{
	uint32 slice_num = 0;
	uint32 dq_vref=0;
	uint32 mr12_ca_vref=0;
	uint32 mr14_dq_vref=0;
	__ddr_print("\r\n");
	__ddr_print("*********LP4 Vref Value*************");
	__ddr_print("\nphy_pad_vref_ctrl_dq_x\n");
	dq_vref = reg_bit_readl(CANDS_PHY0_(1041), 8, 14);
	__ddr_print("0x");
	__ddr_print(uint8tochar(dq_vref>>8));
	__ddr_print(uint8tochar(dq_vref));
	__ddr_print("\n");

	switch(freq_index)
	{
		case 0:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(867)+chn_offset, 0, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(868)+chn_offset, 8, 8);
			break;
		case 1:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(867)+chn_offset, 8, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(868)+chn_offset,16, 8);
			break;
		case 2:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(867)+chn_offset,16, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(868)+chn_offset,24, 8);
			break;
		case 3:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(867)+chn_offset,24, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(869)+chn_offset, 0, 8);
			break;
	}

	__ddr_print("\nmr12_data\n");
	__ddr_print("0x");
	__ddr_print(uint8tochar(mr12_ca_vref));
	__ddr_print("\n");
	__ddr_print("\nmr14_data\n");
	__ddr_print("0x");
	__ddr_print(uint8tochar(mr14_dq_vref));
	__ddr_print("\n");
}
#endif
#endif





/*********************************************************************************************************************
*
**Name: ddr_scan
*      phy_clk_wrdqs_slave_delay			-------0
*      phy_clk_wrdq_slave_delay			-------1
*      phy_rddqs_dq_rise_slave_delay		-------2
*      phy_rddqs_dq_fall_slave_delay		-------3
*	 phy_clk_wr_bypass_slave_delay 		-------4
*	 phy_rddqs_dq_bypass_slave_delay	-------5
*	 vref_range1						-------6
*	 vref_range2						-------7
*
***********************************************************************************************************************/
#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

#ifdef DRAM_LPDDR3
uint32 dll_cnt_min[4][8]=
{
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x00,0x00,0x00,0x00,0x00},
	{0x00,0x200,0x00,0x00,0x00,0x00}
};

uint32 dll_cnt_max[4][8]=
{
	{0x400,0x800,0x400,0x400,0xff,0xff},
	{0x400,0x800,0x400,0x400,0xff,0xff},
	{0x400,0x800,0x400,0x400,0xff,0xff},
	{0x200,0x380,0x100,0x100,0xff,0xff}
};
uint8 norm_dll_step=1;
uint8 bypass_dll_step=1;
#if CA_EN
//ca
#define CA_DLL_CNT_MIN       0x0
#define CA_DLL_CNT_MAX      0x800 //default:[0:0x800]
#endif
#else
uint32 dll_cnt_min[4][8]=
{
	{0x00,0x00,0x00,0x00,0x00,0x00}, //200m
	{0x00,0x240,0x00,0x00,0x00,0x00}, //400m
	{0x00,0x260,0x00,0x00,0x00,0x00}, //600m
	{0x00,0x2f0,0x00,0x00,0x00,0x00}  //1200m
};

uint32 dll_cnt_max[4][8]=
{
	{0x00,0x00,0x00,0x00,0x96,0x8c}, //200m
	{0x130,0x360,0x110,0x110,0xff,0xff}, //400m
	{0x128,0x380,0x110,0x110,0xff,0xff}, //600m
	{0x120,0x400,0x110,0x110,0xff,0xff}  //1200m
};
//phy range1 phy range2 ddr range0 range1
uint32 vref_cnt_min[4][4]=
{
	{0x00,0x00,0x00,0x00},
	{0x00,0x02,0x00,0x00},
	{0x00,0x02,0x00,0x00},
	{0x08,0x00,0X00,0x00}
};

uint32 vref_cnt_max[4][4]=
{
	{0x00,0x3f,0x00,0x32},
	{0x00,0x3f,0x00,0x32},
	{0x00,0x3f,0x00,0x32},
	{0x3a,0x00,0x33,0x00}
};
uint8 norm_dll_step=2;
uint8 bypass_dll_step=1;
uint32 vref_rd_step=2;
uint32 vref_wr_step=3;
uint32 dcdc_volt_min=700;
uint32 dcdc_volt_max=900;
#if CA_EN
//ca
#define CA_DLL_CNT_MIN       0x0
#define CA_DLL_CNT_MAX       0x800 //default:[0:0x800]
#endif
//PHY 15.3%-48.7%
//#define DQ_VREF_PHY_RANGE1_MIN 0x00
//#define DQ_VREF_PHY_RANGE1_MAX 0x3F
//PHY 3.3%-36.7% per 0.521%
//#define DQ_VREF_PHY_RANGE2_MIN 0x00
//#define DQ_VREF_PHY_RANGE2_MAX 0x00
#endif



/*********************************************************************************************************************
*
**@Name:ddr_reinit()
**@Function:
**@Calls:
**@Called by:
**@return
**
*
**********************************************************************************************************************/
void ddr_reinit()
{
	

}




/*********************************************************************************************************************
*
**@Name:phy_dqs_dll_get
**@Function:
**@Calls:
**@Called by:
**@return
**
*
**********************************************************************************************************************/
void ddr_scan_wrdqs(DDR_CHANNEL_NUM_E chn_num,uint32 slice_num,uint32 vref,uint32 slew_rate,uint32 ds)
{
	uint32 ret = 0;
	uint32 chn_offset = (chn_num == 0)?0:0x00800000;
	
	
	uint32 dqs_dll_cnt = 0;
	uint32 line_num = 0;
	uint32 add_dll_cnt =0;
	uint8 dll_step=norm_dll_step;
	if(bypass_mode==1)
	{
		return;
	}
	#if 1
	if(slice_wrdqs_dll[slice_num] > 0x1d0)
	{
		add_dll_cnt = 0x1d0;
	}else
	{
		add_dll_cnt = 0;
	}
	#endif
	for(dqs_dll_cnt = dll_cnt_min[freq_index][0]+add_dll_cnt;dqs_dll_cnt < dll_cnt_max[freq_index][0]+add_dll_cnt; dqs_dll_cnt+=dll_step)
	{	
		phy_dll_set(chn_offset,slice_num,1,dqs_dll_cnt,0);
		#if ENCRPTY_LOG
		if(slice_wrdqs_dll[slice_num] > 0x1D0)
		{
			ddr_scan_dll_print(vref, slew_rate,ds,slice_num,(dqs_dll_cnt-add_dll_cnt-dll_cnt_min[freq_index][0]),1);
		}else
		{
			ddr_scan_dll_print(vref, slew_rate,ds,slice_num, dqs_dll_cnt-dll_cnt_min[freq_index][0],1);
		}
		#endif
		ret = bist_test(chn_num);
		if(ret)
		{	
			#if ENCRPTY_LOG
			FAIL;
			#else
			FAIL_SYMBOL;
			#endif
		}else
		{	
			#if ENCRPTY_LOG
			PASS;
			#else
			PASS_SYMBOL;
			#endif
		}
	}
	phy_dll_set(chn_offset,slice_num,1,0x0,1);
	#if ENCRPTY_LOG
	PARAM_SCAN_END;
	#endif
	#if PARAM_INFO_LOG
	__ddr_print("\r\n");
	#endif
	
}

/*************************************************************************************************************
**
**@name:ddr_scan_dq_wr
**@function:scan DQ of each slice by DQ delay elements
**@@input param:
**@return void
**
*
***************************************************************************************************************/
void ddr_scan_wrdqz(DDR_CHANNEL_NUM_E chn_num,uint32 slice_num,uint32 vref,uint32 slew_rate,uint32 ds)
{
	uint32 ret = 0;
	uint32 wrdq_dll_cnt_min =0;
	uint32 wrdq_dll_cnt_max =0;
	uint8 dll_step=0;
	uint8 dll_type=0;
	#if PARAM_INFO_LOG
	uint8 pass_flag=1;
	uint8 fail_flag=1;
	#endif
	uint32 chn_offset = (chn_num == 0)?0:0x00800000;
	if(1==bypass_mode)
	{
		wrdq_dll_cnt_min=dll_cnt_min[freq_index][4];
		wrdq_dll_cnt_max=dll_cnt_max[freq_index][4];
		dll_step=bypass_dll_step;
		dll_type=1;
	}else
	{
		wrdq_dll_cnt_min=dll_cnt_min[freq_index][1];
		wrdq_dll_cnt_max=dll_cnt_max[freq_index][1];
		dll_step=norm_dll_step;
		dll_type=2;
	}	
	uint32 dq_dll_cnt = 0;
	//set delay line
	for(dq_dll_cnt = wrdq_dll_cnt_min;dq_dll_cnt < wrdq_dll_cnt_max;dq_dll_cnt+=dll_step)
	{	
		phy_dll_set(chn_offset, slice_num, 2,dq_dll_cnt,0);
		#if ENCRPTY_LOG
		ddr_scan_dll_print(vref, slew_rate,ds, slice_num,(dq_dll_cnt-wrdq_dll_cnt_min)/dll_step,dll_type);
		#endif
		ret = bist_test(chn_num);
		if(ret)
		{
			#if ENCRPTY_LOG
			FAIL;
			#else
			FAIL_SYMBOL;
			if((pass_flag==0)&&(fail_flag==1))
			{
				last_pass=dq_dll_cnt-dll_step;
				fail_flag=0;
			}
			if((last_pass-first_pass)<5*dll_step)
			{
				pass_flag=1;
			}
			#endif
		}else
		{
			#if ENCRPTY_LOG
			PASS;
			#else
			PASS_SYMBOL;
			if(pass_flag==1)
			{
				first_pass=dq_dll_cnt;
				pass_flag=0;
			}
			if((last_pass<=first_pass)||((last_pass-first_pass)<5*dll_step))
			{
				fail_flag=1;
			}
			#endif
		}
	}
	//reset delay line
	phy_dll_set(chn_offset, slice_num,2,0x0,1);
	#if ENCRPTY_LOG
	PARAM_SCAN_END;
	#endif

}
	
/*************************************************************************************************************
**
**@name:ddr_scan_dqz_rd
**@function:scan DQ of each slice by DQ delay elements
**@@input param:
**@return void
**
*
***************************************************************************************************************/
void ddr_scan_rddqs_dqz(DDR_CHANNEL_NUM_E chn_num,uint32 slice_num,uint32 vref,uint32 slew_rate,uint32 ds,uint8 dll_type)
{
	uint32 ret = 0;
	uint32 dq_dll_cnt = 0;
	uint32 chn_offset = (chn_num == 0)?0:0x00800000;
	uint32 rd_dll_cnt_min = 0;
	uint32 rd_dll_cnt_max = 0;
	uint8 dll_step=0;
	#if PARAM_INFO_LOG
	uint8 pass_flag=1;
	uint8 fail_flag=1;
	#endif
	 if(dll_type == 3 )
	{
		rd_dll_cnt_min = dll_cnt_min[freq_index][2];
		rd_dll_cnt_max = dll_cnt_max[freq_index][2];
	}
	 if(dll_type == 4)
	{
		rd_dll_cnt_min = dll_cnt_min[freq_index][3];
		rd_dll_cnt_max = dll_cnt_max[freq_index][3];
	}
	 dll_step=norm_dll_step;
	 if(1==bypass_mode)
	 {	
		rd_dll_cnt_min = dll_cnt_min[freq_index][5];
		rd_dll_cnt_max = dll_cnt_max[freq_index][5];
		dll_step=bypass_dll_step;
	 }
	//set delayline
	for(dq_dll_cnt = rd_dll_cnt_min;dq_dll_cnt < rd_dll_cnt_max;dq_dll_cnt+=dll_step)
	{	
		phy_dll_set(chn_offset, slice_num, dll_type,dq_dll_cnt,0);
		
		#if ENCRPTY_LOG
		ddr_scan_dll_print(vref, slew_rate,ds, slice_num,(dq_dll_cnt-rd_dll_cnt_min)/dll_step,dll_type);
		#endif
		ret = bist_test(chn_num);
		if(ret)
		{
			#if ENCRPTY_LOG
			FAIL;
			#else
			FAIL_SYMBOL;
			if((pass_flag==0)&&(fail_flag==1))
			{
				last_pass=dq_dll_cnt-dll_step;
				fail_flag=0;
			}
			if((last_pass-first_pass)<5*dll_step)
			{
				pass_flag=1;
			}
			#endif
		}else
		{	
			#if ENCRPTY_LOG
			PASS;
			#else
			PASS_SYMBOL;
			if(pass_flag==1)
			{
				first_pass=dq_dll_cnt;
				pass_flag=0;
			}
			if((last_pass<=first_pass)||((last_pass-first_pass)<5*dll_step))
			{
				fail_flag=1;
			}
			#endif
		}
	}
	//reset delay line 
	phy_dll_set(chn_offset, slice_num,dll_type,0x0,1);
	#if ENCRPTY_LOG
	PARAM_SCAN_END;
	#endif
}


#if 0
void ddr_scan_ca_lp4(DDR_CHANNEL_NUM_E chn_num,uint8 vref,uint8 ds,uint32 slew_rate)
{


}
#endif

/*
*
*
*
*/
uint32 compute_slave_delay_cnt(uint32 ddr_clk,uint32 chn_offset)
{
	uint32 master_dll=0;
	uint32 t_dll_element=0;
	uint32 tcnt =0;
	if(bypass_mode==0)
	{
		//phy_master_dly_lock_obs_select_x
		reg_bit_set(CANDS_PHY0_(19)+chn_offset,16,3,0x0);
		//sc_phy_snap_regs_x
		reg_bit_set(CANDS_PHY0_(10)+chn_offset,24,1,0x1);
		//phy_master_dly_lock_obs_x
		master_dll = reg_bit_readl(CANDS_PHY0_(35)+chn_offset, 0, 10);
		t_dll_element=10000000/(ddr_clk/1000000)/master_dll/4;
	}
	
	tcnt=1000000/(ddr_clk/1000000)/512;

	return tcnt;

}

/*************************************************************************************************************
**
**@name:ddr_scan_dq_wr
**@function:scan DQ of each slice by DQ delay elements
**@@input param:
**@return void
**
*
***************************************************************************************************************/
void ddr_scan_channel(DDR_CHANNEL_NUM_E chn_num,uint32 ddr_clk)
{
	int i = 0;
	int j = 0;
	#ifdef DRAM_LPDDR3
	uint32 lp3_phy_ds_array_size = 0;
	uint32 lp3_device_ds_array_size=0;
	#else
	uint32 lp4_ds_array_size = 0;
	uint32 lp4_odt_array_size =0;
	#endif
	uint32 slew_rate_array_size =0;
	uint32 tcnt = 0;

	#ifdef DRAM_LPDDR4
	uint32 vref_range1=0;
	uint32 vref_range2=0;
	#endif
	
	#if DEBUG_SCAN
	uint32 timer_start = 0;
	uint32 timer_end = 0;
	uint32 timer_total = 0;
	#endif
	uint32 chn_offset = (chn_num == 0)?0:0x00800000;
	
	//print parameters--- ddr scan script head
	#ifdef DRAM_LPDDR3
	__ddr_print("\r\n@@@@-1");
	#else
	__ddr_print("\r\n@@@@-2");
	#endif
	__ddr_print("\r\n********************************");  
	__ddr_print("\r\n*********0x28400000*********");   //project
	#ifdef DRAM_LPDDR3
	__ddr_print("\r\n*********0x33333333*********");              //lpddr3
	#endif
	#ifdef DRAM_LPDDR4
	__ddr_print("\r\n*********0x44444444*********");              //lpddr4
	#endif
	__ddr_print("\r\n*********");
	__ddr_print("0x");
	__ddr_print(uint8tochar(ddr_clk>>24));
	__ddr_print(uint8tochar(ddr_clk>>16));
	__ddr_print(uint8tochar(ddr_clk>>8));
	__ddr_print(uint8tochar(ddr_clk));
	__ddr_print("**********");
	tcnt=compute_slave_delay_cnt(ddr_clk, chn_offset);
	__ddr_print("\r\n*********0x55aa55aa");
	switch(freq_index)
	{
		case 0:
			__ddr_print(uint8tochar(tcnt));
			break;
		case 1:
			__ddr_print(uint8tochar(tcnt));
			break;
		case 2:
			__ddr_print(uint8tochar(tcnt));
			break;
		case 3:
			__ddr_print(uint8tochar(tcnt));
			break;
		default:while(1);
	}
	__ddr_print("*********");
	__ddr_print("\r\n********************************"); 
	//__ddr_print(uint8tochar(dll_lock_value));

	
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,0,1,0);
	reg_bit_set(CANDS_PHY0_(1024)+chn_offset,8,3,freq_index);

	#ifdef DRAM_LPDDR3
	//get training value for delay line
	phy_dll_training_get(chn_offset);
	//phy_ca_dll_get(chn_offset);
	lp3_ddr_ds=(REG32(CANDS_PHY0_(5)+chn_offset)>>8)&0xf;
	#else
	//get training value for delay line
	phy_dll_training_get(chn_offset);
	//phy_ca_dll_get(chn_offset);
	odt_enable=(REG32(CANDS_PHY0_(4)+chn_offset)>>16)&0x1;
	lp4_ddr_odt=(REG32(CANDS_PHY0_(5)+chn_offset)>>0)&0xf;
	phy_dq_vref=(REG32(CANDS_PHY0_(1041)+chn_offset)>>8)&0x3fff;
	#endif

	#if DEBUG_SCAN
	ddr_scan_master_dll_print(chn_offset);
	ddr_scan_obs_print(chn_offset);
	ddr_scan_training_dll_print(chn_offset);
	timer_start = REG32(0x40230004);
	#ifdef DRAM_LPDDR4
	ddr_scan_vref_print(chn_offset);
	#endif
	#endif

	SCAN_LOG_START;
	#ifdef DRAM_LPDDR3
	uint32 slice_num=0;
	uint8 dll_step=0;
	 uint8 scan_para_num=0;
	 uint8 dll_num=0;
	 uint8  dll_type=3;
	 #if PARAM_INFO_LOG
	 uint32 print_dll_min=0;
	 uint32 print_dll_max=0;
	 #endif
	slew_rate_array_size = ARRAYSIZE(LP3_SLEW_RATE_ARRAY);
	lp3_phy_ds_array_size = ARRAYSIZE(LPDDR3_PHY_DS);
	lp3_device_ds_array_size= ARRAYSIZE(LPDDR3_DEVICE_DS);
	(bypass_mode==1)?(scan_para_num=1):(scan_para_num=2);
	//wr
	for(dll_num=0;dll_num<scan_para_num;dll_num++)
	{
		for(slice_num=0;slice_num<PHY_SLICE;slice_num++)
		{
			for(i = 0; i< slew_rate_array_size; i++)
			{
				cands_phy_slew_rate_set(chn_offset, LP3_SLEW_RATE_ARRAY[i]);
				for(j =0; j < lp3_phy_ds_array_size;j++)
				{
		   		 	//ctl/pub ds set
		   	 		cands_phy_ds_set(chn_offset,LPDDR3_PHY_DS[j]);
					#if  PARAM_INFO_LOG
					if(1==bypass_mode)
					{
						__ddr_print("\rddr_scan_clk_dq_wr_bypass: ");
					}else
					{
						if(dll_num==0)
						{
							__ddr_print("\rddr_scan_clk_wrdqs: ");	
						}else
						{
							__ddr_print("\rddr_scan_clk_dq_wr: ");	
						}				
					}
					param_to_slice_info_print(chn_num,0x0,LP3_SLEW_RATE_ARRAY[i],LPDDR3_PHY_DS[j],slice_num);
					if(1==bypass_mode)
					{
						print_dll_min=dll_cnt_min[freq_index][4];
						print_dll_max=dll_cnt_max[freq_index][4];
						dll_step=bypass_dll_step;
					}else
					{
						print_dll_min=dll_cnt_min[freq_index][1];
						print_dll_max=dll_cnt_max[freq_index][1];
						dll_step=norm_dll_step;
					}
					param_to_start_boundary_print(print_dll_min, print_dll_max, dll_step);
					__ddr_print("\n");
					#endif
					if(dll_num==0)
					{
						//dqs for write
		    				ddr_scan_wrdqs(chn_num,slice_num,0,LP3_SLEW_RATE_ARRAY[i],LPDDR3_PHY_DS[j]);
					}else
					{
						//dq for write
		   				ddr_scan_wrdqz(chn_num,slice_num,0,LP3_SLEW_RATE_ARRAY[i],LPDDR3_PHY_DS[j]);
					}
		   					
				}
			}
		}
	}
	cands_phy_ds_set(chn_offset,lp3_ddr_ds);
	//rd
	for(dll_num=0;dll_num<scan_para_num;dll_num++)
	{
		for(slice_num=0;slice_num<PHY_SLICE;slice_num++)
		{
			for(i = 0; i< slew_rate_array_size; i++)
			{
				for(j =0; j < lp3_device_ds_array_size;j++)
				{
					//dram ds set
					cands_ctrl_ds_set(chn_offset, LPDDR3_DEVICE_DS[j]);
					#if  PARAM_INFO_LOG
					if(1==bypass_mode)
					{
						__ddr_print("\rddr_scan_rddqs_bypass: ");
					}else
					{
						if(dll_num==0)
						{
							__ddr_print("\rddr_scan_rddqs_rise: ");
						}else
						{
							__ddr_print("\rddr_scan_rddqs_fall: ");
						}
							
					}
					param_to_slice_info_print(chn_num,0x0,LP3_SLEW_RATE_ARRAY[i],LPDDR3_DEVICE_DS[j],slice_num);
					if(1==bypass_mode)
					{
						print_dll_min=dll_cnt_min[freq_index][5];
						print_dll_max=dll_cnt_max[freq_index][5];
						dll_step=bypass_dll_step;
							
					}else
					{
						if(dll_num==0)
						{
							print_dll_min=dll_cnt_min[freq_index][2];
							print_dll_max=dll_cnt_max[freq_index][2];
						}else
						{
							print_dll_min=dll_cnt_min[freq_index][3];
							print_dll_max=dll_cnt_max[freq_index][3];
						}
							dll_step=norm_dll_step;
							
					}
					param_to_start_boundary_print(print_dll_min, print_dll_max, dll_step);
					__ddr_print("\n");
					#endif
					(bypass_mode==1)?(dll_type=2):((dll_num==0)?(dll_type=3):(dll_type=4));
					ddr_scan_rddqs_dqz(chn_num,slice_num,0,LP3_SLEW_RATE_ARRAY[i],LPDDR3_DEVICE_DS[j],dll_type);
				
				}
			}
		}
	}
	
     #endif
     #ifdef DRAM_LPDDR4
	 uint32 slice_num=0;
	 uint32 dll_num=0;
	 uint32 rd_ds=0;
	 uint32 wr_ds=0;
	 uint32 dq_vref_min;
	 uint32 dq_vref_max;
	 uint8 dll_step=0;
	 uint8 scan_para_num=0;
	 uint8  dll_type=3;
	 #if PARAM_INFO_LOG
	 uint32 print_dll_min=0;
	 uint32 print_dll_max=0;
	 #endif
	 slew_rate_array_size = ARRAYSIZE(LP4_SLEW_RATE_ARRAY);
       lp4_ds_array_size = ARRAYSIZE(LPDDR4_DS);
	  #if 1
	 //rd
	if(freq_index==3)
	{
	 	lp4_odt_array_size=ARRAYSIZE(LPDDR4_ODT);
	}else
	{
		lp4_odt_array_size=ARRAYSIZE(LPDDR4_DEVICE_DS);
	}
	vref_range1 =vref_cnt_max[freq_index][1]-vref_cnt_min[freq_index][1];
	vref_range2= vref_cnt_max[freq_index][0]-vref_cnt_min[freq_index][0];
	if(vref_range2 !=0)
	{
		dq_vref_min = vref_cnt_min[freq_index][0];
	}else
	{
		dq_vref_min=vref_cnt_min[freq_index][1]+0x3f;
	}
	if(vref_range1 !=0)
	{
             dq_vref_max= vref_cnt_max[freq_index][1]+0x3f;
	}else
	{
		dq_vref_max=vref_cnt_max[freq_index][0];
	}
	if(bypass_mode==1)
	{
		scan_para_num=1;
	}else
	{
		scan_para_num=2;
	}
	for(dll_num=0;dll_num<scan_para_num;dll_num++)
	{
			for(slice_num=0;slice_num<PHY_SLICE;slice_num++)
			{
				for(i = 0; i< slew_rate_array_size; i++)
				{
					cands_phy_slew_rate_set(chn_offset, LP4_SLEW_RATE_ARRAY[i]);
					for(j =0; j < lp4_odt_array_size;j++)
					{
		   	 			//ctl/pub ds set
		    				//cands_ctrl_ds_set(chn_offset, LPDDR4_DS[j]);
		    				if(freq_index==3)
						{
							rd_ds=LPDDR4_ODT[j];
							cands_phy_odt_set(chn_offset, 0x1,rd_ds);
						}else
						{
							rd_ds= LPDDR4_DEVICE_DS[j];
							cands_ctrl_ds_set(chn_offset, rd_ds);
						}
		    				uint32 dq_vref_phy_lv = 0;
						#if  PARAM_INFO_LOG
						if(1==bypass_mode)
						{
							__ddr_print("\rddr_scan_rddqs_bypass: ");
						}else
						{
							if(dll_num==0)
							{
								__ddr_print("\rddr_scan_rddqs_rise: ");
							}else
							{
								__ddr_print("\rddr_scan_rddqs_fall: ");
							}
							
						}
						param_to_slice_info_print(chn_num,0x0,LP4_SLEW_RATE_ARRAY[i],rd_ds,slice_num);
						if(1==bypass_mode)
						{
							print_dll_min=dll_cnt_min[freq_index][5];
							print_dll_max=dll_cnt_max[freq_index][5];
							dll_step=bypass_dll_step;
							
						}else
						{
							if(dll_num==0)
							{
								print_dll_min=dll_cnt_min[freq_index][2];
								print_dll_max=dll_cnt_max[freq_index][2];
							}else
							{
								print_dll_min=dll_cnt_min[freq_index][3];
								print_dll_max=dll_cnt_max[freq_index][3];
							}
							dll_step=norm_dll_step;
							
						}
						param_to_start_boundary_print(print_dll_min, print_dll_max, dll_step);
						__ddr_print("\n");
						#endif
		      				for(dq_vref_phy_lv =dq_vref_min;dq_vref_phy_lv < dq_vref_max;dq_vref_phy_lv +=vref_rd_step)
		      				{
							//mode_lv 0x6:lp4 range1 0x7:lp4 range2
							if(vref_range2!=0)
							{    
								if(dq_vref_phy_lv<0x3f)
								{
									cands_phy_dq_vref_set(chn_offset, 0x7, 0x1, dq_vref_phy_lv);
								}
							}
							if(vref_range1!=0)
							{
								if(dq_vref_phy_lv>=0x3f)
								{
									cands_phy_dq_vref_set(chn_offset, 0x6, 0x1, dq_vref_phy_lv-0x3f);
								}else
								{
									cands_phy_dq_vref_set(chn_offset, 0x6, 0x1, dq_vref_phy_lv);
								}	
							}
							(bypass_mode==1)?(dll_type=2):((dll_num==0)?(dll_type=3):(dll_type=4));
							//dq for read
							ddr_scan_rddqs_dqz(chn_num,slice_num,dq_vref_phy_lv,LP4_SLEW_RATE_ARRAY[i],rd_ds,dll_type); //fall	
							#if PARAM_INFO_LOG
							__ddr_print(uint8tochar(dq_vref_phy_lv));
							param_to_pass_boundary_print();
							__ddr_print("\n");
							#endif
						}
						#if PARAM_INFO_LOG
						PARAM_SCAN_END;
						#endif
		    				//ca
		   				//ddr_scan_ca(chn_num, 0, ds_array_size);
		  			}
				}
			}
	}
	#endif
	#if 1
	if(freq_index==3)
	{
		cands_phy_odt_set(chn_offset,odt_enable,lp4_ddr_odt);
	}else
	{
		cands_ctrl_ds_set(chn_offset, PAD_DRV_40);
	}
	cands_phy_dq_vref_set(chn_offset, (phy_dq_vref>>9)&0xf, (phy_dq_vref>>8)&0x1, phy_dq_vref&0x3f);
	#endif
	#if 1
	vref_range1 =vref_cnt_max[freq_index][2]-vref_cnt_min[freq_index][2];
	vref_range2= vref_cnt_max[freq_index][3]-dll_cnt_min[freq_index][3];
	if(vref_range1 !=0)
	{
		dq_vref_min = vref_cnt_min[freq_index][2];
	}else
	{
		dq_vref_min=vref_cnt_min[freq_index][3]+0x32;
	}
	if(vref_range2 !=0)
	{
             dq_vref_max= vref_cnt_max[freq_index][3]+0x32;
	}else
	{
		dq_vref_max=vref_cnt_max[freq_index][2];
	}
	//wr
	for(slice_num=0;slice_num<PHY_SLICE;slice_num++)
	{
		for(i = 0; i< slew_rate_array_size; i++)
		{
			cands_phy_slew_rate_set(chn_offset, LP4_SLEW_RATE_ARRAY[i]);
			for(j =0; j < lp4_ds_array_size;j++)
			{
		   	 	//ctl/pub ds set
		    		//cands_ctrl_ds_set(chn_offset, LPDDR4_DS[j]);
		    		wr_ds=LPDDR4_DS[j];
		    		cands_phy_ds_set(chn_offset,wr_ds);
		    	       uint32 dq_vref_device_lv = 0;
				#if  PARAM_INFO_LOG
				if(1==bypass_mode)
				{
					__ddr_print("\rddr_scan_clk_dq_wr_bypass: ");
				}else
				{
					
					__ddr_print("\rddr_scan_clk_dq_wr: ");					
				}
				param_to_slice_info_print(chn_num,0x0,LP4_SLEW_RATE_ARRAY[i],wr_ds,slice_num);
				if(1==bypass_mode)
				{
					print_dll_min=dll_cnt_min[freq_index][4];
					print_dll_max=dll_cnt_max[freq_index][4];
					dll_step=bypass_dll_step;
				}else
				{
					print_dll_min=dll_cnt_min[freq_index][1];
					print_dll_max=dll_cnt_max[freq_index][1];
					dll_step=norm_dll_step;
				}
				param_to_start_boundary_print(print_dll_min, print_dll_max, dll_step);
				__ddr_print("\n");
				#endif
		      		for(dq_vref_device_lv =dq_vref_min;dq_vref_device_lv < dq_vref_max;dq_vref_device_lv +=vref_wr_step)
		      		{
					//mode_lv 0x6:lp4 range1 0x7:lp4 range2
					if(vref_range1!=0)
					{    
						if(dq_vref_device_lv<0x32)
						{
							vref_mrw_issue(chn_offset,0 , dq_vref_device_lv);
						}
					}
					if(vref_range2!=0)
					{
						if(dq_vref_device_lv>=0x32)
						{
							vref_mrw_issue(chn_offset,1, dq_vref_device_lv-0x32);
						}else
						{
							vref_mrw_issue(chn_offset,0, dq_vref_device_lv);
						}	
					}
					//dqs for write
					//ddr_scan_wrdqs(chn_num,slice_num,dq_vref_phy_lv,LP4_SLEW_RATE_ARRAY[i],LPDDR4_DS[j]);
					//dq for write
					ddr_scan_wrdqz(chn_num,slice_num,dq_vref_device_lv,LP4_SLEW_RATE_ARRAY[i],wr_ds);		
					#if PARAM_INFO_LOG
					__ddr_print(uint8tochar(dq_vref_device_lv));
					param_to_pass_boundary_print();
					__ddr_print("\n");
					#endif
				}
				
				#if PARAM_INFO_LOG
				PARAM_SCAN_END;
				#endif
		    		//ca
		   		//ddr_scan_ca(chn_num, 0, ds_array_size);
		  	}
		}
	}
	#endif
#endif
	SCAN_LOG_END;
	#if DEBUG_SCAN
	timer_end = REG32(0x40230004);
	timer_total = timer_end - timer_start;
	__ddr_print("\r\nTotal Scan Time: ");
	__ddr_print("0x");
	__ddr_print(uint8tochar(timer_total>>24));
	__ddr_print(uint8tochar(timer_total>>16));
	__ddr_print(uint8tochar(timer_total>>8));
	__ddr_print(uint8tochar(timer_total));
	#endif
}


void update_master_dll_close(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num == 0)?0:0x00800000;
	switch(freq_index)
	{
		case 0:
			break;
		case 1:
			reg_bit_set(CANDS_CTL0_(625)+chn_offset, 0,16,0x0);//upd_ctlupd_high_threshold
			reg_bit_set(CANDS_CTL0_(625)+chn_offset,16,16,0x0);//upd_ctlupd_norm_threshold
			reg_bit_set(CANDS_CTL0_(626)+chn_offset, 0,16,0xffff);//upd_ctlupd_sw_promote_threshold
			reg_bit_set(CANDS_CTL0_(626)+chn_offset,16,16,0x0);//upd_ctlupd_timeout
			reg_bit_set(CANDS_CTL0_(627)+chn_offset,16,16,0xffff);//upd_phyupd_dfi_promote_threshold
			break;
		case 2:
			reg_bit_set(CANDS_CTL0_(690)+chn_offset, 0,16,0x0);//upd_ctlupd_high_threshold
			reg_bit_set(CANDS_CTL0_(690)+chn_offset,16,16,0x0);//upd_ctlupd_norm_threshold
			reg_bit_set(CANDS_CTL0_(691)+chn_offset, 0,16,0xffff);//upd_ctlupd_sw_promote_threshold
			reg_bit_set(CANDS_CTL0_(691)+chn_offset,16,16,0x0);//upd_ctlupd_timeout
			reg_bit_set(CANDS_CTL0_(692)+chn_offset,16,16,0xffff);//upd_phyupd_dfi_promote_threshold
			break;
		case 3:
			reg_bit_set(CANDS_CTL0_(755)+chn_offset, 0,16,0x0);//upd_ctlupd_high_threshold
			reg_bit_set(CANDS_CTL0_(755)+chn_offset,16,16,0x0);//upd_ctlupd_norm_threshold
			reg_bit_set(CANDS_CTL0_(756)+chn_offset, 0,16,0xffff);//upd_ctlupd_sw_promote_threshold
			reg_bit_set(CANDS_CTL0_(756)+chn_offset,16,16,0x0);//upd_ctlupd_timeout
			reg_bit_set(CANDS_CTL0_(757)+chn_offset,16,16,0xffff);//upd_phyupd_dfi_promote_threshold
			reg_bit_set(CANDS_PI0_(287)+chn_offset, 0,16,0x0);//pi_tdfi_ctrlupd_max
			break;
	}

	//ctrlupd_reg_per_aref_en  master delay line
	if(1==bypass_mode)
	{
		reg_bit_set(CANDS_CTL0_(316)+chn_offset,16,1,0x1);	
	}else
	{
		reg_bit_set(CANDS_CTL0_(316)+chn_offset,16,1,0x0);
		reg_bit_set(CANDS_PI0_(278)+chn_offset,8,1,0x0);  //PI_CTRLUPD_REQ_PER_AREF_EN
	}

	reg_bit_set(CANDS_CTL0_(160)+chn_offset,16,4,0x0);
} 



/*************************************************************************************************************
**
**@name:ddr_scan_dq_wr
**@function:scan DQ of each slice by DQ delay elements
**@@input param:
**@return void
**
*
***************************************************************************************************************/
void whale2_ddr_scan(uint32 ddr_clk)
{
    
    volatile uint32 i =0;
    uint32 efuse_value=0;
    uint32 dcdc_volt=0;
    uint32 dcdc_volt_step=50;
    #if PARAM_INFO_LOG
    for(i=0;i<2;i++)
    {
		 efuse_value=ddie_efuse_read(i);
		 __ddr_print("\nUID:0x");
    		__ddr_print(uint8tochar(efuse_value>>24));
    		__ddr_print(uint8tochar(efuse_value>>16));
    		__ddr_print(uint8tochar(efuse_value>>8));
		__ddr_print(uint8tochar(efuse_value));
		__ddr_print("\n");
     }
     #endif
    freq_index=(REG32(CANDS_CTL0_(167))>>8)&0x7;
    bypass_mode=is_bypass_mode(0);

   
    update_master_dll_close(0);
    #ifdef DRAM_LPDDR4
     update_master_dll_close(1);
    #endif

    #if 0
    for(dcdc_volt=dcdc_volt_min;dcdc_volt<=dcdc_volt_max;dcdc_volt+=dcdc_volt_step)
    {
    		__ddr_print("\nVDD CORE:");
    		HextoDec(dcdc_volt);
    		__ddr_print("mV");
		__ddr_print("\n");
    		dcdc_calibrate(12,dcdc_volt);
		ddr_scan_channel(DDR_CHANNEL_0,ddr_clk);
   		 #ifdef DRAM_LPDDR4
    		for(i=0;i<0xff;i++);
    		//ddr_scan_channel(DDR_CHANNEL_1,ddr_clk);
    		#endif
	}
	#else
	ddr_scan_channel(DDR_CHANNEL_0,ddr_clk);
	 #ifdef DRAM_LPDDR4
    	for(i=0;i<0xff;i++);
    	ddr_scan_channel(DDR_CHANNEL_1,ddr_clk);
    	#endif
	#endif
    

}
#endif




