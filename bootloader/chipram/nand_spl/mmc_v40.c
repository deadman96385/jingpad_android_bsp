#include <config.h>
#include <asm/arch/sprd_reg.h>
#include <adi.h>
#include <sci_types.h>
#include "sdio_reg_r8p0.h"
#include <part.h>
#include <timer.h>

#define MMCSD_SECTOR_SIZE 512
#define EXT_CSD_SEC_CNT	212

static SDIO_Hd_Ptr	p_SdHd;
static SDIO_Handle_t	s_EmmcCtl = {0};
static SDIO_Hd_Ptr	p_EmmcHd;

static uint32 sdHighCap = FALSE;
static u32 mmc_sector = 0;

PUBLIC BOOLEAN Emmc_Read(CARD_Partition_e cardPartiton, uint32 startBlk,uint32 num,uint8* buf);

block_dev_desc_t sprd_mmc_dev;
block_dev_desc_t *mmc_get_dev()
{
	return ((block_dev_desc_t *) & sprd_mmc_dev);
}


static uint32 SCI_GetTickCount(void)
{
	return sprd_get_syscnt();
}

void SDIO_Mdelay(uint32 val)
{
	uint32 pre_tick, cur_tick;
	pre_tick = SCI_GetTickCount(); /*set start tick value*/
	cur_tick = pre_tick;
	while(cur_tick  - pre_tick < val)
	{
		cur_tick = SCI_GetTickCount();
	}
}

static uint32 SDHOST_GetDmaAddr_low (SDIO_Hd_Ptr pHd)
{
	uint32 dmaAddr;
	dmaAddr = pHd->host_cfg->EMMC_ADMA2_ADDR_L;
	return dmaAddr;
}

static uint32 SDHOST_GetDmaAddr_high (SDIO_Hd_Ptr pHd)
{
	uint32 dmaAddr;
	dmaAddr = pHd->host_cfg->EMMC_ADMA2_ADDR_H;
	return dmaAddr;
}

static void SDHOST_SetDmaAddr_low (SDIO_Hd_Ptr pHd, uint32 dmaAddr)
{
	pHd->host_cfg->EMMC_ADMA2_ADDR_L = dmaAddr;
}

static void SDHOST_SetDmaAddr_high(SDIO_Hd_Ptr pHd, uint32 dmaAddr)
{
	pHd->host_cfg->EMMC_ADMA2_ADDR_H = dmaAddr;
}
static void SetCardEvent (SDIO_Hd_Ptr pHd, uint32 EventId)
{
	pHd->card_event |= EventId;
}

