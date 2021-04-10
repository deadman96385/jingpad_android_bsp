/**
 * @file mipi_dsih_dphy.c
 * @brief D-PHY driver
 *
 *  Synopsys Inc.
 *  SG DWC PT02
 */
#include "mipi_dsih_dphy.h"
#define PRECISION_FACTOR 		(1000)
/* Reference clock frequency divided by Input Frequency Division Ratio LIMITS */
#define DPHY_DIV_UPPER_LIMIT	(40000)
#ifdef GEN_2
#define DPHY_DIV_LOWER_LIMIT	(5000)
#else
#define DPHY_DIV_LOWER_LIMIT	(1000)
#endif

#if ((defined DWC_MIPI_DPHY_BIDIR_TSMC40LP) || (defined GEN_2))
#define MIN_OUTPUT_FREQ			(80)
#elif defined DPHY2Btql
#define MIN_OUTPUT_FREQ			(200)
#undef GEN_2
#endif

//#define SOFT_DPHY_CALIBRATION

uint8_t mipi_dsih_dphy_calibration(dphy_t * phy)// tianci need check with thomas
{
    uint8_t rd_data[3],sv_data[3];
    uint8_t data[3];
    uint8_t i = 0; /* iterator */
    int8_t j = 0;
    uint8_t sw_cnt;


    /*phy calibration process */
    sw_cnt = 0;
    data[0] = 0x03;
    mipi_dsih_dphy_write(phy, 0x21, data, 1);

    for(i =0; i<50; i++ );

    rd_data[0] = mipi_dsih_dphy_test_data_out(phy);
    printf("data[0] = 0x03,rd_data[0] = %x \n",rd_data[0]);

    for(j=1; j<8; j++)
    {

        data[0] = 0x03;
        data[0] |= j<<2;
        mipi_dsih_dphy_write(phy, 0x21, data, 1);

        for(i =0; i<50; i++) ;

        rd_data[1] = mipi_dsih_dphy_test_data_out(phy);
        printf("data[%d] = %x,rd_data[1] = %x \n",j,data[0],rd_data[1]);
        if((rd_data[1]&0x80) != (rd_data[0]&0x80))
        {
            sw_cnt++;
            printf(" break--data[%d] = %x,rd_data[0] = %x,rd_data[1] = %x \n",j,data[0],rd_data[0],rd_data[1]);
            if(sw_cnt>1)
            {
                printf("phy calibration error,toggles times more than once \n");
                return 0x0f;
            }
            rd_data[0] = rd_data[1];
            sv_data[0] = data[0];
        }
        if((7 == j) && (0 == sw_cnt))
        {
            if(0x80 == (rd_data[1]&0x80))
                return 0x1f;
            if(0x0 == (rd_data[1]&0x80))
                return 0x3;
        }
    }

    for(j=6; j>=0; j--)
    {

        data[0] = 0x03;
        data[0] |= j<<2;
        mipi_dsih_dphy_write(phy, 0x21, data, 1);

        for(i =0; i<50; i++ );

        rd_data[2] = mipi_dsih_dphy_test_data_out(phy);
        printf("next-->data[%d] = %x,rd_data[2] = %x \n",j,data[0],rd_data[2]);
        if((rd_data[2]&0x80) != (rd_data[0]&0x80))
        {
            printf("break--next-->data[%d] = %x,rd_data[2] = %x,rd_data[0] = %x \n",j,data[0],rd_data[2],rd_data[0]);
            rd_data[0] = rd_data[2];
            sv_data[1] = data[0];
        }
    }

    sv_data[0] =(sv_data[0]&0x1c) >>2;
    sv_data[1] =(sv_data[1]&0x1c) >>2;
    sv_data[0] = sv_data[0] + sv_data[1];
    sv_data[1] = sv_data[0] / 2 + sv_data[0] % 2;
    data[0] = (sv_data[1] <<2) | 0x03;

    return data[0];

}

/**
 * Initialise D-PHY module and power up
 * @param phy pointer to structure which holds information about the d-phy
 * module
 * @return error code
 */
dsih_error_t mipi_dsih_dphy_open(dphy_t * phy)
{
    printf("%s enter\n",__func__);
    if (phy == 0)
    {
        return ERR_DSI_PHY_INVALID;
    }
    else if ((phy->core_read_function == 0) || (phy->core_write_function == 0))
    {
        return ERR_DSI_INVALID_IO;
    }
    else if (phy->status == INITIALIZED)
    {
        return ERR_DSI_PHY_INVALID;
    }
    phy->status = NOT_INITIALIZED;
#if 0// tianci need check with thomas
    mipi_dsih_dphy_reset(phy, 0);
    mipi_dsih_dphy_stop_wait_time(phy, 0x1C);
    mipi_dsih_dphy_no_of_lanes(phy, 1);
    mipi_dsih_dphy_clock_en(phy, 1);
    mipi_dsih_dphy_shutdown(phy, 1);
    mipi_dsih_dphy_reset(phy, 1);
#endif
    phy->status = INITIALIZED;
    return OK;
}
/**
 * Configure D-PHY and PLL module to desired operation mode
 * @param phy pointer to structure which holds information about the d-phy
 * module
 * @param no_of_lanes active
 * @param output_freq desired high speed frequency
 * @return error code
 */
void writel_nbits(uint32_t value,uint8_t nbits,uint8_t offset,uint32_t addr)
{
	uint32_t tmp;
	tmp = __raw_readl(addr);
	tmp &= ~(((1 << nbits)-1) << offset);
	tmp |= value << offset;
        __raw_writel(tmp, addr);
}


 #ifdef GEN_2
