#include "ddr_qos.h"


//========================================CANDS_CTL_ALLCHN_INFO========================================//
const CANDS_CTL_PERCHN_QOS_T CANDS_CTL_PERCHN_QOS_INFO[] =
{
        //r_priority    w_priority      bdw             bdw_overflow    fixed_priority_en       all_strobes_used_en     fifo_type_reg
        {0x5,             0x5,              40,             1,              1,                      0,                      3},//BIA/AP(128)
        {0x4,             0x4,              40,             1,              1,                      0,                      3},//VSP/GSP(64)
        {0x3,             0x3,              90,             1,              1,                      0,                      3},//DISP/CAM(128)
        {0x4,             0x4,              40,             1,              1,                      0,                      3},//GPU(128)
        {0x3,             0x3,              40,             1,              1,                      0,                      3},//AG/PUBCP(64)
        {0x2,             0x2,              40,             1,              1,                      0,                      3},//WTL0/WTL1(64)
};

const CANDS_CTL_ALLCHN_QOS_T CANDS_CTL_ALLCHN_QOS_INFO = 
{
	//age_count	addr_cmp_en	ap	arb_cmd_q_threshold	bank_split_en	command_age_count	cs_same_en	disable_rd_interleave
	0xf,		1,		0,	0x17,			1,		0xf,			0,		0,
	//disable_rw_group_w_bank_conlit	inhibit_dram_en	inorder_accept	num_q_entries_act_disable	placement_en
	0,					0,		0,		8,				1,
	//priority_en	q_fullness	rw_same_en	rw_same_page_en	swap_en	w2r_split_en	wr_order_req
	1,		0,		1,		1,		1,	1,		0
};

CANDS_CTL_PERCHN_QOS_T*__get_cands_ctl_perchn_qos_info()
{
	return (CANDS_CTL_PERCHN_QOS_T*)(&CANDS_CTL_PERCHN_QOS_INFO[0]);
};

CANDS_CTL_ALLCHN_QOS_T*__get_cands_ctl_allchn_qos_info()
{
	return (CANDS_CTL_ALLCHN_QOS_T*)(&CANDS_CTL_ALLCHN_QOS_INFO);
};


