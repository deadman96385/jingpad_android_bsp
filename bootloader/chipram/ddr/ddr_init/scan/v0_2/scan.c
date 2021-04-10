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
#include "scan.h"
#include "ddr_init.h"


#define PHY_SLICE  4
#ifdef SCAN_SLICE
#define PHY_SLICE_DQ_NUM  1
#else
#define PHY_SLICE_DQ_NUM  8
#endif

#ifdef DRAM_LPDDR3
#define PHY_CA_NUM   10
#else
#define PHY_CA_NUM   12
#endif

#define ARRAYSIZE(a) (sizeof(a)/sizeof(a[0]))

struct DDR_SCAN_INFO_G
{

	uint32 freq_num;
	FREQ_MODE_E freq_mode;
	MRW_CS_E cs_num;
	uint32 phy_ds;
	uint32 phy_odt;
	uint32 device_ds;
	uint32 device_odt;
	uint32 slew_rate;
	uint32 phy_vref;
	uint32 device_vref;
};
struct DDR_SCAN_INFO_G  scan_info;
 struct DDR_SCAN_INFO_G *scan_info_g=&scan_info;


struct IO_INFO_CFG_T
{
	SCAN_TYPE_E type;
	uint32 slice_num;
	uint32 dq_num;
	uint32 ds;
	uint32 slew_rate;
	uint32 vref;
	uint32 dll;
};

DS_SLEW_E SLEW_RATE_ARRAY[] ={SLEW_RATE0,SLEW_RATE1,SLEW_RATE2};

//driver strength
#ifdef DRAM_LPDDR3
DDR_DS_E LP3_DS[] = { PAD_DRV_40, PAD_DRV_48,PAD_DRV_60};

#endif
#ifdef DRAM_LPDDR4
DDR_DS_E LP4_DS[] = {PAD_DRV_40, PAD_DRV_48_LP4,PAD_DRV_60_LP4};
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

uint32 wrdq_dll[4][8];
uint32 rddqs_fall_dll[4][8];
uint32 rddqs_rise_dll[4][8];
uint32 ca_dll[PHY_CA_NUM];
uint32 rddqs_bypass_dll[4];
uint32 wrdq_bypass_dll[4];
#ifndef ENCRPTY_LOG
uint32 wrdq_start_dll[4][8];
uint32 wrdq_end_dll[4][8];
uint32 wrdq_center_dll[4][8];
uint32 rddqs_fall_start_dll[4][8];
uint32 rddqs_fall_end_dll[4][8];
uint32 rddqs_fall_center_dll[4][8];
uint32 rddqs_rise_start_dll[4][8];
uint32 rddqs_rise_end_dll[4][8];
uint32 rddqs_rise_center_dll[4][8];
uint32 ca_center_dll[PHY_CA_NUM];
uint32 rddqs_bypass_center_dll[4];
uint32 wrdq_bypass_center_dll[4];
#endif


#ifndef ENCRPTY_LOG
uint32 first_pass=0;
uint32 last_pass=0;
uint32 center_pass=0;

void param_to_pass_boundary_print(struct IO_INFO_CFG_T *io_info)
{
	uint32 first_pass_percent=0;
	 uint32 last_pass_percent=0;
	 uint32 state=0;
	 uint32 pass_delta=0;
	first_pass_percent=((first_pass*1000)/512)-((first_pass/512)*1000);
	__ddr_print("\tfirst_pass:0x");
	__ddr_print(uint8tochar(first_pass>>8));
	__ddr_print(uint8tochar(first_pass));
	if(scan_info_g->freq_mode==NORMAL_MODE)
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
	if(scan_info_g->freq_mode==NORMAL_MODE)
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
	pass_delta=last_pass-first_pass;
	__ddr_print("\tpass_delta:0x");
	__ddr_print(uint8tochar(pass_delta>>8));
	__ddr_print(uint8tochar(pass_delta));
	center_pass=(first_pass+last_pass)/2;
	if((io_info->ds==scan_info_g->phy_ds)||(io_info->ds==scan_info_g->device_ds))
	{
		switch(io_info->type)
		{
			case WR_BYPASS_DLL:
				wrdq_bypass_center_dll[io_info->slice_num]=center_pass;
				break;
			case RDDQS_BYPASS_DLL:
				rddqs_bypass_center_dll[io_info->slice_num]=center_pass;
				break;
			case WRDQ_DLL:
				wrdq_start_dll[io_info->slice_num][io_info->dq_num]=first_pass;
				wrdq_end_dll[io_info->slice_num][io_info->dq_num]=last_pass;
				wrdq_center_dll[io_info->slice_num][io_info->dq_num]=center_pass;
				break;
			case RDDQS_FALL_DLL:
				if(io_info->vref==scan_info.phy_vref)
				{
					rddqs_fall_start_dll[io_info->slice_num][io_info->dq_num]=first_pass;
					rddqs_fall_end_dll[io_info->slice_num][io_info->dq_num]=last_pass;
				rddqs_fall_center_dll[io_info->slice_num][io_info->dq_num]=center_pass;
				}
				break;
			case RDDQS_RISE_DLL:
				if(io_info->vref==scan_info.phy_vref)
				{
					rddqs_rise_start_dll[io_info->slice_num][io_info->dq_num]=first_pass;
					rddqs_rise_end_dll[io_info->slice_num][io_info->dq_num]=last_pass;
				rddqs_rise_center_dll[io_info->slice_num][io_info->dq_num]=center_pass;
				}
				break;
			default:while(1);

		}
	}

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

void param_to_slice_info_print(struct IO_INFO_CFG_T *io_info)
{
  __ddr_print("\tchannel: ");
  __ddr_print(uint8tochar(0));
  //__ddr_print("\tvref: ");
  //__ddr_print(uint8tochar(vref));
  __ddr_print("\tslew_rate: ");
  __ddr_print(uint8tochar(io_info->slew_rate));
  __ddr_print("\tds: ");
  switch(io_info->ds)
  {
	case PAD_DRV_40:
		__ddr_print("40ohm");
		break;
	case PAD_DRV_48:
		__ddr_print("48ohm");
		break;
  }
  //__ddr_print(uint8tochar(io_info->ds));
  __ddr_print("\tslice_num: ");
  __ddr_print(uint8tochar(io_info->slice_num));
  __ddr_print("\tdq_num: ");
  __ddr_print(uint8tochar(io_info->dq_num));
   __ddr_print("\n");
}

void param_to_ca_info_print(struct IO_INFO_CFG_T *io_info)
{
  __ddr_print("\tchannel: ");
  __ddr_print(uint8tochar(0));
  __ddr_print("\tslew_rate: ");
  __ddr_print(uint8tochar(io_info->slew_rate));
  __ddr_print("\tds: ");
  __ddr_print(uint8tochar(io_info->ds));
  __ddr_print("\tca_num: ");
  __ddr_print(uint8tochar(io_info->dq_num));
  __ddr_print("\n");
}
#endif
void line_num_print()
{
  __ddr_print("\r\n0x0");
}


void scan_io_print(SCAN_TYPE_E type,uint32 val)
{
	uint32 print_val=0;
	switch(type)
	{
		case DRIVE_STRENGTH:
			   __ddr_print("\t0xc1");
  			__ddr_print(uint8tochar(DRIVE_STRENGTH));
			#ifdef DRAM_LPDDR3
			if(val==LP3_DS[0])
			{
				val=0x28;
			}else
			{
				val=0x30;
			}
			#else

			#endif
			break;
		case SLEW_RATE:
			 __ddr_print("\t0xc2");
  			 __ddr_print(uint8tochar(SLEW_RATE));
			break;
		case SLICEX:
			__ddr_print("\t0xc3");
 			__ddr_print(uint8tochar(SLICEX));
			break;
		case DQZ:
			__ddr_print("\t0xc4");
 			__ddr_print(uint8tochar(DQZ));
			break;
		case DQ_VREF_DEVICE:
			 __ddr_print("\t0xc5");
			 __ddr_print(uint8tochar(DQ_VREF_DEVICE));
			break;
		case DQ_VREF_PHY:
			 __ddr_print("\t0xc5");
			__ddr_print(uint8tochar(DQ_VREF_PHY));
			break;
		default: while(1);

	}
	__ddr_print("00");
 	 __ddr_print(uint8tochar(val));

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
void slave_delay_triggle()
{
//sc_phy_manual_update
  reg_bit_set(CANDS_PHY0_(1026),16,1,1);
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
void ddr_scan_dll_print(struct IO_INFO_CFG_T *io_info,uint32 dll_cnt)
{
	line_num_print();
	scan_io_print(DRIVE_STRENGTH,io_info->ds);
	scan_io_print(SLEW_RATE,io_info->slew_rate);
	scan_io_print(SLICEX,io_info->slice_num);
	#ifndef SCAN_SLICE
	scan_io_print(DQZ,io_info->dq_num);
	#endif
	#ifdef DRAM_LPDDR4
	if((io_info->type==WR_BYPASS_DLL)||(io_info->type==WRDQ_DLL))
	{
		scan_io_print(DQ_VREF_DEVICE,io_info->vref);
	}else
	{
		scan_io_print(DQ_VREF_PHY,io_info->vref);
	}
	#endif
	__ddr_print("\t0xb1");
	__ddr_print(uint8tochar(io_info->type));
	__ddr_print(uint8tochar(dll_cnt>>8));
	__ddr_print(uint8tochar(dll_cnt));

}

public void mr_write(uint32 mr_num,uint32 mr_cs,uint32 mr_value)
{
	reg_bit_set(CANDS_CTL0_(208),16,8,mr_value);
	reg_bit_set(CANDS_CTL0_(183),0,8,mr_num);
	reg_bit_set(CANDS_CTL0_(183),8,8,mr_cs);
	reg_bit_set(CANDS_CTL0_(183),23,1,1);
	reg_bit_set(CANDS_CTL0_(183),24,1,0);
	reg_bit_set(CANDS_CTL0_(183),26,1,0);
	reg_bit_set(CANDS_CTL0_(183),25,1,1);
	while((__raw_readl(CANDS_CTL0_(292))&0x04000000) != 0x04000000);
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


public void cands_device_vref_mrw(uint32 mode,uint32 vref_value)
{
    	uint32 mr_value = (mode<<6)&(vref_value);
	mr_write(0xe,scan_info_g->cs_num,mr_value);
}

public void cands_phy_dq_vref_set(uint32 mode_lv,uint32 en_lv,uint32 vrefsel_lv)
{
	//slice0
	reg_bit_set(CANDS_PHY0_(1047),8,6,vrefsel_lv);
	//reg_bit_set(CANDS_PHY0_(1048),16,1,en_lv);
	//reg_bit_set(CANDS_PHY0_(1048),17,4,mode_lv);
	//slice1
	reg_bit_set(CANDS_PHY0_(1048),0,6,vrefsel_lv);
	//reg_bit_set(CANDS_PHY0_(1049),8,1,en_lv);
	//reg_bit_set(CANDS_PHY0_(1049),9,4,mode_lv);
	//slice2
	reg_bit_set(CANDS_PHY0_(1048),16,6,vrefsel_lv);
	//reg_bit_set(CANDS_PHY0_(1049),24,1,en_lv);
	//reg_bit_set(CANDS_PHY0_(1049),25,4,mode_lv);
	//slice3
	reg_bit_set(CANDS_PHY0_(1049),0,6,vrefsel_lv);
	//reg_bit_set(CANDS_PHY0_(1050),8,1,en_lv);
	//reg_bit_set(CANDS_PHY0_(1050),9,4,mode_lv);
}

public void cands_device_ca_vref_mrw(uint32 range,uint32 mr_value)
{

}

public void cands_phy_ca_vref_set(uint32 mode_lv,uint32 en_lv,uint32 vrefsel_lv)
{
	reg_bit_set(CANDS_PHY0_(1043),16,6,vrefsel_lv);
	reg_bit_set(CANDS_PHY0_(1043),24,1,en_lv);
	reg_bit_set(CANDS_PHY0_(1043),25,4,mode_lv);

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
static void cands_phy_ds_set(DDR_DS_E ddr_ds)
{
	uint8 slice_num=0;
	for(slice_num=0;slice_num<4;slice_num++)
	{
		//phy_dqs_tsel_enable
  		reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200, 25, 1, 1);
		//phy_dqs_tsel_select
  		reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200, 8, 4, ddr_ds);
  		reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200,12, 4, ddr_ds);
		//phy_dq_tsel_enable
  		reg_bit_set(CANDS_PHY0_(5)+slice_num*0x200, 17, 1, 1);
		//phy_dq_tsel_select
  		reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200, 8, 4, ddr_ds);
  		reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200,12, 4, ddr_ds);
	}
}

