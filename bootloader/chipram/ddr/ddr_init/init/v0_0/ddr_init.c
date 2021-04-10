#include "ddr_init.h"
#include "ddr_qos.h"
#include "ddr_timing.h"


void cands_ctl_phy_release(DDR_CHANNEL_NUM_E chn_num)
{
	volatile uint32 i = 0;

	//???
	reg_bit_set(0x402e30f4,18,1,1);

	if(chn_num == DDR_CHANNEL_0)
	{
		//1x/2x clock en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,1,2,3);
		for(i = 0; i<1000; i++);
		//soft reset to 0
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,5,1,0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,7,1,0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,8,1,0);
		for(i = 0; i<1000; i++);
	}
	else
	{

		//1x/2x clock en
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,17,2,3);
		for(i = 0; i<1000; i++);
		//soft reset to 0
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,21,1,0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,23,1,0);
		reg_bit_set(PMU_APB_DDR_SLEEP_CTRL,24,1,0);
		for(i = 0; i<1000; i++);
	}
}



void cands_ctl_actiming_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * fx_timing)
{
	uint32 i = 0;
	static CANDS_CTL_TIMING_T * f0_timing = NULL;
	static CANDS_CTL_TIMING_T * f1_timing = NULL;
	static CANDS_CTL_TIMING_T * f2_timing = NULL;
	static CANDS_CTL_TIMING_T * f3_timing = NULL;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	for(i = 0; i < 4; i++)
	{
		switch(fx_timing[i].freq_point)
		{
			case 0: f0_timing = &fx_timing[i]; break;
			case 1: f1_timing = &fx_timing[i]; break;
			case 2: f2_timing = &fx_timing[i]; break;
			case 3: f3_timing = &fx_timing[i]; break;
			default : break;
		}
	}
	
	__raw_writel(CANDS_CTL0_(16)+chn_offset, f0_timing->TINIT);
	__raw_writel(CANDS_CTL0_(17)+chn_offset, f0_timing->TINIT3);
	__raw_writel(CANDS_CTL0_(18)+chn_offset, f0_timing->TINIT4);
	__raw_writel(CANDS_CTL0_(19)+chn_offset, f0_timing->TINIT5);
	__raw_writel(CANDS_CTL0_(20)+chn_offset, f1_timing->TINIT);
	__raw_writel(CANDS_CTL0_(21)+chn_offset, f1_timing->TINIT3);
	__raw_writel(CANDS_CTL0_(22)+chn_offset, f1_timing->TINIT4);
	__raw_writel(CANDS_CTL0_(23)+chn_offset, f1_timing->TINIT5);
	__raw_writel(CANDS_CTL0_(24)+chn_offset, f2_timing->TINIT);
	__raw_writel(CANDS_CTL0_(25)+chn_offset, f2_timing->TINIT3);
	__raw_writel(CANDS_CTL0_(26)+chn_offset, f2_timing->TINIT4);
	__raw_writel(CANDS_CTL0_(27)+chn_offset, (f2_timing->TINIT5)&0xFFFFFF);
	__raw_writel(CANDS_CTL0_(28)+chn_offset, f0_timing->TRST_PWRON);
	__raw_writel(CANDS_CTL0_(29)+chn_offset, f0_timing->CKE_INACTIVE);
	__raw_writel(CANDS_CTL0_(30)+chn_offset, (f1_timing->TDLL<<16)|f0_timing->TDLL);
	__raw_writel(CANDS_CTL0_(31)+chn_offset, (f0_timing->WRLAT<<24)|(f0_timing->CASLAT_LIN<<16)|f2_timing->TDLL);
	__raw_writel(CANDS_CTL0_(32)+chn_offset, (f1_timing->ADDITIVE_LAT<<24)|(f1_timing->WRLAT<<16)|(f1_timing->CASLAT_LIN<<8)|(f0_timing->ADDITIVE_LAT));
	__raw_writel(CANDS_CTL0_(33)+chn_offset, (f2_timing->ADDITIVE_LAT<<16)|(f2_timing->WRLAT<<8)|(f2_timing->CASLAT_LIN));
	__raw_writel(CANDS_CTL0_(34)+chn_offset, (f0_timing->TRAS_MIN<<24)|(f0_timing->TRC<<16)|(f0_timing->TRRD<<8)|f0_timing->TCCD);
	__raw_writel(CANDS_CTL0_(35)+chn_offset, (f1_timing->TRRD<<24)|(f0_timing->TFAW<<16)|(f0_timing->TRP<<8)|f0_timing->TWTR);
	__raw_writel(CANDS_CTL0_(36)+chn_offset, (f1_timing->TRP<<24)|(f1_timing->TWTR<<16)|(f1_timing->TRAS_MIN<<8)|f1_timing->TRC);
	__raw_writel(CANDS_CTL0_(37)+chn_offset, (f2_timing->TRAS_MIN<<24)|(f2_timing->TRC<<16)|(f2_timing->TRRD<<8)|f1_timing->TFAW);	
	__raw_writel(CANDS_CTL0_(38)+chn_offset, (f0_timing->TRTP<<24)|(f2_timing->TFAW<<16)|(f2_timing->TRP<<8)|f2_timing->TWTR);
	__raw_writel(CANDS_CTL0_(39)+chn_offset, (f0_timing->TMOD<<16)|f0_timing->TMRD);
	__raw_writel(CANDS_CTL0_(40)+chn_offset, (f0_timing->TCKE<<24)|f0_timing->TRAS_MAX);
	__raw_writel(CANDS_CTL0_(41)+chn_offset, (f1_timing->TMOD<<24)|(f1_timing->TMRD<<16)|(f1_timing->TRTP<<8)|f0_timing->TCKESR);
	__raw_writel(CANDS_CTL0_(42)+chn_offset, (f1_timing->TCKE<<24)|(f1_timing->TRAS_MAX));
	__raw_writel(CANDS_CTL0_(43)+chn_offset, (f2_timing->TMOD<<24)|(f2_timing->TMRD<<16)|(f2_timing->TRTP<<18)|f1_timing->TCKESR);
	__raw_writel(CANDS_CTL0_(44)+chn_offset, (f2_timing->TCKE<<24)|(f2_timing->TRAS_MAX));
	__raw_writel(CANDS_CTL0_(45)+chn_offset, (f0_timing->TWR<<24)|(f0_timing->TRCD<<16)|f2_timing->TCKESR);
	__raw_writel(CANDS_CTL0_(46)+chn_offset, (f2_timing->TWR<<24)|(f2_timing->TRCD<<16)|(f1_timing->TWR<<8)|f1_timing->TRCD);
	__raw_writel(CANDS_CTL0_(47)+chn_offset, (f0_timing->TCAMRD<<24)|(f0_timing->TCAENT<<16)|(f0_timing->TCACKEL<<8)|f0_timing->TMRR);
	__raw_writel(CANDS_CTL0_(48)+chn_offset, (f1_timing->TMRZ<<24)|(f0_timing->TMRZ<<16)|(f0_timing->TCACKEH<<8)|(f0_timing->TCAEXT));

	reg_bit_set(CANDS_CTL0_(49)+chn_offset,0,5, (f2_timing->TMRZ));
	reg_bit_set(CANDS_CTL0_(50)+chn_offset,0,24,(f2_timing->TDAL<<16)|(f1_timing->TDAL<<8)|(f0_timing->TDAL));
	
	__raw_writel(CANDS_CTL0_(54)+chn_offset, (f0_timing->TREF<<16)|f0_timing->TRFC);
	__raw_writel(CANDS_CTL0_(55)+chn_offset, (f1_timing->TREF<<16)|f1_timing->TRFC);
	__raw_writel(CANDS_CTL0_(56)+chn_offset, (f2_timing->TREF<<16)|f2_timing->TRFC);
	__raw_writel(CANDS_CTL0_(57)+chn_offset, (f0_timing->TREF_INTERVAL));
	__raw_writel(CANDS_CTL0_(58)+chn_offset, (f1_timing->TPDEX<<16)|f0_timing->TPDEX);
	__raw_writel(CANDS_CTL0_(59)+chn_offset, (f0_timing->TXPDLL<<16)|f2_timing->TPDEX);
	__raw_writel(CANDS_CTL0_(60)+chn_offset, (f2_timing->TXPDLL<<16)|f1_timing->TXPDLL);
	__raw_writel(CANDS_CTL0_(61)+chn_offset, (f2_timing->TMRRI<<16)|(f1_timing->TMRRI<<8)|(f0_timing->TMRRI));
	__raw_writel(CANDS_CTL0_(62)+chn_offset, (f0_timing->TXSNR<<16)|(f0_timing->TXSR));
	__raw_writel(CANDS_CTL0_(63)+chn_offset, (f1_timing->TXSNR<<16)|(f1_timing->TXSR));
	__raw_writel(CANDS_CTL0_(64)+chn_offset, (f2_timing->TXSNR<<16)|(f2_timing->TXSR));
	
	reg_bit_set(CANDS_CTL0_(65)+chn_offset,24,3, f0_timing->CKE_DELAY);	
	reg_bit_set(CANDS_CTL0_(66)+chn_offset,8,24, (f1_timing->CKSRE<<16)|(f0_timing->CKSRX<<8)|(f0_timing->CKSRE));
	reg_bit_set(CANDS_CTL0_(67)+chn_offset,0,24, (f2_timing->CKSRX<<16)|(f2_timing->CKSRE<<8)|(f1_timing->CKSRX));
	
	reg_bit_set(CANDS_CTL0_(111)+chn_offset,8,12, f0_timing->ZQINIT);
	__raw_writel(CANDS_CTL0_(112)+chn_offset, (f0_timing->ZQCS<<16)|(f0_timing->ZQCL));
	__raw_writel(CANDS_CTL0_(113)+chn_offset, (f1_timing->ZQCL<<16)|(f1_timing->ZQINIT));
	__raw_writel(CANDS_CTL0_(114)+chn_offset, (f2_timing->ZQINIT<<16)|(f1_timing->ZQCS));
	__raw_writel(CANDS_CTL0_(115)+chn_offset, (f2_timing->ZQCS<<16)|(f2_timing->ZQCL));
	__raw_writel(CANDS_CTL0_(117)+chn_offset, (f0_timing->ZQ_INTERVAL));

	reg_bit_set(CANDS_CTL0_(118)+chn_offset,8,12,(f0_timing->ZQRESET));

	__raw_writel(CANDS_CTL0_(119)+chn_offset,(f2_timing->ZQRESET<<16)|f1_timing->ZQRESET);

	reg_bit_set(CANDS_CTL0_(152)+chn_offset,24,5, (f0_timing->R2R_DIFFCS_DLY));
	
	__raw_writel(CANDS_CTL0_(153)+chn_offset, (f1_timing->R2R_DIFFCS_DLY<<24)|(f0_timing->W2W_DIFFCS_DLY<<16)|
										   (f0_timing->W2R_DIFFCS_DLY<<8)|(f0_timing->R2W_DIFFCS_DLY));
	__raw_writel(CANDS_CTL0_(154)+chn_offset, (f2_timing->R2R_DIFFCS_DLY<<24)|(f1_timing->W2W_DIFFCS_DLY<<16)|
										   (f1_timing->W2R_DIFFCS_DLY<<8)|(f1_timing->R2W_DIFFCS_DLY));
	__raw_writel(CANDS_CTL0_(155)+chn_offset, (f0_timing->R2R_SAMECS_DLY<<24)|(f2_timing->W2W_DIFFCS_DLY<<16)|
										   (f2_timing->W2R_DIFFCS_DLY<<8)|(f2_timing->R2W_DIFFCS_DLY));
	__raw_writel(CANDS_CTL0_(156)+chn_offset, (f0_timing->W2R_SAMECS_DLY<<24)|(f2_timing->R2W_SAMECS_DLY<<16)|
										   (f1_timing->R2W_SAMECS_DLY<<8)|(f0_timing->R2W_SAMECS_DLY));
	__raw_writel(CANDS_CTL0_(157)+chn_offset, (f1_timing->TDQSCK_MAX<<24)|(f0_timing->TDQSCK_MIN<<16)|
										   (f0_timing->TDQSCK_MAX<<8)|f0_timing->W2W_SAMECS_DLY);

	reg_bit_set(CANDS_CTL0_(158)+chn_offset,0,24, (f2_timing->TDQSCK_MIN<<16)|(f2_timing->TDQSCK_MAX<<8)|f1_timing->TDQSCK_MIN);
	
	__raw_writel(CANDS_CTL0_(960)+chn_offset, f3_timing->TINIT);
	__raw_writel(CANDS_CTL0_(961)+chn_offset, f3_timing->TINIT3);
	__raw_writel(CANDS_CTL0_(962)+chn_offset, f3_timing->TINIT4);
	__raw_writel(CANDS_CTL0_(963)+chn_offset, f3_timing->TINIT5);
	__raw_writel(CANDS_CTL0_(964)+chn_offset, (f3_timing->WRLAT<<24)|(f3_timing->CASLAT_LIN<<16)|f3_timing->TDLL);
	__raw_writel(CANDS_CTL0_(965)+chn_offset, (f3_timing->TRAS_MIN<<24)|(f3_timing->TRC<<16)|(f3_timing->TRRD<<8)|(f3_timing->ADDITIVE_LAT));
	__raw_writel(CANDS_CTL0_(966)+chn_offset, (f3_timing->TRTP<<24)|(f3_timing->TFAW<<16)|(f3_timing->TRP<<8)|f3_timing->TWTR);
	__raw_writel(CANDS_CTL0_(967)+chn_offset, (f3_timing->TMOD<<8)|(f3_timing->TMRD));
	__raw_writel(CANDS_CTL0_(968)+chn_offset, (f3_timing->TCKE<<8)|(f3_timing->TRAS_MAX));
	__raw_writel(CANDS_CTL0_(969)+chn_offset, (f3_timing->TMRZ<<24)|(f3_timing->TWR<<16)|(f3_timing->TRCD<<8)|f3_timing->TCKESR);
	__raw_writel(CANDS_CTL0_(970)+chn_offset, (f2_timing->TRP_AB_CSx<<24)|(f1_timing->TRP_AB_CSx<<16)|
										      (f0_timing->TRP_AB_CSx<<8)|f3_timing->TDAL);
	__raw_writel(CANDS_CTL0_(971)+chn_offset, (f2_timing->TRP_AB_CSx<<24)|(f1_timing->TRP_AB_CSx<<16)|
										      (f0_timing->TRP_AB_CSx<<8)|f3_timing->TRP_AB_CSx);
	__raw_writel(CANDS_CTL0_(972)+chn_offset, (f3_timing->TRFC<<8)|f3_timing->TRP_AB_CSx);
	__raw_writel(CANDS_CTL0_(973)+chn_offset, (f3_timing->TPDEX<<16)|f3_timing->TREF);
	__raw_writel(CANDS_CTL0_(974)+chn_offset, (f3_timing->TMRRI<<16)|f3_timing->TXPDLL);
	__raw_writel(CANDS_CTL0_(975)+chn_offset, (f3_timing->TXSNR<<16)|f3_timing->TXSR);
	
	reg_bit_set(CANDS_CTL0_(976)+chn_offset,0,16, (f3_timing->CKSRX<<8)|f3_timing->CKSRE);
	
	__raw_writel(CANDS_CTL0_(985)+chn_offset, (f3_timing->ZQCL<<16)|f3_timing->ZQINIT);
	__raw_writel(CANDS_CTL0_(986)+chn_offset, (f3_timing->ZQRESET<<16)|f3_timing->ZQCS);
	
	reg_bit_set(CANDS_CTL0_(991)+chn_offset,16,16, (f3_timing->R2W_DIFFCS_DLY<<8)|(f3_timing->R2R_DIFFCS_DLY));
	
	__raw_writel(CANDS_CTL0_(992)+chn_offset, (f3_timing->TDQSCK_MAX<<24)|(f3_timing->R2W_SAMECS_DLY<<16)|
										   (f3_timing->W2W_DIFFCS_DLY<<8)|f3_timing->W2R_DIFFCS_DLY);
	
	reg_bit_set(CANDS_CTL0_(993)+chn_offset,0,8, (f3_timing->TDQSCK_MIN));
}

