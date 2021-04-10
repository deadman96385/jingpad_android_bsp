#include "debug.h"
#if (defined DDR_REINIT_TEST) || (defined POWER_TEST)
#include "sharkl3_ddr_reinit.h"
#include "ddrc_r1p0_phy_cfg_lp3.h"

#define REINIT_LOG_EN
struct RE_ddr_sys_info sys_info_config;
struct RE_ddr_sys_info     *sys_info=&sys_info_config;
struct RE_ddr_debug_info debug_info;
struct RE_ddr_debug_info *reinit_info_g=&debug_info;
struct RE_PUB_CLK_CFG  *clk_cfg;

uint32 start=0;
uint32 end=0;
uint32 ctl_reg0_data[DMC_CTRL_REG0_NUM];
uint32 ctl_reg1_data[DMC_CTRL_REG1_NUM];
uint32 mem_fw_reg_data[MEM_FW_REG_NUM];
uint32 dfi_busmon_reg_data[DFI_BUMON_REG_NUM];
uint32 phy0_reg_data[DMC_PHY_REG_NUM];
uint32 phy1_reg_data[DMC_PHY_REG_NUM];

uint32 mem_fw_reg_add[MEM_FW_REG_SECTION_NUM] = {MEM_FW_(0), MEM_FW_(2), MEM_FW_(3), MEM_FW_(10), MEM_FW_(18), MEM_FW_(36)};

//#define REINIT_TEST_MODE_ADDR (0x00800000)
#define REINIT_TEST_MODE_ADDR (0x00002000)
uint32 dfs_freq[]={156, 311, 933};
enum reinit_test_interval_mode{
short_interval,
long_interval,
random_interval,
};
enum reinit_test_bist_mode{
bist_after_reinit,
bist_over_powerdown,
};
enum reinit_test_dfs_mode{
no_dfs,
dfs_all_freq,
};

struct RE_REINTI_TEST_MODE{
    uint32 interval_s;
    uint32 interval_l;
    uint32 interval_r;
    enum reinit_test_interval_mode interval;
    enum reinit_test_bist_mode  bist;
    enum reinit_test_dfs_mode dfs;
};
struct RE_REINTI_TEST_MODE *reinit_test_mode_addr = REINIT_TEST_MODE_ADDR;

#if (defined REINIT_LOG_EN)&&(!defined POWER_TEST)
#define RX_BUF_MAX_SIZE 2000
char uart_rx_buf[RX_BUF_MAX_SIZE];
uint32 g_uart_rx_buf_index = 0;
uint32 g_uart_rx_buf_index_avild = 0;
static void pwr_uart_put(char *string)
{
    serial_puts(string);
}

static char * pwr_uart_get(void)
{
    char tmp = 0;
    g_uart_rx_buf_index_avild = g_uart_rx_buf_index;
    do{
        tmp = (serial_getc());
        uart_rx_buf[g_uart_rx_buf_index++] = tmp;
    }while('\r' != tmp);
    uart_rx_buf[g_uart_rx_buf_index-1] = '\0';
    return &(uart_rx_buf[g_uart_rx_buf_index_avild]);
}
static int pwr_strcmp(const char * cs,const char * ct)
{
	register signed char __res;

	while (1) {
            if(('\n' == *cs)||('\r' == *cs)){
                cs++;
                continue;
            }
		if ((__res = *cs - *ct++) != 0 || !*cs++)
			break;
	}

	return __res;
}

static void ddr_print(char * string)
{
    pwr_uart_put(string);
}
static void ddr_printc(char word)
{
    serial_putc(word);
}
static char ascii[]="0123456789abcdef";
static void ddr_print_u32_hex(uint32 data)
{
	uint32 index,i;

	ddr_printc('0');
	ddr_printc('x');
	for(i=4;i<=32;i=i+4)
	{
		index= (data>>(32-i))&0xf;
		ddr_printc(ascii[index]);
	}
	ddr_printc(' ');
	return;
}

uint32 mult10(uint32 n)
{
    uint32 sum = 10;
    uint32 m;
    if(n==0) return 1;
    for(m=1; m<n; m++) sum*=10;
    return sum;
}
static void ddr_print_u32_dec(uint32 data)
{
	uint32 index,i;

	for(i=0;i<10;i++)
	{
		index= ((data % mult10((11 - i))) / mult10((10 - i)));
		ddr_printc(ascii[index]);
	}
	index= (data % 10);
	ddr_printc(ascii[index]);
	ddr_printc(' ');
	return;
}
#else
static void pwr_uart_put(char *string)
{
}

static char * pwr_uart_get(void)
{
}
static int pwr_strcmp(const char * cs,const char * ct)
{
}

static void ddr_print(char * string)
{
}
static void ddr_printc(char word)
{
}
static void ddr_print_u32_hex(uint32 data)
{
}

uint32 mult10(uint32 n)
{
}
static void ddr_print_u32_dec(uint32 data)
{
}
#endif