void phy_bios_programming(void)
{
    writel_nbits(0x60,8,0,0xe41b0300);
    writel_nbits(0x7a,8,0,0xe41b0308);
    writel_nbits(0xa1,8,8,0xe41b0308);
    writel_nbits(0x17,6,16,0xe41b0308);
    writel_nbits(0x3,4,0,0xe41b030c);
    writel_nbits(0x0,8,0,0xe41b0310);
    writel_nbits(0x0,2,8,0xe41b0310);
    writel_nbits(0x0,8,16,0xe41b0310);
    writel_nbits(0x0,2,24,0xe41b0310);
    writel_nbits(0x0,3,0,0xe41b0314);
    writel_nbits(0x0,1,16,0xe41b0314);
    writel_nbits(0x4,4,0,0xe41b0318);
    writel_nbits(0x8,5,8,0xe41b0318);
    writel_nbits(0x1,3,16,0xe41b0318);
    writel_nbits(0x22,8,0,0xe41b0320);
    writel_nbits(0x0,2,8,0xe41b0320);
    writel_nbits(0x0,1,0,0xe41b0324);
    writel_nbits(0x2,3,16,0xe41b0324);
    writel_nbits(0x1,1,16,0xe41b030c);

    writel_nbits(0x1,1,5,0xe41b0004);
    writel_nbits(0x0,1,4,0xe41b0004);
    writel_nbits(0x4,3,1,0xe41b0004);
    writel_nbits(0xf,8,0,0xe41b00e0);
    writel_nbits(0xd,8,0,0xe41b00e4);
    writel_nbits(0x22,8,0,0xe41b00e8);
    writel_nbits(0x13,8,0,0xe41b00ec);
    writel_nbits(0x13,8,0,0xe41b00fc);
    writel_nbits(0x20,8,0,0xe41b00f0);
    writel_nbits(0x20,8,0,0xe41b0100);
    writel_nbits(0xf,8,0,0xe41b0104);
    writel_nbits(0x53,8,0,0xe41b010c);
    writel_nbits(0xb,8,0,0xe41b0108);
    writel_nbits(0x1a,8,0,0xe41b0114);
    writel_nbits(0x186,12,0,0xe41b0110);
    writel_nbits(0x9c,8,12,0xe41b0110);
    writel_nbits(0x7,5,11,0xe41b0018);
    writel_nbits(0x4,3,28,0xe41b0058);
}
dsih_error_t mipi_dsih_dphy_configure(dphy_t * phy, uint8_t no_of_lanes, uint32_t output_freq)
{
    printf("%s enter\n",__func__);
    uint32_t loop_divider = 0; /* (M) */
    uint32_t input_divider = 1; /* (N) */
    uint8_t data[4]; /* maximum data for now are 4 bytes per test mode*/
    uint8_t no_of_bytes = 0;
    uint8_t i = 0;
    uint8_t n=0;/* iterator */
    uint8_t range = 0; /* ranges iterator */
    int flag = 0;
	struct
	{
		uint32_t loop_div; /* upper limit of loop divider range */
		uint8_t cp_current; /* icpctrl */
		uint8_t lpf_resistor; /* lpfctrl */
	}
	loop_bandwidth[] =

	{	/* gen 2 associates the charge pump current and LPF resistor with the
		 output frequency ranges (and thus we simplify here to use the
		 counter/pointer of the following structure) */
		{  90, 0x02, 0x02}, { 100, 0x02, 0x02}, { 110, 0x02, 0x02},
		{ 130, 0x02, 0x01}, { 140, 0x02, 0x01}, { 150, 0x02, 0x01},
		{ 170, 0x09, 0x00}, { 180, 0x09, 0x01}, { 200, 0x09, 0x01},
		{ 220, 0x09, 0x04}, { 240, 0x09, 0x04}, { 250, 0x09, 0x04},
		{ 270, 0x06, 0x04}, { 300, 0x06, 0x04}, { 330, 0x09, 0x04},
		{ 360, 0x09, 0x04}, { 400, 0x09, 0x04}, { 450, 0x06, 0x04},
		{ 500, 0x06, 0x04}, { 550, 0x06, 0x04}, { 600, 0x06, 0x04},
		{ 650, 0x0A, 0x04}, { 700, 0x0A, 0x04}, { 750, 0x0A, 0x04},
		{ 800, 0x0A, 0x04}, { 850, 0x0A, 0x04}, { 900, 0x0A, 0x04},
		{ 950, 0x0B, 0x08}, {1000, 0x0B, 0x08}, {1050, 0x0B, 0x08},
		{1100, 0x0B, 0x08}, {1150, 0x0B, 0x08}, {1200, 0x0B, 0x08},
		{1250, 0x0B, 0x08}, {1300, 0x0B, 0x08}, {1350, 0x0B, 0x08},
		{1400, 0x0B, 0x08}, {1450, 0x0B, 0x08}, {1500, 0x0B, 0x08}
	};
	uint32_t delta = 0;
	uint32_t tmp_loop_divider = 0;
	unsigned step = 0;

    struct
    {
        uint32_t freq;  /* upper margin of frequency range */
        uint8_t hs_freq; /* hsfreqrange */
        uint8_t vco_range; /* vcorange */
    }
    ranges[] =
	{
		{  90, 0x00, 0x00}, { 100, 0x10, 0x00}, { 110, 0x20, 0x00},
		{ 130, 0x01, 0x00}, { 140, 0x11, 0x00}, { 150, 0x21, 0x00},
		{ 170, 0x02, 0x00}, { 180, 0x12, 0x00}, { 200, 0x22, 0x00},
		{ 220, 0x03, 0x01}, { 240, 0x13, 0x01}, { 250, 0x23, 0x01},
		{ 270, 0x04, 0x01}, { 300, 0x14, 0x01}, { 330, 0x05, 0x02},
		{ 360, 0x15, 0x02}, { 400, 0x25, 0x02}, { 450, 0x06, 0x02},
		{ 500, 0x16, 0x02}, { 550, 0x07, 0x03}, { 600, 0x17, 0x03},
		{ 650, 0x08, 0x03}, { 700, 0x18, 0x03}, { 750, 0x09, 0x04},
		{ 800, 0x19, 0x04}, { 850, 0x29, 0x04}, { 900, 0x39, 0x04},
		{ 950, 0x0A, 0x05}, {1000, 0x1A, 0x05}, {1050, 0x2A, 0x05},
		{1100, 0x3A, 0x05}, {1150, 0x0B, 0x06}, {1200, 0x1B, 0x06},
		{1250, 0x2B, 0x06}, {1300, 0x3B, 0x06}, {1350, 0x0C, 0x07},
		{1400, 0x1C, 0x07}, {1450, 0x2C, 0x07}, {1500, 0x3C, 0x07}
	};

#ifdef CONFIG_SPRD_SOC_SP9853I
	#define ANLG_PHY_ANALOG_REG0 REG_ANLG_PHY_G2_ANALOG_DSI_0_CTRL_REG0
    __raw_bits_or(BIT_ANLG_PHY_G2_DBG_SEL_ANALOG_DSPLL_IRST_PLL_POR_B_A, REG_ANLG_PHY_G2_ANALOG_DSPLL_REG_SEL_CFG_0);
    writel_nbits(0x0,3,2,REG_ANLG_PHY_G2_ANALOG_DSPLL_CRIT_CTRL_0);
    __raw_bits_and(~BIT_ANLG_PHY_G2_ANALOG_DSPLL_ICTL_PLL_CLKSLICE0_ENABLE_A,REG_ANLG_PHY_G2_ANALOG_DSPLL_PHASE_CTRL_1);
    writel_nbits(0x60,8,0,REG_ANLG_PHY_G2_ANALOG_DSPLL_PLL_DIRECT_CTRL_0);
    writel_nbits(0x60,8,8,REG_ANLG_PHY_G2_ANALOG_DSPLL_PHASE_CTRL_0);
    __raw_bits_or(BIT_ANLG_PHY_G2_ANALOG_DSPLL_IRST_PLL_POR_B_A, REG_ANLG_PHY_G2_ANALOG_DSPLL_CRIT_CTRL_0);
    __raw_bits_or(BIT_ANLG_PHY_G2_ANALOG_DSPLL_ICTL_PLL_CLKSLICE0_ENABLE_A, REG_ANLG_PHY_G2_ANALOG_DSPLL_PHASE_CTRL_1);
    while(BIT_COMMON_APB_INT_REQ_DSIPLL_LOCK_STATUS_RAW_STS !=
		(__raw_readl(REG_COMMON_APB_DSIPLL_LOCK_STATUS) & BIT_COMMON_APB_INT_REQ_DSIPLL_LOCK_STATUS_RAW_STS)){
	printf("[0x%x] warning: busy waiting DSIPLL lock!\n",__raw_readl(REG_COMMON_APB_DSIPLL_LOCK_STATUS));
    }
#else //iwhale2
	#define ANLG_PHY_ANALOG_REG0 REG_ANLG_PHY_G8_ANALOG_DSI_0_CTRL_REG0
#endif
    __raw_bits_and(~(1<<11),ANLG_PHY_ANALOG_REG0);
    /******pgen,fwen,sys_rst,apb_rst*************/
    __raw_bits_or(1<<1, ANLG_PHY_ANALOG_REG0);
    udelay(5);
    __raw_bits_or(1<<2, ANLG_PHY_ANALOG_REG0);
    udelay(10);
#ifdef CONFIG_SPRD_SOC_SP9853I
    __raw_bits_or(1<<2, REG_ANLG_PHY_G2_ANALOG_DSI_0_REG_SEL_CFG_0);
    __raw_bits_or(1<<3, REG_ANLG_PHY_G2_ANALOG_DSI_0_REG_SEL_CFG_0);
#else
    __raw_bits_or(1<<18, REG_ANLG_PHY_G8_ANALOG_DSI_0_REG_SEL_CFG_0);
    __raw_bits_or(1<<19, REG_ANLG_PHY_G8_ANALOG_DSI_0_REG_SEL_CFG_0);
#endif

    __raw_bits_or(1<<20, ANLG_PHY_ANALOG_REG0);
    udelay(500);
    __raw_bits_or(1<<21, ANLG_PHY_ANALOG_REG0);
    udelay(500);

    /*********set pll*******/
    writel_nbits(0x7,5,1,0xe41b0018);
    writel_nbits(0x4,3,28,0xe41b0058);
    writel_nbits(0x2050,16,0,0xe41b0120);
    set_pll_frequency(output_freq);
    udelay(10);
    __raw_bits_or(1<<3, 0xd39000a0);//force pll
    udelay(16);
    while(BIT(17) !=
               (__raw_readl(ANLG_PHY_ANALOG_REG0) & BIT(17))){
       printf("[0x%x] warning: busy waiting analog DSIPLL lock!\n",__raw_readl(ANLG_PHY_ANALOG_REG0));
    }
    /****latchreset,latchen****/
    __raw_bits_or(1<<13, ANLG_PHY_ANALOG_REG0);
    __raw_bits_or(1<<14, ANLG_PHY_ANALOG_REG0);

    /************set hs prepare/zero/trail time*************/
    writel_nbits(0x6,8,0,0xe41b00e4);
    writel_nbits(0x1c,8,0,0xe41b00e8);
    writel_nbits(0x9,8,0,0xe41b00ec);

#ifdef CONFIG_SOC_IWHALE2
    __raw_bits_or(1<<0, ANLG_PHY_ANALOG_REG0+0x30);
#endif
    printf("0x%x = 0x%x\n", ANLG_PHY_ANALOG_REG0, __raw_readl(ANLG_PHY_ANALOG_REG0));

    if (phy == 0)
    {
        return ERR_DSI_INVALID_INSTANCE;
    }
    if (phy->status < INITIALIZED)
    {
        return ERR_DSI_INVALID_INSTANCE;
    }
    if (output_freq < MIN_OUTPUT_FREQ)
    {
        return ERR_DSI_PHY_FREQ_OUT_OF_BOUND;
    }

	loop_divider = ((output_freq * (phy->reference_freq / DPHY_DIV_LOWER_LIMIT)) / phy->reference_freq);
	/* here delta will account for the rounding */
	delta = ((loop_divider * phy->reference_freq) / (phy->reference_freq / DPHY_DIV_LOWER_LIMIT)) - output_freq;
	for (input_divider = 1 + (phy->reference_freq / DPHY_DIV_UPPER_LIMIT); ((phy->reference_freq / input_divider) >= DPHY_DIV_LOWER_LIMIT) && (!flag); input_divider++)
	{
		tmp_loop_divider = ((output_freq * input_divider) / (phy->reference_freq));
		if ((tmp_loop_divider % 2) == 0)
		{	/* if even */
			if (output_freq == (tmp_loop_divider * (phy->reference_freq / input_divider)))
			{	/* exact values found */
				flag = 1;
				loop_divider = tmp_loop_divider;
				delta = output_freq - (tmp_loop_divider * (phy->reference_freq / input_divider));
				/* variable was incremented before exiting the loop */
				input_divider--;
			}
			if ((output_freq - (tmp_loop_divider * (phy->reference_freq / input_divider))) < delta)
			{	/* values found with smaller delta */
				loop_divider = tmp_loop_divider;
				delta = output_freq - (tmp_loop_divider * (phy->reference_freq / input_divider));
				step = 1;
			}
		}
		else
		{
			tmp_loop_divider += 1;
			if (output_freq == (tmp_loop_divider * (phy->reference_freq / input_divider)))
			{	/* exact values found */
				flag = 1;
				loop_divider = tmp_loop_divider;
				delta = (tmp_loop_divider * (phy->reference_freq / input_divider)) - output_freq;
				/* variable was incremented before exiting the loop */
				input_divider--;
			}
			if (((tmp_loop_divider * (phy->reference_freq / input_divider)) - output_freq) < delta)
			{	/* values found with smaller delta */
				loop_divider = tmp_loop_divider;
				delta = (tmp_loop_divider * (phy->reference_freq / input_divider)) - output_freq;
				step = 0;
			}
		}
	}
	if (!flag)
	{
		input_divider = step + (loop_divider * phy->reference_freq) / output_freq;
		printf("sprdfb: D-PHY: Approximated Frequency: %d KHz\n", (loop_divider * (phy->reference_freq / input_divider)));
//		phy->log_info("D-PHY: Approximated Frequency: %d KHz", (loop_divider * (phy->reference_freq / input_divider)));
	}

    /* get the PHY in power down mode (shutdownz=0) and reset it (rstz=0) to
    avoid transient periods in PHY operation during re-configuration procedures. */
    mipi_dsih_dphy_reset(phy, 0);
    mipi_dsih_dphy_clock_en(phy, 0);
    mipi_dsih_dphy_shutdown(phy, 0);
    /* provide an initial active-high test clear pulse in TESTCLR  */
    mipi_dsih_dphy_test_clear(phy, 1);
    mipi_dsih_dphy_test_clear(phy, 0);
    for(n=0;n<100;n++){
	;
    }
    /* find ranges */
    for (range = 0; (range < (sizeof(ranges)/sizeof(ranges[0]))) && ((output_freq / 1000) > ranges[range].freq); range++)
    {
        ;
    }
    if (range >= (sizeof(ranges)/sizeof(ranges[0])))
    {
        return ERR_DSI_PHY_FREQ_OUT_OF_BOUND;
    }
    /* set up board depending on environment if any */
    if (phy->bsp_pre_config != 0)
    {
        phy->bsp_pre_config(phy, 0);
    }

  /* Jessica add - begin*/
    data[0] =  0x83;//0x44;//0x44;//0x40;                 //0x40: ok for 200    clock lane lpx /*about 52ns*/
    mipi_dsih_dphy_write(phy, 0x60, data, 1);
//    data[0] =  0x0;//0xA6;//0xC6;//0xC6;//0x86;                 //0x48: ok for 200     prepare time
//    mipi_dsih_dphy_write(phy, 0x61, data, 1);

//    data[0] =  0x0;//0x6a;//0x6a;//0x4a;                  //0x4a: ok for 200    zero time
//    mipi_dsih_dphy_write(phy, 0x62, data, 1);

    data[0] =  0x83;//0x44;//0x40;//0x40;              // 0x40: ok for 200          data lane lpx /*about 52ns*/
    mipi_dsih_dphy_write(phy, 0x70, data, 1);

//    data[0] =  0x0;//0x84;//0x96;//0x96;//0x86;                //0x48: ok for 200         prepare time
//    mipi_dsih_dphy_write(phy, 0x71, data, 1);

//    data[0] =  0x0;;//0x44;//0x44;//0x40;               //0x4a: ok for 200          zero time
//   mipi_dsih_dphy_write(phy, 0x72, data, 1);

    //data[0] =  0x44;
    //mipi_dsih_dphy_write(phy, 0x73, data, 1);

    //data[0] =  0x7F;
    //mipi_dsih_dphy_write(phy, 0x74, data, 1);

  /* Jessica add - end*/

    data[0] =  0x70;
    mipi_dsih_dphy_write(phy, 0x16, data, 1);

    /* setup digital part */
    /* hs frequency range [7]|[6:1]|[0]*/
    data[0] = (0 << 7) | (ranges[range].hs_freq << 1) | 0;
   //data[0] = (0 << 7) | (0x23 << 1) | 0;
   /*From ASIC, we need unmask this code to make the frequency correct*/
    mipi_dsih_dphy_write(phy, 0x44, data, 1);       //Jessica remove for more accurate frequency
    /* setup PLL */
    /* vco range  [7]|[6:3]|[2:1]|[0] */
    data[0] = (1 << 7) | (ranges[range].vco_range << 3) | (0 << 1) | 0;
    mipi_dsih_dphy_write(phy, 0x10, data, 1);                 //Jessica
#ifdef TESTCHIP
	/* for all Gen2 testchips, bypass LP TX enable idle low power */
	data[0] = 0x80;
	mipi_dsih_dphy_write(phy, 0x32, data, 1);
	mipi_dsih_dphy_write(phy, 0x42, data, 1);
	mipi_dsih_dphy_write(phy, 0x52, data, 1);
	mipi_dsih_dphy_write(phy, 0x82, data, 1);
	mipi_dsih_dphy_write(phy, 0x92, data, 1);
#endif
	if ((loop_divider % 2) != 0)
	{	/* only odd integers are allowed (1 will be subtracted upon writing,
		see below) */
		loop_divider -= 1;

	}
	/* gen 2 associates the charge pump current and LPF resistor with the
	 output frequency ranges (and thus we simplify here to use the
	 counter/pointer of the following structure) */
	i = range;
	data[0] = (0x00 << 6) | (0x01 << 5) | (0x01 << 4);

    mipi_dsih_dphy_write(phy, 0x19, data, 1);      //Jessica

    /* PLL Lock bypass|charge pump current [7:4]|[3:0] */
    data[0] = (0x00 << 4) | (loop_bandwidth[i].cp_current << 0);
    mipi_dsih_dphy_write(phy, 0x11, data, 1);           //Jessica
    /* bypass CP default|bypass LPF default| LPF resistor [7]|[6]|[5:0] */
    data[0] = (0x01 << 7) | (0x01 << 6) |(loop_bandwidth[i].lpf_resistor << 0);
    mipi_dsih_dphy_write(phy, 0x12, data, 1);
    /* PLL input divider ratio [7:0] */
    data[0] = input_divider - 1;
    mipi_dsih_dphy_write(phy, 0x17, data, 1);           //Jessica

    data[0] =	0x04; //short the delay time before BTA
    mipi_dsih_dphy_write(phy, 0x07, data, 1);

//    data[0] = 1;
//    mipi_dsih_dphy_write(phy, 0xB0, data, 1);

    data[0] = 0x8B;
    mipi_dsih_dphy_write(phy, 0x22, data, 1);
//    data[1] = mipi_dsih_dphy_test_data_out(phy);
//    MIPI_PRINT("sprdfb:mipi dphy config-->0x22 write:%x,read:%x \n",data[0],data[1]);

#ifdef SOFT_DPHY_CALIBRATION
    data[0] = mipi_dsih_dphy_calibration(phy);

    mipi_dsih_dphy_write(phy, 0x21, data, 1);

    for(n =0;n<50;n++ );

    data[1] = mipi_dsih_dphy_test_data_out(phy);
    MIPI_PRINT("sprdfb: mipi_dsih_dphy_calibration--> data[0]= %x,data[1] = %x \n",data[0],data[1]);
#endif

    no_of_bytes = 2; /* pll loop divider (code 0x18) takes only 2 bytes (10 bits in data) */
    for (i = 0; i < no_of_bytes; i++)
    {
        data[i] = ((uint8_t)((((loop_divider - 1) >> (5 * i)) & 0x1F) | (i << 7) ));
        /* 7 is dependent on no_of_bytes
        make sure 5 bits only of value are written at a time */
    }

    /* PLL loop divider ratio - SET no|reserved|feedback divider [7]|[6:5]|[4:0] */
    mipi_dsih_dphy_write(phy, 0x18, data, no_of_bytes);
    mipi_dsih_dphy_no_of_lanes(phy, no_of_lanes);
    mipi_dsih_dphy_stop_wait_time(phy, 0x1C);
    mipi_dsih_dphy_clock_en(phy, 1);
    for(n=0;n<100;n++){
	;
    }
    mipi_dsih_dphy_shutdown(phy, 1);
    for(n=0;n<100;n++){
	;
    }
    mipi_dsih_dphy_reset(phy, 1);
    return OK;
}
#else
dsih_error_t mipi_dsih_dphy_configure(dphy_t * phy, uint8_t no_of_lanes, uint32_t output_freq)
{
    uint32_t loop_divider = 0; /* (M) */
    uint32_t input_divider = 1; /* (N) */
    uint8_t data[4]; /* maximum data for now are 4 bytes per test mode*/
    uint8_t no_of_bytes = 0;
    uint8_t i = 0; /* iterator */
    uint8_t n=0;/* iterator */
    uint8_t range = 0; /* ranges iterator */
    int flag = 0;
#ifdef DWC_MIPI_DPHY_BIDIR_TSMC40LP
    struct
    {
        uint32_t freq;  /* upper margin of frequency range */
        uint8_t hs_freq; /* hsfreqrange */
        uint8_t vco_range; /* vcorange */
    }
    ranges[] =
    {
        {90, 0x00, 0x01}, {100, 0x10, 0x01}, {110, 0x20, 0x01},
        {125, 0x01, 0x01}, {140, 0x11, 0x01}, {150, 0x21, 0x01},
        {160, 0x02, 0x01}, {180, 0x12, 0x03}, {200, 0x22, 0x03},
        {210, 0x03, 0x03}, {240, 0x13, 0x03}, {250, 0x23, 0x03},
        {270, 0x04, 0x07}, {300, 0x14, 0x07}, {330, 0x24, 0x07},
        {360, 0x15, 0x07}, {400, 0x25, 0x07}, {450, 0x06, 0x07},
        {500, 0x16, 0x07}, {550, 0x07, 0x0f}, {600, 0x17, 0x0f},
        {650, 0x08, 0x0f}, {700, 0x18, 0x0f}, {750, 0x09, 0x0f},
        {800, 0x19, 0x0f}, {850, 0x0A, 0x0f}, {900, 0x1A, 0x0f},
        {950, 0x2A, 0x0f}, {1000, 0x3A, 0x0f}
    };
    struct
    {
        uint32_t loop_div; /* upper limit of loop divider range */
        uint8_t cp_current; /* icpctrl */
        uint8_t lpf_resistor; /* lpfctrl */
    }
    loop_bandwidth[] =
    {
        {32, 0x06, 0x10}, {64, 0x06, 0x10}, {128, 0x0C, 0x08},
        {256, 0x04, 0x04}, {512, 0x00, 0x01}, {768, 0x01, 0x01},
        {1000, 0x02, 0x01}
    };
#elif defined DPHY2Btql
    struct
    {
        uint32_t loop_div; /* upper limit of loop divider range */
        uint8_t cp_current; /* icpctrl */
        uint8_t lpf_resistor; /* lpfctrl */
    }
    loop_bandwidth[] =
    {
        {32, 0x0B, 0x00}, {64, 0x0A, 0x00}, {128, 0x09, 0x01},
        {256, 0x08, 0x03}, {512, 0x08, 0x07}, {768, 0x08, 0x0F},
        {1000, 0x08, 0x1F}
    };
#endif

#if 1
    uint32_t fbdivratio,fracdiv,fracnen,div5bbypass,div5b,div2or3;
    /******fwen,sys_rst,apb_rst*************/
    __raw_bits_or(1<<1, 0xe4109000); //pgen reset ?
    __raw_bits_or(1<<2, 0xe4109000);
    __raw_bits_or(1<<20, 0xe4109000);
    __raw_bits_or(1<<21, 0xe4109000);
    __raw_bits_or(1<<3, 0xd39000a0);//force pll
    /****latchreset,latchen****/
    __raw_bits_or(1<<13, 0xe4109000);
    __raw_bits_or(1<<14, 0xe4109000);
    FB_PRINT("0xe4109000 = 0x%x\n", __raw_readl(0xe4109000));
    /***********enable dsi**************/
#define PHY_OFFSET 0x0
    __raw_writel(0x0,0xe41b0014+PHY_OFFSET);
    __raw_writel(0x0,0xe41b0000+PHY_OFFSET);
    __raw_writel(0xf,0xe41b0018+PHY_OFFSET);
    __raw_writel(0x0,0xe41b0058+PHY_OFFSET);
    __raw_writel(0x3810,0xe41b0044+PHY_OFFSET);
    __raw_bits_or(1<<4, 0xe41b0120+PHY_OFFSET);
    FB_PRINT("0xe41b0014 = 0x%x\n", __raw_readl(0xe41b0014+PHY_OFFSET));
    FB_PRINT("0xe41b0000 = 0x%x\n", __raw_readl(0xe41b0000+PHY_OFFSET));
    FB_PRINT("0xe41b0018 = 0x%x\n", __raw_readl(0xe41b0018+PHY_OFFSET));
    FB_PRINT("0xe41b0058 = 0x%x\n", __raw_readl(0xe41b0058+PHY_OFFSET));
    FB_PRINT("0xe41b0044 = 0x%x\n", __raw_readl(0xe41b0044+PHY_OFFSET));
    FB_PRINT("0xe41b0120 = 0x%x\n", __raw_readl(0xe41b0120+PHY_OFFSET));
    //__raw_writel(0x10,0xe41b0120+PHY_OFFSET);
    /*********set pll*************/
    if (output_freq == 300*1000) {
       fbdivratio = 0x80;
       fracdiv = 0x0;
       fracnen = 0x0;
       div5bbypass = 0x0;
       div5b = 0x2;
       div2or3 = 0x0;
    } else if (output_freq == 800*1000) {
       fbdivratio = 168;
       fracdiv = 0x0;
       fracnen = 0x0;
       div5bbypass = 0x0;
       div5b = 0x1;
       div2or3 = 0x0;
    } else if (output_freq == 880*1000) {
       fbdivratio = 138;
       fracdiv = 0x0;
       fracnen = 0x0;
       div5bbypass = 0x0;
       div5b = 0x0;
       div2or3 = 0x1;
    }

    __raw_bits_and(~(1<<3),0xd3900000);
    writel_nbits(fbdivratio,8,0,0xe41b0300+PHY_OFFSET);
    //writel_nbits(0x80,8,0,0xe41b0300+PHY_OFFSET);
    writel_nbits(fracdiv,22,0,0xe41b0308+PHY_OFFSET);
    //writel_nbits(0x0,22,0,0xe41b0308+PHY_OFFSET);
    //__raw_bits_and(~(1<<16),0xe41b030c+PHY_OFFSET);
    //writel_nbits(0x0,1,16,0xe41b030c+PHY_OFFSET);
    writel_nbits(fracnen,1,16,0xe41b030c+PHY_OFFSET);

    //writel_nbits(0x0,1,5,0xe41b0004+PHY_OFFSET);
    writel_nbits(div5bbypass,1,5,0xe41b0004+PHY_OFFSET);
    //writel_nbits(0x2,3,1,0xe41b0004+PHY_OFFSET);
    writel_nbits(div5b,3,1,0xe41b0004+PHY_OFFSET);
    //writel_nbits(0x0,1,4,0xe41b0004+PHY_OFFSET);
    writel_nbits(div2or3,1,4,0xe41b0004+PHY_OFFSET);

    __raw_bits_or(1<<0, 0xe41b0120+PHY_OFFSET);
    __raw_bits_or(1<<3, 0xd39000a0);//force pll

    /************set hs prepare time*************/
    __raw_writel(0x1,0xe41b00e4+PHY_OFFSET);

    FB_PRINT("0xe41b0300 = 0x%x\n", __raw_readl(0xe41b0300+PHY_OFFSET));
    FB_PRINT("0xe41b0308 = 0x%x\n", __raw_readl(0xe41b0308+PHY_OFFSET));
    FB_PRINT("0xe41b030c = 0x%x\n", __raw_readl(0xe41b030c+PHY_OFFSET));
    FB_PRINT("0xe41b0004 = 0x%x\n", __raw_readl(0xe41b0004+PHY_OFFSET));
    FB_PRINT("0xe41b0120 = 0x%x\n", __raw_readl(0xe41b0120+PHY_OFFSET));
    FB_PRINT("0xe41b00e4 = 0x%x\n", __raw_readl(0xe41b00e4+PHY_OFFSET));
#endif
    if (phy == 0)
    {
        return ERR_DSI_INVALID_INSTANCE;
    }
    if (phy->status < INITIALIZED)
    {
        return ERR_DSI_INVALID_INSTANCE;
    }
    if (output_freq < MIN_OUTPUT_FREQ)
    {
        return ERR_DSI_PHY_FREQ_OUT_OF_BOUND;
    }
    /* find M and N dividers */
    for (input_divider = 1 + (phy->reference_freq / DPHY_DIV_UPPER_LIMIT); ((phy->reference_freq / input_divider) >= DPHY_DIV_LOWER_LIMIT) && (!flag); input_divider++)
    {   /* here the >= DPHY_DIV_LOWER_LIMIT is a phy constraint, formula should be above 1 MHz */
        if (((output_freq * input_divider) % (phy->reference_freq )) == 0)
        {   /* values found */
            loop_divider = ((output_freq * input_divider) / (phy->reference_freq ));
            if (loop_divider >= 12)
            {
                flag = 1;
            }
        }
    }
    if ((!flag) || ((phy->reference_freq / input_divider) < DPHY_DIV_LOWER_LIMIT))
    {   /* no exact value found in previous for loop */
        /* this solution is not favourable as jitter would be maximum */
        loop_divider = output_freq / DPHY_DIV_LOWER_LIMIT;
        input_divider = phy->reference_freq / DPHY_DIV_LOWER_LIMIT;
    }
    else
    {   /* variable was incremented before exiting the loop */
        input_divider--;
    }
    for (i = 0; (i < (sizeof(loop_bandwidth)/sizeof(loop_bandwidth[0]))) && (loop_divider > loop_bandwidth[i].loop_div); i++)
    {
        ;
    }
    if (i >= (sizeof(loop_bandwidth)/sizeof(loop_bandwidth[0])))
    {
        return ERR_DSI_PHY_FREQ_OUT_OF_BOUND;
    }
    printf("sprdfb: Gen1 D-PHY: Approximated Frequency: %d KHz\n", (loop_divider * (phy->reference_freq / input_divider)));
    /* get the PHY in power down mode (shutdownz=0) and reset it (rstz=0) to
    avoid transient periods in PHY operation during re-configuration procedures. */
    mipi_dsih_dphy_reset(phy, 0);
    mipi_dsih_dphy_clock_en(phy, 0);
    mipi_dsih_dphy_shutdown(phy, 0);
    /* provide an initial active-high test clear pulse in TESTCLR  */
    mipi_dsih_dphy_test_clear(phy, 1);
    mipi_dsih_dphy_test_clear(phy, 0);
#ifdef DWC_MIPI_DPHY_BIDIR_TSMC40LP
    /* find ranges */
    for (range = 0; (range < (sizeof(ranges)/sizeof(ranges[0]))) && ((output_freq / 1000) > ranges[range].freq); range++)
    {
        ;
    }
    if (range >= (sizeof(ranges)/sizeof(ranges[0])))
    {
        return ERR_DSI_PHY_FREQ_OUT_OF_BOUND;
    }
    /* set up board depending on environment if any */
    if (phy->bsp_pre_config != 0)
    {
        phy->bsp_pre_config(phy, 0);
    }
#if 0
  /* Jessica add - begin*/
    data[0] =  0x42;//0x44;//0x44;//0x40;                 //0x40: ok for 200    clock lane lpx /*about 52ns*/
    mipi_dsih_dphy_write(phy, 0x60, data, 1);
//    data[0] =  0x0;//0xA6;//0xC6;//0xC6;//0x86;                 //0x48: ok for 200     prepare time
//    mipi_dsih_dphy_write(phy, 0x61, data, 1);

//    data[0] =  0x0;//0x6a;//0x6a;//0x4a;                  //0x4a: ok for 200    zero time
//    mipi_dsih_dphy_write(phy, 0x62, data, 1);

    data[0] =  0x42;//0x44;//0x40;//0x40;              // 0x40: ok for 200          data lane lpx /*about 52ns*/
    mipi_dsih_dphy_write(phy, 0x70, data, 1);

//    data[0] =  0x0;//0x84;//0x96;//0x96;//0x86;                //0x48: ok for 200         prepare time
//    mipi_dsih_dphy_write(phy, 0x71, data, 1);

//    data[0] =  0x0;;//0x44;//0x44;//0x40;               //0x4a: ok for 200          zero time
//    mipi_dsih_dphy_write(phy, 0x72, data, 1);

    //data[0] =  0x44;
    //mipi_dsih_dphy_write(phy, 0x73, data, 1);

    //data[0] =  0x7F;
    //mipi_dsih_dphy_write(phy, 0x74, data, 1);

  /* Jessica add - end*/
#endif
    /* setup digital part */
    /* hs frequency range [7]|[6:1]|[0]*/
    data[0] = (0 << 7) | (ranges[range].hs_freq << 1) | 0;
   //data[0] = (0 << 7) | (0x23 << 1) | 0;
   /*From ASIC, we need unmask this code to make the frequency correct*/
    mipi_dsih_dphy_write(phy, 0x44, data, 1);       //Jessica remove for more accurate frequency
    /* setup PLL */
    /* vco range  [7]|[6:3]|[2:1]|[0] */
    data[0] = (1 << 7) | (ranges[range].vco_range << 3) | (0 << 1) | 0;
    //mipi_dsih_dphy_write(phy, 0x10, data, 1);                 //Jessica
    /* PLL  reserved|Input divider control|Loop Divider Control|Post Divider Ratio [7:6]|[5]|[4]|[3:0] */
    data[0] = (0x00 << 6) | (0x01 << 5) | (0x01 << 4) | (0x03 << 0); /* post divider default = 0x03 - it is only used for clock out 2*/
    //mipi_dsih_dphy_write(phy, 0x19, data, 1);      //Jessica
#elif defined DPHY2Btql
    /* vco range  [7:5]|[4]|[3]|[2:1]|[0] */
    data[0] =  ((((output_freq / 1000) > 500 )? 1: 0) << 4) | (1 << 3) | (0 << 1) | 0;
    mipi_dsih_dphy_write(phy, 0x10, data, 1);
#endif
    /* PLL Lock bypass|charge pump current [7:4]|[3:0] */
    data[0] = (0x00 << 4) | (loop_bandwidth[i].cp_current << 0);
    //mipi_dsih_dphy_write(phy, 0x11, data, 1);           //Jessica
    /* bypass CP default|bypass LPF default| LPF resistor [7]|[6]|[5:0] */
    data[0] = (0x01 << 7) | (0x01 << 6) |(loop_bandwidth[i].lpf_resistor << 0);
    //mipi_dsih_dphy_write(phy, 0x12, data, 1);
    /* PLL input divider ratio [7:0] */
   data[0] = input_divider - 1;
   //mipi_dsih_dphy_write(phy, 0x17, data, 1);           //Jessica

    data[0] =	0x04; //short the delay time before BTA
    //mipi_dsih_dphy_write(phy, 0x07, data, 1);

//    data[0] = 1;
//    mipi_dsih_dphy_write(phy, 0xB0, data, 1);

    data[0] = 0x1;
    mipi_dsih_dphy_write(phy, 0xB0, data, 1);
//    data[1] = mipi_dsih_dphy_test_data_out(phy);
 //   MIPI_PRINT("sprdfb:mipi dphy config-->0x22 write:%x,read:%x \n",data[0],data[1]);


    no_of_bytes = 2; /* pll loop divider (code 0x18) takes only 2 bytes (10 bits in data) */
    for (i = 0; i < no_of_bytes; i++)
    {
        data[i] = ((uint8_t)((((loop_divider - 1) >> (5 * i)) & 0x1F) | (i << 7) ));
        /* 7 is dependent on no_of_bytes
        make sure 5 bits only of value are written at a time */
    }
    /* PLL loop divider ratio - SET no|reserved|feedback divider [7]|[6:5]|[4:0] */
    mipi_dsih_dphy_write(phy, 0x18, data, no_of_bytes);
    mipi_dsih_dphy_no_of_lanes(phy, no_of_lanes);
    mipi_dsih_dphy_stop_wait_time(phy, 0x1C);
    mipi_dsih_dphy_clock_en(phy, 1);
    for(n=0;n<100;n++){
            ;
    }
    mipi_dsih_dphy_shutdown(phy, 1);
    for(n=0;n<100;n++){
            ;
    }
    mipi_dsih_dphy_reset(phy, 1);
    return OK;
}
#endif
/**
 * Close and power down D-PHY module
 * @param phy pointer to structure which holds information about the d-phy
 * module
 * @return error code
 */
