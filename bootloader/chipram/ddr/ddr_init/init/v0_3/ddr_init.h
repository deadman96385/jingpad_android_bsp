 #include "ddr_common.h"


#define DDR_CLK_FLOATING

#define DDR_SIZE_TO_UBOOT		0xE602B000

#define CANDS_CTL_REG_BASE0 	0Xc0000000
#define CANDS_PI_REG_BASE0   	0Xc0000800
#define CANDS_PHY_REG_BASE0 	0Xc0002000

#define	CANDS_CTL0_(x)	    (CANDS_CTL_REG_BASE0+4*(x))
#define	CANDS_PHY0_(x)	    (CANDS_PHY_REG_BASE0+4*(x))
#define	CANDS_PI0_(x)       (CANDS_PI_REG_BASE0+4*(x))


#define CTL_REG_NUM				481
#define PI_REG_NUM				249
#define PHY_REG_NUM1			1024
#define PHY_REG_NUM2			85

/******************************ANA**************************************************/
#define ANA_DPLL_THM_TOP_0_MODU_CTRL_0	0xE4106004
#define ANA_DPLL_THM_TOP_0_DIV_CTRL_0	0xE4106008


/******************************AON APB**************************************************/
#define AON_APB_CGM_CFG				0xE42e0098
#define AON_APB_CGM_CFG_SET			0xE42e0098+0x1000
#define AON_APB_CGM_CLK_TOP_REG1		0xE42e013c
#define AON_APB_CGM_CLK_TOP_REG1_SET		0xE42e013c+0x1000
#define AON_APB_PUB_FC_CTRL			0xe42e01e0
#define AON_APB_PUB_FC_CTRL_SET			0xe42e01e0+0x1000
#define AON_APB_EMC_CKG_SEL			0xe42e01e4
#define AON_APB_EMC_CKG_SEL_SET	    0xe42e01e4+0x1000
#define PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE 0xC0010000
#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_DUMMY_REG1 PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0x80C0
#define AON_TOP_AON_APB_RF_REG_BASE 0xE42E0000
#define REG_AON_TOP_AON_APB_RF_SP_BASE_ADDR AON_TOP_AON_APB_RF_REG_BASE+0x32A8
#define REG_AON_TOP_AON_APB_RF_SP_BASE_ADDR_SET AON_TOP_AON_APB_RF_REG_BASE+0x42A8
#define REG_AON_TOP_AON_APB_RF_SP_BASE_ADDR_CLR AON_TOP_AON_APB_RF_REG_BASE+0x52A8
#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB_LP_CTRL_0  (PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0x04D0 )
#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB_LP_CTRL_0_SET  (PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0x14D0 )
#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB_LP_CTRL_0_CLR  (PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0x24D0 )
#define REG_AON_TOP_AON_APB_RF_CGM_CLK_TOP_REG1_SET (AON_TOP_AON_APB_RF_REG_BASE + 0x113C)
#define REG_AON_TOP_AON_APB_RF_CGM_CLK_TOP_REG1_CLR (AON_TOP_AON_APB_RF_REG_BASE + 0x213C)
#define token_cands_ctl_phy_release         0x1
#define token_cands_ctl_init                0x2
#define token_cands_pi_init                 0x3
#define token_cands_phy_init                0x4
#define token_cands_phy_pinmux_init         0x5
#define token_cands_ctl_qos_init            0x6
#define token_cands_ctrl_dfs_set            0x7
#define token_cands_phy_deskew_pll_mode_set 0x8
#define token_ddr_freq_target_set           0x9
#define token_ctrl_dfiupd_set               0xa
#define token_ctrl_lp_set                   0xb
#define token_phy_lp_setting                0xc
#define token_cands_phy_ds_odt_sr_set       0xd
#define token_ddr_init_trigger              0xe
#define token_polling_pi_training_done      0xf
#define token_wait_ctl_init_done            0x10
#define token_cands_fsp_para_update         0x11
#define token_pi_training_enable            0x12
#define token_switch_to_dfs_mode            0x13
#define token_dfs_go1                       0x14
#define token_dfs_go2                       0x15
#define token_dfs_go3                       0x16
#define token_dfs_go0                       0x17
#define token_cm4_ddr_wr_check1             0x18
#define token_cm4_ddr_wr_check2             0x19
#define token_cm4_ddr_wr_check3             0x1A
#define token_cm4_ddr_wr_check0             0x1B
#define token_cm4_ddr_wr_check0_INITIAL     0x1C
#define token_cands_ctl_phy_f0              0x1D
#define token_cands_ctl_phy_f1              0x1E
#define token_cands_ctl_phy_f2              0x1F
#define token_cands_ctl_phy_f3              0x20
#define token_pi_training_error             0x21
#define token_i_am_stuck_here               0xFF
#define token_cm4_data_check_pass 0xBA55BA55
#define token_cm4_data_check_fail 0xFA11FA11
/******************************PMU APB**************************************************/
#define PMU_APB_DDR_SLEEP_CTRL		0xE42c0008
#define PMU_APB_DDR0_CHN_SLEEP_CTRL     0xe42c008c
#define PMU_APB_PD_PUB0_SYS_CFG		0xE42B0044
#define DDR0_ACC_RDY			0xe42b02cc
#define PMU_APB_PUB0_SYS_SLEEP_CTRL	0xe42b012c