void reinit_test_mode_init()
{
    reinit_test_mode_addr->interval_s = 100;       //unit ms
    reinit_test_mode_addr->interval_l = 180000;     //unit ms
    reinit_test_mode_addr->interval_r = 1;       //uint ms
    reinit_test_mode_addr->interval = random_interval;    //0: short_interval; 1:long_interval; 2:random_interval
//    reinit_test_mode_addr->bist = bist_after_reinit;
    reinit_test_mode_addr->bist = bist_over_powerdown;
    reinit_test_mode_addr->dfs = no_dfs;
}

struct RE_PUB_CLK_CFG  lp3_clk_info[8]=
{

	/*freq_num, ddr_clk, pll_source, ratio
		pub_dfs_sw_ratio_default, pub_dfs_sw_ratio_d2_default, pub_dfs_sw_clk_mode,half_freq_mode
	*/
	#ifdef TWPLL_CONFIG
	{0,RE_CLK_156M,DPLL0,DESKEW_OFF,1,{0x0,0x5,0x2,0x1,0x2,0x1,0x0}},
	{1,RE_CLK_233M,DPLL0,DESKEW_OFF,1,{0x0,0x3,0x2,0x1,0x2,0x1,0x0}},
	{2,RE_CLK_311M,DPLL0,DESKEW_OFF,1,{0x0,0x2,0x2,0x1,0x2,0x1,0x0}},
	{3,RE_CLK_384M,TWPLL,DESKEW_OFF,1,{0x5,0x0,0x2,0x1,0x2,0x1,0x0}},
	{4,RE_CLK_512M,TWPLL,DESKEW_ON,1,{0x4,0x0,0x1,0x0,0x1,0x1,0x0}},
	{5,RE_CLK_622M,DPLL0,DESKEW_ON,1,{0x0,0x2,0x1,0x0,0x1,0x1,0x0}},
	{6,RE_CLK_768M,TWPLL,DESKEW_OFF,2,{0x6,0x0,0x2,0x0,0x0,0x0,0x0}},  //?
	{7,RE_CLK_933M,DPLL0,DESKEW_OFF,2,{0x0,0x0,0x2,0x2,0x2,0x0,0x0}}  //?
	#else
	{0,RE_CLK_160M,DPLL1,DESKEW_OFF,1,{0x1,0x4,0x2,0x1,0x2,0x1,0x0}},
	{1,RE_CLK_233M,DPLL0,DESKEW_OFF,1,{0x0,0x3,0x2,0x1,0x2,0x1,0x0}},
	{2,RE_CLK_311M,DPLL0,DESKEW_OFF,1,{0x0,0x2,0x2,0x1,0x2,0x1,0x0}},
	{3,RE_CLK_400M,DPLL1,DESKEW_ON,1,{0x1,0x1,0x1,0x1,0x2,0x1,0x0}},
	{4,RE_CLK_533M,DPLL1,DESKEW_ON,1,{0x1,0x2,0x1,0x0,0x1,0x1,0x0}},
	{5,RE_CLK_622M,DPLL0,DESKEW_ON,1,{0x0,0x2,0x1,0x0,0x1,0x1,0x0}},
	{6,RE_CLK_800M,DPLL1,DESKEW_ON,2,{0x1,0x0,0x2,0x0,0x0,0x0,0x0}},
	{7,RE_CLK_933M,DPLL0,DESKEW_OFF,2,{0x0,0x0,0x2,0x0,0x0,0x0,0x0}}  //?
	#endif
};

#ifdef DMA_CONFIG
#define DMA_TRANS_TIMEOUT         (10000)
uint32 dma_chn1,dma_chn2;
DMA_CHNCFG_T channelcfg_1 = {0};
DMA_CHNCFG_T channelcfg_2 = {0};
DMA_LINKLIST_HANDLE linklist_handle_1,linklist_handle_2;

PUBLIC uint32 DMA_chn1_linklist_cfg(void)
{
	channelcfg_1.type = DMA_CHN_TYPE_SOFT;
	channelcfg_1.workmode = DMA_CHN_WORKMODE_LINKLIST;
	channelcfg_1.requestmode= DMA_CHN_REQMODE_LIST;
	channelcfg_1.priority = 0;
	channelcfg_1.src_datawidth  = DMA_DATAWIDTH_WORD;
	channelcfg_1.dest_datawidth = DMA_DATAWIDTH_WORD;
	channelcfg_1.src_step = 4;
	channelcfg_1.dest_step = 4;
}

PUBLIC uint32 DMA_chn1_linklist_set(uint32 src, uint32 des, uint32 length)
{
	    channelcfg_1.src_address = (uint32)(src) ;
	    channelcfg_1.dest_address = (uint32)(des) ;
	    channelcfg_1.total_length  = length;
	    channelcfg_1.block_length  = length;
	    channelcfg_1.frag_length  = length;
	    DMA_HAL_AppendInitLinkList(linklist_handle_1, &channelcfg_1);
}