void cands_ctl_dfilptiming_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * fx_timing)
{
	uint32 i = 0;
	static CANDS_CTL_TIMING_T * f0_timing = NULL;
	static CANDS_CTL_TIMING_T * f1_timing = NULL;
	static CANDS_CTL_TIMING_T * f2_timing = NULL;
	static CANDS_CTL_TIMING_T * f3_timing = NULL;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	for(i = 0; i < 4; i++)
	{
		switch(fx_timing[i].freq_point)
		{
			case 0: f0_timing = &fx_timing[i]; break;
			case 1: f1_timing = &fx_timing[i]; break;
			case 2: f2_timing = &fx_timing[i]; break;
			case 3: f3_timing = &fx_timing[i]; break;
			default : break;
		}
	}

	__raw_writel(CANDS_CTL0_(68)+chn_offset,(f0_timing->LPI_TIMER_WAKEUP<<24)|(f0_timing->LPI_SR_MCCLK_GATE_WAKEUP<<16)|
		                                 (f0_timing->LPI_SR_WAKEUP<<8)|f0_timing->LPI_PD_WAKEUP);
	__raw_writel(CANDS_CTL0_(69)+chn_offset,(f1_timing->LPI_TIMER_WAKEUP<<24)|(f1_timing->LPI_SR_MCCLK_GATE_WAKEUP<<16)|
		                                 (f1_timing->LPI_SR_WAKEUP<<8)|f1_timing->LPI_PD_WAKEUP);
	__raw_writel(CANDS_CTL0_(70)+chn_offset,(f2_timing->LPI_TIMER_WAKEUP<<24)|(f2_timing->LPI_SR_MCCLK_GATE_WAKEUP<<16)|
		                                 (f2_timing->LPI_SR_WAKEUP<<8)|f2_timing->LPI_PD_WAKEUP);
	reg_bit_set(CANDS_CTL0_(72)+chn_offset,0,24, (f0_timing->TDFI_LP_RESP<<16)|f0_timing->LPI_WAKEUP_TIMEOUT);	
	__raw_writel(CANDS_CTL0_(74)+chn_offset, (f0_timing->LP_AUTO_SR_MC_GATE_IDLE<<24)|(f0_timing->LP_AUTO_SR_IDLE<<16)|f0_timing->LP_AUTO_PD_IDLE);	
	reg_bit_set(CANDS_CTL0_(976)+chn_offset,16,16, (f3_timing->LPI_SR_WAKEUP<<8)|(f3_timing->LPI_PD_WAKEUP));
	reg_bit_set(CANDS_CTL0_(977)+chn_offset,16,16, (f3_timing->LPI_TIMER_WAKEUP<<8)|(f3_timing->LPI_SR_MCCLK_GATE_WAKEUP));
}

void cands_ctl_odtiming_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * fx_timing)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	
	static CANDS_CTL_TIMING_T * f0_timing = NULL;
	static CANDS_CTL_TIMING_T * f1_timing = NULL;
	static CANDS_CTL_TIMING_T * f2_timing = NULL;
	static CANDS_CTL_TIMING_T * f3_timing = NULL;

	for(i = 0; i < 4; i++)
	{
		switch(fx_timing[i].freq_point)
		{
			case 0: f0_timing = &fx_timing[i]; break;
			case 1: f1_timing = &fx_timing[i]; break;
			case 2: f2_timing = &fx_timing[i]; break;
			case 3: f3_timing = &fx_timing[i]; break;
			default : break;
		}
	}

	__raw_writel(CANDS_CTL0_(149)+chn_offset, (f0_timing->TODTH_WR<<24)|(f2_timing->TODTL_2CMD<<16)|
		                   			       (f1_timing->TODTL_2CMD<<8)|f0_timing->TODTL_2CMD);

	reg_bit_set(CANDS_CTL0_(150)+chn_offset,0,4, f0_timing->TODTH_RD);	
	reg_bit_set(CANDS_CTL0_(151)+chn_offset,8,24, (f2_timing->WR_TO_ODTH<<16)|(f1_timing->WR_TO_ODTH<<8)|(f0_timing->WR_TO_ODTH));
	reg_bit_set(CANDS_CTL0_(152)+chn_offset,0,24, (f2_timing->RD_TO_ODTH<<16)|(f1_timing->RD_TO_ODTH<<8)|(f0_timing->RD_TO_ODTH));
	reg_bit_set(CANDS_CTL0_(990)+chn_offset,16,8, f3_timing->TODTL_2CMD);
	reg_bit_set(CANDS_CTL0_(991)+chn_offset,0,16, (f3_timing->RD_TO_ODTH<<8)|f3_timing->WR_TO_ODTH);
}