/******************************PUB**************************************************/
#define PUB0_SOFT_DFS_CTRL		0xc0018000
#define PUB0_SOFT_DFS_CTRL_SET	0xc0018000+0x1000
#define PUB0_LP_GEN_CTRL		0xc001802c
#define PUB0_LP_GEN_CTRL_SET	0xc001802c+0x1000
#define AXI_AW_COBUF_EN		0xc001801c


/************Driver Strength*********************/
typedef enum
{
	PAD_DRV_HZ = 0x0,
	PAD_DRV_240 = 0x1,
	PAD_DRV_120 = 0x3,
	PAD_DRV_80 = 0x5,
	PAD_DRV_60 = 0x7,
	PAD_DRV_48 = 0xd,
	PAD_DRV_40 = 0xf,
	PAD_DRV_34 = 0xf,
	PAD_DRV_60_LP4 = 0x6,
	PAD_DRV_48_LP4 = 0x7,
}DDR_DS_E;

/*************Memory Type*********************/
#define IS_LPDDR4(x)    (((x&0xff000000) == 0x40000000)?TRUE:FALSE)
#define IS_LPDDR3(x)    (((x&0xff000000) == 0x30000000)?TRUE:FALSE)
#define IS_2CS(x)       (((x&0x00f00000) == 0x00200000)?TRUE:FALSE)
#define IS_16BIT(x)     (((x&0x00000FF0) == 0x00000160)?TRUE:FALSE)

#define MAX_SECTION_NUM 8


typedef enum
{
    //lpddr3
    //DRAM_LPDDR3             = 0x30000000,
    DRAM_LPDDR3_1CS_4G_X32  = 0x30104320,
    DRAM_LPDDR3_1CS_6G_X32  = 0x30106320,
    DRAM_LPDDR3_1CS_8G_X32  = 0x30108320,
    DRAM_LPDDR3_1CS_8G_X16X2= 0x30108162,
    DRAM_LPDDR3_1CS_12G_X32 = 0x30112320,
    DRAM_LPDDR3_1CS_16G_X32 = 0x30116320,
    DRAM_LPDDR3_2CS_8G_X32  = 0x30208320,
    DRAM_LPDDR3_2CS_12G_X32 = 0x30212320,
    DRAM_LPDDR3_2CS_16G_X32 = 0x30216320,
    DRAM_LPDDR3_2CS_16G_X32_X16X4 = 0x30216324,
    DRAM_LPDDR3_2CS_24G_X32_X16X3 = 0x30224322,
    DRAM_LPDDR3_2CS_24G_X32_X16X4 = 0x30224324,
    DRAM_LPDDR3_2CS_24G_X32 = 0x30224320,
    DRAM_LPDDR3_2CS_32G_X32 = 0x30232320,
    DRAM_LPDDR3_2CS_32G_X32_X16X4 = 0x30232324,

    //lpddr4
    //DRAM_LPDDR4             = 0x40000000,
    DRAM_LPDDR4_1CS_4G_X32  = 0x40104320,
    DRAM_LPDDR4_1CS_6G_X32  = 0x40106320,
    DRAM_LPDDR4_1CS_8G_X32  = 0x40108320,
    DRAM_LPDDR4_1CS_12G_X32 = 0x40112320,
    DRAM_LPDDR4_1CS_16G_X32 = 0x40116320,
    DRAM_LPDDR4_1CS_12G_X16 = 0x40112160,
    DRAM_LPDDR4_1CS_6G_X16  = 0x40106160,
    DRAM_LPDDR4_2CS_8G_X32  = 0x40208320,
    DRAM_LPDDR4_2CS_12G_X32 = 0x40212320,
    DRAM_LPDDR4_2CS_16G_X32 = 0x40216320,
    DRAM_LPDDR4_2CS_24G_X32 = 0x40224320,
    DRAM_LPDDR4_2CS_12G_X16 = 0x40212160,
    DRAM_LPDDR4_2CS_32G_X32 = 0x40232320,
    DRAM_LPDDR4_2CS_16G_X8 = 0x40216080,
}DRAM_TYPE_E;




