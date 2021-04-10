
#include <config.h>
typedef struct
{
	unsigned short  r_priority;
	unsigned short  w_priority;
	unsigned short  bdw;
	unsigned short  bdw_overflow;
	unsigned short  fixed_priority_en;
	unsigned short  all_strobes_used_en;
	unsigned short  fifo_type_reg;
}CANDS_CTL_PERCHN_QOS_T;

typedef struct
{
	unsigned short age_count;
	unsigned short addr_cmp_en;
	unsigned short ap;
	unsigned short arb_cmd_q_shreshold;
	unsigned short bank_split_en;
	unsigned short cmd_age_count;
	unsigned short cs_same_en;
	unsigned short disable_rd_interleave;
	unsigned short disable_rw_group_bank_conflit;
	unsigned short inhibit_dram_en;
	unsigned short in_order_accept;
	unsigned short num_q_entries_act_disable;
	unsigned short placement_en;
	unsigned short priority_en;
	unsigned short q_fullness;
	unsigned short rw_same_en;
	unsigned short rw_same_page_en;
	unsigned short swap_en;
	unsigned short w2r_split_en;
	unsigned short wr_order_req;
}CANDS_CTL_ALLCHN_QOS_T;