dsih_error_t mipi_dsih_dphy_close(dphy_t * phy)
{
    printf("%s enter\n",__func__);
    if (phy == 0)
    {
        return ERR_DSI_INVALID_INSTANCE;
    }
    else if ((phy->core_read_function == 0) || (phy->core_write_function == 0))
    {
        return ERR_DSI_INVALID_IO;
    }
    if (phy->status < NOT_INITIALIZED)
    {
        return ERR_DSI_INVALID_INSTANCE;
    }
    mipi_dsih_dphy_reset(phy, 0);
    mipi_dsih_dphy_reset(phy, 1);
    mipi_dsih_dphy_shutdown(phy, 0);
    phy->status = NOT_INITIALIZED;
    return OK;
}
/**
 * Enable clock lane module
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param en
 */
void mipi_dsih_dphy_clock_en(dphy_t * instance, int en)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_RSTZ, en, 2, 1);
}
/**
 * Reset D-PHY module
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param reset
 */
void mipi_dsih_dphy_reset(dphy_t * instance, int reset)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_RSTZ, reset, 1, 1);
}
/**
 * Power up/down D-PHY module
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param powerup (1) shutdown (0)
 */
void mipi_dsih_dphy_shutdown(dphy_t * instance, int powerup)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_RSTZ, powerup, 0, 1);
}
/**
 * Force D-PHY PLL to stay on while in ULPS
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param force (1) disable (0)
 * @note To follow the programming model, use wakeup_pll function
 */