/*************Memory Auto Detect***************/
#define DDR_AUTO_DETECT
#ifdef DDR_AUTO_DETECT
typedef enum
{
	S4_SDRAM = 0,
	S2_SDRAM = 1,
	N_NVM = 2,
	S8_SDRAM = 3
}DDR_TYPE_E;

typedef enum
{
	MR8_SIZE_64Mb = 0,
	MR8_SIZE_128Mb = 1,
	MR8_SIZE_256Mb = 2,
	MR8_SIZE_512Mb = 3,
	MR8_SIZE_1Gb  =  4,
	MR8_SIZE_2Gb  =  5,
	MR8_SIZE_4Gb  =  6,
	MR8_SIZE_8Gb  =  7,
	MR8_SIZE_16Gb =  8,
	MR8_SIZE_32Gb =  9,

	MR8_SIZE_6Gb  =  14,
	MR8_SIZE_12Gb =  13
}MR8_DDR_SIZE_E;

typedef enum
{
	WIDTH_X32 = 0,
	WIDTH_X16 = 1,
	WIDTH_X8 = 2
}DDR_WIDTH_E;

struct MR8_size_info
{
	uint32 mr8_size;
	uint32 mem_size;
};

struct ddr_detect_info
{
	uint32 mem_size;
	uint32 mem_width;
	uint32 mem_type;
};
#endif
/******************************QOS**************************************************/
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



/******************************Training**************************************************/
#define PUB0_APB_FREQ_CHANGE_LP4_REQ		0xc001005c
#define PUB0_APB_FREQ_CHANGE_LP4_ACK		0xc00180bc
#define PUB0_APB_FREQ_CHANGE_LP4_TYPE	0xc001005c

#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_PHY_BIST       ( PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0x80C4 )
#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_DUMMY_REG0     ( PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0x80BC )
#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_DUMMY_REG0_SET ( PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0x90BC )
#define REG_PUB0_TOP_PUB_APB_RF_PUB0_PUB0_DUMMY_REG0_CLR ( PUB0_TOP_PUB_APB_RF_PUB0_REG_BASE + 0xA0BC )

/******************************DDR LOWPOWER**************************************************/
#define PUB0_APB_PUB_CHN0_LP_CTRL		0xc0014030


/***************************MPU*****************************************************/
#define PUB0_DMC_PORT_REMAP_EN			0xc0010008
#define PUB0_DMC_PORT0_ADDR_REMAP		0xc0010010
#define PUB0_DMC_PORT0_ADDR_REMAP_REG1		0xc00100d0
#define PUB0_DMC_PORT1_ADDR_REMAP		0xc0010014
#define PUB0_DMC_PORT1_ADDR_REMAP_REG1		0xc00100d4
#define PUB0_DMC_PORT2_ADDR_REMAP		0xc0010018
#define PUB0_DMC_PORT2_ADDR_REMAP_REG1		0xc00100d8
#define PUB0_DMC_PORT3_ADDR_REMAP		0xc001001c
#define PUB0_DMC_PORT3_ADDR_REMAP_REG1		0xc00100dc
#define PUB0_DMC_PORT4_ADDR_REMAP		0xc0010020
#define PUB0_DMC_PORT4_ADDR_REMAP_REG1		0xc00100e0
#define PUB0_DMC_PORT5_ADDR_REMAP		0xc0010024
#define PUB0_DMC_PORT5_ADDR_REMAP_REG1		0xc00100e4

/******************************BIST**************************************************/
#define BIST_BASE_ADDR		0xC00D0000
#define BIST_PORT_ADDR 		0xc0018028

#define USER_PATT 0
#define SIPI_PATT 1
#define LFSR_PATT 2

#define DWORD 0
#define BYTE  1
#define HWORD 2
#define WORD  3

#define BIST_WRITE  0
#define BIST_READ   1
#define BIST_ALLWRC 2
#define BIST_ONEWRC 3

#define DDR_CHN0 0
#define DDR_CHN1 1

#define BIST_ARM 0
#define BIST_GPU 1
#define BIST_VSP 2


#define NORMAL_MODE    	0
#define CYCLE_MODE       	1



/***************************Interface*****************************************************/
//#define DDR_SCAN
#define DFS_EN
#define BIST_EN
//#define PLL_NO_WAIT //XH: please check whether need this wait.
//#define PHY_RELEASE_NO_WAIT //XH: please check how many wait time need in reality


