#include "ddr_qos.h"


//========================================CANDS_CTL_ALLCHN_INFO========================================//
const CANDS_CTL_PERCHN_QOS_T CANDS_CTL_PERCHN_QOS_INFO[] =
{
#ifdef DRAM_LPDDR3
        //r_priority    w_priority      bdw             bdw_overflow    fixed_priority_en       all_strobes_used_en     fifo_type_reg
        {5,             5,              18,             1,              1,                      0,                      3},//A53(128)
        {3,             3,              18,             1,              1,                      0,                      3},//DISP(64)
        {4,             4,              18,             1,              1,                      0,                      3},//GPU/GSP(128)
        {5,             5,              18,             1,              1,                      0,                      3},//AP_MTX(64)
        {4,             3,              18,             1,              1,                      0,                      3},//CAM(64)
        {4,             4,              18,             1,              1,                      0,                      3},//VSP(128)
        {2,             2,              18,             1,              1,                      0,                      3},//LWT_DSP(64)
        {2,             2,              18,             1,              1,                      0,                      3},//LWT_ACC(64)
        {3,             3,              18,             1,              1,                      0,                      3},//PUB_CP(64)
        {2,             2,              18,             1,              1,                      0,                      3},//AUD_CP(64)
        {4,             3,              18,             1,              1,                      0,                      3} //CAM2(64)
#else
	//r_priority	w_priority	bdw		bdw_overflow	fixed_priority_en	all_strobes_used_en	fifo_type_reg
	{6,		6,		18,		1,		1,			0,			3},//A53(128)
	{2,		7,		18,		1,		1,			0,			3},//DISP(64)
	{5,		5,		18,		1,		1,			0,			3},//GPU/GSP(128)
	{6,		6,		18,		1,		1,			0,			3},//AP_MTX(64)
	{4,		2,		18,		1,		1,			0,			3},//CAM(64)
	{5,		5,		18,		1,		1,			0,			3},//VSP(128)
	{1,		1,		18,		1,		1,			0,			3},//LWT_DSP(64)
	{1,		1,		18,		1,		1,			0,			3},//LWT_ACC(64)
	{4,		4,		18,		1,		1,			0,			3},//PUB_CP(64)
	{2,		2,		18,		1,		1,			0,			3},//AUD_CP(64)
	{2,		2,		95,		1,		1,			0,			3} //CAM2(64)
#endif
};

const CANDS_CTL_ALLCHN_QOS_T CANDS_CTL_ALLCHN_QOS_INFO = 
{
	//age_count	addr_cmp_en	ap	arb_cmd_q_threshold	bank_split_en	command_age_count	cs_same_en	disable_rd_interleave
	0xf,		1,		0,	15,			1,		0xf,			0,		0,
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