PUBLIC uint32 DMA_HAL_LinkList_chn1_init()
{
	uint32 i;
	dma_chn1 = DMA_HAL_AllocChn (DMA_CHN_TRSF_TYPE_FULL);
	linklist_handle_1 = DMA_HAL_InitLinkList(dma_chn1);
	if (DMA_CHANNELID_INVALID == dma_chn1)
		return DMA_CHANNELID_INVALID;
	DMA_chn1_linklist_cfg();
}

PUBLIC uint32 DMA_chn1_linklist_polling_done(void)
{
	uint32 wait_time;
	//waiting for dma transfer finished
	wait_time = 0;
	while(DMA_TRANS_TIMEOUT > wait_time)
	{
		if(DMA_HAL_PollingListDone(dma_chn1))
			break;
//		for_delay(100);
		wait_time += 1;
	}
	if(DMA_TRANS_TIMEOUT <= wait_time)
		return 0;
	else
		return 1;
}

void DMA_chn1_linklist_addr_set()
{
	uint32 *addr = 0;
	DMA_chn1_linklist_set(&ctl_reg0_data[0], CANDS_CTL0_(0), CTL0_REG_SAVE_SIZE);
	DMA_chn1_linklist_set(&ctl_reg0_data[0], DMC_CTL_(64), DMC_CTRL_REG1_NUM);

	DMA_chn1_linklist_set(&phy0_reg_data[0], DMC_PHY0_(0), DMC_PHY_REG_NUM);
	DMA_chn1_linklist_set(&phy1_reg_data[0], DMC_PHY1_(0), DMC_PHY_REG_NUM);

	addr=mem_fw_reg_data;
	DMA_chn1_linklist_set(addr, mem_fw_reg_add[0], MEM_FW_REG0_NUM);
	DMA_chn1_linklist_set((addr + MEM_FW_REG0_NUM) , mem_fw_reg_add[1], MEM_FW_REG1_NUM);
	DMA_chn1_linklist_set((addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM) , mem_fw_reg_add[2], MEM_FW_REG2_NUM);
	DMA_chn1_linklist_set((addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM + MEM_FW_REG2_NUM) , mem_fw_reg_add[3], MEM_FW_REG3_NUM);
	DMA_chn1_linklist_set((addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM + MEM_FW_REG2_NUM + MEM_FW_REG3_NUM) , mem_fw_reg_add[4], MEM_FW_REG4_NUM);
	DMA_chn1_linklist_set((addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM + MEM_FW_REG2_NUM + MEM_FW_REG3_NUM + MEM_FW_REG4_NUM) , mem_fw_reg_add[5], MEM_FW_REG5_NUM);

	DMA_chn1_linklist_set(&dfi_busmon_reg_data[0], DFI_BUSMON_(0), DFI_BUMON_REG_NUM);
}
#endif

void __data_move(uint32 src,uint32 dst,uint32 count)
{
	volatile uint32 i = 0;

	for(i = 0; i < count;i++)
	{
		REG32(dst+i*4) = REG32(src+i*4);
	}
}


void pub_register_save( )
{
	uint32 *addr;
	//ctl regs save
	addr=ctl_reg0_data;
	__data_move(DMC_CTL_(0),addr,DMC_CTRL_REG0_NUM);
	addr=ctl_reg1_data;
	__data_move(DMC_CTL_(64),addr,DMC_CTRL_REG1_NUM);
	//mem fw regs save
	addr=mem_fw_reg_data;
	__data_move(mem_fw_reg_add[0], addr, MEM_FW_REG0_NUM);
	__data_move(mem_fw_reg_add[1], (addr + MEM_FW_REG0_NUM) , MEM_FW_REG1_NUM);
	__data_move(mem_fw_reg_add[2], (addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM) , MEM_FW_REG2_NUM);
	__data_move(mem_fw_reg_add[3], (addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM + MEM_FW_REG2_NUM), MEM_FW_REG3_NUM);
	__data_move(mem_fw_reg_add[4], (addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM + MEM_FW_REG2_NUM + MEM_FW_REG3_NUM), MEM_FW_REG4_NUM);
	__data_move(mem_fw_reg_add[5], (addr + MEM_FW_REG0_NUM + MEM_FW_REG1_NUM + MEM_FW_REG2_NUM + MEM_FW_REG3_NUM + MEM_FW_REG4_NUM), MEM_FW_REG5_NUM);

	//dfi busmon regs save
	addr=dfi_busmon_reg_data;
	__data_move(DFI_BUSMON_(0),addr,DFI_BUMON_REG_NUM);
	//phy regs save
	addr=phy0_reg_data;
	__data_move(DMC_PHY0_(0),addr,DMC_PHY_REG_NUM);
	addr=phy1_reg_data;
	__data_move(DMC_PHY1_(0),addr,DMC_PHY_REG_NUM);
}

void ctl_register_restore()
{
	uint32 *addr;
	//ctl regs restore
	addr=ctl_reg1_data;
	__data_move((addr+32),DMC_CTL_(96),DMC_CTRL_REG1_NUM-32);
	addr=ctl_reg0_data;
	__data_move(addr,DMC_CTL_(0),DMC_CTRL_REG0_NUM);
	addr=ctl_reg1_data;
	__data_move(addr,DMC_CTL_(64),32);
}