void cands_ctl_dfitiming_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * fx_timing)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	
	static CANDS_CTL_TIMING_T * f0_timing = NULL;
	static CANDS_CTL_TIMING_T * f1_timing = NULL;
	static CANDS_CTL_TIMING_T * f2_timing = NULL;
	static CANDS_CTL_TIMING_T * f3_timing = NULL;

	for(i = 0; i < 4; i++)
	{
		switch(fx_timing[i].freq_point)
		{
			case 0: f0_timing = &fx_timing[i]; break;
			case 1: f1_timing = &fx_timing[i]; break;
			case 2: f2_timing = &fx_timing[i]; break;
			case 3: f3_timing = &fx_timing[i]; break;
			default : break;
		}
	}

	reg_bit_set(CANDS_CTL0_(75)+chn_offset,24,8, (f0_timing->TDFI_INIT_START));

	__raw_writel(CANDS_CTL0_(76)+chn_offset, (f1_timing->TDFI_INIT_START<<16)|f0_timing->TDFI_INIT_COMPLETE);
	__raw_writel(CANDS_CTL0_(77)+chn_offset, (f2_timing->TDFI_INIT_START<<16)|f1_timing->TDFI_INIT_COMPLETE);

	reg_bit_set(CANDS_CTL0_(78)+chn_offset,0,16, f2_timing->TDFI_INIT_COMPLETE);
	reg_bit_set(CANDS_CTL0_(923)+chn_offset,0,24,(f0_timing->DLL_RST_ADJ_DLY<<16)|(f0_timing->DLL_RST_DELAY));
	reg_bit_set(CANDS_CTL0_(924)+chn_offset,8,24, (f2_timing->TDFI_PHY_RDLAT<<16)|(f1_timing->TDFI_PHY_RDLAT<<8)|(f0_timing->TDFI_PHY_RDLAT));

	__raw_writel(CANDS_CTL0_(926)+chn_offset, (f0_timing->TDFI_PHYUPD_TYPE0<<16)|(f0_timing->TDFI_CTRLUPD_MAX));
	__raw_writel(CANDS_CTL0_(927)+chn_offset, (f0_timing->TDFI_PHYUPD_TYPE2<<16)|(f0_timing->TDFI_PHYUPD_TYPE1));
	__raw_writel(CANDS_CTL0_(928)+chn_offset, (f0_timing->TDFI_PHYUPD_RESP<<16)|(f0_timing->TDFI_PHYUPD_TYPE3));
	__raw_writel(CANDS_CTL0_(929)+chn_offset, (f0_timing->TDFI_CTRLUPD_INTERVAL));	
	__raw_writel(CANDS_CTL0_(930)+chn_offset,(f1_timing->TDFI_CTRLUPD_MAX<<16)|(f0_timing->WRLAT_ADJ<<8)|f0_timing->RDLAT_ADJ);
	__raw_writel(CANDS_CTL0_(931)+chn_offset, (f1_timing->TDFI_PHYUPD_TYPE1<<16)|(f0_timing->TDFI_PHYUPD_TYPE0));
	__raw_writel(CANDS_CTL0_(932)+chn_offset, (f1_timing->TDFI_PHYUPD_TYPE3<<16)|(f0_timing->TDFI_PHYUPD_TYPE2));
	__raw_writel(CANDS_CTL0_(933)+chn_offset, (f1_timing->TDFI_PHYUPD_RESP));
	__raw_writel(CANDS_CTL0_(934)+chn_offset, (f1_timing->TDFI_CTRLUPD_INTERVAL));
	__raw_writel(CANDS_CTL0_(935)+chn_offset, (f2_timing->TDFI_CTRLUPD_MAX<<16)|(f1_timing->WRLAT_ADJ<<8)|f1_timing->RDLAT_ADJ);
	__raw_writel(CANDS_CTL0_(936)+chn_offset, (f2_timing->TDFI_PHYUPD_TYPE1<<16)|(f2_timing->TDFI_PHYUPD_TYPE0));
	__raw_writel(CANDS_CTL0_(937)+chn_offset, (f2_timing->TDFI_PHYUPD_TYPE3<<16)|(f2_timing->TDFI_PHYUPD_TYPE2));
	__raw_writel(CANDS_CTL0_(938)+chn_offset, (f2_timing->TDFI_PHYUPD_RESP));
	__raw_writel(CANDS_CTL0_(939)+chn_offset, (f2_timing->TDFI_CTRLUPD_INTERVAL));
	__raw_writel(CANDS_CTL0_(940)+chn_offset, (f1_timing->TDFI_CTRL_DELAY<<24)|(f0_timing->TDFI_CTRL_DELAY<<16)|
										   (f2_timing->WRLAT_ADJ<<8)|f2_timing->RDLAT_ADJ);
	
	reg_bit_set(CANDS_CTL0_(941)+chn_offset,0,24, (f0_timing->TDFI_DRAM_CLK_ENABLE<<16)|(f0_timing->TDFI_DRAM_CLK_DISABLE<<8)|f2_timing->TDFI_CTRL_DELAY);
	reg_bit_set(CANDS_CTL0_(977)+chn_offset,16,16, (f3_timing->TDFI_INIT_START));
	
	__raw_writel(CANDS_CTL0_(978)+chn_offset, f3_timing->TDFI_INIT_COMPLETE);

	reg_bit_set(CANDS_CTL0_(993)+chn_offset,8,24, (f3_timing->TDFI_CTRLUPD_MAX<<8)|(f3_timing->TDFI_PHY_RDLAT));
	
	__raw_writel(CANDS_CTL0_(994)+chn_offset, (f3_timing->TDFI_PHYUPD_TYPE1<<16)|(f3_timing->TDFI_PHYUPD_TYPE0));
	__raw_writel(CANDS_CTL0_(995)+chn_offset, (f3_timing->TDFI_PHYUPD_TYPE3<<16)|(f3_timing->TDFI_PHYUPD_TYPE2));
	__raw_writel(CANDS_CTL0_(996)+chn_offset, f3_timing->TDFI_PHYUPD_RESP);
	__raw_writel(CANDS_CTL0_(997)+chn_offset, f3_timing->TDFI_CTRLUPD_INTERVAL);
	__raw_writel(CANDS_CTL0_(998)+chn_offset, (f3_timing->TDFI_CTRL_DELAY<<16)|(f3_timing->WRLAT_ADJ<<8)|f3_timing->RDLAT_ADJ);
}
void cands_ctl_lvltiming_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * fx_timing)
{
	uint32 i = 0;
	static CANDS_CTL_TIMING_T * f0_timing = NULL;
	static CANDS_CTL_TIMING_T * f1_timing = NULL;
	static CANDS_CTL_TIMING_T * f2_timing = NULL;
	static CANDS_CTL_TIMING_T * f3_timing = NULL;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	for(i = 0; i < 4; i++)
	{
		switch(fx_timing[i].freq_point)
		{
			case 0: f0_timing = &fx_timing[i]; break;
			case 1: f1_timing = &fx_timing[i]; break;
			case 2: f2_timing = &fx_timing[i]; break;
			case 3: f3_timing = &fx_timing[i]; break;
			default : break;
		}
	}
	

	for(i = 0; i < 4; i++)
	{
		switch(fx_timing[i].freq_point)
		{
			case 0: f0_timing = &fx_timing[i]; break;
			case 1: f1_timing = &fx_timing[i]; break;
			case 2: f2_timing = &fx_timing[i]; break;
			case 3: f3_timing = &fx_timing[i]; break;
			default : break;
		}
	}

	reg_bit_set(CANDS_CTL0_(941)+chn_offset,24,8, (f0_timing->TDFI_WRLVL_EN));	
	__raw_writel(CANDS_CTL0_(942)+chn_offset, f0_timing->TDFI_WRLVL_WW);
	__raw_writel(CANDS_CTL0_(943)+chn_offset, f0_timing->TDFI_WRLVL_RESP);
	__raw_writel(CANDS_CTL0_(944)+chn_offset, f0_timing->TDFI_WRLVL_MAX);
	__raw_writel(CANDS_CTL0_(945)+chn_offset, (f0_timing->TDFI_RDLVL_RR<<8)|f0_timing->TDFI_RDLVL_EN);
	__raw_writel(CANDS_CTL0_(946)+chn_offset, f0_timing->TDFI_RDLVL_RESP);
	__raw_writel(CANDS_CTL0_(948)+chn_offset, f0_timing->TDFI_RDLVL_MAX);
	reg_bit_set(CANDS_CTL0_(949)+chn_offset,8,16, (f0_timing->RDLVL_INTERVAL));
	__raw_writel(CANDS_CTL0_(950)+chn_offset, (f0_timing->TDFI_CALVL_EN<<16)|f0_timing->RDLVL_GATE_INTERVAL);
	__raw_writel(CANDS_CTL0_(951)+chn_offset, (f0_timing->TDFI_CALVL_CAPTURE<<16)|f0_timing->TDFI_CALVL_CC);
	__raw_writel(CANDS_CTL0_(952)+chn_offset, (f1_timing->TDFI_CALVL_CAPTURE<<16)|f1_timing->TDFI_CALVL_CC);
	__raw_writel(CANDS_CTL0_(953)+chn_offset, (f2_timing->TDFI_CALVL_CAPTURE<<16)|f2_timing->TDFI_CALVL_CC);
	__raw_writel(CANDS_CTL0_(954)+chn_offset,  f0_timing->TDFI_CALVL_RESP);
	__raw_writel(CANDS_CTL0_(955)+chn_offset,  f0_timing->TDFI_CALVL_MAX);
	__raw_writel(CANDS_CTL0_(957)+chn_offset, (f0_timing->TDFI_RDCSLAT<<24)|(f0_timing->TDFI_PHY_WRDATA<<16)|(f0_timing->CALVL_INTERVAL));
	__raw_writel(CANDS_CTL0_(958)+chn_offset, (f2_timing->TDFI_RDCSLAT<<24)|(f1_timing->TDFI_WRCSLAT<<16)|
										   (f1_timing->TDFI_RDCSLAT<<8)|f0_timing->TDFI_WRCSLAT);
	reg_bit_set(CANDS_CTL0_(959)+chn_offset,0,6,  f2_timing->TDFI_WRCSLAT);
	__raw_writel(CANDS_CTL0_(999)+chn_offset, (f3_timing->TDFI_CALVL_CAPTURE<<16)|f3_timing->TDFI_CALVL_CC);
	__raw_writel(CANDS_CTL0_(1000)+chn_offset, (f3_timing->TDFI_WRCSLAT<<8)|f3_timing->TDFI_RDCSLAT);
}