void mipi_dsih_dphy_force_pll(dphy_t * instance, int force)
{
    printf("%s enter\n",__func__);
    mipi_dsih_dphy_write_part(instance, R_DPHY_RSTZ, force, 3, 1);
}
/**
 * Get force D-PHY PLL module
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @return force value
 */
int mipi_dsih_dphy_get_force_pll(dphy_t * instance)
{
    return mipi_dsih_dphy_read_part(instance, R_DPHY_RSTZ, 3, 1);
}
/**
 * Wake up or make sure D-PHY PLL module is awake
 * This function must be called after going into ULPS and before exiting it
 * to force the DPHY PLLs to wake up. It will wait until the DPHY status is
 * locked. It follows the procedure described in the user guide.
 * This function should be used to make sure the PLL is awake, rather than
 * the force_pll above.
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @return error code
 * @note this function has an active wait
 */
int mipi_dsih_dphy_wakeup_pll(dphy_t * instance)
{
    unsigned i = 0;
    if (mipi_dsih_dphy_status(instance, 0x1) == 0)
    {
        mipi_dsih_dphy_force_pll(instance, 1);
        for (i = 0; i < DSIH_PHY_ACTIVE_WAIT; i++)
        {
            if(mipi_dsih_dphy_status(instance, 0x1))
            {
                break;
            }
        }
        if (mipi_dsih_dphy_status(instance, 0x1) == 0)
        {
            return ERR_DSI_PHY_PLL_NOT_LOCKED;
        }
    }
    return OK;
}
/**
 * Configure minimum wait period for HS transmission request after a stop state
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param no_of_byte_cycles [in byte (lane) clock cycles]
 */