void pub_register_restore( )
{
	uint32 *addr;
	//mem fw regs save
	addr=mem_fw_reg_data;
	__data_move(addr,MEM_FW_(0),MEM_FW_REG0_NUM);
	__data_move((addr+2),MEM_FW_(2),MEM_FW_REG1_NUM);
	__data_move((addr+3),MEM_FW_(3),MEM_FW_REG2_NUM);
	__data_move((addr+10),MEM_FW_(10),MEM_FW_REG3_NUM);
	__data_move((addr+18),MEM_FW_(18),MEM_FW_REG4_NUM);
	__data_move((addr+36),MEM_FW_(36),MEM_FW_REG5_NUM);
	//dfi busmon regs save
	addr=dfi_busmon_reg_data;
	__data_move(addr,DFI_BUSMON_(0),DFI_BUMON_REG_NUM);

}

void phy_register_restore()
{
	uint32 *addr;
	//phy regs save
	addr=phy0_reg_data;
	__data_move(addr,DMC_PHY0_(0),DMC_PHY_REG_NUM);
	addr=phy1_reg_data;
	__data_move(addr,DMC_PHY1_(0),DMC_PHY_REG_NUM);;
}

void pub_clk_update()
{
	uint32 val=0;
        if(0 == (clk_cfg+sys_info->freq_num)->dfs_cfg.updated)
        {
        	//pub_dfs_sw_ratio_default.dpll_sel, 0:dpll0, 1:dpll1
        	(clk_cfg+sys_info->freq_num)->dfs_cfg.pll_sel = reg_bit_get(DFS_SW_CTRL,15,3);
        	//pub_dfs_sw_ratio_default.dpll_div_sel
        	(clk_cfg+sys_info->freq_num)->dfs_cfg.dpll_div_sel = reg_bit_get(DFS_SW_CTRL,18,4);
        	//pub_dfs_sw_clk_mode_default
        	(clk_cfg+sys_info->freq_num)->dfs_cfg.deskew_mode = reg_bit_get(DFS_SW_CTRL1,18,2);
        	//pub_dfs_sw_ratio_d2_default.x1_sel
        	(clk_cfg+sys_info->freq_num)->dfs_cfg.x1_sel = reg_bit_get(DFS_SW_CTRL1,8,2);
        	//pub_dfs_sw_ratio_d2_default.d2_sel
        	(clk_cfg+sys_info->freq_num)->dfs_cfg.d2_sel = reg_bit_get(DFS_SW_CTRL1,10,2);
        	//half_freq_mode
        	(clk_cfg+sys_info->freq_num)->dfs_cfg.half_freq_mode = reg_bit_get(DMC_CTL_(104),30,1);
                (clk_cfg+sys_info->freq_num)->dfs_cfg.updated = 1;
        }
}