void cands_phy_slice_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T *phy_timing_info, uint32 slice_num)
{

	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	static CANDS_PHY_TIMING_T *slice_timing_f0 = NULL;
	static CANDS_PHY_TIMING_T *slice_timing_f1 = NULL;
	static CANDS_PHY_TIMING_T *slice_timing_f2 = NULL;
	static CANDS_PHY_TIMING_T *slice_timing_f3 = NULL;

	
	for(i = 0; i < 4; i++)
	{
		switch(phy_timing_info[i].freq_point)
		{
			case 0: slice_timing_f0 = &phy_timing_info[i]; break;
			case 1: slice_timing_f1 = &phy_timing_info[i]; break;
			case 2: slice_timing_f2 = &phy_timing_info[i]; break;
			case 3: slice_timing_f3 = &phy_timing_info[i]; break;
			default : break;
		}
	}

	__raw_writel(CANDS_PHY0_(0)+chn_offset+(slice_num<<8), slice_timing_f0->DEN_PHY_DQ_TIMING_REG);
	__raw_writel(CANDS_PHY0_(1)+chn_offset+(slice_num<<8), slice_timing_f0->DEN_PHY_DQS_TIMING_REG);
	__raw_writel(CANDS_PHY0_(2)+chn_offset+(slice_num<<8), slice_timing_f0->DEN_PHY_GATE_LPBK_CTRL_REG);
	__raw_writel(CANDS_PHY0_(3)+chn_offset+(slice_num<<8), slice_timing_f0->DEN_PHY_READ_CTRL_REG);
	__raw_writel(CANDS_PHY0_(4)+chn_offset+(slice_num<<8), slice_timing_f0->PHY_DLL_MASTER_CTRL_REG);
	__raw_writel(CANDS_PHY0_(5)+chn_offset+(slice_num<<8), slice_timing_f0->PHY_DLL_SLAVE_CTRL_REG);
	__raw_writel(CANDS_PHY0_(6)+chn_offset+(slice_num<<8), slice_timing_f0->DEN_PHY_IE_TIMING_REG);
  
	__raw_writel(CANDS_PHY0_(7)+chn_offset+ (slice_num<<8), slice_timing_f1->DEN_PHY_DQ_TIMING_REG);
	__raw_writel(CANDS_PHY0_(8)+chn_offset+ (slice_num<<8), slice_timing_f1->DEN_PHY_DQS_TIMING_REG);
	__raw_writel(CANDS_PHY0_(9)+chn_offset+ (slice_num<<8), slice_timing_f1->DEN_PHY_GATE_LPBK_CTRL_REG);
	__raw_writel(CANDS_PHY0_(10)+chn_offset+(slice_num<<8), slice_timing_f1->DEN_PHY_READ_CTRL_REG);
	__raw_writel(CANDS_PHY0_(11)+chn_offset+(slice_num<<8), slice_timing_f1->PHY_DLL_MASTER_CTRL_REG);
	__raw_writel(CANDS_PHY0_(12)+chn_offset+(slice_num<<8), slice_timing_f1->PHY_DLL_SLAVE_CTRL_REG);
	__raw_writel(CANDS_PHY0_(13)+chn_offset+(slice_num<<8), slice_timing_f1->DEN_PHY_IE_TIMING_REG);
                                                     
	__raw_writel(CANDS_PHY0_(14)+chn_offset+(slice_num<<8), slice_timing_f2->DEN_PHY_DQ_TIMING_REG);
	__raw_writel(CANDS_PHY0_(15)+chn_offset+(slice_num<<8), slice_timing_f2->DEN_PHY_DQS_TIMING_REG);
	__raw_writel(CANDS_PHY0_(16)+chn_offset+(slice_num<<8), slice_timing_f2->DEN_PHY_GATE_LPBK_CTRL_REG);
	__raw_writel(CANDS_PHY0_(17)+chn_offset+(slice_num<<8), slice_timing_f2->DEN_PHY_READ_CTRL_REG);
	__raw_writel(CANDS_PHY0_(18)+chn_offset+(slice_num<<8), slice_timing_f2->PHY_DLL_MASTER_CTRL_REG);
	__raw_writel(CANDS_PHY0_(19)+chn_offset+(slice_num<<8), slice_timing_f2->PHY_DLL_SLAVE_CTRL_REG);
	__raw_writel(CANDS_PHY0_(20)+chn_offset+(slice_num<<8), slice_timing_f2->DEN_PHY_IE_TIMING_REG);
	                                                   
	__raw_writel(CANDS_PHY0_(21)+chn_offset+(slice_num<<8), slice_timing_f3->DEN_PHY_DQ_TIMING_REG);
	__raw_writel(CANDS_PHY0_(22)+chn_offset+(slice_num<<8), slice_timing_f3->DEN_PHY_DQS_TIMING_REG);
	__raw_writel(CANDS_PHY0_(23)+chn_offset+(slice_num<<8), slice_timing_f3->DEN_PHY_GATE_LPBK_CTRL_REG);
	__raw_writel(CANDS_PHY0_(24)+chn_offset+(slice_num<<8), slice_timing_f3->DEN_PHY_READ_CTRL_REG);
	__raw_writel(CANDS_PHY0_(25)+chn_offset+(slice_num<<8), slice_timing_f3->PHY_DLL_MASTER_CTRL_REG);
	__raw_writel(CANDS_PHY0_(26)+chn_offset+(slice_num<<8), slice_timing_f3->PHY_DLL_SLAVE_CTRL_REG);
	__raw_writel(CANDS_PHY0_(27)+chn_offset+(slice_num<<8), slice_timing_f3->DEN_PHY_IE_TIMING_REG);
                                                     
	__raw_writel(CANDS_PHY0_(33)+chn_offset+(slice_num<<8), slice_timing_f0->PHY_LVL_CONFIG_REG);
	__raw_writel(CANDS_PHY0_(34)+chn_offset+(slice_num<<8), slice_timing_f1->PHY_LVL_CONFIG_REG);
	__raw_writel(CANDS_PHY0_(35)+chn_offset+(slice_num<<8), slice_timing_f2->PHY_LVL_CONFIG_REG);
	__raw_writel(CANDS_PHY0_(36)+chn_offset+(slice_num<<8), slice_timing_f3->PHY_LVL_CONFIG_REG);	
                                                     
	__raw_writel(CANDS_PHY0_(39)+chn_offset+(slice_num<<8), slice_timing_f0->PHY_WRLVL_CONFIG_REG);
	__raw_writel(CANDS_PHY0_(40)+chn_offset+(slice_num<<8), slice_timing_f1->PHY_WRLVL_CONFIG_REG);
	__raw_writel(CANDS_PHY0_(41)+chn_offset+(slice_num<<8), slice_timing_f2->PHY_WRLVL_CONFIG_REG);
	__raw_writel(CANDS_PHY0_(42)+chn_offset+(slice_num<<8), slice_timing_f3->PHY_WRLVL_CONFIG_REG);	
	
}

void cands_phy_core_init(DDR_CHANNEL_NUM_E chn_num,CANDS_PHY_TIMING_T  *phy_timing_info)
{
	uint32 i = 0;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	static CANDS_PHY_TIMING_T *core_timing_f0 = NULL;
	static CANDS_PHY_TIMING_T *core_timing_f1 = NULL;
	static CANDS_PHY_TIMING_T *core_timing_f2 = NULL;
	static CANDS_PHY_TIMING_T *core_timing_f3 = NULL;
	
	for(i = 0; i < 4; i++)
	{
		switch(phy_timing_info[i].freq_point)
		{
			case 0: core_timing_f0 = &phy_timing_info[i]; break;
			case 1: core_timing_f1 = &phy_timing_info[i]; break;
			case 2: core_timing_f2 = &phy_timing_info[i]; break;
			case 3: core_timing_f3 = &phy_timing_info[i]; break;
			default : break;
		}
	}

	__raw_writel(CANDS_PHY0_(320)+chn_offset, 0); //PHY_FREQ_SEL
	__raw_writel(CANDS_PHY0_(321)+chn_offset, core_timing_f0->DEN_PHY_CTRL_REG);
	__raw_writel(CANDS_PHY0_(322)+chn_offset, core_timing_f0->DEN_PHY_DESKEW_CTRL_REG);
	__raw_writel(CANDS_PHY0_(323)+chn_offset, core_timing_f1->DEN_PHY_CTRL_REG);
	__raw_writel(CANDS_PHY0_(324)+chn_offset, core_timing_f1->DEN_PHY_DESKEW_CTRL_REG);
	__raw_writel(CANDS_PHY0_(325)+chn_offset, core_timing_f2->DEN_PHY_CTRL_REG);
	__raw_writel(CANDS_PHY0_(326)+chn_offset, core_timing_f2->DEN_PHY_DESKEW_CTRL_REG);
	__raw_writel(CANDS_PHY0_(327)+chn_offset, core_timing_f3->DEN_PHY_CTRL_REG);
	__raw_writel(CANDS_PHY0_(328)+chn_offset, core_timing_f3->DEN_PHY_DESKEW_CTRL_REG);
	__raw_writel(CANDS_PHY0_(329)+chn_offset, core_timing_f0->DEN_PHY_DESKEW_BYPASS_REG);
	__raw_writel(CANDS_PHY0_(331)+chn_offset, core_timing_f0->DEN_PHY_CALVL_CTRL_REG);
	__raw_writel(CANDS_PHY0_(333)+chn_offset, core_timing_f0->DEN_PHY_LP_WAKEUP_REG);
	__raw_writel(CANDS_PHY0_(334)+chn_offset, core_timing_f0->DEN_PHY_PAD_TSEL_REG);
	__raw_writel(CANDS_PHY0_(335)+chn_offset, core_timing_f0->PHY_PAD_DRIVE_REG_0);
	__raw_writel(CANDS_PHY0_(336)+chn_offset, core_timing_f0->PHY_PAD_DRIVE_REG_1);
	__raw_writel(CANDS_PHY0_(337)+chn_offset, core_timing_f0->PHY_PAD_DRIVE_REG_2);
	__raw_writel(CANDS_PHY0_(338)+chn_offset, core_timing_f0->PHY_PAD_TERM_REG_0);
	__raw_writel(CANDS_PHY0_(339)+chn_offset, core_timing_f0->PHY_PAD_CAL_CTRL_REG0);
	__raw_writel(CANDS_PHY0_(341)+chn_offset, core_timing_f0->PHY_PAD_ATB_CTRL_REG_AC |
	                                          core_timing_f0->PHY_PAD_VREF_CTRL_REG_AC);	                                          
	__raw_writel(CANDS_PHY0_(342)+chn_offset, core_timing_f0->PHY_CDN_CAL_INTERVAL_REG_AC_0);
	__raw_writel(CANDS_PHY0_(343)+chn_offset, core_timing_f0->PHY_CDN_CAL_INTERVAL_REG_AC_1);
	
}


void cands_phy_ds_init(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
#if 0
    //dq
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 20, 1, 0); //read dq odt off
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 25, 1, 0); //write dq odt off
//    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 21, 4, DDR_DS);//read odt/drv val
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 21, 4, LPDDR3_DS_HZ);//read odt/drv val
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 26, 4, DDR_DS);//write drv


    //dqs
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 10, 1, 0); //read dqs odt off
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 15, 1, 0); //write dqs odt off
//    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 11, 4, DDR_DS);    //read dqs drv        
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 11, 4, LPDDR3_DS_HZ);    //read dqs drv            
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 16, 4, DDR_DS);    //write dqs drv
    reg_bit_set(CANDS_PHY0_(335)+chn_offset, 29, 1, 1);    //dqs rpull 


    //dm
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 0, 1, 0);   //read dm odt off 
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 5, 1, 0);   //write dm odt off  
//    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 1, 4, DDR_DS);    //read dm ds
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 1, 4, LPDDR3_DS_HZ);    //read dm ds
    reg_bit_set(CANDS_PHY0_(334)+chn_offset, 6, 4, DDR_DS);     //write dm ds

    //dq/dqs/dm POD & RPULL off
    REG32(CANDS_PHY0_(335)+chn_offset) = 0;
#endif
    //clk ds
    reg_bit_set(CANDS_PHY0_(336)+chn_offset, 31, 1, 1);    //pod off
    reg_bit_set(CANDS_PHY0_(336)+chn_offset, 28, 1, 1);    //rpull off
    reg_bit_set(CANDS_PHY0_(336)+chn_offset, 16, 4, DDR_DS);//nmos
    reg_bit_set(CANDS_PHY0_(336)+chn_offset, 20, 4, DDR_DS);//pmos
#if 0
    //ca ds
    reg_bit_set(CANDS_PHY0_(336)+chn_offset, 15, 1, 0);    //pod off
    reg_bit_set(CANDS_PHY0_(336)+chn_offset, 4, 4, DDR_DS);
    reg_bit_set(CANDS_PHY0_(336)+chn_offset, 0, 4, DDR_DS);

    //input feedback
    reg_bit_set(CANDS_PHY0_(337)+chn_offset, 31, 1, 0);//pod off
    reg_bit_set(CANDS_PHY0_(337)+chn_offset, 20, 4, DDR_DS);
    reg_bit_set(CANDS_PHY0_(337)+chn_offset, 16, 4, DDR_DS);    

    //input and output feedback and lpbk_dqs pads
    reg_bit_set(CANDS_PHY0_(337)+chn_offset, 15, 1, 0);//pod off
    reg_bit_set(CANDS_PHY0_(337)+chn_offset, 4, 4, DDR_DS);
    reg_bit_set(CANDS_PHY0_(337)+chn_offset, 0, 4, DDR_DS); 