void cands_phy_odt_set( uint32 enable,DDR_DS_E ddr_odt)
{
	uint32 slice_num=0;
	for(slice_num=0;slice_num<4;slice_num++)
	{
		//phy_dqs_tsel_enable
  		reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200, 24, 1, enable);
		//phy_dqs_tsel_select
  		reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200, 0, 4, ddr_odt);
		reg_bit_set(CANDS_PHY0_(7)+slice_num*0x200, 4, 4, 0x0);
		//phy_dq_tsel_enable
  		reg_bit_set(CANDS_PHY0_(5)+slice_num*0x200, 16, 1, enable);
		//phy_dq_tsel_select
  		reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200, 0, 4, ddr_odt);
		reg_bit_set(CANDS_PHY0_(6)+slice_num*0x200, 4, 4, 0x0);

	}
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
void cands_device_ds_mrw(MRW_TYPE_E mrw_type, MRW_CS_E mrw_cs, uint32 mrw_num, uint32 cs0_data, uint32 cs1_data)
{
	if(mrw_cs == MRW_ALL_CS)
	{
		reg_bit_set(CANDS_CTL0_(183), 24, 1,1);
        }else
        {
		reg_bit_set(CANDS_CTL0_(183), 24, 1, 0);
	 }
	reg_bit_set(CANDS_CTL0_(183), 8, 8, mrw_cs);


	if(mrw_type == MRW_SINGLE)
	{
		reg_bit_set(CANDS_CTL0_(183), 23, 1, 1);
	}else
	{
		reg_bit_set(CANDS_CTL0_(183), 23, 1, 0);
	}

	if(mrw_type == MRW_M16_M17)
	{
		reg_bit_set(CANDS_CTL0_(183), 18, 1, 1);
	}else
	{
		reg_bit_set(CANDS_CTL0_(183), 18, 1, 0);
	}

	if(mrw_type == MRW_M0_M1_M2_M3_M11)
	{
		reg_bit_set(CANDS_CTL0_(183), 17, 1, 1);

	}else
	{
		reg_bit_set(CANDS_CTL0_(183), 17, 1, 0);
	}

	reg_bit_set(CANDS_CTL0_(183), 0, 8, mrw_num);
	//mrsingle_data
	reg_bit_set(CANDS_CTL0_(183), 0, 8, cs0_data);
	reg_bit_set(CANDS_CTL0_(183), 0, 8, cs1_data);
    //trigger the mrw sequence
	reg_bit_set(CANDS_CTL0_(183), 25, 1, 1);
	//wait fot int_status--bit[26] mode register has completed and another mode register write may be issued
	while((__raw_readl(CANDS_CTL0_(292))&0x04000000) != 0x04000000);

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

static void cands_ctrl_ds_set(DDR_DS_E ddr_ds)
{
	uint32 mr_ds_val = 0;
	#ifdef DRAM_LPDDR3
	switch(ddr_ds)
	{
            //case PAD_DRV_34:
	//	 mr_ds_val = 1;
	//	 break;
	     case PAD_DRV_40:
		 mr_ds_val = 2;
		 break;
	     case PAD_DRV_48:
		 mr_ds_val =3;
		 break;
	    case PAD_DRV_60:
		 mr_ds_val =4;
		 break;
         default:
		 mr_ds_val =1;
	}
	#endif
	#ifdef DRAM_LPDDR4
	switch(ddr_ds)
	{
	//	case PAD_DRV_34:
	//		mr_ds_val = 0x31;
	//		break;
		case PAD_DRV_40:
			mr_ds_val = 0x31;
			break;
		case PAD_DRV_48_LP4:
			mr_ds_val = 0x29;
			break;
		case PAD_DRV_60_LP4:
			mr_ds_val = 0x21;
			break;
	}
	#endif
	mr_write(0x3, scan_info_g->cs_num, mr_ds_val);
}

public void cands_ca_ds_set()
{

}

public void cands_ca_odt_set(){}

public void cands_device_ca_ds_mrw(){}


public void cands_phy_slew_rate_set(DS_SLEW_E ds_slew)
{
	//phy_pad_data_drive
	reg_bit_set(CANDS_PHY0_(1074),0,4,ds_slew); //slewn
	reg_bit_set(CANDS_PHY0_(1074),4,4,ds_slew);//slewp
	//phy_pad_dqs_driver
	reg_bit_set(CANDS_PHY0_(1074),16,4,ds_slew); //slewn
	reg_bit_set(CANDS_PHY0_(1074),20,4,ds_slew);//slewp
}

public void cands_phy_ca_slewrate_set(DS_SLEW_E ds_slew)
{
	//phy_pad_addr_drive
	reg_bit_set(CANDS_PHY0_(1075),8,4,ds_slew);
	reg_bit_set(CANDS_PHY0_(1075),12,4,ds_slew);

}




//DQ  for write
uint32 wrdq_dll_addr[4][8] =
{
	//slice0
	{68,68,69,69,70,70,71,71},
	//slice1
	{196,196,197,197,198,198,199,199},
	//slice2
	{324,324,325,325,326,326,327,327},
	//slice3
	{452,452,453,453,454,454,455,455},
};
uint32 wrdq_start_bit[4][8]=
{
	{0,16,0,16,0,16,0,16},
	{0,16,0,16,0,16,0,16},
	{0,16,0,16,0,16,0,16},
	{0,16,0,16,0,16,0,16},
};

//DQS for read
uint32 rddqs_fall_dll_addr[4][8] =
{
	//slice0
	{78,79,80,81,82,83,84,85},
	//slice1
	{206,207,208,209,210,211,212,213},
	//slice2
	{334,335,336,337,338,339,340,341},
	//slice3
	{462,463,464,465,466,467,468,469},

};
uint32 rddqs_rise_dll_addr[4][8] =
{
	//slice0
	{78,79,80,81,82,83,84,85},
	//slice1
	{206,207,208,209,210,211,212,213},
	//slice2
	{334,335,336,337,338,339,340,341},
	//slice3
	{462,463,464,465,466,467,468,469},

};

uint32 wrdq_bypass_dll_addr[4]=
{
	257,129,385,1
};
uint32 rddqs_bypass_dll_addr[4]=
{
	266,138,394,10
};



#ifdef DRAM_LPDDR3
uint32 ca_dll_addr[10]={675,673,674,673,674,546,547,545,544,545};
uint32 ca_start_bit[10]={0,0,16,16,0,16,0,16,8,0};
#else
uint32 ca_dll_addr[12]={};
uint32 ca_start_bit[12]={};
#endif

struct SWAP_INFO_CFG_T
{
	uint32 *wr_base_addr;
	uint32 *wr_offset;
	uint32 *rd_base_addr;
	uint32 byte_swap;
	uint32 *bit_swap;

};
struct SWAP_INFO_CFG_T swap_info;

struct SWAP_INFO_CFG_T  *dll_addr_info_cfg=&swap_info;

/*********************************************************************************************************************
*
**@Name:phy_dll_training_addr_get
**@Function:
**@Calls:
**@Called by:
**@return
**
*
**********************************************************************************************************************/
void phy_dll_training_addr_get()
{
	uint32 slice_num=0;
	uint32 dq_num=0;
	uint32 change_slice_num=0;
	uint32 change_dq_num=0;
	for(slice_num=0;slice_num<4;slice_num++)
	{
		change_slice_num=(dll_addr_info_cfg->byte_swap>>(slice_num*8))&0xff;
		for(dq_num=0;dq_num<8;dq_num++)
		{
			change_dq_num=(*(dll_addr_info_cfg->bit_swap+slice_num)>>(dq_num*4))&0xf;
			wrdq_dll_addr[slice_num][dq_num]=*(dll_addr_info_cfg->wr_base_addr+change_dq_num)+128*change_slice_num;
			wrdq_start_bit[slice_num][dq_num]=*(dll_addr_info_cfg->wr_offset+change_dq_num);
			rddqs_rise_dll_addr[slice_num][dq_num]=*(dll_addr_info_cfg->rd_base_addr+change_dq_num)+128*change_slice_num;
			rddqs_fall_dll_addr[slice_num][dq_num]=*(dll_addr_info_cfg->rd_base_addr+change_dq_num)+128*change_slice_num;
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
void phy_dll_training_get( )
{
	uint32 slice_num=0;
	uint32 slice_dq_num=0;
	uint32 ca_num=0;
	if(scan_info_g->freq_mode==BYPASS_MODE)
	{
		for(slice_num=0;slice_num<4;slice_num++)
		{
			wrdq_bypass_dll[slice_num] = reg_bit_readl(CANDS_PHY0_(wrdq_bypass_dll_addr[slice_num]),10, 8);
			rddqs_bypass_dll[slice_num] = reg_bit_readl(CANDS_PHY0_(rddqs_bypass_dll_addr[slice_num]), 2, 8);
		}
		return;
	}

	for(slice_num=0;slice_num<4;slice_num++)
	{
		for(slice_dq_num=0;slice_dq_num<8;slice_dq_num++)
		{
			wrdq_dll[slice_num][slice_dq_num] = reg_bit_readl(CANDS_PHY0_(wrdq_dll_addr[slice_num][slice_dq_num]), wrdq_start_bit[slice_num][slice_dq_num], 11);
			rddqs_rise_dll[slice_num][slice_dq_num] = reg_bit_readl(CANDS_PHY0_(rddqs_rise_dll_addr[slice_num][slice_dq_num]),0, 10);
			rddqs_fall_dll[slice_num][slice_dq_num] = reg_bit_readl(CANDS_PHY0_(rddqs_fall_dll_addr[slice_num][slice_dq_num]),16, 10);
		}
	}
	for(ca_num=0;ca_num<PHY_CA_NUM;ca_num++)
	{
		ca_dll[ca_num]=reg_bit_readl(CANDS_PHY0_(ca_dll_addr[ca_num]),ca_start_bit[ca_num],11);
	}
}


/*********************************************************************************************************************
*
**@Name:phy_dll_scan_range
**@Function:According to the training result, dll range is computed.
**@Calls:
**@Called by:
**@return
**
*
**********************************************************************************************************************/
uint32 wr_dll_upper_threshold=0xb8;
uint32 wr_dll_lower_threshold=0x88;
uint32 rd_dll_upper_threshold=0xb8;
uint32 rd_dll_lower_threshold=0x88;
uint32 ca_dll_upper_threshold=0xa8;
uint32 ca_dll_lower_threshold=0x78;
#ifdef DRAM_LPDDR4
//phy range1 phy range2 ddr range0 range1
uint32 phy_vref_min[2][2]={0x0,0x0};
uint32 phy_vref_max[2][2]={0x3f,0x3f};
uint32 device_vref_min[2][2]={0x0,0x0};
uint32 device_vref_max[2][2]={0x32,0x32};
#endif

struct RANGE_CFG_T
{
	uint32 slewrate_cfg;
	uint32 ds_cfg;
	uint32 vref_cfg;
	uint32 dll_cfg;
};

struct SCAN_RANGE_CFG_T
{
	struct RANGE_CFG_T min_cfg;
	struct RANGE_CFG_T max_cfg;
	uint32 vref_step;
	uint32 dll_step;
};

struct SCAN_RANGE_CFG_T ca_range_cfg,wr_range_cfg,rd_range_cfg;
struct SCAN_RANGE_CFG_T *ca_range=&ca_range_cfg;
struct SCAN_RANGE_CFG_T	*wr_range=&wr_range_cfg;
struct SCAN_RANGE_CFG_T	*rd_range=&rd_range_cfg;

void phy_scan_range_cfg(struct SCAN_RANGE_CFG_T *range,SCAN_TYPE_E type)
{
	uint32 slice_num=0;
	uint32 dq_num=0;
	uint32 ca_num=0;
	uint32 dll_total=0;
	uint32 dll_average=0;

	range->min_cfg.slewrate_cfg=0x0;
	range->max_cfg.slewrate_cfg=0x1;
	#ifdef DRAM_LPDDR3
	range->min_cfg.ds_cfg=0x0;
	range->max_cfg.ds_cfg=0x1;
	#else
	range->min_cfg.ds_cfg=0x0;
	range->max_cfg.ds_cfg=0x3;
	#endif
	range->min_cfg.vref_cfg=0xf;
	range->max_cfg.vref_cfg=0x40;
	range->vref_step=0x2;
	switch(type)
	{
		case WR_BYPASS_DLL:
			range->min_cfg.dll_cfg=0x0;
			range->max_cfg.dll_cfg=0xff;
			#ifdef DRAM_LPDDR4
			range->min_cfg.vref_cfg=0x0;
			range->max_cfg.vref_cfg=0x32;
			range->vref_step=0x3;
			#endif
			range->dll_step=0x1;
			break;
		case RDDQS_BYPASS_DLL:
			range->min_cfg.dll_cfg=0x0;
			range->max_cfg.dll_cfg=0xff;
			#ifdef DRAM_LPDDR4
			range->min_cfg.vref_cfg=0x0;
			range->max_cfg.vref_cfg=0x3f;
			range->vref_step=0x2;
			#endif
			range->dll_step=0x1;
			break;
		case WRDQ_DLL:
			for(slice_num=0;slice_num<4;slice_num++)
			{
				for(dq_num=0;dq_num<8;dq_num++)
				{
					dll_total+=wrdq_dll[slice_num][dq_num];
				}
			}
			dll_average=(dll_total/32);
			if(dll_average>=wr_dll_lower_threshold)
			{
				range->min_cfg.dll_cfg=dll_average-wr_dll_lower_threshold;
			}else
			{
				range->min_cfg.dll_cfg=0;
			}
			range->max_cfg.dll_cfg=dll_average+wr_dll_upper_threshold;
//			range->min_cfg.dll_cfg=0;
//			range->max_cfg.dll_cfg=0x400;
			#ifdef DRAM_LPDDR4
			range->min_cfg.vref_cfg=0x0;
			range->max_cfg.vref_cfg=0x32;
			range->vref_step=0x3;
			#endif
			range->dll_step=0x2;
			break;
		case RDDQS_RISE_DLL:
		case RDDQS_FALL_DLL:
			for(slice_num=0;slice_num<4;slice_num++)
			{
				for(dq_num=0;dq_num<8;dq_num++)
				{
					dll_total+=rddqs_rise_dll[slice_num][dq_num];
				}
			}
			dll_average=(dll_total/32);
			if(dll_average>=rd_dll_lower_threshold)
			{
				range->min_cfg.dll_cfg=dll_average-rd_dll_lower_threshold;
			}else
			{
				range->min_cfg.dll_cfg=0;
			}
			range->min_cfg.dll_cfg=0;
			range->max_cfg.dll_cfg=dll_average+rd_dll_upper_threshold;
//			range->min_cfg.dll_cfg=0;
//			range->max_cfg.dll_cfg=0x400;
			#ifdef DRAM_LPDDR4
			range->min_cfg.vref_cfg=0x0;
			range->max_cfg.vref_cfg=0x3f;
			range->vref_step=0x2;
			#endif
			range->dll_step=0x2;
			break;
		case CA_DLL:
			for(ca_num=0;ca_num<PHY_CA_NUM;ca_num++)
			{
				dll_total+=ca_dll[ca_num];
			}
			dll_average=(dll_total/PHY_CA_NUM);
			if(dll_average>=ca_dll_lower_threshold)
			{
				range->min_cfg.dll_cfg=dll_average-ca_dll_lower_threshold;
			}else
			{
				range->min_cfg.dll_cfg=0;
			}
			range->max_cfg.dll_cfg=dll_average+ca_dll_upper_threshold;
			#ifdef DRAM_LPDDR4
			range->min_cfg.vref_cfg=0x0;
			range->max_cfg.vref_cfg=0x0;
			range->vref_step=0x2;
			#endif
			break;
		default:while(1);
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
**dll_type: 1-wrdqs 2-wrdq 3-rddqs_rise 4-rddqs_fall  normal mode
**             1-wr      2-rd     bypass mode
**
**
*
**********************************************************************************************************************/
void phy_dll_set(struct IO_INFO_CFG_T *io_info,uint32 value,DLL_MODE_E mode)
{
	uint32 dll_value=0;
	uint32 slice_dq_num=0;

	switch(io_info->type)
	{
		case WR_BYPASS_DLL:
			(mode==RESET_MODE)?(dll_value=wrdq_bypass_dll[io_info->slice_num]):(dll_value=value);
			reg_bit_set(CANDS_PHY0_(wrdq_bypass_dll_addr[io_info->slice_num]),10,8,dll_value);
			break;
		case RDDQS_BYPASS_DLL:
			(mode==RESET_MODE)?(dll_value=value=rddqs_bypass_dll[io_info->slice_num]):(dll_value=value);
			reg_bit_set(CANDS_PHY0_(rddqs_bypass_dll_addr[io_info->slice_num]),2,8,dll_value);
			break;
		case WRDQ_DLL:
			#ifdef SCAN_SLICE
			for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
			{
				(mode==RESET_MODE)?dll_value=(wrdq_dll[io_info->slice_num][slice_dq_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(wrdq_dll_addr[io_info->slice_num][slice_dq_num]),wrdq_start_bit[slice_dq_num],11,dll_value);
			}
			#else
			(mode==RESET_MODE)?dll_value=(wrdq_dll[io_info->slice_num][io_info->dq_num]):(dll_value=value);
			reg_bit_set(CANDS_PHY0_(wrdq_dll_addr[io_info->slice_num][io_info->dq_num]),wrdq_start_bit[io_info->slice_num][io_info->dq_num],11,dll_value);
			#endif
			break;
		case RDDQS_RISE_DLL:
			#ifdef SCAN_SLICE
			for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
			{
				(mode==RESET_MODE)?(dll_value=rddqs_rise_dll[io_info->slice_num][slice_dq_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(rddqs_rise_dll_addr[io_info->slice_num][slice_dq_num]), 0,10,dll_value);
			}
			#else
			(mode==RESET_MODE)?(dll_value=rddqs_rise_dll[io_info->slice_num][io_info->dq_num]):(dll_value=value);
			reg_bit_set(CANDS_PHY0_(rddqs_rise_dll_addr[io_info->slice_num][io_info->dq_num]), 0,10,dll_value);
			#endif
			break;
		case RDDQS_FALL_DLL:
			#ifdef SCAN_SLICE
			for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
			{
				(mode==RESET_MODE)?(dll_value=rddqs_fall_dll[io_info->slice_num][slice_dq_num]):(dll_value=value);
				reg_bit_set(CANDS_PHY0_(rddqs_fall_dll_addr[io_info->slice_num][slice_dq_num]),16,10,dll_value);
			}
			#else
			(mode==RESET_MODE)?(dll_value=rddqs_fall_dll[io_info->slice_num][io_info->dq_num]):(dll_value=value);
			reg_bit_set(CANDS_PHY0_(rddqs_fall_dll_addr[io_info->slice_num][io_info->dq_num]),16,10,dll_value);
			#endif
			break;
		default:while(1);
	}
      slave_delay_triggle();
      manual_clear_gate_init(0);
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
public void phy_ca_dll_set(struct IO_INFO_CFG_T *io_info,uint32 value,DLL_MODE_E mode)
{
  slave_delay_triggle();

}


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
#ifndef ENCRPTY_LOG
void ddr_scan_master_dll_print()
{
	uint32 dll_value=0;
	__ddr_print("\r\n");
	__ddr_print("*********Master Delay Line*************");
	__ddr_print("\nphy_master_dly_obs_0\n");
	//sc_phy_snap_obs_reg
	reg_bit_set(CANDS_PHY0_(14), 24, 1, 1);
	//phy_master_dly_lock_obs
	dll_value=reg_bit_readl(CANDS_PHY0_(38),16,10);
	__ddr_print("0x");
	__ddr_print(uint8tochar(dll_value>>8));
	__ddr_print(uint8tochar(dll_value));
	__ddr_print("\t");
	__ddr_print("\n");
}

struct TRAINING_OBS_T
{
	SCAN_TYPE_E type;
	uint32 select_addr;
	uint32 select_offset;
	uint32 select_bit_num;
	uint32 obs_addr;
	uint32 obs_offset;
	uint32 obs_bit_num;
};


void ddr_scan_training_obs_print(struct TRAINING_OBS_T obs)
{
	uint32 dq_num=0;
	uint32 change_dq_num=0;
	uint32 slice_num=0;
	uint32 change_slice_num=0;
	uint32 select_num=0;
	uint32 obs_val=0;
		for(slice_num=0;slice_num<4;slice_num++)
	{
		change_slice_num=(dll_addr_info_cfg->byte_swap>>(slice_num*8))&0xff;
		for(dq_num=0;dq_num<8;dq_num++)
		{
			change_dq_num=(*(dll_addr_info_cfg->bit_swap+slice_num)>>(dq_num*4))&0xf;
			switch(obs.type)
			{
				case WRDQ_DLL:
					select_num=change_dq_num;
					break;
				case RDDQS_RISE_DLL:
					if(change_dq_num==8)
					{
						select_num=0x10;
					}else
					{
						select_num=change_dq_num;
					}
					break;
				case RDDQS_FALL_DLL:
					if(change_dq_num==8)
					{
						select_num=0x18;
					}else
					{
						select_num=change_dq_num+0x8;
					}
					break;
			}
			reg_bit_set(CANDS_PHY0_(obs.select_addr)+change_slice_num*0x200,obs.select_offset,obs.select_bit_num,select_num);
			//phy_wdqlvl_dqdm_le_dly_obs
			obs_val=reg_bit_readl(CANDS_PHY0_(obs.obs_addr)+change_slice_num*0x200,obs.obs_offset,obs.obs_bit_num);
			__ddr_print("0x");
			__ddr_print(uint8tochar(obs_val>>8));
			__ddr_print(uint8tochar(obs_val));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
}


void ddr_scan_training_boundary_print()
{
	struct TRAINING_OBS_T obs;
	__ddr_print("\r\n");
	__ddr_print("*********WDQLVL Training Obs Value*************");
	__ddr_print("\nphy_wdqlvl_dqdm_le_dly_obs\n");
	obs.type=WRDQ_DLL;
	obs.select_addr=29;
	obs.select_offset=0;
	obs.select_bit_num=4;
	obs.obs_addr=50;
	obs.obs_offset=0;
	obs.obs_bit_num=11;
	ddr_scan_training_obs_print(obs);
	__ddr_print("\nphy_wdqlvl_dqdm_te_dly_obs\n");
	obs.obs_offset=16;
	ddr_scan_training_obs_print(obs);
	__ddr_print("\r\n");
	__ddr_print("*********RDLVL RISE Training Obs Value*************");
	__ddr_print("\nphy_rdlvl_rddqs_dq_le_dly_obs\n");
	obs.type=RDDQS_RISE_DLL;
	obs.select_addr=27;
	obs.select_offset=8;
	obs.select_bit_num=5;
	obs.obs_addr=47;
	obs.obs_offset=0;
	obs.obs_bit_num=10;
	ddr_scan_training_obs_print(obs);
	__ddr_print("\nphy_rdlvl_rddqs_dq_te_dly_obs\n");
	obs.obs_offset=16;
	ddr_scan_training_obs_print(obs);
	__ddr_print("\r\n");
	__ddr_print("*********RDLVL FALL Training Obs Value*************");
	__ddr_print("\nphy_rdlvl_rddqs_dq_le_dly_obs\n");
	obs.type=RDDQS_FALL_DLL;
	obs.select_addr=27;
	obs.select_offset=8;
	obs.select_bit_num=5;
	obs.obs_addr=47;
	obs.obs_offset=0;
	obs.obs_bit_num=10;
	ddr_scan_training_obs_print(obs);
	__ddr_print("\nphy_rdlvl_rddqs_dq_te_dly_obs\n");
	obs.obs_offset=16;
	ddr_scan_training_obs_print(obs);
}

void ddr_scan_result_dll_print()
{
	uint32 slice_num=0;
	uint32 slice_dq_num=0;
	__ddr_print("\nDDR SCAN RESULT\n");
	if(scan_info_g->freq_mode==BYPASS_MODE)
	{
	__ddr_print("\nphy_clk_wr_bypass_slave_delay\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		__ddr_print("0x");
		__ddr_print(uint8tochar(wrdq_bypass_center_dll[slice_num]>>8));
		__ddr_print(uint8tochar(wrdq_bypass_center_dll[slice_num]));
		__ddr_print("\t");
	}
	__ddr_print("\nphy_rddqs_dq_bypass_slave_delay\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		__ddr_print("0x");
		__ddr_print(uint8tochar(rddqs_bypass_center_dll[slice_num]>>8));
		__ddr_print(uint8tochar(rddqs_bypass_center_dll[slice_num]));
		__ddr_print("\t");
	}
	}
else{
	__ddr_print("\nphy_clk_wrdqz_slave_delay\n");
	__ddr_print("\n--------------start------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(wrdq_start_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(wrdq_start_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\n----------------end------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(wrdq_end_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(wrdq_end_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\n----------------center------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(wrdq_center_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(wrdq_center_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_fall_slave_delay\n");
	__ddr_print("\n----------------start------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_fall_start_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_fall_start_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\n----------------end------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_fall_end_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_fall_end_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\n----------------center------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_fall_center_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_fall_center_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_rise_slave_delay\n");
	__ddr_print("\n----------------start------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_rise_start_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_rise_start_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\n----------------end------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_rise_end_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_rise_end_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\n----------------center------------------------------------\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_rise_center_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_rise_center_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	#if 0
	__ddr_print("\nphy_adr_clk_wr_slave_delay\n");

	for(slice_dq_num =0; slice_dq_num < PHY_CA_NUM; slice_dq_num++)
	{
		__ddr_print("0x");
		__ddr_print(uint8tochar(ca_center_dll[slice_dq_num]>>8));
		__ddr_print(uint8tochar(ca_center_dll[slice_dq_num]));
		__ddr_print("\t");
	}
	__ddr_print("\n");
	#endif
  }

}

void ddr_scan_training_dll_print()
{
uint32 slice_num = 0;
uint32 slice_dq_num = 0;
__ddr_print("\r\n");
__ddr_print("*********Training Delay Line*************");

if(scan_info_g->freq_mode==BYPASS_MODE)
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
		__ddr_print(uint8tochar(wrdq_bypass_dll[slice_num]>>8));
		__ddr_print(uint8tochar(wrdq_bypass_dll[slice_num]));
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
		__ddr_print(uint8tochar(rddqs_bypass_dll[slice_num]>>8));
		__ddr_print(uint8tochar(rddqs_bypass_dll[slice_num]));
		__ddr_print("\t");
	}
	}
else{
	uint32 rddqs_gate_addr=0;
	uint32 rddqs_gate_value=0;
	__ddr_print("\nphy_rddqs_gate_slave_delay_addr\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		rddqs_gate_addr=87+slice_num*128;
		HextoDec(rddqs_gate_addr);
		__ddr_print("\t");
	}
	__ddr_print("\nphy_rddqs_gate_slave_delay\n");
	for(slice_num = 0; slice_num < 4; slice_num++)
	{
		rddqs_gate_addr=87+slice_num*128;
		rddqs_gate_value=reg_bit_readl(CANDS_PHY0_(rddqs_gate_addr), 0,10);
		__ddr_print("0x");
		__ddr_print(uint8tochar(rddqs_gate_value>>8));
		__ddr_print(uint8tochar(rddqs_gate_value));
		__ddr_print("\t");
	}
	__ddr_print("\n");
	__ddr_print("\nphy_clk_wrdqz_slave_delay_addr\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			HextoDec(wrdq_dll_addr[slice_num][slice_dq_num]);
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_clk_wrdqz_slave_delay\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(wrdq_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(wrdq_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_fall_slave_delay_addr\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			HextoDec(rddqs_fall_dll_addr[slice_num][slice_dq_num]);
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_fall_slave_delay\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_fall_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_fall_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_rise_slave_delay_addr\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			HextoDec(rddqs_rise_dll_addr[slice_num][slice_dq_num]);
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_rddqs_dqz_rise_slave_delay\n");
	for(slice_num = 0;slice_num < 4; slice_num++)
	{
		for(slice_dq_num =0; slice_dq_num < 8; slice_dq_num++)
		{
			__ddr_print("0x");
			__ddr_print(uint8tochar(rddqs_rise_dll[slice_num][slice_dq_num]>>8));
			__ddr_print(uint8tochar(rddqs_rise_dll[slice_num][slice_dq_num]));
			__ddr_print("\t");
		}
		__ddr_print("\n");
	}
	__ddr_print("\nphy_adr_clk_wr_slave_delay\n");

	for(slice_dq_num =0; slice_dq_num < PHY_CA_NUM; slice_dq_num++)
	{
		__ddr_print("0x");
		__ddr_print(uint8tochar(ca_dll[slice_dq_num]>>8));
		__ddr_print(uint8tochar(ca_dll[slice_dq_num]));
		__ddr_print("\t");
	}
	__ddr_print("\n");

  }

}

void ddr_scan_vref_print()
{
	uint32 slice_num = 0;
	uint32 slice_dq_num=0;
	uint32 dq_vref=0;
	uint32 mr12_ca_vref=0;
	uint32 mr14_dq_vref=0;
	uint32 rx_val=0;
	__ddr_print("\r\n");
	__ddr_print("*********Vref Value*************");
	__ddr_print("\nphy_pad_vref_ctrl_dq_x\n");
	dq_vref = reg_bit_readl(CANDS_PHY0_(1048), 8, 14);
	__ddr_print("0x");
	__ddr_print(uint8tochar(dq_vref>>8));
	__ddr_print(uint8tochar(dq_vref));
	__ddr_print("\n");

	switch(scan_info_g->freq_num)
	{
		case 0:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(211),16, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(213), 0, 8);
			break;
		case 1:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(211),24, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(213), 8, 8);
			break;
		case 2:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(212), 0, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(213),16, 8);
			break;
		case 3:
			mr12_ca_vref = reg_bit_readl(CANDS_CTL0_(212), 8, 8);
			mr14_dq_vref = reg_bit_readl(CANDS_CTL0_(213),24, 8);
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
	__ddr_print("\r\n");
	__ddr_print("*********RX CAL Value*************");
	for(slice_num=0;slice_num<4;slice_num++)
	{
		for(slice_dq_num=0;slice_dq_num<9;slice_dq_num++)
		{
			rx_val=reg_bit_readl(CANDS_PHY0_(56)+slice_dq_num*4+slice_num*0x200,0,24);
			__ddr_print("0x");
			__ddr_print(uint8tochar(rx_val>>16));
			__ddr_print(uint8tochar(rx_val>>8));
			__ddr_print(uint8tochar(rx_val));
			__ddr_print("\t");
		}
		__ddr_print("\r\n");
	}
}
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

//
uint32 bist_test()
{
	volatile uint32 i=0;
	uint32 bist_timeout=0;
	uint32 bist_result=0;
	uint32 bist_base_offset=0;
	uint32 bist_adr_base=0;
	uint32 port0_result=0;
	uint32 port1_result=0;
	uint32 port2_result=0;

	REG32(0xc0018028) =0x2a;

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		bist_adr_base = i*0x20000000;
		#ifdef SIPI_BIST
		REG32(0xc00d0000+bist_base_offset) =0x30021b1;
		REG32(0xc00d0004+bist_base_offset) =0x1fFf;
		REG32(0xc00d0008+bist_base_offset) =bist_adr_base;
		REG32(0xc00d000c+bist_base_offset) =0x0;
		REG32(0xc00d0010+bist_base_offset) =0x0ff0c3a5;
		REG32(0xc00d0014+bist_base_offset) =0xffffaa55;
		REG32(0xc00d0018+bist_base_offset) =0x1111aa55;
		REG32(0xc00d001c+bist_base_offset) =0xaaaaaa55;
		REG32(0xc00d0020+bist_base_offset) =0x1234aa55;
		REG32(0xc00d0024+bist_base_offset) =0x0000aa55;
		REG32(0xc00d0028+bist_base_offset) =0x00000000;
		REG32(0xc00d002c+bist_base_offset) =0x00000000;

		REG32(0xc00d0008+bist_base_offset) =bist_adr_base;
		REG32(0xc00d0004+bist_base_offset) =0x1fFf;
		REG32(0xc00d0000+bist_base_offset) =0x30021b5;
		#else
		REG32(0xc00d0000+bist_base_offset) =0x30021D1;
		REG32(0xc00d0004+bist_base_offset) =0x1fFf;
		REG32(0xc00d0008+bist_base_offset) =bist_adr_base;
		REG32(0xc00d000c+bist_base_offset) =0x0;
		REG32(0xc00d00cc+bist_base_offset)=0x12345678;
		REG32(0xc00d00d0+bist_base_offset)=0x89abcdef;
		REG32(0xc00d00d4+bist_base_offset)=0x8abce529;
		REG32(0xc00d00d8+bist_base_offset)=0xfbed20ec;
		REG32(0xc00d0008+bist_base_offset) =bist_adr_base;
		REG32(0xc00d0004+bist_base_offset) =0x1fFf;
		REG32(0xc00d0000+bist_base_offset) =0x30021D5;
		#endif
	}

	for(i=0;i<3;i++)
	{
		bist_base_offset = i*0x4000;
		#if 0
		REG32(0xc00d0000+bist_base_offset) =0x30021b3;
		#else
		REG32(0xc00d0000+bist_base_offset) =0x30021D3;
		#endif
	}

	while((REG32(0xc00d00b0) & 0x2) != 0x2);
	while((REG32(0xc00d00b0+0x4000) & 0x2) != 0x2);
	while((REG32(0xc00d00b0+0x8000) & 0x2) != 0x2);

	((REG32(0xc00d00b0) & 0x1) == 0x1)?(port0_result=1):(port0_result=0);
	((REG32(0xc00d00b0+0x4000) & 0x1) == 0x1)?(port1_result=1):(port1_result=0);
	((REG32(0xc00d00b0+0x8000) & 0x1) == 0x1)?(port1_result=1):(port1_result=0);

	if((port0_result==1)||(port1_result==1)||(port2_result==1))
	{
		bist_result=1;

	}else
	{
		bist_result=0;
	}

	REG32(0xc0018028) =0x0;
	return bist_result;
}



/*************************************************************************************************************
**
**@name:ddr_scan_dqz
**@function:scan DQ of each slice by DQ delay elements
**@@input param:
**@return void
**
*
***************************************************************************************************************/
void ddr_scan_dqz(struct IO_INFO_CFG_T *io_info,struct SCAN_RANGE_CFG_T *range)
{
	uint32 ret = 0;
	uint32 dll_type=0;
	uint32 dq_dll_cnt = 0;
	#ifndef ENCRPTY_LOG
	uint32 pass_flag=1;
	uint32 fail_flag=1;
	#endif
	//set delay line
	for(dq_dll_cnt = range->min_cfg.dll_cfg;dq_dll_cnt < range->max_cfg.dll_cfg;dq_dll_cnt+=range->dll_step)
	{
		io_info->dll=dq_dll_cnt;
		phy_dll_set(io_info,dq_dll_cnt,SET_MODE);
		#ifdef ENCRPTY_LOG
		ddr_scan_dll_print(io_info,(dq_dll_cnt-range->min_cfg.dll_cfg)/range->dll_step);
		#endif
		ret = bist_test();
		if(ret)
		{
			#ifdef ENCRPTY_LOG
			FAIL;
			#else
			FAIL_SYMBOL;
			if((pass_flag==0)&&(fail_flag==1))
			{
				last_pass=dq_dll_cnt-range->dll_step;
				fail_flag=0;
			}
			if((last_pass-first_pass)<5*range->dll_step)
			{
				pass_flag=1;
			}
			#endif
		}else
		{
			#ifdef ENCRPTY_LOG
			PASS;
			#else
			PASS_SYMBOL;
			if(pass_flag==1)
			{
				first_pass=dq_dll_cnt;
				pass_flag=0;
			}
			if((last_pass<=first_pass)||((last_pass-first_pass)<5*range->dll_step))
			{
				fail_flag=1;
			}
			#endif
		}
	}
	//reset delay line
	phy_dll_set( io_info,0x0,RESET_MODE);
	#ifdef ENCRPTY_LOG
	PARAM_SCAN_END;
	#endif

}


void ddr_scan_rd(uint8 slice_num,uint8 dq_num,SCAN_TYPE_E type)
{
	uint32 slewrate_num,slewrate;
	uint32 ds_num=0,ds=0;
	uint32 vref_lv=0;
	struct IO_INFO_CFG_T *io_info_cfg;
	struct IO_INFO_CFG_T io_info_def;
	io_info_cfg=&io_info_def;
	io_info_cfg->slice_num=slice_num;
	io_info_cfg->dq_num=dq_num;
	io_info_cfg->type=type;
	for(slewrate_num=rd_range->min_cfg.slewrate_cfg;slewrate_num<rd_range->max_cfg.slewrate_cfg;slewrate_num++)
	{
		slewrate=SLEW_RATE_ARRAY[slewrate_num];
		cands_phy_slew_rate_set(slewrate);
		io_info_cfg->slew_rate=slewrate;
		for(ds_num=rd_range->min_cfg.ds_cfg;ds_num<rd_range->max_cfg.ds_cfg;ds_num++)
		{
			#ifdef DRAM_LPDDR3
			ds=LP3_DS[ds_num];
			cands_ctrl_ds_set(ds);
			#else
			ds=LP4_DS[ds_num];
			if(scan_info_g->device_odt !=0x0)
			{
				cands_phy_odt_set(0x1, ds);
			}else
			{
				cands_ctrl_ds_set(ds);
			}
			#endif
			io_info_cfg->ds=ds;
			#ifndef ENCRPTY_LOG
			switch(type)
			{
				case RDDQS_BYPASS_DLL:
					__ddr_print("\rddr_scan_rddqs_bypass: ");
					break;
				case RDDQS_RISE_DLL:
					__ddr_print("\rddr_scan_rddqs_rise: ");
					break;
				case RDDQS_FALL_DLL:
					__ddr_print("\rddr_scan_rddqs_fall: ");
					break;
				default:while(1);
			}
			param_to_slice_info_print(io_info_cfg);
			param_to_start_boundary_print(rd_range->min_cfg.dll_cfg, rd_range->max_cfg.dll_cfg, rd_range->dll_step);
			__ddr_print("\n");
			#endif
			#ifdef DRAM_LPDDR3
			for(vref_lv =rd_range->min_cfg.vref_cfg;vref_lv < rd_range->max_cfg.vref_cfg;vref_lv +=rd_range->vref_step)
			{
				io_info_cfg->vref=vref_lv;
				//mode_lv 0x6:lp4 range1 0x7:lp4 range2
				cands_phy_dq_vref_set(0x6, 0x1,vref_lv);
				wait_us(50);
				//dq for read
				ddr_scan_dqz(io_info_cfg,rd_range); //fall
				#ifndef ENCRPTY_LOG
				__ddr_print(uint8tochar(vref_lv));
				param_to_pass_boundary_print(io_info_cfg);
				__ddr_print("\n");
				#endif
			}
			cands_phy_dq_vref_set(0x6, 0x1,0x1f);
			#else
			for(vref_lv =rd_range->min_cfg.vref_cfg;vref_lv < rd_range->max_cfg.vref_cfg;vref_lv +=rd_range->vref_step)
		    {
		      		io_info_cfg->vref=vref_lv;
				//mode_lv 0x6:lp4 range1 0x7:lp4 range2
				if(scan_info_g->phy_odt!=0)
				{
					cands_phy_dq_vref_set(0x7, 0x1, vref_lv);
				}else
				{
					cands_phy_dq_vref_set(0x6, 0x1,vref_lv);
				}
				io_info_cfg->vref=vref_lv;
				//dq for read
				ddr_scan_dqz(io_info_cfg); //fall
				#ifndef ENCRPTY_LOG
				__ddr_print(uint8tochar(vref_lv));
				param_to_pass_boundary_print(io_info_cfg);
				__ddr_print("\n");
				#endif
			}
			#endif
			#ifndef ENCRPTY_LOG
			PARAM_SCAN_END;
			#endif
		}
	}
	cands_phy_slew_rate_set(scan_info_g->slew_rate);
	if(scan_info_g->phy_odt !=0x0)
	{
		cands_phy_odt_set(0x1,scan_info_g->phy_odt);
		#ifdef DRAM_LPDDR4
		cands_phy_dq_vref_set(0x7, 0x1, scan_info_g->phy_vref);
		#endif
	}else
	{
		cands_ctrl_ds_set(scan_info_g->phy_ds);
		#ifdef DRAM_LPDDR4
		cands_phy_dq_vref_set(0x6, 0x1, scan_info_g->phy_vref);
		#endif
	}

}

void ddr_scan_wr(uint32 slice_num,uint32 dq_num,SCAN_TYPE_E type)
{
	uint32 slewrate_num,slewrate;
	uint32 ds_num,ds;
	uint32 vref_lv=0;
	struct IO_INFO_CFG_T *io_info_cfg;
	struct IO_INFO_CFG_T io_info_def;
	io_info_cfg=&io_info_def;
	io_info_cfg->slice_num=slice_num;
	io_info_cfg->dq_num=dq_num;
	io_info_cfg->type=type;
	for(slewrate_num=wr_range->min_cfg.slewrate_cfg;slewrate_num<wr_range->max_cfg.slewrate_cfg;slewrate_num++)
	{
		slewrate=SLEW_RATE_ARRAY[slewrate_num];
		cands_phy_slew_rate_set(slewrate);
		io_info_cfg->slew_rate=slewrate;
//		for(ds_num=wr_range->min_cfg.ds_cfg;ds_num<wr_range->max_cfg.ds_cfg;ds_num++)
		{ds_num=wr_range->min_cfg.ds_cfg;
			#ifdef DRAM_LPDDR3
			ds=LP3_DS[ds_num];
			#else
			ds=LP4_DS[ds_num];
			#endif
			cands_phy_ds_set(ds);
			io_info_cfg->ds=ds;
			#ifndef ENCRPTY_LOG
			switch(type)
			{
				case WR_BYPASS_DLL:
					__ddr_print("\rddr_scan_clk_dq_wr_bypass: ");
					break;
				case WRDQ_DLL:
					__ddr_print("\rddr_scan_clk_dq_wr: ");
					break;
				default:while(1);
			}
			param_to_slice_info_print(io_info_cfg);
			param_to_start_boundary_print(wr_range->min_cfg.dll_cfg,wr_range->max_cfg.dll_cfg,wr_range->dll_step);
			__ddr_print("\n");
			#endif
			#ifdef DRAM_LPDDR3
			//dq for wr
			ddr_scan_dqz(io_info_cfg,wr_range); //fall
			#ifndef ENCRPTY_LOG
			param_to_pass_boundary_print(io_info_cfg);
			__ddr_print("\n");
			#endif
			#else
			for(vref_lv =wr_range->min_cfg.vref_cfg;vref_lv < wr_range->max_cfg.vref_cfg;vref_lv +=wr_range->vref_step)
		      	{
		      		io_info_cfg->vref=vref_lv;
				//mode_lv 0x6:lp4 range1 0x7:lp4 range2
				if(scan_info_g->phy_odt!=0)
				{
					cands_device_vref_mrw(0 ,vref_lv);
				}else
				{
					cands_device_vref_mrw(1, vref_lv);
				}
				io_info_cfg->vref=vref_lv;
				//dq for read
				ddr_scan_dqz(io_info_cfg); //fall
				#ifndef ENCRPTY_LOG
				__ddr_print(uint8tochar(vref_lv));
				param_to_pass_boundary_print(io_info_cfg);
				__ddr_print("\n");
				#endif
			}
			#endif
			#ifndef ENCRPTY_LOG
			PARAM_SCAN_END;
			#endif
		}
	}
	cands_phy_slew_rate_set(scan_info_g->slew_rate);
	cands_phy_ds_set(scan_info_g->phy_ds);
	#ifdef DRAM_LPDDR4
	if(scan_info_g->phy_odt != 0x0)
	{
		cands_device_vref_mrw(0,scan_info_g->device_vref);
	}else
	{
		cands_device_vref_mrw(1,scan_info_g->device_vref);
	}
	#endif
}

void ddr_scan_ca()
{


}

/*
*
*
*
*/
uint32 compute_slave_delay_cnt(uint32 ddr_clk)
{
	uint32 master_dll=0;
	uint32 t_dll_element=0;
	uint32 tcnt =0;
	if(scan_info_g->freq_mode==BYPASS_MODE)
	{
		//phy_master_dly_lock_obs_select_x
		reg_bit_set(CANDS_PHY0_(23),16,3,0x0);
		//sc_phy_snap_regs_x
		reg_bit_set(CANDS_PHY0_(14),24,1,0x1);
		//phy_master_dly_lock_obs_x
		master_dll = reg_bit_readl(CANDS_PHY0_(38),16, 10);
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
void ddr_scan_channel(uint32 ddr_clk)
{
	volatile uint32 i=0;
	uint32 tcnt = 0;

	uint32 slice_num=0;
	uint32 dq_num=0;
	uint32 ca_num=0;

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
//        ddr_print_u32_hex(ddr_clk);
	__ddr_print("\r\n*********");
	__ddr_print("0x");
	__ddr_print(uint8tochar(ddr_clk>>24));
	__ddr_print(uint8tochar(ddr_clk>>16));
	__ddr_print(uint8tochar(ddr_clk>>8));
	__ddr_print(uint8tochar(ddr_clk));
	__ddr_print("**********");
	//tcnt=compute_slave_delay_cnt(ddr_clk);
	__ddr_print("\r\n*********0x55aa55aa");
	//__ddr_print(uint8tochar(tcnt));

	__ddr_print("*********");
	__ddr_print("\r\n********************************");
	//__ddr_print(uint8tochar(dll_lock_value));


	//get training value for delay line
	phy_dll_training_addr_get();
	phy_dll_training_get();

	#ifndef ENCRPTY_LOG
	ddr_scan_master_dll_print();
	ddr_scan_training_boundary_print();
	ddr_scan_training_dll_print();
	ddr_scan_vref_print();
	#endif
	if(scan_info_g->freq_mode==BYPASS_MODE)
	{
		phy_scan_range_cfg(wr_range,WR_BYPASS_DLL);
		phy_scan_range_cfg(rd_range,RDDQS_BYPASS_DLL);
	}else
	{
		phy_scan_range_cfg(wr_range,WRDQ_DLL);
		phy_scan_range_cfg(rd_range,RDDQS_RISE_DLL);

	}

	SCAN_LOG_START;
	for(slice_num=0;slice_num<PHY_SLICE;slice_num++)
	{

		for(dq_num=0;dq_num<PHY_SLICE_DQ_NUM;dq_num++)
		{
			if(scan_info_g->freq_mode==BYPASS_MODE)
			{
				ddr_scan_wr(slice_num,dq_num,WR_BYPASS_DLL);
				ddr_scan_rd(slice_num,dq_num,RDDQS_BYPASS_DLL);
			}else
			{
				ddr_scan_wr(slice_num,dq_num,WRDQ_DLL);
				ddr_scan_rd(slice_num,dq_num,RDDQS_RISE_DLL);
				ddr_scan_rd(slice_num,dq_num,RDDQS_FALL_DLL);
			}
		}
	}
	#if 0
	for(ca_num=0;ca_num<PHY_CA_NUM;ca_num++)
	{

	}
	#endif
	SCAN_LOG_END;
	#ifndef ENCRPTY_LOG
	ddr_scan_result_dll_print();
	#endif
}

uint32 wr_addr[9]={68,68,69,69,70,70,71,71,72};
uint32 wr_addr_offset[9]={0,16,0,16,0,16,0,16,0};
uint32 rd_addr[9]={78,79,80,81,82,83,84,85,86};

uint32 byte_swap_cfg=0x00030102;
//uint32 bit_swap[4]={0x10237485,0x75685310,0x56847012,0x57240163};
uint32 bit_swap_cfg[4]={0x02718365,0x53671420,0x17046325,0x64073251};
#if 0
uint32 byte_swap=0x02030100;
uint32 bit_swap[4]={0x18076452,0x86735102,0x06587421,0x78523016};
#endif

void ddr_scan_dll_info_set()
{
	swap_info.wr_base_addr=wr_addr;
	swap_info.wr_offset=wr_addr_offset;
	swap_info.rd_base_addr=rd_addr;
	swap_info.byte_swap=byte_swap_cfg;
	swap_info.bit_swap=bit_swap_cfg;
	 scan_info.freq_num=(REG32(CANDS_CTL0_(175))>>16)&0x7;
    	reg_bit_set(CANDS_PHY0_(1024),0,1,0);
   	reg_bit_set(CANDS_PHY0_(1024),8,3,scan_info.freq_num);
    	if((( REG32(CANDS_PHY0_(479))>>8)&0xf)==0xc)
   	 {
	  	scan_info.freq_mode=BYPASS_MODE;
   	 }else
    	{
		  scan_info.freq_mode=NORMAL_MODE;
    	 }
	 scan_info.cs_num=MRW_CS0;
    	#ifdef DRAM_LPDDR3
    	scan_info.phy_ds=(REG32(CANDS_PHY0_(6))>>8)&0xf;
	scan_info.phy_odt=0x0;
	scan_info.phy_vref=(REG32(CANDS_PHY0_(1047))>>8)&0x3f;
    	#else
	scan_info.phy_ds=(REG32(CANDS_PHY0_(6))>>8)&0xf;
     	scan_info.phy_odt=(REG32(CANDS_PHY0_(6))>>0)&0xf;
     	scan_info.phy_vref=(REG32(CANDS_PHY0_(1047))>>8)&0x3fff;
    	#endif
	scan_info.slew_rate=REG32(CANDS_PHY0_(1074))&0xf;
	switch(scan_info.freq_num)
	{
		case 0:
			//MR3
			scan_info.device_ds=(REG32(CANDS_CTL0_(208))>>24)&0xff;
			//mr11
			scan_info.device_odt=(REG32(CANDS_CTL0_(210))>>8)&0xff;
			//mr14
			scan_info.device_vref=(REG32(CANDS_CTL0_(213))>>0)&0xff;
			break;
		case 1:
			//MR3
			scan_info.device_ds=(REG32(CANDS_CTL0_(209))>>0)&0xff;
			//mr11
			scan_info.device_odt=(REG32(CANDS_CTL0_(210))>>16)&0xff;
			//mr14
			scan_info.device_vref=(REG32(CANDS_CTL0_(213))>>8)&0xff;
			break;
		case 2:
			//MR3
			scan_info.device_ds=(REG32(CANDS_CTL0_(209))>>8)&0xff;
			//mr11
			scan_info.device_odt=(REG32(CANDS_CTL0_(210))>>24)&0xff;
			//mr14
			scan_info.device_vref=(REG32(CANDS_CTL0_(213))>>16)&0xff;
			break;
		case 3:
			//MR3
			scan_info.device_ds=(REG32(CANDS_CTL0_(209))>>16)&0xff;
			//mr11
			scan_info.device_odt=(REG32(CANDS_CTL0_(211))>>0)&0xff;
			//mr14
			scan_info.device_vref=(REG32(CANDS_CTL0_(213))>>24)&0xff;
			break;
		default:while(1);
	}
}


void ddr_lowpower_close()
{
	uint32 lp_state_cs0,lp_state_cs1;
	reg_bit_set(CANDS_CTL0_(163),24,2,0x3);
	reg_bit_set(CANDS_CTL0_(153),24,4,0x0);
	reg_bit_set(CANDS_CTL0_(141), 0,1,0x1);
	while((lp_state_cs0 !=0) &&(lp_state_cs1 !=0))
	{
		lp_state_cs0=(REG32(CANDS_CTL0_(153))>>8)&0xf;
		lp_state_cs1=(REG32(CANDS_CTL0_(153))>>16)&0xf;
	}

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
void ddr_scan(uint32 ddr_clk)
{

    	volatile uint32 i =0;
	#if DEBUG_SCAN
	uint32 timer_start = 0;
	uint32 timer_end = 0;
	uint32 timer_total = 0;
	#endif

	#ifndef ENCRPTY_LOG
    	//timer_start = REG32(0x40230004);
	#endif
	ddr_lowpower_close();
	ddr_scan_dll_info_set();
   	ddr_scan_channel(ddr_clk);
   	#if 0
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