void pub_clk_init()
{
	uint32 val=0;
	//pub_dfs_hw_enable, 0:dfs_sw_dfs_mode, 1:hw_dfs_mode
	reg_bit_set(DFS_HW_CTRL,0,1,0);
	//dfs_clk_auto_mode, 0:dmc clock init flow triggered by sw, 1:dmc clock init HW auto mode triggered by dfs_req
	reg_bit_set(DMC_CLK_INIT_CFG,0,1,0);
	//dfs_sw_dfs_mode, 0:pure-software dfs mode, 1:software dfs mode
	reg_bit_set(DFS_PURE_SW_CTRL,0,1,1);
	//pub_dfs_sw_ratio_default.dpll_sel, 0:dpll0, 1:dpll1
	reg_bit_set(DFS_SW_CTRL,15,3,(clk_cfg+sys_info->freq_num)->dfs_cfg.pll_sel);
	//pub_dfs_sw_ratio_default.dpll_div_sel
	reg_bit_set(DFS_SW_CTRL,18,4,(clk_cfg+sys_info->freq_num)->dfs_cfg.dpll_div_sel);
	//pub_dfs_sw_clk_mode_default
	reg_bit_set(DFS_SW_CTRL1,18,2,(clk_cfg+sys_info->freq_num)->dfs_cfg.deskew_mode);
	//pub_dfs_sw_ratio_d2_default.x1_sel
	reg_bit_set(DFS_SW_CTRL1,8,2,(clk_cfg+sys_info->freq_num)->dfs_cfg.x1_sel);
	//pub_dfs_sw_ratio_d2_default.d2_sel
	reg_bit_set(DFS_SW_CTRL1,10,2,(clk_cfg+sys_info->freq_num)->dfs_cfg.d2_sel);
	//half_freq_mode
	reg_bit_set(DMC_CTL_(104),30,1,(clk_cfg+sys_info->freq_num)->dfs_cfg.half_freq_mode);
	//read target dfs value
	val= (((phy0_reg_data[4+(sys_info->freq_num*20)]>>14)&0x1)<<8)
			 | ((phy0_reg_data[3+(sys_info->freq_num*20)])&0xff);
	//pub_dfs_sw_ddl_adjs
	reg_bit_set(DFS_SW_CTRL2,0,9,val);
	//dmc_clk_init_sw_start
	reg_bit_set(DMC_CLK_INIT_SW_START,0,1,0x1);
	//dmc_clk_init_sw_done
	while((REG32(DMC_CLK_STATE)&0x1) != 1);
	//clear dmc_clk_init_sw_start
	reg_bit_set(DMC_CLK_INIT_SW_START,0,1,0x0);
}
uint32 phy_reset_data[8][4]={
    {DMC_GUI_PHY_DATA_LP3_160_02,  DMC_GUI_PHY_DATA_LP3_160_03,  DMC_GUI_PHY_DATA_LP3_160_04,  DMC_GUI_PHY_DATA_LP3_160_07 },
    {DMC_GUI_PHY_DATA_LP3_233_02,  DMC_GUI_PHY_DATA_LP3_233_03,  DMC_GUI_PHY_DATA_LP3_233_04,  DMC_GUI_PHY_DATA_LP3_233_07 },
    {DMC_GUI_PHY_DATA_LP3_311_02,  DMC_GUI_PHY_DATA_LP3_311_03,  DMC_GUI_PHY_DATA_LP3_311_04,  DMC_GUI_PHY_DATA_LP3_311_07 },
    {DMC_GUI_PHY_DATA_LP3_400_02,  DMC_GUI_PHY_DATA_LP3_400_03,  DMC_GUI_PHY_DATA_LP3_400_04,  DMC_GUI_PHY_DATA_LP3_400_07 },
    {DMC_GUI_PHY_DATA_LP3_533_02,  DMC_GUI_PHY_DATA_LP3_533_03,  DMC_GUI_PHY_DATA_LP3_533_04,  DMC_GUI_PHY_DATA_LP3_533_07 },
    {DMC_GUI_PHY_DATA_LP3_622_02,  DMC_GUI_PHY_DATA_LP3_622_03,  DMC_GUI_PHY_DATA_LP3_622_04,  DMC_GUI_PHY_DATA_LP3_622_07 },
    {DMC_GUI_PHY_DATA_LP3_800_02,  DMC_GUI_PHY_DATA_LP3_800_03,  DMC_GUI_PHY_DATA_LP3_800_04,  DMC_GUI_PHY_DATA_LP3_800_07 },
    {DMC_GUI_PHY_DATA_LP3_933_02,  DMC_GUI_PHY_DATA_LP3_933_03,  DMC_GUI_PHY_DATA_LP3_933_04,  DMC_GUI_PHY_DATA_LP3_933_07 },
    };
void ddr_reinit_pre_modify()
{
    uint32 reg_num_tmp = 0;
    uint32 i = 0;
	//close lowpoer
	reg_bit_set(&ctl_reg0_data[0],8,1,0x0);//rf_auto_sleep_en
	reg_bit_set(&ctl_reg1_data[(73-64)],12,1,0X0);//drf_ext_clk_ag_en
	//
	reg_bit_set(&ctl_reg0_data[0], 9, 1,0X0);//disable rf_auto_gate_en
	reg_bit_set(&ctl_reg1_data[(69-64)], 24, 2,0X0);//disable MR4
	reg_bit_set(&ctl_reg1_data[(75-64)], 0, 1, 0X0);//
	reg_bit_set(&ctl_reg1_data[(81-64)], 16, 1, 0X0);//disable cpst period en

	//if device is lp4, set ddr_pin_mux
	if(LPDDR4 == sys_info->ddr_type)
	{
		//gucphy_pin_mux_setting
		REG32(DMC_PHY1_(207))=0x02400050;
		//reg_mlb_ca_bit_patter_hi
		reg_bit_set(DMC_PHY1_(208),0,9,0x13);
	}
        for(i = 0; i < 8; i++)
        {
            reg_num_tmp = (i * 20);
	    REG32(&phy0_reg_data[(reg_num_tmp+2)]) = (phy_reset_data[i][0]);//
	    REG32(&phy0_reg_data[(reg_num_tmp+3)]) = (phy_reset_data[i][1]);//
	    REG32(&phy0_reg_data[(reg_num_tmp+4)]) = (phy_reset_data[i][2]);//
	    REG32(&phy0_reg_data[(reg_num_tmp+7)]) = (phy_reset_data[i][3]);//
	    REG32(&phy1_reg_data[(reg_num_tmp+2)]) = (phy_reset_data[i][0]);//
	    REG32(&phy1_reg_data[(reg_num_tmp+3)]) = (phy_reset_data[i][1]);//
	    REG32(&phy1_reg_data[(reg_num_tmp+4)]) = (phy_reset_data[i][2]);//
	    REG32(&phy1_reg_data[(reg_num_tmp+7)]) = (phy_reset_data[i][3]);//
        }
}