void mipi_dsih_dphy_stop_wait_time(dphy_t * instance, uint8_t no_of_byte_cycles)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_IF_CFG, no_of_byte_cycles, 8, 8);
}
/**
 * Set number of active lanes
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param no_of_lanes
 */
void mipi_dsih_dphy_no_of_lanes(dphy_t * instance, uint8_t no_of_lanes)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_IF_CFG, no_of_lanes - 1, 0, 2);
}
/**
 * Get number of currently active lanes
 * @param instance pointer to structure which holds information about the d-phy
 *  module
 * @return number of active lanes
 */
uint8_t mipi_dsih_dphy_get_no_of_lanes(dphy_t * instance)
{
    return mipi_dsih_dphy_read_part(instance, R_DPHY_IF_CFG, 0, 2);
}
/**
 * SPRD ADD
 * Set non-continuous clock mode
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param enable
 */
void mipi_dsih_dphy_enable_nc_clk(dphy_t * instance, int enable)
{
	mipi_dsih_dphy_write_part(instance, R_DPHY_LPCLK_CTRL, enable, 1, 1);
}

/**
 * Request the PHY module to start transmission of high speed clock.
 * This causes the clock lane to start transmitting DDR clock on the
 * lane interconnect.
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param enable
 * @note this function should be called explicitly by user always except for
 * transmitting
 */
