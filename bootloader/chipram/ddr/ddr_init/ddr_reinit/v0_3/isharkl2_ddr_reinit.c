#include "isharkl2_common.h"
#include "isharkl2_ddr_reinit.h"


//typedef unsigned long int	uint32;
#define PMU_DUMMY_REG				0xe60A2000

uint32 pub_wakeup_freq ;
uint32 pub_poweron_start_time;
uint32 pub_poweron_end_time;

void __data_move(uint32 src,uint32 dst,uint32 count)
{
	volatile uint32 i = 0;

	for(i = 0; i < count;i++)
	{
		REG32(dst+i*4) = REG32(src+i*4);
	}
}

void ctl_phy_reset()
{
	reg_bit_set(SYS_SOFT_RESET, 6, 1, 1);		        //pub0_SRST
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 3, 1, 1);		//DDR0_UMCTL_SRST
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 5, 1, 1);		//DDR0_AHB_SRST
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 6, 1, 1);		//DDR0_PHY_SRST
}

 void ctl_phy_release()
{
	reg_bit_set(SYS_SOFT_RESET, 6, 1, 0);        //pub0_SRST
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 3, 1, 0);//DDR0_UMCTL_SRS
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 6, 1, 0);//DDR0_PHY_SRST
	reg_bit_set(PMU_APB_DDR_SLEEP_CTRL, 5, 1, 0);//DDR0_AHB_SRST
}

void ctl_save_register(struct IRAM_DDR_REG_INFO *ddr_reg_info )
{
	__data_move(CANDS_CTL0_(0), ddr_reg_info->ctl_reg, 481);
}


void pi_save_register(struct IRAM_DDR_REG_INFO *ddr_reg_info )
{
	__data_move(CANDS_PI0_(0), ddr_reg_info->pi_reg, 249);
}

void phy_save_register(struct IRAM_DDR_REG_INFO *ddr_reg_info )
{
	uint32 freq_num=0;
	for(freq_num=0;freq_num<4;freq_num++)
	{

		REG32(CANDS_PHY0_(1024)) &= ~(0x1 << 0);
		REG32(CANDS_PHY0_(1024)) &= ~(0XFFFF << 8);
		/*select which frequcey set to update*/
		REG32(CANDS_PHY0_(1024)) |= ((3-freq_num) << 8);
		__data_move( CANDS_PHY0_(1024),ddr_reg_info->phy_reg[3-freq_num][0], PHY0_REG0_SAVE_SIZE);
		__data_move( CANDS_PHY0_(0),ddr_reg_info->phy_reg[3-freq_num][1], PHY0_REG1_SAVE_SIZE);
		__data_move( CANDS_PHY0_(128),ddr_reg_info->phy_reg[3-freq_num][2], PHY0_REG1_SAVE_SIZE);
		__data_move( CANDS_PHY0_(256),ddr_reg_info->phy_reg[3-freq_num][3], PHY0_REG1_SAVE_SIZE);
		__data_move( CANDS_PHY0_(384),ddr_reg_info->phy_reg[3-freq_num][4], PHY0_REG1_SAVE_SIZE);
		__data_move( CANDS_PHY0_(512),ddr_reg_info->phy_reg[3-freq_num][5], PHY0_REG2_SAVE_SIZE);
		__data_move( CANDS_PHY0_(640),ddr_reg_info->phy_reg[3-freq_num][6], PHY0_REG2_SAVE_SIZE);
		__data_move( CANDS_PHY0_(768),ddr_reg_info->phy_reg[3-freq_num][7], PHY0_REG2_SAVE_SIZE);
		__data_move( CANDS_PHY0_(896),ddr_reg_info->phy_reg[3-freq_num][8], PHY0_REG2_SAVE_SIZE);
	}
}

void pub_restore_register()
{
	uint32 axi_port=0;
	REG32(PUB0_TOP_PUB0_DUMMY_REG)=0x01800000;
	for(axi_port=0;axi_port<6;axi_port++)
	{
		REG32(PUB0_APB_PUB_CHN0_LP_CTRL+(axi_port*4))=0x31;
	}
}