void ddr_reinit_pre_set()
{
	//close lowpoer
	reg_bit_set(DMC_CTL_(0),8,1,0x0);//rf_auto_sleep_en
	reg_bit_set(DMC_CTL_(73),12,1,0X0);//drf_ext_clk_ag_en
	//
	reg_bit_set(DMC_CTL_(0), 9, 1,0X0);//disable rf_auto_gate_en
	reg_bit_set(DMC_CTL_(69), 24, 2,0X0);//disable MR4
	reg_bit_set(DMC_CTL_(75), 0, 1, 0X0);//
	reg_bit_set(DMC_CTL_(81), 16, 1, 0X0);//disable cpst period en
	//set reinit frequency num
	reg_bit_set(DMC_CTL_(75),4,3,sys_info->freq_num);//drf_dfs_reg_sel

	//if device is lp4, set ddr_pin_mux
	if(LPDDR4 == sys_info->ddr_type)
	{
		//gucphy_pin_mux_setting
		REG32(DMC_PHY1_(207))=0x02400050;
		//reg_mlb_ca_bit_patter_hi
		reg_bit_set(DMC_PHY1_(208),0,9,0x13);
	}
}

void polling_ddr_reinit_done()
{
	//ddr init start
	REG32(DMC_CTL_(3)) = 0xf;
	while(((REG32(DMC_CTL_(3))>>16)&0x3) != 0x3);
	REG32(DMC_CTL_(3)) = 0x0;

}

void ddr_reinit()
{
	uint32 i,val;
        uint32 reg_num_tmp;
	//set DPLL Frequency
	//reg_bit_set(APB_EB2,11, 3,0x7);//bit[11]:anlg_eb bit[12]:pin_apb_eb bit[13]:anlg_apb_eb
	//reg_bit_set(DPLL0_CTRL1,0,23,0x627627);//DPLL0_KINT
	//reg_bit_set(DPLL0_CTRL1,23, 7,0x47);//DPLL0_NINT
	//reg_bit_set(DPLL1_CTRL1,0,23,0x627627);//DPLL1_KINT
	//reg_bit_set(DPLL1_CTRL1,23, 7,0x47);//DPLL1_NINT
	pub_clk_init();
	#ifdef DMA_CONFIG
	DMA_HAL_Linklist_Transfer(linklist_handle_1);
	while(!(DMA_HAL_PollingListDone(dma_chn1)));
	reg_bit_set(DDR_PHY_RET_CFG,16,1,0x0);//ddr_umctl_soft_rst 0:keep ddr umctl in normal mode, 1: reset DDR UMCTL
	#else
	//mem_fw/dfi_busmon/ddr_phy
	pub_register_restore();
	//restore ddr_phy
	phy_register_restore();
	//restore dmc_ctl
	ctl_register_restore();
	//ctrl setting
//	ddr_reinit_pre_set();
	#endif
	//release ctl function
	reg_bit_set(DDR_PHY_RET_CFG,16,1,0x0);//ddr_umctl_soft_rst 0:keep ddr umctl in normal mode, 1: reset DDR UMCTL
        //update timing
	reg_bit_set(DMC_CTL_(75), 0, 1, 0x1);
        //rpull disable
        reg_num_tmp = (sys_info->freq_num * 20) + 9;
	reg_bit_set(DMC_PHY0_(reg_num_tmp),31,1,0x0);// only lp3 RPULL
	reg_bit_set(DMC_PHY1_(reg_num_tmp),31,1,0x0);// only lp3 RPULL
	//read target dfs value
	val= (((phy0_reg_data[4+(sys_info->freq_num*20)]>>14)&0x1)<<8)
			 | ((phy0_reg_data[3+(sys_info->freq_num*20)])&0xff);
	//pub_dfs_sw_ddl_adjs
	reg_bit_set(DFS_SW_CTRL2,0,9,val);
	//release ddr phy function
	reg_bit_set(DMC_RST_CTL,0,1,0x0);
	//polling ddr reinit done
	polling_ddr_reinit_done();
	//set dmc ctrl lowpower
	reg_bit_set(DMC_CTL_(0),8,1,0x1);//rf_auto_sleep_en
	reg_bit_set(DMC_CTL_(0),9,1,0x1);//rf_auto_sleep_en
	reg_bit_set(DMC_CTL_(73),12,1,0x1);//drf_ext_clk_ag_en
//	reg_bit_set(DMC_CTL_(81), 16, 1, 0X1);//enable cpst period en
	//ensure device to entry into self-refresh
	while(((REG32(DMC_CTL_(73))>>24)&0xff) != 0xff);
	//disable io retention
	reg_bit_set(DDR_OP_MODE_CFG,30,1,0x1);//ddr_phy_ret_en_clr_sw
	reg_bit_set(DDR_OP_MODE_CFG,30,1,0x0);//ddr_phy_ret_en_clr_sw
	//set qos
        reg_num_tmp = (sys_info->freq_num * 20) + 9;
        REG32(DMC_PHY0_(reg_num_tmp)) = phy0_reg_data[reg_num_tmp];
        REG32(DMC_PHY1_(reg_num_tmp)) = phy1_reg_data[reg_num_tmp];
        REG32(DMC_CTL_(39)) = 0xdeadbeef;
}