void mipi_dsih_dphy_enable_hs_clk(dphy_t * instance, int enable)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_LPCLK_CTRL, enable, 0, 1);
}
/**
 * One bit is asserted in the trigger_request (4bits) to cause the lane module
 * to cause the associated trigger to be sent across the lane interconnect.
 * The trigger request is synchronous with the rising edge of the clock.
 * @note: Only one bit of the trigger_request is asserted at any given time, the
 * remaining must be left set to 0, and only when not in LPDT or ULPS modes
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param trigger_request 4 bit request
 */
dsih_error_t mipi_dsih_dphy_escape_mode_trigger(dphy_t * instance, uint8_t trigger_request)
{
    uint8_t sum = 0;
    int i = 0;
    for (i = 0; i < 4; i++)
    {
        sum += ((trigger_request >> i) & 1);
    }
    if (sum == 1)
    {
        /* clear old trigger */
        mipi_dsih_dphy_write_part(instance, R_DPHY_TX_TRIGGERS, 0x00, 0, 4);
        mipi_dsih_dphy_write_part(instance, R_DPHY_TX_TRIGGERS, trigger_request, 0, 4);
        for (i = 0; i < DSIH_PHY_ACTIVE_WAIT; i++)
        {
            if(mipi_dsih_dphy_status(instance, 0x0010))
            {
                break;
            }
        }
        mipi_dsih_dphy_write_part(instance, R_DPHY_TX_TRIGGERS, 0x00, 0, 4);
        if (i >= DSIH_PHY_ACTIVE_WAIT)
        {
            return ERR_DSI_TIMEOUT;
        }
        return OK;
    }
    return ERR_DSI_INVALID_COMMAND;
}
/**
 * ULPS mode request/exit on all active data lanes.
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param enable (request 1/ exit 0)
 * @return error code
 * @note this is a blocking function. wait upon exiting the ULPS will exceed 1ms
 */