#ifdef DMA_CONFIG
uint32 dma_chn1;
DMA_CHNCFG_T chn1_cfg = {0};
DMA_LINKLIST_HANDLE linklist_handle_1;

PUBLIC uint32 DMA_chn1_linklist_cfg(void)
{
	chn1_cfg.type = DMA_CHN_TYPE_SOFT;
	chn1_cfg.workmode = DMA_CHN_WORKMODE_LINKLIST;
	chn1_cfg.requestmode= DMA_CHN_REQMODE_LIST;
	chn1_cfg.priority = 0;
	chn1_cfg.src_datawidth  = DMA_DATAWIDTH_WORD;
	chn1_cfg.dest_datawidth = DMA_DATAWIDTH_WORD;
	chn1_cfg.src_step = 4;
	chn1_cfg.dest_step = 4;
}

PUBLIC uint32 DMA_chn1_linklist_set(uint32 src, uint32 des, uint32 length)
{
	    chn1_cfg.src_address = (uint32)(src) ;
	    chn1_cfg.dest_address = (uint32)(des) ;
	    chn1_cfg.total_length  = length;
	    chn1_cfg.block_length  = length;
	    chn1_cfg.frag_length  = length;
	    DMA_HAL_AppendInitLinkList(linklist_handle_1, &chn1_cfg);
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


void DMA_chn1_linklist_addr_set()
{
	uint32 freq_num=0;
	struct IRAM_DDR_REG_INFO *addr_info=&iram_addr_info;
	DMA_chn1_linklist_set(&addr_info->ctl_reg,CANDS_CTL0_(0), CTL0_REG_SAVE_SIZE*4);
	DMA_chn1_linklist_set(&addr_info->pi_reg,CANDS_PI0_(0), PI0_REG_SAVE_SIZE*4);

	for(freq_num=0;freq_num<4;freq_num++)
	{
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(1024), PHY0_REG0_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(0), PHY0_REG1_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(128), PHY0_REG1_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(256), PHY0_REG1_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(384), PHY0_REG1_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(512), PHY0_REG2_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(640), PHY0_REG2_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(768), PHY0_REG2_SAVE_SIZE*4);
		DMA_chn1_linklist_set(&addr_info->phy_reg[freq_num],CANDS_PHY0_(896), PHY0_REG2_SAVE_SIZE*4);
	}

	//DMA_chn1_linklist_set(&phy0_1_f3[0],CANDS_PHY0_(1024), REG1_SAVE_SIZE);
	//DMA_chn1_linklist_set(&phy0_2_f3[0],CANDS_PHY0_(0), 0x1000);

}
#else
void ctl_restore_register(struct IRAM_DDR_REG_INFO *ddr_reg_info )
{
	__data_move( ddr_reg_info->ctl_reg,CANDS_CTL0_(0), 481);
}

void pi_restore_register(struct IRAM_DDR_REG_INFO *ddr_reg_info )
{
	__data_move( ddr_reg_info->pi_reg,CANDS_PI0_(0), 249);
}

void phy_restore_register(struct IRAM_DDR_REG_INFO *ddr_reg_info )
{
	uint32 freq_num=0;
	for(freq_num=0;freq_num<4;freq_num++)
	{
		REG32(CANDS_PHY0_(1024)) &= ~(0x1 << 0);
		REG32(CANDS_PHY0_(1024)) &= ~(0XFFFF << 8);
		/*select which frequcey set to update*/
		REG32(CANDS_PHY0_(1024)) |= ((freq_num) << 8);
		__data_move( ddr_reg_info->phy_reg[freq_num][0],CANDS_PHY0_(1024), PHY0_REG0_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][1],CANDS_PHY0_(0), PHY0_REG1_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][2],CANDS_PHY0_(128), PHY0_REG1_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][3],CANDS_PHY0_(256), PHY0_REG1_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][4],CANDS_PHY0_(384), PHY0_REG1_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][5],CANDS_PHY0_(512), PHY0_REG2_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][6],CANDS_PHY0_(640), PHY0_REG2_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][7],CANDS_PHY0_(768), PHY0_REG2_SAVE_SIZE);
		__data_move( ddr_reg_info->phy_reg[freq_num][8],CANDS_PHY0_(896), PHY0_REG2_SAVE_SIZE);
	}
}
#endif

