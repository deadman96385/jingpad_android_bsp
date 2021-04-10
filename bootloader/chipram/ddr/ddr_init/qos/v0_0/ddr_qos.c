#include "ddr_qos.h"


CANDS_QOS_T CANDS_PORT_INFO[] =
{
//  fixed_priority_en, r_priority, w_priority, bdw, bdw_overflow, all_strobes_used_en, arb_cmdq_th, age_count, command_age_count, q_fullness, n_q_entries_act_disable, }, //  port num, port master, port width, 
  {         1,             11,         11,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  0,        A53,         128,        
  {         1,              3,         13,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  1,        DISP,        64,         
  {         1,             15,         15,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  2,        GPU/GSP,     128,        
  {         1,              9,          9,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  3,        AP_NOC_MTX,  64,         
  {         1,              8,          7,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  4,        CAM,         64,         
  {         1,              7,          8,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  5,        VSP,         128,        
  {         1,              0,          0,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  6,        LWT_DSP,     64,         
  {         1,              0,          0,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  7,        LWT_ACC,     64,         
  {         1,              4,          4,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  8,        AUD CP,      64,         
  {         1,              1,          1,     100,       1,               0,               0,        0xff,          0xff,             0,              0x1b,           }, //  9,        PUB CP,      64,         
};

CANDS_QOS_T *__get_qos_info()
{
	return (CANDS_QOS_T *)(CANDS_PORT_INFO);
}