#if 1 
dsih_error_t mipi_dsih_dphy_ulps_data_lanes(dphy_t * instance, int enable)
{
    int timeout;
    /* mask 1 0101 0010 0000 */
    uint16_t data_lanes_mask = 0;
    if (enable)
    {
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 1, 2, 1);
        return OK;
    }
    else
    {
        if (mipi_dsih_dphy_status(instance, 0x1) == 0)
        {
            return ERR_DSI_PHY_PLL_NOT_LOCKED;
        }
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 1, 3, 1);
        switch (mipi_dsih_dphy_get_no_of_lanes(instance))
        {
        case 3:
            data_lanes_mask |= (1 << 12);
        case 2:
            data_lanes_mask |= (1 << 10);
        case 1:
            data_lanes_mask |= (1 << 8);
        case 0:
            data_lanes_mask |= (1 << 5);
            break;
        default:
            data_lanes_mask = 0;
            break;
        }
        for (timeout = 0; timeout < DSIH_PHY_ACTIVE_WAIT; timeout++)
        {
            /* verify that the DPHY has left ULPM */
            /* mask 1010100100000 */
            if (mipi_dsih_dphy_status(instance, data_lanes_mask) == data_lanes_mask)
            {
                /* wait at least 1ms */
                break;
            }
            /* wait at least 1ms */
            for (timeout = 0; timeout < ONE_MS_ACTIVE_WAIT; timeout++)
            {
                ;
            }
        }
        if (mipi_dsih_dphy_status(instance, data_lanes_mask) != data_lanes_mask)
        {
//			instance->log_info("stat %x, mask %x", mipi_dsih_dphy_status(instance, data_lanes_mask), data_lanes_mask);
            return ERR_DSI_TIMEOUT;
        }
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 0, 2, 1);
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 0, 3, 1);
    }
    return OK;
}
#else
void mipi_dsih_dphy_ulps_data_lanes(dphy_t * instance, int enable)
{
    int timeout;
    if (enable)
    {
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 1, 3, 1);
    }
    else
    {
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 1, 4, 1);
        for (timeout = 0; timeout < DSIH_PHY_ACTIVE_WAIT; timeout++)
        {
            /* verify that the DPHY has left ULPM */
            /* mask 1010100100000 */
            if (mipi_dsih_dphy_status(instance, 0x1520) == 0)
            {
                /* wait at least 1ms */
                for (timeout = 0; timeout < ONE_MS_ACTIVE_WAIT; timeout++)
                {
                    ;
                }
                break;
            }
        }
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 0, 3, 1);
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 0, 4, 1);
    }
}
#endif
/**
 * ULPS mode request/exit on Clock Lane.
 * @param instance pointer to structure which holds information about the
 * d-phy module
 * @param enable 1 or disable 0 of the Ultra Low Power State of the clock lane
 * @return error code
 * @note this is a blocking function. wait upon exiting the ULPS will exceed 1ms
 */