uint32 pattern[2]={0x5555aaaa,0xaaaa5555};
void ddr_data_wr(uint32 addr,uint32 size)
{
	uint32 num=0;
	for(num=0;num<size;num++)
	{
		if(num%2==0)
		{
			REG32(addr+num*4)=pattern[0];
		}else
		{
			REG32(addr+num*4)=pattern[1];
		}
	}

}

uint32  ddr_data_check(uint32 addr,uint32 size)
{
	uint32 num=0;
	uint32 status=0;
	for(num=0;num<size;num++)
	{
		if(pattern[num%2]!=REG32(addr+num*4))
		{
			status=1;
		}
	}
	return status;
}


void pub_reinit(struct IRAM_DDR_REG_INFO *ddr_reg_info)
{
	uint32 ddr_access_result = 0;
	uint32 bist_result = 0;
	uint32 i;
	/*STEP4*/
	ctl_phy_release();// release ctl phy
	//while(((REG32(SYS_SLP_STATUS)>>8)&0xf) != 0x6);
	/*Initiate command processing in the controller. Set to 1 to initiate*/
	ddr_reg_info->ctl_reg[0] &= ~(0x1 << 0);
	ddr_reg_info->pi_reg[0] &= ~(0x1 << 0);

	/*--------------------start freq---------------*/
	//dfibus_boot_freq
	ddr_reg_info->ctl_reg[32] &= ~(0x7 << 16);
	ddr_reg_info->ctl_reg[32] |= (pub_wakeup_freq<<16);
	//dfibus_freq_init
	ddr_reg_info->ctl_reg[32] &= ~(0x7 << 24);				//iwahle2:Defines the DFI bus boot frequency.
	ddr_reg_info->ctl_reg[32] |= (pub_wakeup_freq<< 24);
	//lpi_wakeup_en
	ddr_reg_info->ctl_reg[151] &= ~(0x1<<16);					// enables  power-down wakeup,

	#ifdef DMA_CONFIG
	DMA_HAL_Linklist_Transfer(linklist_handle_1);
	while(!(DMA_HAL_PollingListDone(dma_chn1)));
	#else
	pi_restore_register(ddr_reg_info);
	ctl_restore_register(ddr_reg_info);
	phy_restore_register(ddr_reg_info);
	#endif

#ifndef DO_TRAINING
 	REG32(CANDS_CTL0_(32)) |=(0x1 << 0);		//no_phy_ind_train_init
 	REG32(CANDS_CTL0_(32)) &=~(0x1 << 8);	//no_phy_ind_train_init
#else
 	REG32(CANDS_PI0_(1)) |= (0x1 << 8);		//pi_init_lvl_en
 	REG32(CANDS_PI0_(1)) |= (0x1 << 0);		//pi_normal_lvl_seq
	reg_bit_set(CANDS_CTL0_(38), 0, 6, pub_wakeup_freq);	//pi work freq
#endif

	/*STEP8*/
	//REG32(CANDS_PHY0_(1050)) |= (1<< 10); 	    //lp4
	REG32(CANDS_CTL0_(102)) |=(0x1 << 16);	    //PWRUP_SREFRESH_EXIT


#ifndef FORCE_DEEP_SLEEP
	/*use for sw enter self-refresh*/
	reg_bit_set(CANDS_PHY0_(1051), 8, 4, 0x4);	        //PHY_SET_DFI_INPUT_0
	REG32(DDR_PHY_DATA_RET) &=~(0x1 << 0);			//remove data retention
#endif


#ifdef RPULL
	reg_bit_set(CANDS_PHY0_(1075), 29, 1, 0x1);     // phy_pad_dqs RPULL enable
#endif


#if 0
	REG32(CANDS_PHY0_(1093)) |= (1<<0);		// yu zhao
#endif

#ifdef DO_TRAINING
	//REG32(CANDS_PI0_(95))  |= (0x1 << 16);		//pi_rdlvl_on_sref_exit
	//REG32(CANDS_PI0_(96))  |= (0x1 << 0);		//pi_rdlvl_gate_on_sref_exit
	REG32(CANDS_PI0_(0))  |= (0x1 << 0);		//yu zhao
#else
	REG32(CANDS_PI0_(0))  &= ~(0x1 << 0);	//yu zhao
#endif

	reg_bit_set(CANDS_CTL0_(153), 24, 4, 0);		//LP AUTO ENTRT EN

	reg_bit_set(CANDS_PHY0_(1096), 8, 3, 5);		//PHY_CAL_CLK_SELECT_0 20-10-9:48

	 //ctl start set
	REG32(CANDS_CTL0_(0))  |= (0x1 << 0);	//step9

	//wait ddr init done:The low power operation has been completed.
	while((REG32(CANDS_CTL0_(292))&0x10) != 0x10);		//step10
	ddr_info_g->init_done=1;
	subsys_bus_clk_div_cfg(pub_wakeup_freq);
	REG32(DDR0_ACC_RDY) |=(0x1<<0);
	if(ddr_data_check(ddr_info_g->bist_addr, 0x100))
	{
		reinit_info_g->state_selfrefresh++;
	}
	if(cm4_bist_test(0x3, 0x0, 0x1fff))
	{
		reinit_info_g->poweron_bist_result++;
	}
	REG32(PUB0_SYS_SLEEP_CTRL) |= (0x1<<4);


}