#endif
	
}

void cands_ctl_basicmode_init(DDR_CHANNEL_NUM_E chn_num)
{	
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//ddr type
	if(IS_LPDDR3(DDR_TYPE))
	{
		reg_bit_set(CANDS_CTL0_(0)+chn_offset,8,4, 0x7);
	}
	else if(IS_LPDDR2(DDR_TYPE))
	{
		reg_bit_set(CANDS_CTL0_(0)+chn_offset,8,4,0x5);
	}
	else if(IS_DDR3(DDR_TYPE))
	{
		reg_bit_set(CANDS_CTL0_(0)+chn_offset,8,4,0x6);
	}
	else
	{
		//not lpddr3,lpddr2,ddr3,  error ddr type, hold
		while(1);
	}

	reg_bit_set(CANDS_CTL0_(27)+chn_offset,24,1,0x0);  //no_auto_mrr_init disable,mr8 and mr11 will be auto read out durining init
	reg_bit_set(CANDS_CTL0_(33)+chn_offset,24,3,0x4);  //DRAM burst interrupt interval in cycle, n-1
	reg_bit_set(CANDS_CTL0_(45)+chn_offset, 8,1,0x0);  //write burst interrupt with one read command, set 1 to allow
	reg_bit_set(CANDS_CTL0_(49)+chn_offset,24,0,0x1);  //tras_lock, allow excute auto-percharge before tras_min_fn_x is expired, should check!!!!
	reg_bit_set(CANDS_CTL0_(49)+chn_offset,16,1,0x0);  //concurrent auto-percharge,should check!!!!  memory should support if set 1
	reg_bit_set(CANDS_CTL0_(49)+chn_offset, 8,1,0x0);  //auto-percharge enable,should check!!!!disable???

	//bl
	reg_bit_set(CANDS_CTL0_(50)+chn_offset,24,3,(DDR_BL==8)?3:2);//DDR burst length, 1:bl2 2:bl4 3:bl8
	
	__raw_writel(CANDS_CTL0_(51)+chn_offset, 0x0); //DIMM operation support,only for DDR3
	__raw_writel(CANDS_CTL0_(52)+chn_offset, 0x100); //bit8: optimized RMODW logic enable,for which purpose??? should check

	


	__raw_writel(CANDS_CTL0_(65)+chn_offset, (1<<16) | //interrupt memory initialization to enter self-refresh, set 1 to enable, should check!!!
	                                 	  (0<<8)  | //disable auto refresh request associated with self-refresh exit, should check!!!
	                                 	  (0<<0));   //allow powerup via self-refresh instead of full memory initialization,set 1 to enable,should check!!!
	//dll off when frequency change                      
	reg_bit_set(CANDS_CTL0_(75)+chn_offset,16,4,0); //dll off when frequency change, bit0 for f0, bit1 for f1, bit2 for f2, bit3 for f3
	                                             //should check!!! I think f0=166M can dll off
	//hardware frequency change enable
	reg_bit_set(CANDS_CTL0_(75)+chn_offset, 8,1,1); 

	//phy resiter write during frequency change
	reg_bit_set(CANDS_CTL0_(78)+chn_offset,24,1,1); //phy register write enable durinig frequency change,set 1 to enable
	__raw_writel(CANDS_CTL0_(79)+chn_offset, 0x540); //register address enalbe which will be written during frequency change
	                                        //should check!!!I think should write PHY_FREQ_SEL when ctl frequency change
	__raw_writel(CANDS_CTL0_(80)+chn_offset, 0x0); //data write to PHY_FREQ_SEL if ctl frequency change to f0
	__raw_writel(CANDS_CTL0_(81)+chn_offset, 0x1); //data write to PHY_FREQ_SEL if ctl frequency change to f1
	__raw_writel(CANDS_CTL0_(82)+chn_offset, 0x2); //data write to PHY_FREQ_SEL if ctl frequency change to f2
	__raw_writel(CANDS_CTL0_(979)+chn_offset, 0x3); //data write to PHY_FREQ_SEL if ctl frequency change to f3	
	__raw_writel(CANDS_CTL0_(83)+chn_offset, 0x0); //data write mask to PHY_FREQ_SEL if ctl frequency change

	//mr4 count period
	reg_bit_set(CANDS_CTL0_(88)+chn_offset, 16, 16, 0); //number of long count between periodic read MR4,set 0 to disable,
	                                      			 //can't open until training done	
	//long count period
	reg_bit_set(CANDS_CTL0_(111)+chn_offset, 0, 5, 0); //long count period, 0:1024clk 0x10:512clk 0x18:256clk 0x1c:128clk 0x1e:64clk 0x1f:32clk

	//zq
	reg_bit_set(CANDS_CTL0_(116)+chn_offset, 8, 4, 2); //zq calibration type when exit self-refresh, bit0:zqcs, bit1:zqcl, bit2:zqinit, bit3:zqrst
	__raw_writel(CANDS_CTL0_(120)+chn_offset, (1<<8) | //zqcs to all cs when set 1
		                 			       (ZQINIT_DIS<<0));  //disable ZQ during initialization, set 0 to enable

	//auto-precharge bit
	__raw_writel(CANDS_CTL0_(121)+chn_offset, (0xA<<24));// auto-precharge bit in dram address

	//lpddr2-s4, reduc, burst-on-fly bit, cs map
	__raw_writel(CANDS_CTL0_(126)+chn_offset, (IS_LPDDR2(DDR_TYPE)<<24) | //LPDDR2-S4
	                       			  	   (0<<16) | //REDUC, eanble half-datapath of controller,set 1 to enable,should check!!!
	                       			       (IS_DDR3(DDR_TYPE)<<8)  | //burst-on-fly bit, only used when DDR3, other should set to 0,should check!!! different from changsheng code
	                                       (IS_2CS(DDR_TYPE)?3:1));   //cs map
	                       
	__raw_writel(CANDS_CTL0_(128)+chn_offset, (1<<24) | //automatic controller initiated update enable
	                                       (0<<16) | //dfi controller-initiated update,wirte 1 to trigger
	                                       (0<<0));   //determid if controller can re-order write command from same id or port

	//1T timing
	reg_bit_set(CANDS_CTL0_(959)+chn_offset, 8, 1, 1); //1T timing enable, only used when LPDDR2&LPDDR3

	//DRAM CLK DISABLE
	reg_bit_set(CANDS_CTL0_(925)+chn_offset, 8, 2, 0);//dfi_dram_clk_disable,bit0:cs0  bit1:cs1, set 1 to disable,should check!!!
	
	return;
}
void cands_ctl_addmap_init(DDR_CHANNEL_NUM_E chn_num,DRAM_TYPE_E ddr_type)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;
	volatile uint32 row_cs0 = 0;
	volatile uint32 row_cs1 = 0;
	volatile uint32 col_cs0 = 0;
	volatile uint32 col_cs1 = 0;	
	volatile uint32 cs_val_0 = 0;
	volatile uint32 cs_val_1 = 0;
	volatile uint32 cs_mask_0 = 0x7fff;
	volatile uint32 cs_mask_1 = 0x7fff;
	volatile uint32 row_diff_0 = 0;
	volatile uint32 row_diff_1 = 0;
	volatile uint32 col_diff_0 = 0;
	volatile uint32 col_diff_1 = 0;
	volatile uint32 i = 0;
	
	if(IS_LPDDR3(ddr_type))
	{
		if(IS_2CS(ddr_type))
		{
			switch((ddr_type&0xff000)>>12)
			{
				case 0x8:  row_cs0 = 14; col_cs0 = 10; row_cs1 = 14; col_cs1 = 10; break;
				case 0x12: row_cs0 = 15; col_cs0 = 10; row_cs1 = 14; col_cs1 = 10; break;
				case 0x16: row_cs0 = 15; col_cs0 = 10; row_cs1 = 15; col_cs1 = 10; break;
				default: row_cs0 = 14; col_cs0 = 10; row_cs1 = 14; col_cs1 = 10; break;
			}		
		}
		else
		{
			row_cs1 = 0;
			col_cs1 = 0;

			switch((ddr_type&0xff000)>>12)
			{
				case 0x4:  row_cs0 = 14; col_cs0 = 10; break;
				case 0x6:  row_cs0 = 15; col_cs0 = 10; break;
				case 0x8:  row_cs0 = 15; col_cs0 = 10; break;
				case 0x12: row_cs0 = 15; col_cs0 = 11; break;
				case 0x16: row_cs0 = 15; col_cs0 = 11; break;
				default: row_cs0 = 14; col_cs0 = 10; break;
			}
		
		}
	}
    else
	{
		if(IS_2CS(ddr_type))
		{
			switch((ddr_type&0xff000)>>12)
			{
				case 0x4:  row_cs0 = 14; col_cs0 = 9;  row_cs1 = 14; col_cs1 = 9; break;
				case 0x6:  row_cs0 = 14; col_cs0 = 10; row_cs1 = 14; col_cs1 = 9; break;
				case 0x8:  row_cs0 = 14; col_cs0 = 10; row_cs1 = 14; col_cs1 = 10; break;
				case 0x12: row_cs0 = 15; col_cs0 = 10; row_cs1 = 14; col_cs1 = 10; break;
				case 0x16: row_cs0 = 15; col_cs0 = 10; row_cs1 = 15; col_cs1 = 10; break;
				default: row_cs0 = 14; col_cs0 = 10; row_cs1 = 14; col_cs1 = 10; break;
			}		
		}
		else
		{
			row_cs1 = 0;
			col_cs1 = 0;

			switch((ddr_type&0xff000)>>12)
			{
				case 0x2:  row_cs0 = 14; col_cs0 = 9; break;			
				case 0x4:  row_cs0 = 14; col_cs0 = 10; break;
				case 0x8:  row_cs0 = 15; col_cs0 = 10; break;
				default: row_cs0 = 14; col_cs0 = 10; break;
			}
		
		}
	}


	row_diff_0 = 16-row_cs0;
	row_diff_1 = 16-row_cs1;

	col_diff_0 = 12-col_cs0;
	col_diff_1 = 12-col_cs1;
	

	//caluate cs_mask_0 value
	for(i = 0; i < (row_diff_0+col_diff_0); i++)
	{
		cs_mask_0 = cs_mask_0 >> 1;
	}

	//caluate cs_mask_1 value
	if(IS_2CS(ddr_type))
	{
		for(i = 0; i < (row_diff_1+col_diff_1); i++)
		{
			cs_mask_1 = cs_mask_1 >> 1;
		}
	}
	
	//caluate cs_val_1
	cs_val_1 = cs_val_0+cs_mask_0+1;
	
	__raw_writel(CANDS_CTL0_(987)+chn_offset, (row_diff_1<<24) | //row diff 1
		                        		   (row_diff_0<<16) | //row diff 0
		                                   (0<<16) |  //bank diff 1
		                                   (0<<16));   //bank diff 0

	__raw_writel(CANDS_CTL0_(988)+chn_offset, (cs_val_0<<16) 	| //cs value 0
		                                   (col_diff_1<<8) | //column diff 1
		                                   (col_diff_0));   //column diff 0

						   
	__raw_writel(CANDS_CTL0_(989)+chn_offset, (cs_mask_0<<16) 	| //cs mask 0
						                   (cs_val_1));        //cs value 1

	reg_bit_set(CANDS_CTL0_(990)+chn_offset,0,16, cs_mask_1);
}