/***************************Customer Interface*****************************************************/
#define ODT_40OHM		6
#define ODT_48OHM		5
#define ODT_60OHM		4
#define ODT_80OHM		3
#define VREF_ODT_40OHM_LP4X			0x11		//25%	range0
#define VREF_ODT_48OHM_LP4X			0x5d		//50.1%	range0
#define VREF_ODT_60OHM_LP4X			0x19		//30%	range0
#define VREF_ODT_80OHM_LP4X			0x1f		//33.3% range0
#define VREF_CA_LP4X					0x5d		//50%	range1
//#define DRAM_LPDDR3
#define LP3_1GB_PCS
#define DRAM_PIN_SWAP 0x1
//#define BIST_TEST_FX
#define LP4X_ODT_SET	0//ODT_48OHM
//per-cs training setting
//please note some parameter in PHY slice has both frequency copy and CS copy, this form a matrix of FSP/CS
//PHY default support per-CS training(PHY_PER_CS_TRAINING_MULTICAST_EN_0/1/2/3 default to 0x1).it just stores the per-CS traiing result.
//the per-CS training function is controlled by PI module, by parameter such as "PI_RDLVL_CS" and "PI_RDLVL_CS_MAP" 
#define PI_CS_MAP           0x3          //XH: this is used to limit PI training on one CS to reduce simulation time, must be set to 1 in real chip if necessary, Please evaluate.
#define PI_TRAINING_ON      0x1

#ifdef DRAM_LPDDR3
#define PI_WRLVL_EN         0x0
#define PI_CALVL_EN         0x0
#define PI_RDLVL_GATE_EN    0x1 //bit[1]:during no-initialization, bit[0]: during initialization
#define PI_RDLVL_EN         0x0
#define PI_WDQLVL_EN        0 //XH: LP3 should do this?
#define PI_CA_TRAIN_VREF_EN 0 //XH: ?
#define PI_WDQLVL_VREF_EN   0 //XH: ?

#define DRAM_DS		0x2		//40ohm	mr3_data
#else
#define PI_WRLVL_EN         0x1
#define PI_CALVL_EN         0x1
#define PI_RDLVL_GATE_EN    0x1 //bit[1]:during no-initialization, bit[0]: during initialization
#define PI_RDLVL_EN         0x1
#define PI_WDQLVL_EN        1 //XH: LP3 should do this?
#define PI_CA_TRAIN_VREF_EN 1 //XH: ?
#define PI_WDQLVL_VREF_EN   1 //XH: ?

#define DRAM_DS	0x31	//40ohm mr3_data
#endif
#ifdef DRAM_LPDDR4_1000M
#define PI_FREQ_MAP		0xe	//define which freq point would be trained, each bit repreasent one freq point
#else
#define PI_FREQ_MAP		0x1e	//define which freq point would be trained, each bit repreasent one freq point
#endif

//#define PHY_PER_CS_TRAINING         0x1  //XH: this is used to limit PI training on one CS to reduce simulation time, must be set to 1 in real chip if necessary, Please evaluate.
//#define PHY_PER_CS_TRAINING_WR_PATH 0   //should modify to 1 for specific parts, such as read path which has different tDQSCK parameter. but
//                                        //for write path, it may be not necessary. please update it later
//#define PHY_PER_CS_TRAINING_RD_GATE 1   //should modify to 1 for specific parts, such as read path which has different tDQSCK parameter. but
//                                        //for write path, it may be not necessary. please update it later. make sure it is implemented
//#define PHY_PER_CS_TRAINING_RD_EYE  1   //should modify to 1 for specific parts, such as read path which has different tDQSCK parameter. but
                                        //for write path, it may be not necessary. please update it later. make sure it is implemented

//training when exit sr
#define PI_WRLVL_ON_SREF_EXIT 0         //XH: TBD ???
#define PI_RDLVL_ON_SREF_EXIT 0         //XH: TBD ???
#define PI_RDLVL_GATE_ON_SREF_EXIT 0    //XH: TBD ???
#define PI_CALVL_ON_SREF_EXIT 0         //XH: TBD ???
#define PI_WDQLVL_ON_SREF_EXIT 0        //XH: TBD ???
//#define LP3_SIM_FAST_INIT //make tinit smaller to speed up simulation. must comment off in chip
#define CANDS_CTL_QOS_CFG_OFF //to speed up simulation only, please comment off this in chip
//#define PHY_DS_ODT_SR_CFG_OFF //to speed up simulation only, please comment off this in chip
#define DPLL_NO_WAIT //XH: please check whether need this wait.
#define PHY_RELEASE_NO_WAIT //XH: please check how many wait time need after reset released in chip

/***************************DDR CLK CONDFIG*****************************************************/
//#define LP3_F0_153 //
#define DPLL_CFG_LP3	920
#define DDR_FREQ_INFO_ADDR 0xe602a044
//lp4
#define PHY_PLL_BYPASS_F0		0x1
#define PHY_PLL_BYPASS_F1 		0x1
#define PHY_PLL_BYPASS_F2 		0x1
#define PHY_PLL_BYPASS_F3 		0x1

//#define WATCH_DOG_REBOOT_TEST