uint32 pub_power_on(struct IRAM_DDR_REG_INFO *ddr_reg_info)
{

#ifdef FORCE_MODE
	if((REG32(PWR_STATE_DBG2) & (0x1F << 15))== (0x7 << 15))
	{
		#ifdef FORCE_DEEP_SLEEP
			/*STEP 1*/
			REG32(PUB0_SYS_SLEEP_CTRL) &= ~(0x1 << 2); // clear ddr_deep_sleep
			REG32(PUB0_SYS_SLEEP_CTRL) &= ~(0x1 << 4); // clear ddr_deep_sleep
		#else
			REG32(PD_PUB0_SYS_PWR_CFG) &= ~(0x1 << 24);
			REG32(PD_PUB0_SYS_PWR_CFG) &= ~(0x1 << 25);
		#endif
		/*STEP2*/
		REG32(PUB0_SYS_SLEEP_CTRL) |= (0x1 << 6); 		//DDR0_SLEEP_DISABLE
	}
	else
	{
		REG32(DDR0_ACC_RDY) |= (0x1 << 0);
		return 0;
	}
#endif

	while((REG32(PWR_STATE_DBG2) & (0x1F << 15)) != 0x0);

        wait_us(10);
	//ddr reinit and ddr can access
	pub_reinit(ddr_reg_info);
	//free DMA
	#ifdef DMA_CONFIG
	DMA_HAL_FreeLinkList(linklist_handle_1);
	#endif
	//recover pub registers
	pub_restore_register();
	ddr_info_g->sleep_flag=0;
	if((!ddr_info_g->sleep_flag)&&ddr_info_g->init_done)
	{
		ddr_dfs_reg_cfg();
		dfi_bm_cfg();
	}

	if(ddr_info_g->hw_dfs_en)
	{
		ddr_hwdfs_set(ENABLE);
	}
	REG32(DDR_SLEEP_CTRL) &= ~(0x1<<0); //ddr0_umctl_eb
	REG32(DDR_SLEEP_CTRL) &= ~(0x1<<1); //ddr0_phy_eb
	REG32(PUB0_SYS_SLEEP_CTRL) &= ~(0x1 << 6);	//STEP12

	return 0;

}