void cands_ctl_odtmode_init(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	__raw_writel(CANDS_CTL0_(148)+chn_offset, (2<<24) | //write odt enable on cs1
		                                   (2<<16) | //read odt enable on cs1
		                                   (1<<8)  | //write odt enable on cs0
		                                   (1<<0));   //read odt enable on cs0

	reg_bit_set(CANDS_CTL0_(990)+chn_offset, 24, 1, 0);//f3 odt enable
	reg_bit_set(CANDS_CTL0_(150)+chn_offset, 24, 1, 0);//f2 odt enable
	reg_bit_set(CANDS_CTL0_(150)+chn_offset, 16, 1, 0);//f1 odt enable
	reg_bit_set(CANDS_CTL0_(150)+chn_offset,  8, 1, 0);//f0 odt enable
	
	//reg_bit_set(CANDS_CTL0_(151)+chn_offset,  0, 1, IS_LPDDR3(DDR_TYPE));//assert ODT at all times except during read,only used when LPDDR3
    reg_bit_set(CANDS_CTL0_(151)+chn_offset,  0, 1, 0);//assert ODT at all times except during read,only used when LPDDR3	
}

void cands_ctl_lvlmode_init(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//CA training
	__raw_writel(CANDS_CTL0_(169)+chn_offset, (0<<8) | //ca training cs chip select
	                                       (0<<0));  //ca training trigger

	__raw_writel(CANDS_CTL0_(170)+chn_offset, 0x000556aa); //ca training pattern0
	__raw_writel(CANDS_CTL0_(171)+chn_offset, 0x000aa955); //ca training pattern0 before and after calibration command
	__raw_writel(CANDS_CTL0_(172)+chn_offset, 0x000aa955); //ca training pattern1
	__raw_writel(CANDS_CTL0_(173)+chn_offset, 0x000556aa); //ca training pattern1 before and after calibration command
	__raw_writel(CANDS_CTL0_(174)+chn_offset, 0x000556aa); //ca training pattern2
	__raw_writel(CANDS_CTL0_(175)+chn_offset, 0x000aa955); //ca training pattern2 before and after calibration command
	__raw_writel(CANDS_CTL0_(176)+chn_offset, 0x000aa955); //ca training pattern3
	__raw_writel(CANDS_CTL0_(177)+chn_offset, 0x000556aa); //ca training pattern3 before and after calibration command

	__raw_writel(CANDS_CTL0_(178)+chn_offset, (0<<24) | //enable periodic ca training
		                                   (1<<16) | //PHy support for dfi CA training 
		                                   (3<<8));   //ca training pattern, 3 for all pattern

	__raw_writel(CANDS_CTL0_(179)+chn_offset, ((IS_2CS(DDR_TYPE)?3:1)<<24) | //cs map for ca training
		                                   (0<<16) | //ca training cs rotate
		                                   (1<<8)  | //automatic refresh and non data command during CA training
		                                   (0));      //automatic ca training when exit self-refresh
	reg_bit_set(CANDS_CTL0_(956)+chn_offset, 8, 1, CALVL_EN);//MC ca training enable,should check!!!
	reg_bit_set(CANDS_CTL0_(956)+chn_offset, 0, 1, 0);//dfi_calvl_training signal mask durining ca training

	//write leveling
	__raw_writel(CANDS_CTL0_(161)+chn_offset, (0x28<<24) |// delay from issuing MRS to first write leveling mode
	                                       (0xd<<16)  |// delay from issuing MRS to first DQS strobe for write leveling mode
	                                       (0x0<<8));   // cs map for write leveling

	__raw_writel(CANDS_CTL0_(162)+chn_offset, (1<<24) | //PHY support for DFI write leveling, set 1 to enable
	                                       (0<<8)  | //long counter between automatic write leveling
	                                       (WRLVL_EN<<0));   //write leveling enable
	__raw_writel(CANDS_CTL0_(163)+chn_offset, (1<<24) | //auto-refresh and other non-data command in middle of write leveling
	                                       (0<<16) | //mask for dfi_wlvl_resp signal during write leveling
	                                       (0<<8)  | //automatic write leveling when exit self-refresh
	                                       (0<<0));   //periodic write leveling enable
	reg_bit_set(CANDS_CTL0_(164)+chn_offset, 8, 2, IS_2CS(DDR_TYPE)?3:1); //write leveling cs map,should check!!!different with 161???
	reg_bit_set(CANDS_CTL0_(164)+chn_offset, 0, 1, 0); //write leveling cs rotate

	//read gate & data eye training
	__raw_writel(CANDS_CTL0_(165)+chn_offset, (0<<24) | //read gate training pattern
	                                       (0<<16) | //read data eye training pattern
	                                       (0<<8)  | //read leveling cs select
	                                       (0<<0));   //read gate training trigger

	__raw_writel(CANDS_CTL0_(166)+chn_offset, (0<<24) | //read data eye training enable when exit self refresh
	                                       (0<<16) | //periodic read data eye training enable
	                                       (1<<8)  | //PHY support for dfi gate training
	                                       (1<<0));   //PHY support for dfi data eye training

	__raw_writel(CANDS_CTL0_(167)+chn_offset, (1<<16) | //auto-refresh enable during data eye or gate training
	                                       (0<<8)  | //read gate training enable when exit self refresh
	                                       (0<<0));   //periodic read gate training enable

	__raw_writel(CANDS_CTL0_(168)+chn_offset, ((IS_2CS(DDR_TYPE)?3:1)<<24) | //gate training chip select map
	                                       ((IS_2CS(DDR_TYPE)?3:1)<<16) | //data eye training chip select map
	                                       (0<<8) |   //read gate training cs rotate
	                                       (0<<0));    //read eye training cs rotate

	__raw_writel(CANDS_CTL0_(947)+chn_offset, (RDGLVL_EN<<16) | //enable MC gate training module, set 0 to dsiable, should check!!!
		                                   (RDELVL_EN<<8)  | //enable Mc data training module, set 0 to disable, should check!!!
		                                   (0<<0));   //mask for dfi_rdlvl_resp signale during data eye training

		                   

}
void cands_ctl_qos_init(DDR_CHANNEL_NUM_E chn_num,CANDS_QOS_T * port_info)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

    //addr_cmp_en
    reg_bit_set(CANDS_CTL0_(122)+chn_offset, 16, 1, 1);
    //age_count
    reg_bit_set(CANDS_CTL0_(122)+chn_offset,  0, 8, 0xff);
    //command_age_count
    reg_bit_set(CANDS_CTL0_(122)+chn_offset,  8, 8, 0xff);
    
    //bank_split_en
    reg_bit_set(CANDS_CTL0_(123)+chn_offset,   0, 1, 1);
    //placement_en
    reg_bit_set(CANDS_CTL0_(123)+chn_offset,   8, 1, 1);
    //priority_en
    reg_bit_set(CANDS_CTL0_(123)+chn_offset,  16, 1, 1);
    //rw_same_en
    reg_bit_set(CANDS_CTL0_(123)+chn_offset,  24, 1, 1);

    //rw_same_page_en
    reg_bit_set(CANDS_CTL0_(124)+chn_offset,   0, 1, 1);
    //cs_same_en
    reg_bit_set(CANDS_CTL0_(124)+chn_offset,   8, 1, 1);
    //w2r_split_en
    reg_bit_set(CANDS_CTL0_(124)+chn_offset,  16, 1, 1);    
    //disable_rw_group_w_bnk_conflict
    reg_bit_set(CANDS_CTL0_(124)+chn_offset,  24, 2, 1);

    //num_q_entries_act_disable
    reg_bit_set(CANDS_CTL0_(125)+chn_offset,   0, 5, 0);    
    //swap_en
    reg_bit_set(CANDS_CTL0_(125)+chn_offset,   8, 1, 1);
    //disable_rd_interleave
    reg_bit_set(CANDS_CTL0_(125)+chn_offset,  16, 1, 0);
    //inhibit_dram_cmd
    reg_bit_set(CANDS_CTL0_(125)+chn_offset,  24, 2, 0);

    //memdata_ratio_X
    reg_bit_set(CANDS_CTL0_(127)+chn_offset,   0, 3, 0);
    //memdata_ratio_X
    reg_bit_set(CANDS_CTL0_(127)+chn_offset,   8, 3, 0);    
    //q_fullness
    reg_bit_set(CANDS_CTL0_(127)+chn_offset,  16, 5, 0x1e);
    //in_order_accept
    reg_bit_set(CANDS_CTL0_(127)+chn_offset,  24, 1, 0);

    //arb_cmd_q_threshold
    reg_bit_set(CANDS_CTL0_(914)+chn_offset,  16, 5,31); //should check !!!

    //axiY_fifo_type_reg
    reg_bit_set(CANDS_CTL0_(181)+chn_offset,   0, 2, 3); //A53
    reg_bit_set(CANDS_CTL0_(182)+chn_offset,   8, 2, 3); //DISP
    reg_bit_set(CANDS_CTL0_(183)+chn_offset,  16, 2, 3); //GPU/GSP
    reg_bit_set(CANDS_CTL0_(184)+chn_offset,  24, 2, 3); //AP_NOC_MTX
    reg_bit_set(CANDS_CTL0_(186)+chn_offset,   0, 2, 3); //CAM
    reg_bit_set(CANDS_CTL0_(187)+chn_offset,   8, 2, 3); //VSP
    reg_bit_set(CANDS_CTL0_(188)+chn_offset,  16, 2, 3); //LWT_DSP
    reg_bit_set(CANDS_CTL0_(189)+chn_offset,  24, 2, 3); //LWT_ACC
    reg_bit_set(CANDS_CTL0_(191)+chn_offset,   0, 2, 3); //AUD CP    
    reg_bit_set(CANDS_CTL0_(192)+chn_offset,   8, 2, 3); //PUB CP    
    //axiY_address_range_enable
    reg_bit_set(CANDS_CTL0_(192)+chn_offset,  24, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(193)+chn_offset,   0, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(193)+chn_offset,   8, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(193)+chn_offset,  16, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(193)+chn_offset,  24, 1, 0); //should check !!!    
    reg_bit_set(CANDS_CTL0_(194)+chn_offset,   0, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(194)+chn_offset,   8, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(194)+chn_offset,  16, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(194)+chn_offset,  24, 1, 0); //should check !!!
    reg_bit_set(CANDS_CTL0_(195)+chn_offset,   0, 1, 0); //should check !!!
    //axiY_all_strobes_used_enable
    reg_bit_set(CANDS_CTL0_(180)+chn_offset,   0, 1, port_info[0].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(181)+chn_offset,   8, 1, port_info[1].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(182)+chn_offset,  16, 1, port_info[2].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(183)+chn_offset,  24, 1, port_info[3].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(185)+chn_offset,   0, 1, port_info[4].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(186)+chn_offset,   8, 1, port_info[5].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(187)+chn_offset,  16, 1, port_info[6].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(188)+chn_offset,  24, 1, port_info[7].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(190)+chn_offset,   0, 1, port_info[8].ALL_STRB_EN);
    reg_bit_set(CANDS_CTL0_(191)+chn_offset,   8, 1, port_info[9].ALL_STRB_EN);
    //axiY_bdw
    reg_bit_set(CANDS_CTL0_(914)+chn_offset,  24, 7, port_info[0].BDW); //A53     128
    reg_bit_set(CANDS_CTL0_(915)+chn_offset,  16, 7, port_info[1].BDW); //DISP    64
    reg_bit_set(CANDS_CTL0_(916)+chn_offset,   8, 7, port_info[2].BDW); //GPU/GSP 128
    reg_bit_set(CANDS_CTL0_(917)+chn_offset,   0, 7, port_info[3].BDW); //AP_NOC_MTX 64
    reg_bit_set(CANDS_CTL0_(917)+chn_offset,  24, 7, port_info[4].BDW); //CAM     64
    reg_bit_set(CANDS_CTL0_(918)+chn_offset,  16, 7, port_info[5].BDW); //VSP     128
    reg_bit_set(CANDS_CTL0_(919)+chn_offset,   8, 7, port_info[6].BDW); //LWT_DSP 64
    reg_bit_set(CANDS_CTL0_(920)+chn_offset,   0, 7, port_info[7].BDW); //LWT_ACC 64
    reg_bit_set(CANDS_CTL0_(920)+chn_offset,  24, 7, port_info[8].BDW); //AUD CP  64
    reg_bit_set(CANDS_CTL0_(921)+chn_offset,  16, 7, port_info[9].BDW); //PUB CP  64
    //axiY_bdw_overflow
    reg_bit_set(CANDS_CTL0_(915)+chn_offset,   0, 1, port_info[0].BDW_OVFL); //A53     128
    reg_bit_set(CANDS_CTL0_(915)+chn_offset,  24, 1, port_info[1].BDW_OVFL); //DISP    64
    reg_bit_set(CANDS_CTL0_(916)+chn_offset,  16, 1, port_info[2].BDW_OVFL); //GPU/GSP 128
    reg_bit_set(CANDS_CTL0_(917)+chn_offset,   8, 1, port_info[3].BDW_OVFL); //AP_NOC_MTX 64
    reg_bit_set(CANDS_CTL0_(918)+chn_offset,   0, 1, port_info[4].BDW_OVFL); //CAM     64
    reg_bit_set(CANDS_CTL0_(918)+chn_offset,  24, 1, port_info[5].BDW_OVFL); //VSP     128
    reg_bit_set(CANDS_CTL0_(919)+chn_offset,  16, 1, port_info[6].BDW_OVFL); //LWT_DSP 64
    reg_bit_set(CANDS_CTL0_(920)+chn_offset,   8, 1, port_info[7].BDW_OVFL); //LWT_ACC 64
    reg_bit_set(CANDS_CTL0_(921)+chn_offset,   0, 1, port_info[8].BDW_OVFL); //AUD CP  64
    reg_bit_set(CANDS_CTL0_(921)+chn_offset,  24, 1, port_info[9].BDW_OVFL); //PUB CP  64
    //axiY_fixed_port_priority_enable
    reg_bit_set(CANDS_CTL0_(180)+chn_offset,   8, 1, port_info[0].FIX_EN); //A53
    reg_bit_set(CANDS_CTL0_(181)+chn_offset,  16, 1, port_info[1].FIX_EN); //DISP
    reg_bit_set(CANDS_CTL0_(182)+chn_offset,  24, 1, port_info[2].FIX_EN); //GPU/GSP
    reg_bit_set(CANDS_CTL0_(184)+chn_offset,   0, 1, port_info[3].FIX_EN); //AP_NOC_MTX
    reg_bit_set(CANDS_CTL0_(185)+chn_offset,   8, 1, port_info[4].FIX_EN); //CAM
    reg_bit_set(CANDS_CTL0_(186)+chn_offset,  16, 1, port_info[5].FIX_EN); //VSP
    reg_bit_set(CANDS_CTL0_(187)+chn_offset,  24, 1, port_info[6].FIX_EN); //LWT_DSP
    reg_bit_set(CANDS_CTL0_(189)+chn_offset,   0, 1, port_info[7].FIX_EN); //LWT_ACC
    reg_bit_set(CANDS_CTL0_(190)+chn_offset,   8, 1, port_info[8].FIX_EN); //AUD CP
    reg_bit_set(CANDS_CTL0_(191)+chn_offset,  16, 1, port_info[9].FIX_EN); //PUB CP
    //axiY_r_priority
    reg_bit_set(CANDS_CTL0_(180)+chn_offset,  16, 4, port_info[0].RD_PRIORITY); //A53
    reg_bit_set(CANDS_CTL0_(181)+chn_offset,  24, 4, port_info[1].RD_PRIORITY); //DISP
    reg_bit_set(CANDS_CTL0_(183)+chn_offset,   0, 4, port_info[2].RD_PRIORITY); //GPU/GSP
    reg_bit_set(CANDS_CTL0_(184)+chn_offset,   8, 4, port_info[3].RD_PRIORITY); //AP_NOC_MTX
    reg_bit_set(CANDS_CTL0_(185)+chn_offset,  16, 4, port_info[4].RD_PRIORITY); //CAM
    reg_bit_set(CANDS_CTL0_(186)+chn_offset,  24, 4, port_info[5].RD_PRIORITY); //VSP
    reg_bit_set(CANDS_CTL0_(188)+chn_offset,   0, 4, port_info[6].RD_PRIORITY); //LWT_DSP
    reg_bit_set(CANDS_CTL0_(189)+chn_offset,   8, 4, port_info[7].RD_PRIORITY); //LWT_ACC
    reg_bit_set(CANDS_CTL0_(190)+chn_offset,  16, 4, port_info[8].RD_PRIORITY); //AUD CP
    reg_bit_set(CANDS_CTL0_(191)+chn_offset,  24, 4, port_info[9].RD_PRIORITY); //PUB CP
    //axiY_w_priority
    reg_bit_set(CANDS_CTL0_(180)+chn_offset,  24, 4, port_info[0].WR_PRIORITY); //A53
    reg_bit_set(CANDS_CTL0_(182)+chn_offset,   0, 4, port_info[1].WR_PRIORITY); //DISP
    reg_bit_set(CANDS_CTL0_(183)+chn_offset,   8, 4, port_info[2].WR_PRIORITY); //GPU/GSP
    reg_bit_set(CANDS_CTL0_(184)+chn_offset,  16, 4, port_info[3].WR_PRIORITY); //AP_NOC_MTX
    reg_bit_set(CANDS_CTL0_(185)+chn_offset,  24, 4, port_info[4].WR_PRIORITY); //CAM
    reg_bit_set(CANDS_CTL0_(187)+chn_offset,   0, 4, port_info[5].WR_PRIORITY); //VSP
    reg_bit_set(CANDS_CTL0_(188)+chn_offset,   8, 4, port_info[6].WR_PRIORITY); //LWT_DSP
    reg_bit_set(CANDS_CTL0_(189)+chn_offset,  16, 4, port_info[7].WR_PRIORITY); //LWT_ACC
    reg_bit_set(CANDS_CTL0_(190)+chn_offset,  24, 4, port_info[8].WR_PRIORITY); //AUD CP
    reg_bit_set(CANDS_CTL0_(192)+chn_offset,   0, 4, port_info[9].WR_PRIORITY); //PUB CP
    	
}