void pub_acc_rdy_set()
{
	uint32 acc_val=0x0;
	reg_bit_set(PUB_ACC_RDY,0,1,0x1);
	while(acc_val != 1)
	{
		acc_val =REG32(PUB_ACC_RDY)&0x1;
	}

}


uint32 pub_power_on()
{
	//force pub poweron
	reg_bit_set(PD_PUB_SYS_CFG,25, 1,0x0);//pub_sys_force_shutdown
	while(((REG32(PWR_STATUS2_DBG)>>20)&0x1f) != 0x0);//pd_pub_sys_state
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE,0,16,0x0);//pub_sys_auto_light_sleep_enable
	//ddr reinit
	ddr_reinit();
	#ifdef DMA_CONFIG
	DMA_HAL_FreeLinkList(linklist_handle_1);
	#endif
        #ifdef BIST_TEST_RE
        if(bist_over_powerdown == reinit_test_mode_addr->bist)
        {
            dmc_ddr_read(0);
        }
        if(bist_after_reinit == reinit_test_mode_addr->bist)
        {
            dmc_ddr_test(0);
        }
        #endif
	pub_acc_rdy_set();
}

void pub_power_off()
{
	volatile uint32 i=1;
	uint32 state=0x0;
        #ifdef BIST_TEST_RE
        if(bist_over_powerdown == reinit_test_mode_addr->bist)
        {
            dmc_ddr_write(0);
        }
        #endif
        #ifdef DEBUG_REINIT
	//ensure device to entry into self-refresh
	while(((REG32(DMC_CTL_(73))>>24)&0xff) != 0xff);
	REG32(PUB_ACC_RDY)  &= ~(0x1<<0);
        #endif
	while((REG32(PUB_ACC_RDY)&0X1) != 0x0)
	{
		wait_us(1);
	}
	//check ddr_slp_ctrl_state
	state=(REG32(DDR_SLP_CTRL_CFG0)>>22)&0xf;
	if(state != 0xa)
	{
		//return;
	}
	//save ddr frequency num
	sys_info->freq_num=(REG32(DMC_CTL_(75))>>8)&0x7;
	//set reinit frequency num
	reg_bit_set(&ctl_reg1_data[(75-64)],4,3,sys_info->freq_num);//drf_dfs_reg_sel
        pub_clk_update();
	//force pub shutdown
	reg_bit_set(PD_PUB_SYS_CFG,25, 1,0x1);//pub_sys_force_shutdown
	while(((REG32(PWR_STATUS2_DBG)>>20)&0x1f) != 0x7);//pd_pub_sys_state
	//while(((REG32(DDR_SLP_CTRL_CFG0)>>22)&0xf) != 0x7);//pub_slp_ctrl_state
	#ifdef DMA_CONFIG
	DMA_chn1_linklist_addr_set();
	#endif

}


void ddr_reinit_prepare()
{
	//pub_sys_force_shutdown
	reg_bit_set(PD_PUB_SYS_CFG,25,1,0x0);
	//pub_sys_auto_shutdown_en
	reg_bit_set(PD_PUB_SYS_CFG,24,1,0x0);
}

void pub_auto_poweroff_set()
{
	//pub_sys_auto_deep_sleep_enable
	reg_bit_set(SLEEP_CTL2,16,1,0x1);
	//pub_sys_auto_light_sleep_enable
	reg_bit_set(PUB_SYS_AUTO_LIGHT_SLEEP_ENABLE,0,16,0xffff);
//	reg_bit_set(DDR_OP_MODE_CFG, 24,1,0x1);//ddr_phy_auto_ret_en
	reg_bit_set(DDR_OP_MODE_CFG,30,1,0x0);//ddr_phy_ret_en_clr_sw
}



void reinit_handler(uint32 id,RE_PUB_STATUS status)
{
	uint32 i=1;
	uint32 pub_eic_state=0;
	uint32 pub_level=status;
//	while(i);
//	SCI_DisableIRQ();
	#ifndef DEBUG_REINIT
	pub_level=EIC_HAL_GetPol(EIC_LATCH_ID(4));
	if(HIGH_LEVEL == pub_level)
	{
		/* Toggle trigger pol*/
		EIC_HAL_SetIntSense(EIC_LATCH_ID(LATCH_ALL_DEEP_SLEEP), GPIO_INT_LEVEL_LOW);
	}else
	{
		/* Toggle trigger pol*/
		EIC_HAL_SetIntSense(EIC_LATCH_ID(LATCH_ALL_DEEP_SLEEP), GPIO_INT_LEVEL_HIGH);
	}
	/* Clear interrupt*/
	EIC_HAL_ClrIntSts(EIC_LATCH_ID(LATCH_ALL_DEEP_SLEEP));
	#endif
	if(HIGH_LEVEL == pub_level)
	{

		if(reinit_info_g->pub_poweroff_state)
		{
                        reinit_info_g->reg_pmu_apb_sleep_status = REG32(REG_PMU_APB_SLEEP_STATUS);
			start=REG32(0x40040004);
			pub_power_off();
			end=REG32(0x40040004);
			reinit_info_g->pub_poweroff_time = (end - start) * (31);
			reinit_info_g->pub_poweroff_num++;
		}
	}
	else													//power on
	{
		if(reinit_info_g->pub_poweroff_state)
		{
			start=REG32(0x40040004);
			pub_power_on();
			end=REG32(0x40040004);
			reinit_info_g->pub_poweron_time = (end - start) * (31);
			reinit_info_g->pub_poweron_num++;
		}
		else
		{
			reg_bit_set(PUB_ACC_RDY,0,1,1);
		}
	}
//	SCI_RestoreIRQ();
}