void pub_power_off()
{
	volatile uint32 i=1;
	REG32(DDR_SLEEP_CTRL) |= (0x1 << 0); 						//ddr0_umctl_eb
	REG32(DDR_SLEEP_CTRL) |= (0x1 << 1); 						//ddr0_phy_eb

	/*STEP1*/
	REG32(DDR_PHY_DATA_RET) |= (0x1 << 0); 						//ddr0_phy_retention_eb

	//REG32(PUB0_FORCE_SLEEP) |= (0x1 << 3);					//pub0_force_lightsleep  QA

#ifdef FORCE_DEEP_SLEEP
	/*STEP2*/
	REG32(PUB0_SYS_SLEEP_CTRL) &= ~(0x1 << 8);					//disable ddr0 auto deep sleep
#endif

#ifdef FORCE_DEEP_SLEEP
	/*STEP3*/
	REG32(PD_PUB0_SYS_PWR_CFG) |= (0x1 << 24);   	 			//PD_PUB0_SYS_AUTO_SHUTDOWN_EN

	/*STEP4*/
	REG32(PD_PUB0_FORCE_SLEEP) |= (0x1 <<2);  				//force deep sleep(refresh and power down
#else
	/*self-refresh with memory clock gating*/
	reg_bit_set(CANDS_CTL0_(141),0,9,0x2a);

	/*polling */
	while(((REG32(CANDS_CTL0_(292)) >> 0x5) &0x1 ) != 0x1);

	/*move io data retention*/
	REG32(DDR_PHY_DATA_RET) |= (0x1 << 0);

	/*force pub power down*/
	REG32(PD_PUB0_SYS_PWR_CFG) &= ~(0x1 << 24);   	 			//PD_PUB0_SYS_AUTO_SHUTDOWN_EN
	REG32(PD_PUB0_SYS_PWR_CFG) |= (0x1 << 25);					//PD_PUB0_SYS_FORCE
#endif
	while((REG32(PWR_STATE_DBG2) & (0x1F << 15)) != (0x7 << 15));		//waitting until  done = 1
	#ifdef DMA_CONFIG
	DMA_chn1_linklist_addr_set();
	#endif

}


void ddr_reinit_prepare()
{
	REG32(DDR0_ACC_RDY) |= (0x1 << 0);
	//REG32(DDR0_LIGHT_ACC_RDY) |= (0x1 << 0);
	//reg_bit_set(DDR0_SLP_CFG,0,16,DDR0_SLEEP_WAIT_CNT);
	//reg_bit_set(DDR0_SLP_CFG,16,16,DDR0_PWR_DOWN_WAIT_CNT);
	if(ddr_info_g->ddr_type==LPDDR3)
	{
		reg_bit_set(PUB_MEM_RESET_RET,0,2,0X0);
	}
	REG32(PD_PUB0_SYS_SHUTDOWN_MARK) &= ~(0xF);  	// clear status
	#ifdef FORCE_MODE
		reg_bit_set(PD_PUB0_SYS_PWR_CFG, 24, 2,0x0); //pub0 mode is force shutdown
	#else
		reg_bit_set(PD_PUB0_SYS_PWR_CFG, 24, 2,0x1); //power domain auto shut down when ap deep sleep
	#endif
}



