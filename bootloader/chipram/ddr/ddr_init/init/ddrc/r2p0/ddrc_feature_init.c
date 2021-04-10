/**************
**qos configure
**interleave configure
**prefetch
************/
#include "ddrc_init.h"
#include "ddrc_feature_init.h"

extern DRAM_INFO_T dram_info;


const QOS_TIMEOUT_CHN_T qos_timeout_per_ch[]=
{
	//rf_timeout_thr_rd_chx	rf_timeout_thr_wr_chx		rf_pri_wr_chx		rf_pri_rd_chx
	{0x0,					0x0,						0x6,				0x6},//CPU
	{0x0,					0x0,						0x6,				0x6},//GPU
	{0x0,					0x0,						0xd,				0xd},//DPU/DCAM
	{0x0,					0x0,						0x7,				0x7},//ISP
	{0x0,					0x0,						0x7,				0x7},//AP/VSP/AON
	{0x0,					0x0,						0xe,				0xe},//WTLCP
	{0x0,					0x0,						0x9,				0x9},//PUBCP/AUDCP
};

void ctrl_qos_timeout_set()
{
	u32 chn_num=0;
	for(chn_num=0;chn_num<PUB_CHN_NUM;chn_num++)
	{
		reg_bit_set(DMC_CTL0_(0x0020+chn_num*0x8),24, 8,qos_timeout_per_ch[chn_num].timeout_thr_rd_ch);//rf_timeout_thr_rd_ch
		reg_bit_set(DMC_CTL0_(0x0020+chn_num*0x8),16, 8,qos_timeout_per_ch[chn_num].timeout_thr_wr_ch);//rf_timeout_thr_wr_ch
		reg_bit_set(DMC_CTL0_(0x0020+chn_num*0x8), 0, 4,qos_timeout_per_ch[chn_num].pri_wr_ch);//rf_pri_wr_ch
		reg_bit_set(DMC_CTL0_(0x0024+chn_num*0x8), 0, 4,qos_timeout_per_ch[chn_num].pri_rd_ch);//rf_pri_rd_ch
	}

}

void ctrl_urgent_set()
{
	//enable urgent machine
	reg_bit_set(DMC_CTL0_(0x0014),9,1,0x1);//rf_urgent_qos_en
	//high urgent
	reg_bit_set(DMC_CTL0_(0x0130),16,16,0x8080);//rf_hi_urgent_map
	//low urgent
	reg_bit_set(DMC_CTL0_(0x0130), 0,16,0x4040);//rf_lo_urgent_map
}

void pub_sys_urgent_set()
{
	//bypass qosc urgent
	reg_bit_set(QOS_SWITCH,0,1,0x1);//qos_urgent_sel
	reg_bit_set(QOS_SWITCH,1,1,0x1);//urgent_chn_sel
	//qos value
	__raw_writel(PUB_AXI_QOS_URGENT_REG_0,0x77dd6666);
	reg_bit_set(PUB_AXI_QOS_URGENT_REG_1,0,24,0x99ee77);
	//qos threshold/aon channel qos
	__raw_writel(QOS_THRESHOLD_0,0xffcc6600);
}

void ddrc_ctrl_perf_set()
{
	//performace
	reg_bit_set(DMC_CTL0_(0x0010), 0,16,0x1);//rf_port_prefetch_en
	reg_bit_set(DMC_CTL0_(0x0010),16, 3,0x1);//rf_prefetch_cnt
	reg_bit_set(DMC_CTL0_(0x0010),19, 1,0x1);//rf_ba_prefetch_en
	reg_bit_set(DMC_CTL0_(0x0024), 8, 1,0x1);//rf_urgent_rd_ch0
	reg_bit_set(DMC_CTL0_(0x003c), 8, 1,0x0);//rf_urgent_rd_ch3
}

void ap_ctrl_qos_set()
{
	reg_bit_set(AP_QOS0, 8,16,0x5555);
	__raw_writel(AP_QOS1,0x55555555);
	reg_bit_set(AP_QOS2, 0,24,0x5566cf);
}

void ddrc_ctrl_qos_set()
{
	ctrl_qos_timeout_set();
	ctrl_urgent_set();
	pub_sys_urgent_set();
	ddrc_ctrl_perf_set();
	ap_ctrl_qos_set();

}

void ddrc_ctrl_interleave_init(u32 intlv_size )
{
	//interleave_cfg
	reg_bit_set(DMC_CTL0_(0x0014), 0, 3,0x0);//rf_interleave_size 0:64B/1:128B/2:256B/3:512B/4:1KB/5:2KB/6:4KB/7:8K
	reg_bit_set(DMC_CTL0_(0x0144),24, 3,(dram_info.dram_type==DRAM_LP3)?0x0:0x1);//rf_interleave_mode 0:non interleave 1:ch0/1 2:ch2/3 3:ch0/1/2/3
	reg_bit_set(DMC_CTL0_(0x0148), 0,14, RF_LINEAR_BASE_CHN0);//rf_linear_base_chn0
	reg_bit_set(DMC_CTL0_(0x0148),16,14, RF_LINEAR_BASE_CHN1);//rf_linear_base_chn1
	reg_bit_set(DMC_CTL0_(0x014c), 0,14, RF_LINEAR_BASE_CHN2);//rf_linear_base_chn2
	reg_bit_set(DMC_CTL0_(0x014c),16,14, RF_LINEAR_BASE_CHN3);//rf_linear_base_chn3
	reg_bit_set(DMC_CTL0_(0x0150), 0,14, RF_INTERLEAVE_BASE);//rf_linear_base
	reg_bit_set(DMC_CTL0_(0x0150),16,14, RF_INTERLEAVE_OFFSET);//rf_linear_offset
}

void ddrc_ctrl_interleave_set(u32 intlv_size)
{
	if(dram_info.dram_type==DRAM_LP3)
	{
		dram_info.intlv_size=0x0;
	}else
	{
		switch(intlv_size)
		{
		case INT_SIZE_64B:dram_info.intlv_size=0x40;break;
		case INT_SIZE_128B:dram_info.intlv_size=0x80;break;
		case INT_SIZE_256B:dram_info.intlv_size=0x100;break;
		case INT_SIZE_512B:dram_info.intlv_size=0x200;break;
		case INT_SIZE_1KB:dram_info.intlv_size=0x400;break;
		}
	}
	reg_bit_set(DMC_CTL0_(0x0014), 0, 3,intlv_size);//rf_interleave_size 0:64B/1:128B/2:256B/3:512B/4:1KB/5:2KB/6:4KB/7:8K
}