void ddr_sys_info_init()
{
	clk_cfg=lp3_clk_info;
	if((REG32(DMC_CTL_(0))>>29)&0x1)
	{
		sys_info->ddr_type=LPDDR4;
	}else
	{
		sys_info->ddr_type=LPDDR3;
	}
	sys_info->freq_num=(REG32(DMC_CTL_(75))>>8)&0x7;
	sys_info->ddr_clk=(clk_cfg+sys_info->freq_num)->ddr_clk;
}

void reinit_debug_info_init()
{
	reinit_info_g->reg_pmu_apb_sleep_status = 0x0;
	reinit_info_g->pub_poweroff_state = 0x1;
	reinit_info_g->pub_poweroff_time = 0x0;
	reinit_info_g->pub_poweroff_num = 0x0;
	reinit_info_g->pub_poweron_time = 0x0;
	reinit_info_g->pub_poweron_num = 0x0;

}

void DMC_ReInit(void)
{
    pub_sys_clk_force_on(1);
#ifdef DMA_CONFIG
	DMA_HAL_LinkList_chn1_init();
#endif
	ddr_sys_info_init();
	reinit_debug_info_init();
	ddr_reinit_prepare();
	pub_register_save();
	pub_auto_poweroff_set();
        pub_sys_clk_force_on();
        ddr_reinit_pre_modify();
	#ifdef DEBUG_REINIT
	reg_bit_set(0x402e0000,9,4,0xf);
        reinit_test_mode_init();
        ddr_print("\r\nCurrent DDR frequency : F");
        ddr_print_u32_dec((REG32(DMC_CTL_(75))>>8)&0x7);
    while(1)
    {
        reinit_test_mode_addr->interval_r = ((sprd_get_syscnt())%(reinit_test_mode_addr->interval_l));
        ddr_print("\r\nInterval timer:");
        ddr_print_u32_dec(*(((uint32 *)reinit_test_mode_addr) + (uint32)reinit_test_mode_addr->interval));
        ddr_print("ms");
        reinit_handler(0x0,PUB_POWEROFF);
        ddr_print("\r\npub poweroff num:");
        ddr_print_u32_dec(reinit_info_g->pub_poweroff_num);
        ddr_print("\r\npub poweroff time consumpution:");
        ddr_print_u32_dec(reinit_info_g->pub_poweroff_time);
        ddr_print("us");
        //wait
        if(short_interval == reinit_test_mode_addr->interval)
        {
            mdelay(reinit_test_mode_addr->interval_s);
        }
        else if(long_interval == reinit_test_mode_addr->interval)
        {
            mdelay(reinit_test_mode_addr->interval_l);
        }
        else if(random_interval == reinit_test_mode_addr->interval)
        {
            mdelay(reinit_test_mode_addr->interval_r);
        }
        else
        {
            ddr_print("\r\nInvalid interval mode");
        }
        reinit_handler(0x0,PUB_POWERON);
        ddr_print("\r\npub poweron num:");
        ddr_print_u32_dec(reinit_info_g->pub_poweron_num);
        ddr_print("\r\npub poweron time consumpution:");
        ddr_print_u32_dec(reinit_info_g->pub_poweron_time);
        ddr_print("us");
        if(no_dfs == reinit_test_mode_addr->dfs)
        {
        }
        else if(dfs_all_freq == reinit_test_mode_addr->dfs)
        {
            ddr_print("\r\nCurrent DDR frequency : F");
            ddr_print_u32_dec((REG32(DMC_CTL_(75))>>8)&0x7);
        }
        else
        {
            ddr_print("\r\nInvalid dfs mode");
        }
    }
	#else
	//subsys entry into deep sleep
	reg_bit_set(0x402b00cc,16,4,0xf);
	EIC_LATCH_RegCallback(EIC_LATCH_ID(LATCH_ALL_DEEP_SLEEP),
							GPIO_INT_LEVEL_HIGH,
							SCI_FALSE,
							(EIC_CALLBACK) reinit_handler);
	#endif
}

#if (defined POWER_TEST)
void pwr_DMC_ReInit(void)
{
	ddr_sys_info_init();
	reinit_debug_info_init();
	ddr_reinit_prepare();
	pub_register_save();
	pub_auto_poweroff_set();
        pub_sys_clk_force_on();
        ddr_reinit_pre_modify();
}
#endif

#endif