void reinit_handler(struct IRAM_DDR_REG_INFO *ddr_reg_info,PUB_STATUS status)
{
	uint32 i=1;
	uint32 pub_eic_state=1;
	uint32 pub_level=0;
	SCI_DisableIRQ();
	#if 0
	pub_level=EIC_HAL_GetPol(EIC_LATCH_ID(LATCH_RESERVED));
	pub_eic_state=(REG32(0x50060084)&(1<<3))>>3;
	#endif
	if(pub_eic_state==1)
	{
	#if  0
		if(HIGH_LEVEL == pub_level)
		{
			/* Toggle trigger pol*/
			EIC_HAL_SetIntSense(EIC_LATCH_ID(LATCH_RESERVED), GPIO_INT_LEVEL_LOW);
		}else
		{
			/* Toggle trigger pol*/
			EIC_HAL_SetIntSense(EIC_LATCH_ID(LATCH_RESERVED), GPIO_INT_LEVEL_HIGH);
		}
		/* Clear interrupt*/
		EIC_HAL_ClrIntSts(EIC_LATCH_ID(LATCH_RESERVED));
	#endif
		if(PUB_POWEROFF== status) 		 						/*hosan:pwoer off interrupt*/
		{
			REG32(DDR0_ACC_RDY)=0x0;
			ddr_info_g->sleep_flag=1;
			if(reinit_info_g->pub_poweroff_state)
			{
				#ifdef FORCE_MODE
				pub_power_off();
				ctl_phy_reset();        					//rest phy and ctl
				#endif
			}
			reinit_info_g->pub_sleep_counter++;
		}
		else													//power on
		{
			if(reinit_info_g->pub_poweroff_state)
			{
				//pub_poweron_start_time = REG32(0xe4050058);
				pub_power_on(ddr_reg_info); 				/*hosan: power on and reinit*/
			}
			else
			{
				REG32(DDR0_ACC_RDY) |= (0x1 << 0);
			}
		}
	}
	else
	{

	}

	SCI_RestoreIRQ();
}

void ddr_sys_info_init()
{
	uint32 freq_num=0;
	freq_num=(REG32(CANDS_CTL0_(175))>>16)&0x3;
	ddr_info_g->ddr_type=(REG32(CANDS_CTL0_(0))>>8)&0xf;
	ddr_info_g->ddr_clk=(dfs_info_constant+freq_num)->freq_clk;
	ddr_info_g->freq_num=freq_num;
	ddr_info_g->support_freq_num=0x4;
	ddr_info_g->bist_addr=0x0;
	ddr_info_g->init_done=0x1;
	ddr_info_g->sleep_flag=0x0;
	ddr_info_g->dfs_mode=0x0;
	ddr_info_g->dfi_bm_timer=10;
	ddr_info_g->hw_dfs_en=DISABLE;
	ddr_info_g->dfs_freq_en=0x0;

	reinit_info_g->pub_poweroff_state=1;
	reinit_info_g->pub_sleep_counter=0;
	reinit_info_g->pub_wakeup_counter=0;
	reinit_info_g->pub_poweron_step=0;
	reinit_info_g->pub_poweroff_step=0;
	reinit_info_g->pub_poweron_aver_time=0;
	reinit_info_g->pub_poweron_max_time=0;
	reinit_info_g->pub_poweroff_aver_time=0;
	reinit_info_g->pub_poweroff_max_time=0;
	reinit_info_g->state_selfrefresh=0;
	reinit_info_g->poweron_bist_result=0;

}

void DMC_Reinit(void)
{
	#ifdef DMA_CONFIG
	DMA_HAL_LinkList_chn1_init();
	#endif
	struct IRAM_DDR_REG_INFO *ddr_reg_info =&iram_addr_info;
	ddr_iram_addr_init(ddr_reg_info);
	ddr_sys_info_init();
	ddr_data_wr(ddr_info_g->bist_addr,0x100);
#ifdef RETENTION_FREQ
	pub_wakeup_freq = 3;		//force F3 wakeup
#else
	pub_wakeup_freq  = (REG32(CANDS_CTL0_(175)+0)>>16)&0x7;  //iwahle2
#endif
	ddr_reinit_prepare();
	phy_save_register(ddr_reg_info);							//save phy register  new
	pi_save_register(ddr_reg_info);
	ctl_save_register(ddr_reg_info);
	wait_us(10);
	while(1)
	{
		reinit_handler(ddr_reg_info,PUB_POWEROFF);
        	wait_us(10);
		reinit_handler(ddr_reg_info,PUB_POWERON);
        	wait_us(10);

	}
}

