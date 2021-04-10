#include "isharkl2_common.h"
#include "isharkl2_dfi_bm.h"


volatile uint32 mutex_flag = 0;



void dfi_bm_entry()
{
	mutex_flag++;
}

void dfi_bm_exit()
{
	mutex_flag--;
}

void bm_timer_eb(uint32 flag)
{
	reg_bit_set(AON_APB_CGM_REG1, 1, 1,flag);
}


static void dfi_bm_timer_cfg(uint32 data)
{
	reg_bit_set(BUSMON_TIMER_CFG,2,1,0x0);//timer_disable
	REG32(BUSMON_TIMER2_HIGH_LEN)=data;//high_len
	REG32(BUSMON_TIMER2_LOW_LEN)=0x1;  //low_len
	reg_bit_set(BUSMON_TIMER_CFG,2,1,0x1);//timer_en
	reg_bit_set(BUSMON_TIMER_CFG,0,1,0x1);

}

void busmon_timer_ms_cfg(uint32 count)
{
	uint32 reg_val;
	uint32 tbusmon=count;
	if(tbusmon> TIME_MS_MAX)
	{

	}else
	{
		tbusmon=tbusmon*1000*1000;
		tbusmon=tbusmon/DFS_TIMER_STEP*10;
		reg_val=(uint32)tbusmon;
		dfi_bm_timer_cfg(reg_val);
	}
}

uint32 busmon_timer_ms_get()
{

}

void dfi_bm_int_clear()
{
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN,0,2,0x3);
}

void dfi_bm_uf_int_set(uint32 enable)
{
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN,1,1,enable);
}

void dfi_bm_int_en(uint32 enable)
{
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN,0,1,enable);
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN,1,1,enable);
	reg_bit_set(PUB0_DFS_BUSMON_INT_EN,2,1,enable);
	reg_bit_set(PUB0_DFS_BUSMON_CFG,0,1,enable);
}

void dfi_bm_off()
{
	if(0==ddr_info_g->sleep_flag)
	{
		dfi_bm_int_clear();
		dfi_bm_int_en(0x0);
	}

}

void dfi_bm_on()
{
	if(0==ddr_info_g->sleep_flag)
	{
		dfi_bm_int_en(0x1);
	}
}

uint32 ddr_hwdfs_set(uint32 flag)
{
	if(0==pub_umctl_eb_lock())
	{
		return 1;
	}
	if(flag)
	{
		ddr_info_g->hw_dfs_en=ENABLE;
		if(0==ddr_info_g->sleep_flag)
		{
			dfi_bm_int_en(0x1);
		}
	}else
	{
		ddr_info_g->hw_dfs_en=DISABLE;
		if(0==ddr_info_g->sleep_flag)
		{
			dfi_bm_int_en(0x1);
		}
	}

	pub_umctl_eb_unlock();
	return 0;
}

void dfi_bm_cfg()
{
	uint32 freq_num=0;
	for(freq_num=0;freq_num<ddr_info_g->support_freq_num;freq_num++)
	{
		REG32(PUB0_DFS_BUSMON_OVERFLOW_THOLD_F0+freq_num*8)=(dfs_info_constant+freq_num)->bm_of_threshold;
		REG32(PUB0_DFS_BUSMON_UNDERFLOW_THOLD_F0+freq_num*8)=(dfs_info_constant+freq_num)->bm_uf_threshold;
	}
	REG32(PUB0_DFS_BUSMON_CFG)=0x1;
}

void dfi_bm_init()
{
	//cgm_cm3_tmr2_en
	reg_bit_set(AON_APB_CGM_REG1,19,1,0x1);
	//26m force enable
	reg_bit_set(AON_CLK_PREDIV_GATE_EN_SEL3_CFG,2,1,0x0);
	reg_bit_set(AON_CLK_PREDIV_GATE_EN_CTL3_CFG,2,1,0x0);
	//enable busmonitor timer eb
	reg_bit_set(AON_APB_CGM_REG1,1,1,0x1);
	if(1==ddr_info_g->init_done)
	{
		dfi_bm_cfg();
	}
	busmon_timer_ms_cfg(ddr_info_g->dfi_bm_timer);
}
#if 0
/*************************************************ISR********************************************************/
LOCAL int bm_hal_isr_handler(const uint32 num)
{
	if(0==pub_umctl_eb_lock())
	{
		return ISR_DONE;
	}
	if(mutex_flag>=1)
	{
		pub_umctl_eb_unlock();
		return ISR_DONE;
	}

	dfi_bm_entry();
	dfs_f(DFI_BM_REQ);
	dfi_bm_exit();
	pub_umctl_eb_unlock();
	return ISR_DONE;
}

PUBLIC void bm_hal_dfs_irq (void)
{
	/* Register bm IRQ */
	if(TB_SUCCESS == ISR_RegHandler(TB_PUB0_DFI_BM_INT, (TB_ISR)bm_hal_isr_handler))
	{
		 /* irq_enable register:enable Bus monitor PUB0 DFS interrupt */
		 CHIPDRV_EnableIRQINT(TB_PUB0_DFI_BM_INT);
	}
}


void bm_hal_dfs_init(void)
{
	bm_hal_dfs_irq();
}
#endif