static uint32 _WaitCardEvent (SDIO_Hd_Ptr pHd, uint32 EventId)
{
	if ( EventId == (pHd->card_event & EventId))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/*********************************************************************
**	Description :
**		This function used to get normal interrupt status.
**	Param :
**		pHd : emmc control handle.
**	Return :
**		msg : interrupt message.
**	Date					Author				Operation
**	2013/05/09			ypxie				optimization
*********************************************************************/
static uint32 SDHOST_GetNMLIntStatus (SDIO_Hd_Ptr pHd)
{
	volatile uint32 tmpReg;
	uint32 msg;

	tmpReg = pHd->host_cfg->INT_STA;
	msg = 0;

	if (0 != (tmpReg & BIT_15))
	{
		msg |= SIG_ERR;
	}

	if (0 != (tmpReg & BIT_8))
	{
		msg |= SIG_CARD_IN;
	}

	if (0 != (tmpReg & BIT_6))
	{
		msg |= SIG_CARD_INSERT;
	}

	if (0 != (tmpReg & BIT_7))
	{
		msg |= SIG_CARD_REMOVE;
	}

	if (0 != (tmpReg & BIT_5))
	{
		msg |= SIG_BUF_RD_RDY;
	}

	if (0 != (tmpReg & BIT_4))
	{
		msg |= SIG_BUF_WD_RDY;
	}

	if (0 != (tmpReg & BIT_3))
	{
		msg |= SIG_DMA_INT;
	}

	if (0 != (tmpReg & BIT_2))
	{
		msg |= SIG_BLK_CAP;
	}

	if (0 != (tmpReg & BIT_1))
	{
		msg |= SIG_TRANS_CMP;
	}

	if (0 != (tmpReg & BIT_0))
	{
		msg |= SIG_CMD_CMP;
	}

	return msg;
} /* end of SDHOST_GetNMLIntStatus*/

/*********************************************************************
**	Description :
**		This function used to get error interrupt status.
**	Param :
**		pHd : emmc control handle.
**	Return :
**		msg : interrupt message.
**	Date					Author				Operation
**	2013/05/09			ypxie				optimization
*********************************************************************/
static uint32 SDHOST_GetErrCode (SDIO_Hd_Ptr pHd)
{
	volatile uint32 tmpReg;
	uint32 err_msg;

	tmpReg = pHd->host_cfg->INT_STA;
	err_msg = 0;

	if (0 != (tmpReg & BIT_28))
	{
		err_msg |= ERR_RSP;
	}

	if (0 != (tmpReg & BIT_24))
	{
		err_msg |= ERR_CMD12;
	}

	if (0 != (tmpReg & BIT_23))
	{
		err_msg |= ERR_CUR_LIMIT;
	}

	if (0 != (tmpReg & BIT_22))
	{
		err_msg |= ERR_DATA_END;
	}

	if (0 != (tmpReg & BIT_21))
	{
		err_msg |= ERR_DATA_CRC;
	}

	if (0 != (tmpReg & BIT_20))
	{
		err_msg |= ERR_DATA_TIMEOUT;
	}

	if (0 != (tmpReg & BIT_19))
	{
		err_msg |= ERR_CMD_INDEX;
	}

	if (0 != (tmpReg & BIT_18))
	{
		err_msg |= ERR_CMD_END;
	}

	if (0 != (tmpReg & BIT_17))
	{
		err_msg |= ERR_CMD_CRC;
	}

	if (0 != (tmpReg & BIT_16))
	{
		err_msg |= ERR_CMD_TIMEOUT;
	}

	return err_msg;
} /* end of SDHOST_GetErrCode */

/*********************************************************************
**	Description :
**		This function used to disable signal interrupt, status int and clear int status.
**	Param :
**		pHd : emmc control handle.
**		msg : irq information.
**	Return :
**		msg : interrupt message.
**	Date					Author				Operation
**	2013/05/10			ypxie				optimization
*********************************************************************/
static void SDHOST_NML_INT_SigSt_Dis (SDIO_Hd_Ptr pHd, uint32 msg)
{
	volatile uint32 tmpReg = 0;

	if (0 != (msg & SIG_ERR))
	{
		tmpReg |= (BIT_28 | BIT_24 | BIT_23 | BIT_22 | BIT_21 | BIT_20
					| BIT_19 | BIT_18 | BIT_17 | BIT_16);
	}

	if (0 != (msg & SIG_CARD_IN))
	{
		tmpReg |= BIT_8;
	}

	if (0 != (msg & SIG_CARD_INSERT))
	{
		tmpReg |= BIT_6;
	}

	if (0 != (msg & SIG_CARD_REMOVE))
	{
		tmpReg |= BIT_7;
	}

	if (0 != (msg & SIG_BUF_RD_RDY))
	{
		tmpReg |= BIT_5;
	}

	if (0 != (msg & SIG_BUF_WD_RDY))
	{
		tmpReg |= BIT_4;
	}

	if (0 != (msg & SIG_DMA_INT))
	{
		tmpReg |= BIT_3;
	}

	if (0 != (msg & SIG_BLK_CAP))
	{
		tmpReg |= BIT_2;
	}

	if (0 != (msg & SIG_TRANS_CMP))
	{
		tmpReg |= BIT_1;
	}

	if (0 != (msg & SIG_CMD_CMP))
	{
		tmpReg |= BIT_0;
	}

	pHd->host_cfg->INT_SIG_EN &= ~tmpReg;
	pHd->host_cfg->INT_STA_EN &= ~tmpReg;
	pHd->host_cfg->INT_STA = tmpReg;
} /* end of SDHOST_NML_INT_SigSt_Dis */

/*********************************************************************
**	Description :
**		This function used to enable interrupt status & signal.
**	Param :
**		pHd : emmc control handle.
**		msg : irq information.
**	Return :
**		msg : interrupt message.
**	Date					Author				Operation
**	2013/05/10			ypxie				optimization
*********************************************************************/
static void SDHOST_NML_INT_SigSt_En (SDIO_Hd_Ptr pHd,uint32 msg)
{
	volatile uint32 tmpReg = 0;
	uint32 err_msg;

	if (0 != (msg&SIG_ERR))
	{
		//_ERR_IntStatus_En (sdhost_handler,sdhost_handler->err_filter);
		err_msg = pHd->err_filter;
#ifndef CONFIG_SOC_SHARKLJ1
		if (0 != (err_msg & ERR_RSP))
		{
			tmpReg |= BIT_28;
		}
#endif
		if (0 != (err_msg & ERR_CMD12))
		{
			tmpReg |= BIT_24;
		}

		if (0 != (err_msg & ERR_CUR_LIMIT))
		{
			tmpReg |= BIT_23;
		}

		if (0 != (err_msg & ERR_DATA_END))
		{
			tmpReg |= BIT_22;
		}

		if (0 != (err_msg & ERR_DATA_CRC))
		{
			tmpReg |= BIT_21;
		}

		if (0 != (err_msg & ERR_DATA_TIMEOUT))
		{
			tmpReg |= BIT_20;
		}

		if (0 != (err_msg & ERR_CMD_INDEX))
		{
			tmpReg |= BIT_19;
		}

		if (0 != (err_msg & ERR_CMD_END))
		{
			tmpReg |= BIT_18;
		}

		if (0 != (err_msg & ERR_CMD_CRC))
		{
			tmpReg |= BIT_17;
		}

		if (0 != (err_msg & ERR_CMD_TIMEOUT))
		{
			tmpReg |= BIT_16;
		}

	}

	if (0 != (msg & SIG_CARD_IN))
	{
		tmpReg |= BIT_8;
	}

	if (0 != (msg & SIG_CARD_INSERT))
	{
		tmpReg |= BIT_6;
	}

	if (0 != (msg & SIG_CARD_REMOVE))
	{
		tmpReg |= BIT_7;
	}

	if (0 != (msg & SIG_BUF_RD_RDY))
	{
		tmpReg |= BIT_5;
	}

	if (0 != (msg & SIG_BUF_WD_RDY))
	{
		tmpReg |= BIT_4;
	}

	if (0 != (msg & SIG_DMA_INT))
	{
		tmpReg |= BIT_3;
	}

	if (0 != (msg & SIG_BLK_CAP))
	{
		tmpReg |= BIT_2;
	}

	if (0 != (msg & SIG_TRANS_CMP))
	{
		tmpReg |= BIT_1;
	}

	if (0 != (msg & SIG_CMD_CMP))
	{
		tmpReg |= BIT_0;
	}
	pHd->host_cfg->INT_STA_EN |= tmpReg;
	pHd->host_cfg->INT_SIG_EN |= tmpReg;
} /* end of SDHOST_NML_INT_SigSt_En */

/*********************************************************************
**	Description :
**		This function is irq process.
**	Param :
**		isrNum :
**	Return :
**		CALL_HISR
**	Date					Author				Operation
**	2013/05/09			ypxie				optimization
*********************************************************************/
static int _SDHOST_IrqHandle (uint32 isrNum)
{
	uint32 msg;
	uint32 errCode;
	SDIO_Hd_Ptr pHd;

	pHd = &s_EmmcCtl;

	msg = SDHOST_GetNMLIntStatus (pHd);
	errCode = SDHOST_GetErrCode (pHd);

	SDHOST_NML_INT_SigSt_Dis(pHd, msg);
	pHd->sig_callBack(msg,  errCode);
	return 0;
} /* end of _SDHOST_IrqHandle*/

/*********************************************************************
**	Description :
**		This function used to process irq.
**	Param :
**		msg		: interrupt message
**		errCode	: error information
**		slotNum	: slot number
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/09			ypxie				optimization
*********************************************************************/
static void  _irqCardProc (uint32 msg, uint32 errCode)
{
	SDIO_Hd_Ptr pHd;
	pHd = &s_EmmcCtl;

	/* card interrupt happened , may be some operation error happened */
	if (0 != (SIG_CARD_IN & msg))
	{
		SetCardEvent (pHd, SIG_CARD_IN);
	}

	if (0 != (SIG_CARD_INSERT & msg)) 			/* card is inserted in slot */
	{
		SetCardEvent (pHd, SIG_CARD_INSERT);
	}
	else if (0 != (SIG_CARD_REMOVE & msg))		/* card is plug out from slot */
	{
		SetCardEvent (pHd, SIG_CARD_REMOVE);
	}
	else if (0 != (SIG_ERR&msg))		/* some error happened during the transmission */
	{
		pHd->card_errCode |= errCode;
		SetCardEvent (pHd, SIG_ALL);
		return;
	}

	if (0 != (SIG_TRANS_CMP & msg))			/* transmission complete */
	{
		SetCardEvent (pHd, SIG_TRANS_CMP);
	}
	else if (0 != (SIG_DMA_INT & msg))
	{
		volatile uint32 nextAddr_low;
		volatile uint32 nextAddr_high;

		nextAddr_low = SDHOST_GetDmaAddr_low (pHd);
		nextAddr_high = SDHOST_GetDmaAddr_high(pHd);

		SDHOST_SetDmaAddr_low (pHd, nextAddr_low);
		SDHOST_SetDmaAddr_high (pHd, nextAddr_high);

		SDHOST_NML_INT_SigSt_En(pHd, SIG_DMA_INT);
	}

	if (0 != (SIG_CMD_CMP&msg))
	{
		SetCardEvent (pHd, SIG_CMD_CMP);
	}
} /* end of _irqCardProc*/

static void SDHOST_SdClk_Enable (SDIO_Hd_Ptr pHd, SDIO_OnOff_e enFlg)
{
	if (enFlg == SDIO_ON)
	{
		pHd->host_cfg->EMMC_CLK_CTRL |= BIT_2;
	}
	else /* if (enFlg == SDIO_OFF) */
	{
		if ((pHd->host_cfg->EMMC_CLK_CTRL & BIT_2) != 0) {
			pHd->host_cfg->EMMC_CLK_CTRL &= ~BIT_2;
			SDIO_Mdelay(1);
		}
	}
}

static void SDHOST_InternalClk_Enable (SDIO_Hd_Ptr pHd, SDIO_OnOff_e enFlg)
{
	if (enFlg == SDIO_ON)
	{
		/* Enable internal clock */
		pHd->host_cfg->EMMC_CLK_CTRL |= BIT_0;
		/* Wait internal clock stable */
		while (0 == (pHd->host_cfg->EMMC_CLK_CTRL & BIT_1)) ;
	}
	else /* if (enFlg == SDIO_OFF) */
	{
		pHd->host_cfg->EMMC_CLK_CTRL &= (~BIT_0);
	}

}

/*********************************************************************
**	Description :
**		This function used to set control reset.
**	Param :
**		pHd		: emmc control handle.
**		rstType	: reset type.
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/09			ypxie				optimization
*********************************************************************/
static void SDHOST_RST (SDIO_Hd_Ptr pHd, SDIO_Rst_e rstType)
{
	switch (rstType)
	{
		case RST_DAT_LINE:
			pHd->host_cfg->EMMC_CLK_CTRL |= BIT_25;
			while (0 != (pHd->host_cfg->EMMC_CLK_CTRL & BIT_25)) ;
			break;

		case RST_CMD_LINE:
			pHd->host_cfg->EMMC_CLK_CTRL |= BIT_26;
			while (0!= (pHd->host_cfg->EMMC_CLK_CTRL & BIT_26)) ;
			break;

		case RST_CMD_DAT_LINE:
			pHd->host_cfg->EMMC_CLK_CTRL |= (BIT_25 | BIT_26);
			while (0 != (pHd->host_cfg->EMMC_CLK_CTRL & (BIT_25 | BIT_26)));
			break;

		case RST_ALL:
			SDHOST_SdClk_Enable(pHd, SDIO_OFF);
			pHd->host_cfg->EMMC_CLK_CTRL |= BIT_24;
			while (0 != (pHd->host_cfg->EMMC_CLK_CTRL & BIT_24));
			break;

		default:
			break;
	}
} /* end of SDHOST_RST */


static int div_2(unsigned int dividend, unsigned int divisor, int *prem)
{
	if (divisor == 0)
		return 0;

	if (dividend < divisor)
		return 0;
	else if (dividend == divisor)
		return 1;

	unsigned int k, c, res = 0, rem = 0;

	while (dividend > divisor) {
		for (k = 0, c = divisor; dividend >= c; c <<= 1, k++) {
			if (dividend - c < divisor) {
				res += 1 << k;
				rem = dividend - c;
				break;
			}
		}
		if (dividend - c < divisor)
			break;

		res += 1 << (k - 1);
		dividend -= c >> 1;
	}

	if (prem)
		*prem = rem;

	return res;
}
/*********************************************************************
**	Description :
**		This function used to enable voltage for emmc.
**	Param :
**		emmcCore	:  default used 3.0V.
**		emmcIo		: default used 1.8V.
**	Return :
**		none
**	Date					Author				Operation
**	2013/08/13			ypxie				creat
**	2013/08/15			ypxie				added tiger power on or off
*********************************************************************/
static void SDHOST_Volt_Enable (SDIO_OnOff_e voltFlg)
{
	if (SDIO_ON == voltFlg)
	{
	#if defined(CONFIG_ADIE_SC2723)
		ANA_REG_BIC(ANA_REG_GLB_LDO_DCDC_PD, BIT_7);
		SDIO_Mdelay(10);
	#elif defined(CONFIG_ADIE_SC2731)
		ANA_REG_BIC(ANA_REG_GLB_LDO_EMMCCORE_REG0, BIT_0);
		SDIO_Mdelay(10);
	#endif
	}
	else if (SDIO_OFF == voltFlg)
	{

	#if defined(CONFIG_ADIE_SC2723)
		ANA_REG_OR(ANA_REG_GLB_LDO_DCDC_PD, BIT_7);
		SDIO_Mdelay(10);
	#elif defined(CONFIG_ADIE_SC2731)
		ANA_REG_OR(ANA_REG_GLB_LDO_EMMCCORE_REG0, BIT_0);
		SDIO_Mdelay(10);
	#endif
	}
} /* end of SDHOST_Volt_Enable */

/*********************************************************************
**	Description :
**		This function used to register emmc control.
**	Param :
**		fun	: irq call back fun.
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/17			ypxie				optimization
**	2013/08/12			ypxie				add disable sdclk fot clear glitch
*********************************************************************/
static SDIO_Hd_Ptr SDHOST_Register (SDIO_CALLBACK fun)
{
	/* Set emmc controller base address first */
	s_EmmcCtl.host_cfg = (SDIO_REG_CFG *) ( (volatile uint32 *) EMMC_BASE_ADDR);
	/* enable emmc ahb_clock, and reset it. */
#if defined(CONFIG_SOC_WHALEK) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_ROC1) || defined(CONFIG_SOC_SHARKL5PRO)
	REG32 (REG_AP_APB_APB_EB) |= BIT_AP_APB_EMMC_EB;
#else
	REG32 (REG_AP_AHB_AHB_EB) |= BIT_AP_AHB_EMMC_EB;
#endif

	SDHOST_SdClk_Enable(&s_EmmcCtl, SDIO_OFF);

#if defined(CONFIG_SOC_WHALEK) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_ROC1) || defined(CONFIG_SOC_SHARKL5PRO)
	REG32 (REG_AP_APB_APB_RST) |= BIT_AP_APB_EMMC_SOFT_RST;
#else
	REG32 (REG_AP_AHB_AHB_RST) |= BIT_AP_AHB_EMMC_SOFT_RST;
#endif
	SDIO_Mdelay(1);

#if defined(CONFIG_SOC_WHALEK) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_ROC1) || defined(CONFIG_SOC_SHARKL5PRO)
	REG32 (REG_AP_APB_APB_RST) &= ~BIT_AP_APB_EMMC_SOFT_RST;
#else
	REG32 (REG_AP_AHB_AHB_RST) &= ~BIT_AP_AHB_EMMC_SOFT_RST;
#endif

	s_EmmcCtl.open_flag = TRUE;
	s_EmmcCtl.base_clock = 384000000;
	s_EmmcCtl.sig_callBack = fun;
	s_EmmcCtl.err_filter = 0;
	return &s_EmmcCtl;
} /* end of SDHOST_Register */

static void SDHOST_SetErrCodeFilter (SDIO_Hd_Ptr pHd, uint32 err_msg)
{
	pHd->err_filter = err_msg;
}

/*********************************************************************
**	Description :
**		This function used to set hareware timeout tick clock. (2 ^ (clkcnt+13))*T_BSCLK
**	Param :
**		pHd		: emmc handle
**		clk_cnt	: clock count.
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/17			ypxie				optimization
*********************************************************************/
static void SDHOST_SetDataTimeOutValue (SDIO_Hd_Ptr pHd, uint8 clk_cnt)
{
	volatile uint32 tmpReg,tmpIntReg;

	tmpIntReg = pHd->host_cfg->INT_STA_EN;

	pHd->host_cfg->INT_STA_EN &= ~BIT_20;

	tmpReg = pHd->host_cfg->EMMC_CLK_CTRL;
	tmpReg &= ~ (0xF << 16);
	tmpReg |= (clk_cnt << 16);
	pHd->host_cfg->EMMC_CLK_CTRL = tmpReg;

	pHd->host_cfg->INT_STA_EN = tmpIntReg;
}

/*********************************************************************
**	Description :
**		This function used to send command of sub.
**	Param :
**		pHd		: emmc handle
**		clk_cnt	: clock count.
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/17			ypxie				optimization
*********************************************************************/
static void SDHOST_SetCmd (SDIO_Hd_Ptr pHd,
							uint32 cmdIndex,
							uint32 transmode,
							SDIO_CmdType_e cmd_type,
							CARD_CmdRsp_e Response)
{
	volatile uint32 tmpReg;

	tmpReg = pHd->host_cfg->CMD_TRANSMODE;
	tmpReg &= (~ (0x7F | 0x30000 | 0x3FF80000));

	if (0 != (TRANS_MODE_CMPLETE_SIG_EN & transmode))
	{
		tmpReg |= SDIO_TRANS_COMP_ATA;
	}

	if (0 != (TRANS_MODE_MULTI_BLOCK & transmode))
	{
		tmpReg |= SDIO_TRANS_MULTIBLK;
	}

	if (0 != (TRANS_MODE_READ & transmode))
	{
		tmpReg |= SDIO_TRANS_DIR_READ;
	}

	if (0 != (TRANS_MODE_CMD12_EN & transmode))
	{
		tmpReg |= SDIO_TRANS_AUTO_CMD12_EN;
	}

	if (0 != (TRANS_MODE_BLOCK_COUNT_EN & transmode))
	{
		tmpReg |= SDIO_TRANS_BLK_CNT_EN;
	}

	if (0 != (TRANS_MODE_DMA_EN & transmode))
	{
		tmpReg |= SDIO_TRANS_DMA_EN;
	}

	if (0 != (CMD_HAVE_DATA & transmode))
	{
		tmpReg |= SDIO_CMD_DATA_PRESENT;
	}

	switch (cmd_type)
	{
		case CMD_TYPE_NORMAL:
			tmpReg |= SDIO_CMD_TYPE_NML;
			break;

		case CMD_TYPE_SUSPEND:
			tmpReg |= SDIO_CMD_TYPE_SUSPEND;
			break;

		case CMD_TYPE_RESUME:
			tmpReg |= SDIO_CMD_TYPE_RESUME;
			break;

		case CMD_TYPE_ABORT:
			tmpReg |= SDIO_CMD_TYPE_ABORT;
			break;

		default:
			break;
	}

	switch (Response)
	{
		case CMD_NO_RSP:
			tmpReg |= SDIO_NO_RSP;
			break;

		case CMD_RSP_R1:
			tmpReg |= SDIO_R1;
			break;

		case CMD_RSP_R2:
			tmpReg |= SDIO_R2;
			break;

		case CMD_RSP_R3:
			tmpReg |= SDIO_R3;
			break;

		case CMD_RSP_R4:
			tmpReg |= SDIO_R4;
			break;

		case CMD_RSP_R5:
			tmpReg |= SDIO_R5;
			break;

		case CMD_RSP_R6:
			tmpReg |= SDIO_R6;
			break;

		case CMD_RSP_R7:
			tmpReg |= SDIO_R7;
			break;

		case CMD_RSP_R1B:
			tmpReg |= SDIO_R1B;
			break;

		case CMD_RSP_R5B:
			tmpReg |= SDIO_R5B;
			break;

		default:
			break;

	}

	tmpReg |= (cmdIndex<<24);

	pHd->host_cfg->CMD_TRANSMODE = tmpReg;

} /* end of SDHOST_SetCmd */

static void SDHOST_SetDataParam (SDIO_Hd_Ptr pHd, uint32 block_size, uint32 block_cnt)
{
	pHd->host_cfg->DMA_BLK_SIZE = block_size;
	pHd->host_cfg->DMA_BLK_COUNT = block_cnt;
#if 0
	volatile uint32 tmpReg;

	tmpReg = pHd->host_cfg->BLK_SIZE_COUNT;

	/* Set Block Size */
	tmpReg &= (~BIT_15);
	tmpReg &= (~ (0xFFF));
	if (0x1000 == block_size)
	{
		tmpReg |= BIT_15;
	}
	else
	{
		tmpReg |= block_size;
	}

	/* Set Block Cnt */
	tmpReg &= (~0xFFFF0000);
	tmpReg |= (block_cnt << 16);

	/* Set DMA Buf Size */
	tmpReg &= (~ (0x07<<12));

	pHd->host_cfg->BLK_SIZE_COUNT = tmpReg;
#endif
}

/*********************************************************************
**	Description :
**		This function used to get rsp from buffer.
**	Param :
**		pHd			: emmc handle
**		Response		: .
**		rspBuf		: .
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/17			ypxie				optimization
*********************************************************************/
static void SDHOST_GetRspFromBuf (SDIO_Hd_Ptr pHd,
								CARD_CmdRsp_e Response,
								uint8 *rspBuf)
{
	uint32 tmpRspBuf[4];
	uint32 i;

	tmpRspBuf[0] = pHd->host_cfg->RSP0;
	tmpRspBuf[1] = pHd->host_cfg->RSP1;
	tmpRspBuf[2] = pHd->host_cfg->RSP2;
	tmpRspBuf[3] = pHd->host_cfg->RSP3;

	for (i = 0; i < 4; i++)
	{
		rspBuf[0 + (i << 2) ] = (uint8) ( (tmpRspBuf[i] >> 24) & 0xFF);
		rspBuf[1 + (i << 2) ] = (uint8) ( (tmpRspBuf[i] >> 16) & 0xFF);
		rspBuf[2 + (i << 2) ] = (uint8) ( (tmpRspBuf[i] >> 8) & 0xFF);
		rspBuf[3 + (i << 2) ] = (uint8) (tmpRspBuf[i] & 0xFF);
	}

	switch (Response)
	{
		case CMD_NO_RSP:
			break;

		case CMD_RSP_R1:
		case CMD_RSP_R1B:
		case CMD_RSP_R3:
		case CMD_RSP_R4:
		case CMD_RSP_R5:
		case CMD_RSP_R6:
		case CMD_RSP_R7:
		case CMD_RSP_R5B:
			rspBuf[0] = (uint8) ( (tmpRspBuf[0]>>24) &0xFF);
			rspBuf[1] = (uint8) ( (tmpRspBuf[0]>>16) &0xFF);
			rspBuf[2] = (uint8) ( (tmpRspBuf[0]>>8) &0xFF);
			rspBuf[3] = (uint8) (tmpRspBuf[0]&0xFF);
			break;

		case CMD_RSP_R2:
			rspBuf[0] = (uint8) ( (tmpRspBuf[3]>>16) &0xFF);
			rspBuf[1] = (uint8) ( (tmpRspBuf[3]>>8) &0xFF);
			rspBuf[2] = (uint8) (tmpRspBuf[3]&0xFF);

			rspBuf[3] = (uint8) ( (tmpRspBuf[2]>>24) &0xFF);
			rspBuf[4] = (uint8) ( (tmpRspBuf[2]>>16) &0xFF);
			rspBuf[5] = (uint8) ( (tmpRspBuf[2]>>8) &0xFF);
			rspBuf[6] = (uint8) (tmpRspBuf[2]&0xFF);

			rspBuf[7] = (uint8) ( (tmpRspBuf[1]>>24) &0xFF);
			rspBuf[8] = (uint8) ( (tmpRspBuf[1]>>16) &0xFF);
			rspBuf[9] = (uint8) ( (tmpRspBuf[1]>>8) &0xFF);
			rspBuf[10] = (uint8) (tmpRspBuf[1]&0xFF);

			rspBuf[11] = (uint8) ( (tmpRspBuf[0]>>24) &0xFF);
			rspBuf[12] = (uint8) ( (tmpRspBuf[0]>>16) &0xFF);
			rspBuf[13] = (uint8) ( (tmpRspBuf[0]>>8) &0xFF);
			rspBuf[14] = (uint8) (tmpRspBuf[0]&0xFF);
			break;

		default:
			break;
	}
	return;
} /* end of SDHOST_GetRspFromBuf */

/*********************************************************************
**	Description :
**		This function used to send cmd.
**	Param :
**		pHd		: emmc handle
**		cmd		: command.
**		argument	: 
**		dataParam	: blk buf,size, num.
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/17			ypxie				optimization
*********************************************************************/
static SDIO_Error_e SDIO_SendCmd ( SDIO_Hd_Ptr pHd,
								CARD_Cmd_e cmd,
								uint32 argument,
								DATA_Param_t *dataParam,
								uint8 *rspBuf)
{
	uint32 tmpIntFilter;

	SDHOST_SdClk_Enable(pHd, SDIO_ON);
	SDHOST_NML_INT_SigSt_Dis(pHd, SIG_ALL);

	SDHOST_SetDataTimeOutValue (pHd, 0xF);
	SDHOST_SetErrCodeFilter (pHd, s_cmdDetail[cmd].err_filter);
	tmpIntFilter = s_cmdDetail[cmd].int_filter;

	if (NULL != s_cmdDetail[cmd].err_filter)
	{
		tmpIntFilter |= SIG_ERR;
	}

	if (NULL != dataParam)
	{
		tmpIntFilter |= SIG_DMA_INT;
	}

	SDHOST_NML_INT_SigSt_En(pHd, tmpIntFilter);

	pHd->card_errCode = 0;
	pHd->card_event = 0;

	if (NULL != dataParam)
	{
		uint32 bufferSize = 0;
		uint32 ulBufferAddr_low = 0;
		uint32 ulBufferAddr_high = 0;

		bufferSize = dataParam->blk_len  *  (dataParam->blk_num);

		ulBufferAddr_low = (uint32)((uint64)(dataParam->data_buf)) & 0xffffffff;
		ulBufferAddr_high = (uint32)(((uint64)(dataParam->data_buf)) >> 32) & 0xffffffff;

		SDHOST_SetDmaAddr_low (pHd, ulBufferAddr_low);
		SDHOST_SetDmaAddr_high (pHd, ulBufferAddr_high);

		SDHOST_SetDataParam (pHd, dataParam->blk_len, dataParam->blk_num);
	}

	pHd->host_cfg->CMD_ARGUMENT = argument;
	SDHOST_SetCmd (pHd, 
					s_cmdDetail[cmd].cmd_index,
					s_cmdDetail[cmd].transmode,
					CMD_TYPE_NORMAL, 
					s_cmdDetail[cmd].response);

	while (0 != _WaitCardEvent(pHd, s_cmdDetail[cmd].int_filter))
	{
		_SDHOST_IrqHandle((uint32)pHd);
	}

	SDHOST_RST (pHd, RST_CMD_DAT_LINE);

	if( 0 !=  (pHd->card_event & SIG_ERR ))
	{
		//send  cmd   error  happend return 0xff
		return  0xff;
	}

	SDHOST_GetRspFromBuf (pHd, s_cmdDetail[cmd].response, rspBuf);

	return SDIO_ERR_NONE;
}/* end of SDIO_SendCmd */

/*********************************************************************
**	Description :
**		This function used to set sd clock.
**	Param :
**		pHd		: emmc handle
**		sdio_clk	: want to set clock.
**	Return :
**		none
**	Date				Author				Operation
**	2013/05/17			ypxie				optimization
**	2013/08/12			ypxie				delete old code.
*********************************************************************/
static uint32 SDHOST_ClkFreq_Set (SDIO_Hd_Ptr pHd, uint32 sdioClk)
{
	volatile uint32 tmpReg;
	uint32 clkDiv;

	/* SDCLK Frequency Select ,Configure SDCLK select */

        /* Select 2x clock source */
	if(pHd->base_clock < (sdioClk * 2)){
		clkDiv = 0;
	}else{
		clkDiv = pHd->base_clock / (sdioClk * 2);

		if((pHd->base_clock / clkDiv) > (sdioClk * 2)) {
			clkDiv++;
		}
	}

	if(clkDiv % 2)
		clkDiv = (clkDiv + 1) / 2;
	else
		clkDiv = clkDiv / 2;

	tmpReg = pHd->host_cfg->EMMC_CLK_CTRL;

	tmpReg &= (~(0x3ff << 6));
	tmpReg |= ((clkDiv >> 8) & 0x3) << 6;
	tmpReg |= (clkDiv & 0xff) << 8;

	if(clkDiv){
		pHd->sd_clock = pHd->base_clock / (2 * clkDiv);
	}else{
		pHd->sd_clock = pHd->base_clock / 2;
	}

	pHd->host_cfg->EMMC_CLK_CTRL = tmpReg;

	return pHd->sd_clock;

} /* end of SDHOST_ClkFreq_Set */


static BOOLEAN SDIO_SetClk (SDIO_Hd_Ptr pHd, uint32 sdioClk)
{
	SDHOST_SdClk_Enable (pHd, SDIO_OFF);
	/* r7p0 need switch clock source; r8p0 need not */
#ifndef CONFIG_WHALE2
	SDHOST_ClkFreq_Set(pHd, sdioClk);
#else
	REG32 (SPRD_AONCKG_BASE+AON_EMMC_CLK_2X_CFG) = AON_CLK_FREQ_26M;
#endif
	SDHOST_SdClk_Enable (pHd, SDIO_ON);

	return TRUE;
}
/*********************************************************************
**	Description :
**		This function used to set DMA as SDMA mode.
**	Param :
**		pHd			: emmc handle
**		widthType	: want to set clock.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
*********************************************************************/
static BOOLEAN SDIO_SetDmaMode (SDIO_Hd_Ptr pHd, uint32 dmamode)
{
        //set DMA mode as SDMA 
	uint32 regVal;

	regVal = pHd->host_cfg->HOST_CTL1;

	regVal &= ~(dmamode);

	pHd->host_cfg->HOST_CTL1= regVal;

	return TRUE;
}
/*********************************************************************
**	Description :
**		This function used to enable 64 bit.
**	Param :
**		pHd			: emmc handle
**		widthType	: want to set clock.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
*********************************************************************/
static BOOLEAN SDIO_Enable64Bit (SDIO_Hd_Ptr pHd, uint32 datawidth)
{
	//enable 64bit address
	uint32 regVal;

	regVal = pHd->host_cfg->HOST_CTL2;

	regVal =  regVal | datawidth;

	pHd->host_cfg->HOST_CTL2 = regVal;

	return TRUE;
}
/*********************************************************************
**	Description :
**		This function used to set card to high speed mode.
**	Param :
**		pHd			: emmc handle
**		widthType	: want to set clock.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
*********************************************************************/
static BOOLEAN SDIO_SetBusWidth (SDIO_Hd_Ptr pHd, SDIO_BusWidth_e busWidth)
{
	uint32 regVal;

	regVal = pHd->host_cfg->HOST_CTL1;

	/* clear bus width set bits */
	regVal &= ~((1 << 5) | (1 << 1));
	switch (busWidth)
	{
		case SDIO_BUS_1_BIT:
			break;

		case SDIO_BUS_4_BIT:
			regVal |= 1 << 1;
			break;

		case SDIO_BUS_8_BIT:
			regVal |= 1 << 5;
			break;

		default:
			break;
	}

	pHd->host_cfg->HOST_CTL1 = regVal;

	return TRUE;
}


static BOOLEAN CARD_SDIO_SetBlockLength(SDIO_Hd_Ptr pHd,uint32 length)
{
	uint8 rspBuf[16];

	if(0 != SDIO_SendCmd(pHd, CARD_CMD16_SET_BLOCKLEN,
						length, (DATA_Param_t *)NULL, rspBuf))
	{
		return FALSE;
	}
	pHd->block_len = length;
	return TRUE;
}

static BOOLEAN get_card_status(SDIO_Hd_Ptr pHd,uint8 *rspBuf)
{
	return SDIO_SendCmd(pHd, CARD_CMD13_SEND_STATUS, 1 << 16, NULL, rspBuf);
}
/*********************************************************************
**	Description :
**		This function used to check card is busy or ready.
**	Param :
**		pHd			: emmc handle
**		width		: bus width.
**	Return :
**		none
**	Date					Author				Operation
**	2013/08/09			ypxie				optimization
**	2013/08/12			ypxie				clear redundant variable
*********************************************************************/
static BOOLEAN IsCardReady(SDIO_Hd_Ptr pHd)
{
	uint32 pre_tick = 0, cur_tick = 0;
	uint8 rspBuf[16] ;

	pre_tick = SCI_GetTickCount();
	do
	{
		if (SDIO_ERR_NONE == get_card_status(pHd, rspBuf))
		{
			if   (rspBuf[2] & BIT_0)
				return TRUE;
		}
		cur_tick = SCI_GetTickCount();
		if(3000 <  (cur_tick - pre_tick))
		{
			return FALSE;
		}
	}
	while(1);
}
/*********************************************************************
**	Description :
**		This function used to set card to high speed mode.
**	Param :
**		pHd			: emmc handle
**		cardPartition	: want to set clock.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
*********************************************************************/
static BOOLEAN MMC_SWITCH(SDIO_Hd_Ptr pHd, uint8 index, uint8 value)
{
	uint8 rspBuf[16];
	uint32 argument = 0;

	argument = CMD6_ACCESS_MODE_WRITE_BYTE | CMD6_CMD_SET;
	argument |= index << CMD6_BIT_MODE_OFFSET_INDEX;
	argument |= value << CMD6_BIT_MODE_OFFSET_VALUE;


	if(0 != SDIO_SendCmd(pHd, CARD_ACMD6_SET_EXT_CSD, argument, NULL, rspBuf))
	{
		return FALSE;
	}

	if(FALSE == IsCardReady(pHd))
	{
		return FALSE;
	}

	return TRUE;
}
/*********************************************************************
**	Description :
**		This function used to select current partition.boot1, boot2, user.
**	Param :
**		pHd			: emmc handle
**		cardPartition	: want to set clock.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/18			ypxie				optimization
*********************************************************************/
static CARD_SDIO_SelCurPartition( SDIO_Hd_Ptr pHd, CARD_Partition_e cardPartiton)
{
	uint8 rspBuf[16];
	uint32 argument = 0;
	uint8 value = 0;

	if (pHd->cur_partition < PARTITION_MAX)
	{
		if (pHd->cur_partition == cardPartiton)
		{
			return TRUE;
		}
	}
	switch(cardPartiton)
	{
		case PARTITION_USER:
			value = (PARTITION_CFG_ENABLE_BOOT1 |PARTITION_CFG_ACCESS_USER);
			break;
		case PARTITION_BOOT1:
			value = (PARTITION_CFG_ENABLE_BOOT1 |PARTITION_CFG_ACCESS_BOOT1);
			break;
		case PARTITION_BOOT2:
			value = (PARTITION_CFG_ENABLE_BOOT1 |PARTITION_CFG_ACCESS_BOOT2);
			break;
		case PARTITION_RPMB:
		case PARTITION_GENERAL_P1:
		case PARTITION_GENERAL_P2:
		case PARTITION_GENERAL_P3:
		case PARTITION_GENERAL_P4:
		default:
			return FALSE;
			break;
	}
	if(FALSE ==MMC_SWITCH(pHd,EXT_CSD_PARTITION_CFG_INDEX,value))
	{
		 return FALSE;
	}

	pHd->cur_partition = cardPartiton;

	return TRUE;
}
/*********************************************************************
**	Description :
**		This function used to set card and host bus width.
**	Param :
**		pHd			: emmc handle
**		width		: bus width.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
**	2013/08/12			ypxie				support 1,8 bits buswidth
*********************************************************************/
static BOOLEAN CARD_SDIO_SetBusWidth(SDIO_Hd_Ptr pHd, SDIO_BusWidth_e busWidth)
{
	uint8 rspBuf[16];
	uint32 argu = 0;

	if(FALSE ==MMC_SWITCH(pHd,EXT_CSD_BUS_WIDTH_INDEX,busWidth))
	{
		 return FALSE;
	}

	SDIO_SetBusWidth(pHd, busWidth);

	pHd->bus_width = busWidth;

	return TRUE;
}

static BOOLEAN mmc_read_ext_csd(SDIO_Hd_Ptr pHd, u8 *rspBuf)
{
	u8 ext_csd[512];
	DATA_Param_t data;

	data.data_buf = ext_csd;
	data.blk_len = 512;
	data.blk_num = 1;

	if (0 != SDIO_SendCmd(pHd, CARD_CMD8_IF_COND_MMC, NULL, &data, rspBuf)) {
		return FALSE;
	}

	mmc_sector = (ext_csd[EXT_CSD_SEC_CNT]) |
			(ext_csd[EXT_CSD_SEC_CNT + 1] << 8) |
			(ext_csd[EXT_CSD_SEC_CNT + 2] << 16) |
			(ext_csd[EXT_CSD_SEC_CNT + 3] << 24);

	return TRUE;
}
/*********************************************************************
**	Description :
**		This function used to initialize card.
**	Param :
**		pHd			: emmc handle
**		width		: bus width.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
**	2013/08/12			ypxie				added params for card
*********************************************************************/
static BOOLEAN CARD_SDIO_InitCard(SDIO_Hd_Ptr pHd,
								uint32 sdioClk,
								SDIO_BusWidth_e busWidth)
{
	uint8 rspBuf[16];
	uint32 pre_tick, cur_tick;

	if (0 != SDIO_SendCmd(pHd, CARD_CMD0_GO_IDLE_STATE, 0, NULL, rspBuf))
	{
		return FALSE;
	}

	pre_tick = SCI_GetTickCount(); /*set start tick value*/       
	do
	{
		if (0 != SDIO_SendCmd(pHd, CARD_CMD1_SEND_OP_COND,
							0x00FF8000 | SECTOR_MODE, NULL, rspBuf))
		{
			continue;
		}

		if(0 != (rspBuf[0] & BIT_7))
		{
			break;
		}

		cur_tick = SCI_GetTickCount();

		if( 10000 <  (cur_tick - pre_tick))
		{
			return FALSE;
		} 

	} while(1);

	/* Get CID */
	if (0 != SDIO_SendCmd(pHd, CARD_CMD2_ALL_SEND_CID, 0, NULL, rspBuf))
	{	
		return FALSE;
	}

	if (0 != SDIO_SendCmd(pHd, CARD_CMD3_SET_RELATIVE_ADDR, 1 << 16, NULL, rspBuf))
	{
		return FALSE;
	}

	if(0 != SDIO_SendCmd(pHd, CARD_CMD7_SELECT_DESELECT_CARD, 1<<16, NULL, rspBuf))
	{
		return FALSE;
	}

	if (FALSE == mmc_read_ext_csd(pHd, rspBuf)) {
		return FALSE;
	}

	/* get Boot2 Capacity */
	/*
	if ( FALSE == CARD_SDIO_SelCurPartition(pHd, PARTITION_BOOT2) )
	{
		return FALSE;
	}
	*/

	if (FALSE == MMC_SWITCH(pHd, EXT_CSD_HS_TIMING_INDEX, 1))
	{
		return FALSE;
	}

	SDIO_SetClk(pHd, sdioClk);

	if(FALSE == CARD_SDIO_SetBusWidth(pHd, busWidth))
	{
		return FALSE;
	}

	if(FALSE == CARD_SDIO_SetBlockLength(pHd, CARD_DATA_BLOCK_LEN))
	{
		return FALSE;
	}
	return TRUE;
} /* end of CARD_SDIO_InitCard */

/*********************************************************************
**	Description :
**		This function used to set sdio poower on or off
**	Param :
**		pHd			: emmc handle
**		width		: bus width.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
*********************************************************************/
static BOOLEAN SDIO_PowerCtl (SDIO_Hd_Ptr pHd, SDIO_OnOff_e pwrFlg)
{
	switch (pwrFlg)
	{
		case SDIO_ON:
			/* disable sd clock, and reset controller.*/
			SDHOST_RST(pHd, RST_ALL);
			SDHOST_Volt_Enable (SDIO_ON);
#ifndef CONFIG_FPGA
#ifndef CONFIG_WHALE2
			#ifdef EMMC_HS_MODE
				REG32 ( SPRD_APCLK_PHYS + APB_EMMC_CLK_2X_CFG ) =  APB_CLK_FREQ;
			#endif
#if defined (CONFIG_SOC_ROC1)
                       if(AP_EMMC_CLK_2X_CFG)
                               REG32 (CTL_BASE_AP_CLK_CORE+AP_EMMC_CLK_2X_CFG) = AP_CLK_FREQ_384M;
#else
			if(AON_EMMC_CLK_2X_CFG)
				REG32 (SPRD_AONCKG_BASE+AON_EMMC_CLK_2X_CFG) = AON_CLK_FREQ_384M;
#endif
			/* set init clock freq as 400k Hz in bringup phase */
			SDHOST_ClkFreq_Set(pHd, 400000);
#else
			/* set frequece for sdio. */
			REG32 (SPRD_AONCKG_BASE+AON_EMMC_CLK_2X_CFG) = AON_CLK_FREQ_200K_DIV|AON_CLK_FREQ_1M;
#endif
#if defined(CONFIG_SOC_SHARKL5)  || defined(CONFIG_SOC_SHARKL5PRO)
			if(AP_EMMC_CLK_2X_CFG)
				REG32 (CTL_BASE_AP_CLK_CORE+AP_EMMC_CLK_2X_CFG) = AP_CLK_FREQ_384M;
			SDHOST_ClkFreq_Set(pHd, 400000);
#endif
#endif
			SDHOST_InternalClk_Enable(pHd, SDIO_ON);
			SDHOST_SdClk_Enable(pHd, SDIO_ON);
			break;

		case SDIO_OFF:
			/* disable sd clock. */
			SDHOST_SdClk_Enable(pHd, SDIO_OFF);
			SDHOST_RST (pHd, RST_ALL);
			SDHOST_Volt_Enable (SDIO_OFF);
			break;

		default:
			break;
	}
	return TRUE;
}

PUBLIC BOOLEAN Emmc_Init( void )
{
	uint32 ret = 0;
	p_EmmcHd = SDHOST_Register ( _irqCardProc); 

	//SDIO_PowerCtl(p_EmmcHd, SDIO_OFF);
	SDIO_PowerCtl(p_EmmcHd, SDIO_ON);

	p_EmmcHd->block_len = 0;
	p_EmmcHd->rca = 1;
	p_EmmcHd->bus_width = SDIO_BUS_1_BIT;
	p_EmmcHd->cur_partition = PARTITION_MAX;
#ifndef CONFIG_X86
	SDIO_Enable64Bit(p_EmmcHd, EMMC_ENABLE_64BIT);
#endif
	SDIO_SetDmaMode(p_EmmcHd, EMMC_SDMA_MODE);
#ifndef CONFIG_FPGA
	ret = CARD_SDIO_InitCard(p_EmmcHd, SDIO_CLK_48M, SDIO_BUS_8_BIT);
#else
	ret = CARD_SDIO_InitCard(p_EmmcHd, SDIO_BASE_CLK_26M, SDIO_BUS_1_BIT);
#endif
	sprd_mmc_dev.part_type = PART_TYPE_EFI;
	sprd_mmc_dev.dev = 0;
	/* FIXME fill in the correct size (is set to 32MByte) */
	sprd_mmc_dev.blksz = MMCSD_SECTOR_SIZE;
	sprd_mmc_dev.block_read = Emmc_Read;
	sprd_mmc_dev.lba = mmc_sector;

	return ret;
}

/*********************************************************************
**	Description :
**		This function used to read from emmc card.
**	Param :
**		none
**	Return :
**		none
**	Date					Author				Operation
**	2013/08/09			ypxie				optimization
*********************************************************************/
static BOOLEAN CARD_SDIO_ReadMultiBlock(CARD_Partition_e  cardPartiton,
									SDIO_Hd_Ptr pHd,
									uint32 startBlk,
									uint32 num,
									uint8* buf)
{
	uint8 rspBuf[16];
	uint32 addr = 0xFFFFFFFF;
	DATA_Param_t data;

	//addr = startBlk*pHd->block_len;
	addr = startBlk;

	data.blk_len = pHd->block_len;
	data.blk_num = num;
	data.data_buf = buf;

	if (FALSE == IsCardReady(pHd))
	{
		return FALSE;
	}

	if(FALSE == CARD_SDIO_SetBlockLength(pHd, CARD_DATA_BLOCK_LEN))
	{
		return FALSE;
	}

	if(0 != SDIO_SendCmd(pHd, CARD_CMD18_READ_MULTIPLE_BLOCK, addr, &data, rspBuf))
	{
		SDIO_SendCmd(pHd, CARD_CMD12_STOP_TRANSMISSION, NULL, NULL, rspBuf);
		return FALSE;
	}
	if(0 != SDIO_SendCmd(pHd,CARD_CMD12_STOP_TRANSMISSION,NULL,NULL,rspBuf))
	{
		return FALSE;
	}
	return TRUE;

}

PUBLIC BOOLEAN Emmc_Read(CARD_Partition_e  cardPartiton, uint32 startBlk,uint32 num,uint8* buf)
{
	uint32 ret = 0;
	uint32 count = 0;
	uint8 rspBuf[16];

	if (p_EmmcHd->cur_partition != cardPartiton)
	{
		if(0 != SDIO_SendCmd(p_EmmcHd,CARD_CMD13_SEND_STATUS, 1<<16,NULL,rspBuf))
		{
			return FALSE;
		}

		if ( FALSE == CARD_SDIO_SelCurPartition(p_EmmcHd, cardPartiton))
		{
			return FALSE;
		}
	}

	do{
		ret = CARD_SDIO_ReadMultiBlock(cardPartiton, p_EmmcHd, startBlk, num, buf);
	}while((ret == FALSE) && (++count < 5));

	return ret;
}

PUBLIC void Emmc_DisSdClk(void )
{
	SDHOST_SdClk_Enable(p_EmmcHd, SDIO_OFF);
}

#ifdef CONFIG_SD_BOOT
/*********************************For SD Boot************************************/

static BOOLEAN SD_CARD_SDIO_SetBusWidth(SDIO_Hd_Ptr pHd, SDIO_BusWidth_e busWidth)
{
	uint8 rspBuf[16];

	if (0 != SDIO_SendCmd(pHd, CARD_ACMD55_APP_CMD, (pHd->rca) << 16, NULL, rspBuf)) {
		return FALSE;
	}

	if (0 != SDIO_SendCmd(pHd, CARD_CMD6_APP_SET_BUS_WIDTH, 2, NULL, rspBuf)) {
		return FALSE;
	}

	SDIO_SetBusWidth(pHd, busWidth);
	pHd->bus_width = busWidth;

	return TRUE;
}

/*********************************************************************
**	Description :
**		This function used to register emmc control.
**	Param :
**		fun	: irq call back fun.
**	Return :
**		none
**	Date					Author				Operation
**	2013/05/17			ypxie				optimization
**	2013/08/12			ypxie				add disable sdclk fot clear glitch
*********************************************************************/
static SDIO_Hd_Ptr SD_HOST_Register(SDIO_CALLBACK fun)
{
	/* Set emmc controller base address first */
	s_EmmcCtl.host_cfg = (SDIO_REG_CFG *) ((volatile uint32 *)SDIO0_BASE_ADDR);
	/* enable emmc ahb_clock, and reset it. */

#if defined(CONFIG_SOC_WHALEK) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_SHARKL5PRO)
	REG32 (REG_AP_APB_APB_EB) |= BIT_AP_APB_SDIO0_EB;
#else
	REG32 (REG_AP_AHB_AHB_EB) |= BIT_AP_AHB_SDIO0_EB;
#endif
	SDHOST_SdClk_Enable(&s_EmmcCtl, SDIO_OFF);

#if defined(CONFIG_SOC_WHALEK) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_SHARKL5PRO)
	REG32(REG_AP_APB_APB_RST) |= BIT_AP_APB_SDIO0_SOFT_RST;
#else
	REG32(REG_AP_AHB_AHB_RST) |= BIT_AP_AHB_SDIO0_SOFT_RST;
#endif
	SDIO_Mdelay(1);

#if defined(CONFIG_SOC_WHALEK) || defined(CONFIG_SOC_SHARKL5) || defined(CONFIG_SOC_SHARKL5PRO)
	REG32(REG_AP_APB_APB_RST) &= ~BIT_AP_APB_SDIO0_SOFT_RST;
#else
	REG32(REG_AP_AHB_AHB_RST) &= ~BIT_AP_AHB_SDIO0_SOFT_RST;
#endif

	s_EmmcCtl.open_flag = TRUE;
	s_EmmcCtl.sig_callBack = fun;
	s_EmmcCtl.err_filter = 0;
	return &s_EmmcCtl;
}

static void  SD_SetClk (SDIO_Hd_Ptr pHd, uint32 sdioClk)
{
	SDHOST_SdClk_Enable (pHd, SDIO_OFF);
	SDIO_Mdelay(1);
	/* r7p0 need switch clock source; r8p0 need not */
#ifndef CONFIG_WHALE2
	SDHOST_ClkFreq_Set(pHd, sdioClk);
	SDIO_Mdelay(1);
#else
	REG32 (SPRD_AONCKG_BASE+AON_SDIO0_CLK_2X_CFG) = AON_CLK_FREQ_26M;
#endif
	SDHOST_SdClk_Enable (pHd, SDIO_ON);
}
/*********************************************************************
**	Description :
**		This function used to initialize card.
**	Param :
**		pHd			: emmc handle
**		width		: bus width.
**	Return :
**		none
**	Date					Author				Operation
**	2013/07/19			ypxie				optimization
**	2013/08/12			ypxie				added params for card
*********************************************************************/
static BOOLEAN SD_CARD_SDIO_InitCard(SDIO_Hd_Ptr pHd, uint32 sdioClk, SDIO_BusWidth_e busWidth)
{
	uint8 rspBuf[16];
	uint16 rca;
	uint32 pre_tick, cur_tick;

	//for cmd0
	if (0 != SDIO_SendCmd(pHd, CARD_CMD0_GO_IDLE_STATE, 0, NULL, rspBuf)) {
		return FALSE;
	}
	//for cmd8
	if (0 != SDIO_SendCmd(pHd, CARD_CMD8_IF_COND_SD, 0x000001AA, NULL, rspBuf)) {
		return FALSE;
	} else {
		if (!((0xAA == rspBuf[3]) && (0x01 == rspBuf[2]))) {
			return FALSE;
		}
	}

	//for cmd55 and cmd41
	do {
		if (0 != SDIO_SendCmd(pHd, CARD_ACMD55_APP_CMD, 0, NULL, rspBuf)) {
			return FALSE;
		}

		if (0 != SDIO_SendCmd(pHd, CARD_ACMD41_SEND_OP_COND, 0x40ff8000, NULL, rspBuf)) {
			return FALSE;
		}

		if (0 != (rspBuf[0] & BIT_7)) {
			if (0 != (rspBuf[0] & BIT_6)) {
				sdHighCap = TRUE;
			} else {
				sdHighCap = FALSE;
			}
			break;
		}

	} while (1);

	//for CID
	if (0 != SDIO_SendCmd(pHd, CARD_CMD2_ALL_SEND_CID, 0, NULL, rspBuf)) {
		return FALSE;
	}
	//for RCA
	if (0 != SDIO_SendCmd(pHd, CARD_CMD3_SET_RELATIVE_ADDR, 0, NULL, rspBuf)) {
		return FALSE;
	}
	rca = rspBuf[0];
	rca = rca << 8;
	rca = rca | rspBuf[1];
	pHd->rca = rca;

	//for CMD7
	if (0 != SDIO_SendCmd(pHd, CARD_CMD7_SELECT_DESELECT_CARD, (pHd->rca) << 16, NULL, rspBuf)) {
		return FALSE;
	}
	//set BUSWIDTH
	if (FALSE == SD_CARD_SDIO_SetBusWidth(pHd, busWidth)) {
		return FALSE;
	}
	SD_SetClk(pHd, sdioClk);
	//set BLOCKLEN
	if (FALSE == CARD_SDIO_SetBlockLength(pHd, CARD_DATA_BLOCK_LEN)) {
		return FALSE;
	}
	return TRUE;
}				/* end of CARD_SDIO_InitCard */

static uint32 SD_Set_init_clk(SDIO_Hd_Ptr pHd)
{
	SDHOST_RST(pHd, RST_ALL);
#ifndef CONFIG_WHALE2
#if defined(CONFIG_SOC_ROC1)
         if (AP_SDIO0_CLK_2X_CFG)
         REG32 (SPRD_APCLK_PHYS+AP_SDIO0_CLK_2X_CFG) = AP_CLK_FREO_26M;
#else
        if(AON_SDIO0_CLK_2X_CFG)
	REG32 (SPRD_AONCKG_BASE+AON_SDIO0_CLK_2X_CFG) = AON_CLK_FREQ_26M;
#endif
	/* set init clock freq as 400k Hz in bringup phase */
	SDHOST_ClkFreq_Set(pHd, 400000);
#else
	REG32 (SPRD_AONCKG_BASE+AON_SDIO0_CLK_2X_CFG) = AON_CLK_FREQ_200K_DIV|AON_CLK_FREQ_1M;
#endif
	SDHOST_InternalClk_Enable(pHd, SDIO_ON);
	SDHOST_SdClk_Enable(pHd, SDIO_ON);
}


PUBLIC BOOLEAN SD_Init(void)
{
	uint32 ret = 0;
	p_SdHd = SD_HOST_Register(_irqCardProc);
	SD_Set_init_clk(p_SdHd);
	p_SdHd->block_len = 0;
	p_SdHd->rca = 1;
	p_SdHd->bus_width = SDIO_BUS_1_BIT;
	p_SdHd->cur_partition = PARTITION_MAX;
	ret = SD_CARD_SDIO_InitCard(p_SdHd, SDIO_BASE_CLK_26M, SDIO_BUS_4_BIT);

	return ret;
}

/*********************************************************************
**	Description :
**		This function used to read from emmc card.
**	Param :
**		none
**	Return :
**		none
**	Date					Author				Operation
**	2013/08/09			ypxie				optimization
*********************************************************************/
static BOOLEAN SD_CARD_SDIO_ReadMultiBlock( SDIO_Hd_Ptr pHd, uint32 startBlk, uint32 num, uint8 * buf)
{
	uint8 rspBuf[16];
	uint32 addr = 0xFFFFFFFF;
	DATA_Param_t data;

	if (TRUE == sdHighCap) {
		addr = startBlk;
	} else {
		addr = startBlk * pHd->block_len;
	}

	data.blk_len = pHd->block_len;
	data.blk_num = num;
	data.data_buf = buf;

	if (0 != SDIO_SendCmd(pHd, CARD_CMD18_READ_MULTIPLE_BLOCK, addr, &data, rspBuf)) {
		SDIO_SendCmd(pHd, CARD_CMD12_STOP_TRANSMISSION, NULL, NULL, rspBuf);
		return FALSE;
	}
	if (0 != SDIO_SendCmd(pHd, CARD_CMD12_STOP_TRANSMISSION, NULL, NULL, rspBuf)) {
		return FALSE;
	}
	return TRUE;

}

PUBLIC BOOLEAN SD_CARD_Read(uint32 startBlk, uint32 num, uint8 * buf)
{
	uint32 ret = 0;
	uint8 rspBuf[16];

	ret = SD_CARD_SDIO_ReadMultiBlock( p_SdHd, startBlk, num, buf);
	return ret;
}
#endif