void cands_ctl_lpmode_init(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

    reg_bit_set(CANDS_CTL0_(66)+chn_offset, 0, 2, 0);// enable refresh while in low power mode, bit0 for cs0, bit1 for cs1

	__raw_writel(CANDS_CTL0_(71)+chn_offset, (0x3<<8) | //lpi timer counter
	                                      (1<<4)  | //LPI timer low power wakeup enable
	                                      (1<<2)  | //self-refresh with mem&ctl clock gating low power wakeup enable
	                                      (1<<1)  | //self-refresh low power wakeup enable
	                                      (1<<0));   //power-down wakeup enable

	//all auto low power function disable???should check					  
	__raw_writel(CANDS_CTL0_(73)+chn_offset, (0<<25) | //auto memory clock gate enable when self-resh
		                                  (0<<24) | //auto memory clock gate enable when power down
		                                  (0<<18) | //auto exit when self-refresh with memory and ctl clock gating
		                                  (0<<17) | //auto exit when self-refresh
		                                  (0<<16) | //auto exit when power down
		                                  (0<<10) | //auto entry when self-refresh with memory and ctl clock gating
		                                  (0<<9)  | //auto entry when self-refresh
		                                  (0<<8));   //auto entry when power down
}

//should use after ddr init to open lowpower function 
void cands_ctl_lpmode_open(DDR_CHANNEL_NUM_E chn_num)
{
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//all auto low power function disable???should check					  
	__raw_writel(CANDS_CTL0_(73)+chn_offset, (1<<25) | //auto memory clock gate enable when self-resh
		                                  (1<<24) | //auto memory clock gate enable when power down
		                                  (1<<18) | //auto exit when self-refresh with memory and ctl clock gating
		                                  (1<<17) | //auto exit when self-refresh
		                                  (1<<16) | //auto exit when power down
		                                  (1<<10) | //auto entry when self-refresh with memory and ctl clock gating
		                                  (1<<9)  | //auto entry when self-refresh
		                                  (1<<8));   //auto entry when power down
	
}
void cands_ctl_modereg_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * fx_timing,DRAM_TYPE_E ddr_type)
{
	uint32 i = 0;
	static CANDS_CTL_TIMING_T * f0_timing = NULL;
	static CANDS_CTL_TIMING_T * f1_timing = NULL;
	static CANDS_CTL_TIMING_T * f2_timing = NULL;
	static CANDS_CTL_TIMING_T * f3_timing = NULL;
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	for(i = 0; i < 4; i++)
	{
		switch(fx_timing[i].freq_point)
		{
			case 0: f0_timing = &fx_timing[i]; break;
			case 1: f1_timing = &fx_timing[i]; break;
			case 2: f2_timing = &fx_timing[i]; break;
			case 3: f3_timing = &fx_timing[i]; break;
			default : break;
		}
	}
	
	switch(DDR_DS)
	{
		case  LPDDR3_DS_34R3:
		//case  LPDDR2_DS_34R3:
			f0_timing->MR3_DATA_CSn= 1;
			f1_timing->MR3_DATA_CSn = 1;
			f2_timing->MR3_DATA_CSn = 1;
			f3_timing->MR3_DATA_CSn = 1;
			break;
		case LPDDR3_DS_40R:
		//case LPDDR2_DS_40R:
			f0_timing->MR3_DATA_CSn = 2;
			f1_timing->MR3_DATA_CSn = 2;
			f2_timing->MR3_DATA_CSn = 2;
			f3_timing->MR3_DATA_CSn = 2;
			break;
		case LPDDR3_DS_48R:
		//case LPDDR2_DS_48R:
			f0_timing->MR3_DATA_CSn = 3;
			f1_timing->MR3_DATA_CSn = 3;
			f2_timing->MR3_DATA_CSn = 3;
			f3_timing->MR3_DATA_CSn = 3;
			break;
		case LPDDR3_DS_60R:
		//case LPDDR2_DS_60R:
			f0_timing->MR3_DATA_CSn = 4;
			f1_timing->MR3_DATA_CSn = 4;
			f2_timing->MR3_DATA_CSn = 4;
			f3_timing->MR3_DATA_CSn = 4;
			break;
		case LPDDR3_DS_80R:
		//case LPDDR2_DS_80R:
			f0_timing->MR3_DATA_CSn = 6;
			f1_timing->MR3_DATA_CSn = 6;
			f2_timing->MR3_DATA_CSn = 6;
			f3_timing->MR3_DATA_CSn = 6;
			break;
		defalut:
			f0_timing->MR3_DATA_CSn = 2;
			f1_timing->MR3_DATA_CSn = 2;
			f2_timing->MR3_DATA_CSn = 2;
			f3_timing->MR3_DATA_CSn = 2;
			break;			
	}
	
	__raw_writel(CANDS_CTL0_(89)+chn_offset, (f0_timing->MR1_DATA_CSn<<16)|f0_timing->MR0_DATA_CSn);
	__raw_writel(CANDS_CTL0_(90)+chn_offset, (f1_timing->MR0_DATA_CSn<<16)|f0_timing->MR2_DATA_CSn);
	__raw_writel(CANDS_CTL0_(91)+chn_offset, (f1_timing->MR2_DATA_CSn<<16)|f1_timing->MR1_DATA_CSn);
	__raw_writel(CANDS_CTL0_(92)+chn_offset, (f2_timing->MR1_DATA_CSn<<16)|f2_timing->MR0_DATA_CSn);
	
	reg_bit_set(CANDS_CTL0_(93)+chn_offset,0,16, f2_timing->MR2_DATA_CSn);

	__raw_writel(CANDS_CTL0_(94)+chn_offset, (f1_timing->MR3_DATA_CSn<<16)|f0_timing->MR3_DATA_CSn);
	__raw_writel(CANDS_CTL0_(95)+chn_offset, (f0_timing->MR11_DATA_CSn<<24)|f2_timing->MR3_DATA_CSn);
	__raw_writel(CANDS_CTL0_(96)+chn_offset, (f2_timing->MR11_DATA_CSn<<8)|f1_timing->MR11_DATA_CSn);
	__raw_writel(CANDS_CTL0_(97)+chn_offset, (f0_timing->MR1_DATA_CSn<<16)|f0_timing->MR0_DATA_CSn);
	__raw_writel(CANDS_CTL0_(98)+chn_offset, (f1_timing->MR0_DATA_CSn<<16)|f0_timing->MR2_DATA_CSn);
	__raw_writel(CANDS_CTL0_(99)+chn_offset, (f1_timing->MR2_DATA_CSn<<16)|f1_timing->MR1_DATA_CSn);
	__raw_writel(CANDS_CTL0_(100)+chn_offset,(f2_timing->MR1_DATA_CSn<<16)|f2_timing->MR0_DATA_CSn);

	reg_bit_set(CANDS_CTL0_(101)+chn_offset,0,16, (f2_timing->MR2_DATA_CSn<<16));

	__raw_writel(CANDS_CTL0_(102)+chn_offset, (f1_timing->MR3_DATA_CSn<<16)|f0_timing->MR3_DATA_CSn);
	__raw_writel(CANDS_CTL0_(103)+chn_offset, (f0_timing->MR11_DATA_CSn<<24)|f2_timing->MR3_DATA_CSn);
	__raw_writel(CANDS_CTL0_(104)+chn_offset, (f2_timing->MR11_DATA_CSn<<8)|f1_timing->MR11_DATA_CSn);
	__raw_writel(CANDS_CTL0_(980)+chn_offset, (f3_timing->MR1_DATA_CSn<<16)|f3_timing->MR0_DATA_CSn);
	__raw_writel(CANDS_CTL0_(981)+chn_offset, (f3_timing->MR3_DATA_CSn<<16)|f3_timing->MR2_DATA_CSn);
	__raw_writel(CANDS_CTL0_(982)+chn_offset, (f3_timing->MR0_DATA_CSn<<16)|f3_timing->MR11_DATA_CSn);
	__raw_writel(CANDS_CTL0_(983)+chn_offset, (f3_timing->MR2_DATA_CSn<<16)|f3_timing->MR1_DATA_CSn);
	__raw_writel(CANDS_CTL0_(984)+chn_offset, (f3_timing->MR11_DATA_CSn<<16)|f3_timing->MR3_DATA_CSn);	
}