#if 1
dsih_error_t mipi_dsih_dphy_ulps_clk_lane(dphy_t * instance, int enable)
{
    int timeout;
    /* mask 1000 */
    uint16_t clk_lane_mask = 0x0008;
    if (enable)
    {
        /* mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 0, 0, 1); */
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 1, 0, 1);
    }
    else
    {
        if (mipi_dsih_dphy_status(instance, 0x1) == 0)
        {
            return ERR_DSI_PHY_PLL_NOT_LOCKED;
        }
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 1, 1, 1);
        for (timeout = 0; timeout < DSIH_PHY_ACTIVE_WAIT; timeout++)
        {
            /* verify that the DPHY has left ULPM */
            /* mask 1010100100000 */
            if (mipi_dsih_dphy_status(instance, clk_lane_mask) == clk_lane_mask)
            {
                /* wait at least 1ms */
                instance->log_info("stat %x, mask %x", mipi_dsih_dphy_status(instance, clk_lane_mask), clk_lane_mask);
                break;
            }
            /* wait at least 1ms */
            for (timeout = 0; timeout < ONE_MS_ACTIVE_WAIT; timeout++)
            {
                /* dummy operation for the loop not to be optimised */
                enable = mipi_dsih_dphy_status(instance, clk_lane_mask);
            }
        }
        if (mipi_dsih_dphy_status(instance, clk_lane_mask) != clk_lane_mask)
        {
            return ERR_DSI_TIMEOUT;
        }
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 0, 0, 1);
        mipi_dsih_dphy_write_part(instance, R_DPHY_ULPS_CTRL, 0, 1, 1);
    }
    return OK;
}
#else
void mipi_dsih_dphy_ulps_clk_lane(dphy_t * instance, int enable)
{
    int timeout;
    if (enable)
    {
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 0, 0, 1);
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 1, 1, 1);
    }
    else
    {
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 1, 2, 1);
        for (timeout = 0; timeout < DSIH_PHY_ACTIVE_WAIT; timeout++)
        {
            /* verify that the DPHY has left ULPM */
            /* mask 1010100100000 */
            if (mipi_dsih_dphy_status(instance, 0x0004) == 0)
            {
                /* wait at least 1ms */
                for (timeout = 0; timeout < ONE_MS_ACTIVE_WAIT; timeout++)
                {
                    ;
                }
                break;
            }
        }
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 0, 1, 1);
        mipi_dsih_dphy_write_part(instance, R_DSI_HOST_PHY_IF_CTRL, 0, 2, 1);
    }
}
#endif
/**
 * Get D-PHY PPI status
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param mask
 * @return status
 */
uint32_t mipi_dsih_dphy_status(dphy_t * instance, uint16_t mask)
{
    return mipi_dsih_dphy_read_word(instance, R_DPHY_STATUS) & mask;
}
/**
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param value
 */
void mipi_dsih_dphy_test_clock(dphy_t * instance, int value)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_TST_CRTL0, value, 1, 1);
}
/**
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param value
 */
void mipi_dsih_dphy_test_clear(dphy_t * instance, int value)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_TST_CRTL0, value, 0, 1);
}
/**
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param on_falling_edge
 */
void mipi_dsih_dphy_test_en(dphy_t * instance, uint8_t on_falling_edge)
{
    mipi_dsih_dphy_write_part(instance, R_DPHY_TST_CRTL1, on_falling_edge, 16, 1);
}
/**
 * @param instance pointer to structure which holds information about the d-phy
 * module
 */
uint8_t mipi_dsih_dphy_test_data_out(dphy_t * instance)
{
    return mipi_dsih_dphy_read_part(instance, R_DPHY_TST_CRTL1, 8, 8);
}
/**
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param test_data
 */
void mipi_dsih_dphy_test_data_in(dphy_t * instance, uint8_t test_data)
{
    mipi_dsih_dphy_write_word(instance, R_DPHY_TST_CRTL1, test_data);
}
/**
 * Write to D-PHY module (encapsulating the digital interface)
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param address offset inside the D-PHY digital interface
 * @param data array of bytes to be written to D-PHY
 * @param data_length of the data array
 */
void mipi_dsih_dphy_write(dphy_t * instance, uint8_t address, uint8_t * data, uint8_t data_length)
{
#if 0
    unsigned i = 0;
    if (data != 0)
    {
#if ((defined DWC_MIPI_DPHY_BIDIR_TSMC40LP) || (defined DPHY2Btql) || (defined GEN_2))
        /* set the TESTCLK input high in preparation to latch in the desired test mode */
        mipi_dsih_dphy_test_clock(instance, 1);
        /* set the desired test code in the input 8-bit bus TESTDIN[7:0] */
        mipi_dsih_dphy_test_data_in(instance, address);
        /* set TESTEN input high  */
        mipi_dsih_dphy_test_en(instance, 1);
        /* drive the TESTCLK input low; the falling edge captures the chosen test code into the transceiver */
        mipi_dsih_dphy_test_clock(instance, 0);
        /* set TESTEN input low to disable further test mode code latching  */
        mipi_dsih_dphy_test_en(instance, 0);
        /* start writing MSB first */
        for (i = data_length; i > 0; i--)
        {
            /* set TESTDIN[7:0] to the desired test data appropriate to the chosen test mode */
            mipi_dsih_dphy_test_data_in(instance, data[i - 1]);
            /* pulse TESTCLK high to capture this test data into the macrocell; repeat these two steps as necessary */
            mipi_dsih_dphy_test_clock(instance, 1);
            mipi_dsih_dphy_test_clock(instance, 0);
        }
#endif
    }
#endif
}



/* abstracting BSP */
/**
 * Write to whole register to D-PHY module (encapsulating the bus interface)
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param reg_address offset
 * @param data 32-bit word
 */
void mipi_dsih_dphy_write_word(dphy_t * instance, uint32_t reg_address, uint32_t data)
{
    if (instance->core_write_function != 0)
    {
        instance->core_write_function(instance->address, reg_address, data);
    }
}
/**
 * Write bit field to D-PHY module (encapsulating the bus interface)
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param reg_address offset
 * @param data bits to be written to D-PHY
 * @param shift from the right hand side of the register (big endian)
 * @param width of the bit field
 */
void mipi_dsih_dphy_write_part(dphy_t * instance, uint32_t reg_address, uint32_t data, uint8_t shift, uint8_t width)
{
    uint32_t mask = 0;
    uint32_t temp = 0;
    if (instance->core_read_function != 0)
    {
        mask = (1 << width) - 1;
        temp = mipi_dsih_dphy_read_word(instance, reg_address);
        temp &= ~(mask << shift);
        temp |= (data & mask) << shift;
        mipi_dsih_dphy_write_word(instance, reg_address, temp);
    }
}
/**
 * Read whole register from D-PHY module (encapsulating the bus interface)
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param reg_address offset
 * @return data 32-bit word
 */
uint32_t mipi_dsih_dphy_read_word(dphy_t * instance, uint32_t reg_address)
{
    if (instance->core_read_function == 0)
    {
        return ERR_DSI_INVALID_IO;
    }
    return instance->core_read_function(instance->address, reg_address);
}
/**
 * Read bit field from D-PHY module (encapsulating the bus interface)
 * @param instance pointer to structure which holds information about the d-phy
 * module
 * @param reg_address offset
 * @param shift from the right hand side of the register (big endian)
 * @param width of the bit field
 * @return data bits to be written to D-PHY
 */
uint32_t mipi_dsih_dphy_read_part(dphy_t * instance, uint32_t reg_address, uint8_t shift, uint8_t width)
{
    return (mipi_dsih_dphy_read_word(instance, reg_address) >> shift) & ((1 << width) - 1);
}