void cands_ctl_init(DDR_CHANNEL_NUM_E chn_num,CANDS_CTL_TIMING_T * fx_timing,CANDS_QOS_T * port_info,DRAM_TYPE_E ddr_type)
{

	//timing init
	cands_ctl_actiming_init(chn_num,fx_timing);
	cands_ctl_dfilptiming_init(chn_num,fx_timing);
	cands_ctl_odtiming_init(chn_num,fx_timing);
	cands_ctl_dfitiming_init(chn_num,fx_timing);
	cands_ctl_lvltiming_init(chn_num,fx_timing);

	//mode init
	cands_ctl_basicmode_init(chn_num);
	cands_ctl_addmap_init(chn_num,ddr_type);
	cands_ctl_odtmode_init(chn_num);
	cands_ctl_lvlmode_init(chn_num);
	cands_ctl_lpmode_init(chn_num);
	cands_ctl_modereg_init(chn_num,fx_timing,ddr_type);
	cands_ctl_qos_init(chn_num,port_info);	
}

void cands_phy_init(DDR_CHANNEL_NUM_E chn_num, CANDS_PHY_TIMING_T  *phy_timing_info)
{
	uint32 slice_num = 0;

	//step1: init phy core
	cands_phy_core_init(chn_num, phy_timing_info);

	//step2: init phy slice
	for(slice_num = PHY_SLICE0; slice_num <= PHY_SLICE4; slice_num++)
	{
		cands_phy_slice_init(chn_num, phy_timing_info,slice_num);
	}

	cands_phy_ds_init(chn_num);
}

uint32 __get_mhz_num(unsigned long ddr_clk)
{
	volatile uint32 i = 0;

	for(;;)
	{
		if(ddr_clk > 0)
		{
			ddr_clk -= 1000000;
			i++;
		}
		else
		{
			return i;
		}
	}
}

void ddr_clk_set(DDR_CHANNEL_NUM_E chn_num,unsigned int ddr_clk)
{
	volatile uint32 ddr_freq = 0;
	volatile uint32 clk_reg_val = 0;

	ddr_freq = __get_mhz_num(ddr_clk);

	//cal div value	
	switch(ddr_freq)
	{
		case 100: clk_reg_val = 0x3d;break;//dpll, 100mhz
		case 160: clk_reg_val = 0x34;break;//dpll, 160mhz
		case 192: clk_reg_val = 0x10;break;//twpll,192mhz
		case 200: clk_reg_val = 0x35;break;//dpll, 200mhz
		case 256: clk_reg_val = 0x11;break;//twpll,256mhz
		case 320: clk_reg_val = 0x14;break;//dpll, 320mhz
		case 384: clk_reg_val = 0x00;break;//twpll,384mhz
		case 400: clk_reg_val = 0x15;break;//dpll, 400mhz
		case 456: clk_reg_val = 0x03;break;//dpll, 456mhz
		case 512: clk_reg_val = 0x01;break;//twpll,512mhz
		case 533: clk_reg_val = 0x16;break;//dpll, 533mhz
		case 640: clk_reg_val = 0x04;break;//dpll, 640mhz
		case 768: clk_reg_val = 0x02;break;//twpll,768mhz
		case 800: clk_reg_val = 0x05;break;//dpll, 800mhz
		default : clk_reg_val = 0x34;
	}
	
	if(chn_num == 0)
	{
		//set dpll0 to 1600mhz
		reg_bit_set(AON_APB_DPLL0_CFG0, 0,10,0x3e);
		reg_bit_set(AON_APB_DPLL0_CFG0,20, 2,0x03);

		//set dpll0 div
		reg_bit_set(AON_APB_CGM_CFG,0,8,clk_reg_val);
	
		//enable ddr 1x/2x clk
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,15,2,3); 
	}  
	else
	{
		//disable pub1 force shutdown
		reg_bit_set(PMU_APB_PD_PUB1_SYS_CFG, 25,1,0);
		
		//set dpll1 to 1600mhz
		reg_bit_set(AON_APB_DPLL1_CFG0, 0,10,0x3e);
		reg_bit_set(AON_APB_DPLL1_CFG0,19, 2,0x03);

		//set dpll0 div
		reg_bit_set(AON_APB_CGM_CFG,16,8,clk_reg_val);
	
		//enable ddr 1x/2x clk
		reg_bit_set(AON_APB_CGM_CLK_TOP_REG1,17,2,3); 
	}
}

void ddr_init(DDR_CHANNEL_NUM_E chn_num,unsigned int ddr_clk)
{
	volatile uint32 value = 0;
	volatile uint32 i = 0;
	
	CANDS_CTL_TIMING_T  *ctl_timing_info = (CANDS_CTL_TIMING_T *)((unsigned long)__get_ctl_timing_info()); 
	CANDS_PHY_TIMING_T  *phy_timing_info = (CANDS_PHY_TIMING_T *)((unsigned long)__get_phy_timing_info());
	CANDS_QOS_T         * qos_info       = (CANDS_QOS_T *)((unsigned long)__get_qos_info());
	
	uint32 chn_offset = (chn_num==0)?0:0x00800000;

	//set ddr clk div
	ddr_clk_set(chn_num,ddr_clk);

	//ctl&phy reset release	
	cands_ctl_phy_release(chn_num);

	//wait until clk stable
	wait_10us(10);
	
	//close auto refresh
	reg_bit_set(CANDS_CTL0_(53)+chn_offset,16,1,0);
	
	//config ctl&phy regiser
	cands_ctl_init(chn_num,ctl_timing_info,qos_info,DDR_TYPE);
	cands_phy_init(chn_num,phy_timing_info);
	
	//set deskew pll bypass
	//reg_bit_set(CANDS_PHY0_(329,1);
	
	//controller init trigger
	reg_bit_set(CANDS_CTL0_(0)+chn_offset,0,1,1);
	
	//wait init finish
	i = 0;
	while((REG32(CANDS_CTL0_(130)+chn_offset)&0X10) != 0X10)
	{
	    i++;
	    //wait 1ms
	    wait_10us(100);
	    
	    if(i > 1000)
	    {
	        __ddr_print("DDR init wait done can't finish, error !!!");
	        __ddr_wdg_reset();
	    }
	};
	
	//open auto refresh
	reg_bit_set(CANDS_CTL0_(53)+chn_offset,16,1,1); //??? should check
	
}

#define DDR0_ACC_RDY    0x402b3084
#define DDR1_ACC_RDY    0x402b3088

static void prepare_for_reinit(void)
{
	reg_bit_set(DDR0_ACC_RDY,0,1,1);
	reg_bit_set(DDR1_ACC_RDY,0,1,1);
}

void sdram_init(uint32 ddr_clk)
{
	ddr_init(0,ddr_clk);
	ddr_init(1,ddr_clk);
	prepare_for_reinit();
}
